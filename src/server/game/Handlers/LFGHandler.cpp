/*
 * Copyright (C) 2008-2012 TrinityCore <http://www.trinitycore.org/>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "WorldSession.h"
#include "WorldPacket.h"
#include "DBCStores.h"
#include "Player.h"
#include "Group.h"
#include "LFGMgr.h"
#include "ObjectMgr.h"
#include "GroupMgr.h"
#include "GameEventMgr.h"
#include "InstanceScript.h"

void BuildPlayerLockDungeonBlock(ByteBuffer& data, const LfgLockMap& lock, Player* plr)
{  
    data << uint32(lock.size());
    for (LfgLockMap::const_iterator it = lock.begin(); it != lock.end(); ++it)
    {
        data << uint32(it->first);                         // Dungeon entry (id + type)
        data << uint32(it->second);                        // Lock status

        uint32 itemLevelRequired = 0;

        switch(it->first & 0xFFFFFF)
        {
            // Gardiens des Mogu’shan
            case 527:
                itemLevelRequired = 460;
                break;
            default:
                break;
        }

        data << uint32(itemLevelRequired);
        data << uint32(plr->GetAverageItemLevel());
    }
}

void BuildPartyLockDungeonBlock(WorldPacket& data, const LfgLockPartyMap& lockMap, Player* plr)
{
    ByteBuffer dataBuffer;
    data.WriteBits(lockMap.size(), 24);
    data.WriteBit(0);
    for (LfgLockPartyMap::const_iterator it = lockMap.begin(); it != lockMap.end(); ++it)
    {
        ObjectGuid guid = it->first;                         // Player guid
        data.WriteBit(guid[3]);
        data.WriteBit(guid[4]);
        data.WriteBit(guid[5]);
        data.WriteBit(guid[2]);
        data.WriteBit(guid[0]);
        data.WriteBit(guid[6]);
        data.WriteBit(guid[7]);
        data.WriteBits(it->second.size(), 22); // Size of lock dungeons
        data.WriteBit(guid[1]);
        dataBuffer.WriteByteSeq(guid[2]);
        dataBuffer.WriteByteSeq(guid[3]);
        dataBuffer.WriteByteSeq(guid[7]);
        dataBuffer.WriteByteSeq(guid[5]);
        BuildPlayerLockDungeonBlock(dataBuffer, it->second, plr);
        dataBuffer.WriteByteSeq(guid[6]);
        dataBuffer.WriteByteSeq(guid[4]);
        dataBuffer.WriteByteSeq(guid[0]);
        dataBuffer.WriteByteSeq(guid[1]);
    }
    data.FlushBits();
    data.append(dataBuffer);
}

void WorldSession::HandleLfgJoinOpcode(WorldPacket& recvData)
{
    uint32 numDungeons;
    uint32 dungeon;
    uint32 roles;
    uint8 length = 0;
    uint8 unk8 = 0;
    for (int i = 0; i < 3; i++)
        recvData.read_skip<uint32>();
    recvData >> unk8;
    recvData >> roles;
    length = recvData.ReadBits(10);
    numDungeons = recvData.ReadBits(24);
    recvData.FlushBits();
    if (!numDungeons)
    {
        sLog->outDebug(LOG_FILTER_NETWORKIO, "CMSG_LFG_JOIN [" UI64FMTD "] no dungeons selected", GetPlayer()->GetGUID());
        recvData.rfinish();
        return;
    }

    LfgDungeonSet newDungeons;
    for (uint32 i = 0; i < numDungeons; ++i)
    {
        recvData >> dungeon;
        dungeon &= 0xFFFFFF;
        newDungeons.insert(dungeon);       // remove the type from the dungeon entry
    }
    std::string comment = recvData.ReadString(length);

    const LFGDungeonEntry* entry = sLFGDungeonStore.LookupEntry(*newDungeons.begin() & 0xFFFFFF);
    uint8 type = LFG_TYPE_DUNGEON;
    uint8 maxGroupSize = 5;
    if (entry != NULL)
        type = entry->difficulty == RAID_TOOL_DIFFICULTY ? LFG_TYPE_RAID : entry->isScenario() ? LFG_TYPE_SCENARIO : LFG_TYPE_DUNGEON;
    if (type == LFG_TYPE_RAID)
        maxGroupSize = 25;
    if (type == LFG_TYPE_SCENARIO)
        maxGroupSize = 3;

    if (!sWorld->getBoolConfig(CONFIG_DUNGEON_FINDER_ENABLE) ||
        (GetPlayer()->GetGroup() && GetPlayer()->GetGroup()->GetLeaderGUID() != GetPlayer()->GetGUID() &&
        (GetPlayer()->GetGroup()->GetMembersCount() == maxGroupSize || !GetPlayer()->GetGroup()->isLFGGroup())))
    {
        recvData.rfinish();
        return;
    }

    sLog->outDebug(LOG_FILTER_NETWORKIO, "CMSG_LFG_JOIN [" UI64FMTD "] roles: %u, Dungeons: %u, Comment: %s", GetPlayer()->GetGUID(), roles, uint8(newDungeons.size()), comment.c_str());
    sLFGMgr->Join(GetPlayer(), uint8(roles), newDungeons, comment);
}

void WorldSession::HandleLfgLeaveOpcode(WorldPacket&  /*recvData*/)
{
    Group* grp = GetPlayer()->GetGroup();

    sLog->outDebug(LOG_FILTER_NETWORKIO, "CMSG_LFG_LEAVE [" UI64FMTD "] in group: %u", GetPlayer()->GetGUID(), grp ? 1 : 0);

    // Check cheating - only leader can leave the queue
    if (!grp || grp->GetLeaderGUID() == GetPlayer()->GetGUID())
        sLFGMgr->Leave(GetPlayer(), grp);
}

void WorldSession::HandleLfgProposalResultOpcode(WorldPacket& recvData)
{
    uint32 lfgGroupID;                                     // Internal lfgGroupID
    bool accept;                                           // Accept to join?
    recvData >> lfgGroupID;
    recvData.read_skip<uint32>();
    recvData.read_skip<uint32>();
    recvData.read_skip<uint32>();
    ObjectGuid unk;

    unk[5] = recvData.ReadBit();
    unk[1] = recvData.ReadBit();
    unk[0] = recvData.ReadBit();
    unk[2] = recvData.ReadBit();
    unk[4] = recvData.ReadBit();
    unk[6] = recvData.ReadBit();
    unk[3] = recvData.ReadBit();
    unk[7] = recvData.ReadBit();

    recvData.ReadByteSeq(unk[4]);
    recvData.ReadByteSeq(unk[1]);
    recvData.ReadByteSeq(unk[2]);
    recvData.ReadByteSeq(unk[5]);
    recvData.ReadByteSeq(unk[0]);
    recvData.ReadByteSeq(unk[7]);
    recvData.ReadByteSeq(unk[3]);
    recvData.ReadByteSeq(unk[6]);

    recvData.ReadBits(3);
    accept = recvData.ReadBit();

    // Osef du GUID
    recvData.rfinish();

    sLog->outDebug(LOG_FILTER_NETWORKIO, "CMSG_LFG_PROPOSAL_RESULT [" UI64FMTD "] proposal: %u accept: %u", GetPlayer()->GetGUID(), lfgGroupID, accept ? 1 : 0);
    sLFGMgr->UpdateProposal(lfgGroupID, GetPlayer()->GetGUID(), accept);
}

void WorldSession::HandleLfgSetRolesOpcode(WorldPacket& recvData)
{
    uint32 roles;
    uint8 unk;
    recvData >> roles;                                    // Player Group Roles
    recvData >> unk;

    uint64 guid = GetPlayer()->GetGUID();
    Group* grp = GetPlayer()->GetGroup();
    if (!grp)
    {
        sLog->outDebug(LOG_FILTER_NETWORKIO, "CMSG_LFG_SET_ROLES [" UI64FMTD "] Not in group", guid);
        return;
    }
    uint64 gguid = grp->GetGUID();
    sLog->outDebug(LOG_FILTER_NETWORKIO, "CMSG_LFG_SET_ROLES: Group [" UI64FMTD "], Player [" UI64FMTD "], Roles: %u", gguid, guid, roles);
    sLFGMgr->UpdateRoleCheck(gguid, guid, roles);
}

void WorldSession::HandleLfgSetCommentOpcode(WorldPacket&  recvData)
{
    std::string comment;
    recvData >> comment;
    uint64 guid = GetPlayer()->GetGUID();
    sLog->outDebug(LOG_FILTER_NETWORKIO, "CMSG_SET_LFG_COMMENT [" UI64FMTD "] comment: %s", guid, comment.c_str());

    sLFGMgr->SetComment(guid, comment);
}

void WorldSession::HandleLfgSetBootVoteOpcode(WorldPacket& recvData)
{
    bool agree;                                            // Agree to kick player
    agree = recvData.ReadBit();

    sLog->outDebug(LOG_FILTER_NETWORKIO, "CMSG_LFG_SET_BOOT_VOTE [" UI64FMTD "] agree: %u", GetPlayer()->GetGUID(), agree ? 1 : 0);
    sLFGMgr->UpdateBoot(GetPlayer(), agree);
}

void WorldSession::HandleLfgTeleportOpcode(WorldPacket& recvData)
{
    bool out;
    recvData >> out;

    sLog->outDebug(LOG_FILTER_NETWORKIO, "CMSG_LFG_TELEPORT [" UI64FMTD "] out: %u", GetPlayer()->GetGUID(), out ? 1 : 0);
    sLFGMgr->TeleportPlayer(GetPlayer(), out, true);
}

void WorldSession::HandleLfgPlayerLockInfoRequestOpcode(WorldPacket& /*recvData*/)
{
    uint64 guid = GetPlayer()->GetGUID();
    sLog->outDebug(LOG_FILTER_NETWORKIO, "CMSG_LFD_PLAYER_LOCK_INFO_REQUEST [" UI64FMTD "]", guid);

    // Get Random dungeons that can be done at a certain level and expansion
    LfgDungeonSet randomDungeons;
    uint8 level = GetPlayer()->getLevel();
    uint8 expansion = GetPlayer()->GetSession()->Expansion();
    for (uint32 i = 0; i < sLFGDungeonStore.GetNumRows(); ++i)
    {
        LFGDungeonEntry const* dungeon = sLFGDungeonStore.LookupEntry(i);
        if (dungeon && dungeon->expansion <= expansion && dungeon->minlevel <= level && level <= dungeon->maxlevel)
        {
            if (dungeon->flags & LFG_FLAG_SEASONAL)
            {
                if (HolidayIds holiday = sLFGMgr->GetDungeonSeason(dungeon->ID))
                    if (!IsHolidayActive(holiday))
                        continue;
            }
            else if (dungeon->type != LFG_TYPE_RANDOM)
                continue;
            randomDungeons.insert(dungeon->Entry());
        }
    }

    // Get player locked Dungeons
    LfgLockMap lock = sLFGMgr->GetLockedDungeons(guid);
    uint32 rsize = uint32(randomDungeons.size());
    uint32 lsize = uint32(lock.size());

    sLog->outDebug(LOG_FILTER_NETWORKIO, "SMSG_LFG_PLAYER_INFO [" UI64FMTD "]", guid);
    WorldPacket data(SMSG_LFG_PLAYER_INFO, 1 + rsize * (4 + 1 + 4 + 4 + 4 + 4 + 1 + 4 + 4 + 4) + 4 + lsize * (1 + 4 + 4 + 4 + 4 + 1 + 4 + 4 + 4));

    data << uint8(randomDungeons.size());                  // Random Dungeon count
    for (LfgDungeonSet::const_iterator it = randomDungeons.begin(); it != randomDungeons.end(); ++it)
    {
        data << uint32(*it);                               // Dungeon Entry (id + type)
        LfgReward const* reward = sLFGMgr->GetRandomDungeonReward(*it, level);
        Quest const* qRew = NULL;
        uint8 done = 0;
        if (reward)
        {
            qRew = sObjectMgr->GetQuestTemplate(reward->reward[0].questId);
            if (qRew)
            {
                done = !GetPlayer()->CanRewardQuest(qRew, false);
                if (done)
                    qRew = sObjectMgr->GetQuestTemplate(reward->reward[1].questId);
            }
        }
        if (qRew)
        {
            data << uint8(done);
            data << uint32(qRew->GetRewOrReqMoney());
            data << uint32(qRew->XPValue(GetPlayer()));
            data << uint32(reward->reward[done].variableMoney);
            data << uint32(reward->reward[done].variableXP);
            // Unk 4.2.2 Part
            for(int i = 0; i < 9; i++)
                data << uint32(0);
            data << uint8(0);
            for(int i = 0; i < 3; i++)
                data << uint32(0);
            data << uint32(0);
            data << uint32(0);
            // Unk 4.2.2 Part End
            data << uint8(qRew->GetRewItemsCount() + qRew->GetRewCurrencyCount());
            if (qRew->GetRewItemsCount())
            {
                ItemTemplate const* iProto = NULL;
                for (uint8 i = 0; i < QUEST_REWARDS_COUNT; ++i)
                {
                    if (!qRew->RewardItemId[i])
                        continue;

                    iProto = sObjectMgr->GetItemTemplate(qRew->RewardItemId[i]);

                    data << uint32(qRew->RewardItemId[i]);
                    data << uint32(iProto ? iProto->DisplayInfoID : 0);
                    data << uint32(qRew->RewardItemIdCount[i]);
                    data << uint8(0); // Is Currency
                }
            }
            if (qRew->GetRewCurrencyCount())
            {
                CurrencyTypesEntry const* iCurrencyType = NULL;

                for (uint8 i = 0; i < QUEST_REWARDS_COUNT; ++i)
                {
                    if (!qRew->RewardCurrencyId[i])
                        continue;

                    iCurrencyType = sCurrencyTypesStore.LookupEntry(qRew->RewardCurrencyId[i]);

                    data << uint32(qRew->RewardCurrencyId[i]);
                    data << uint32(0); // unk for Currency, maybe some display id ?
                    data << uint32(qRew->RewardCurrencyCount[i]);
                    data << uint8(1); // Is Currency
                }
            }
        }
        else
        {
            data << uint8(0);
            data << uint32(0);
            data << uint32(0);
            data << uint32(0);
            data << uint32(0);
            // Unk 4.2.2 Part
            for(int i = 0; i < 9; i++)
                data << uint32(0);
            data << uint8(0);
            for(int i = 0; i < 3; i++)
                data << uint32(0);
            data << uint32(0);
            data << uint32(0);
            // Unk 4.2.2 Part End
            data << uint8(0);
        }
    }
    BuildPlayerLockDungeonBlock(data, lock, GetPlayer());
    SendPacket(&data);
}

void WorldSession::HandleLfgPartyLockInfoRequestOpcode(WorldPacket&  /*recvData*/)
{
    uint64 guid = GetPlayer()->GetGUID();
    sLog->outDebug(LOG_FILTER_NETWORKIO, "CMSG_LFD_PARTY_LOCK_INFO_REQUEST [" UI64FMTD "]", guid);

    Group* grp = GetPlayer()->GetGroup();
    if (!grp)
        return;

    // Get the locked dungeons of the other party members
    LfgLockPartyMap lockMap;
    for (GroupReference* itr = grp->GetFirstMember(); itr != NULL; itr = itr->next())
    {
        Player* plrg = itr->getSource();
        if (!plrg)
            continue;

        uint64 pguid = plrg->GetGUID();
        if (pguid == guid)
            continue;

        lockMap[pguid] = sLFGMgr->GetLockedDungeons(pguid);
    }

    uint32 size = 0;
    for (LfgLockPartyMap::const_iterator it = lockMap.begin(); it != lockMap.end(); ++it)
        size += 8 + 4 + uint32(it->second.size()) * (4 + 4 + 4 + 4);

    sLog->outDebug(LOG_FILTER_NETWORKIO, "SMSG_LFG_PARTY_INFO [" UI64FMTD "]", guid);
    WorldPacket data(SMSG_LFG_PARTY_INFO, 1 + size);
    BuildPartyLockDungeonBlock(data, lockMap, GetPlayer());
    SendPacket(&data);
}

void WorldSession::HandleLfrSearchOpcode(WorldPacket& recvData)
{
    uint32 entry;                                          // Raid id to search
    recvData >> entry;
    sLog->outDebug(LOG_FILTER_NETWORKIO, "CMSG_SEARCH_LFG_JOIN [" UI64FMTD "] dungeon entry: %u", GetPlayer()->GetGUID(), entry);
    //SendLfrUpdateListOpcode(entry);
}

void WorldSession::HandleLfrLeaveOpcode(WorldPacket& recvData)
{
    uint32 dungeonId;                                      // Raid id queue to leave
    recvData >> dungeonId;
    sLog->outDebug(LOG_FILTER_NETWORKIO, "CMSG_SEARCH_LFG_LEAVE [" UI64FMTD "] dungeonId: %u", GetPlayer()->GetGUID(), dungeonId);
    //sLFGMgr->LeaveLfr(GetPlayer(), dungeonId);
}

void WorldSession::SendLfgUpdatePlayer(const LfgUpdateData& updateData)
{
    bool queued = false;
    bool extrainfo = false;
    bool quit = false;

    switch (updateData.updateType)
    {
        case LFG_UPDATETYPE_JOIN_PROPOSAL:
        case LFG_UPDATETYPE_ADDED_TO_QUEUE:
            queued = true;
            extrainfo = true;
            break;
        //case LFG_UPDATETYPE_CLEAR_LOCK_LIST: // TODO: Sometimes has extrainfo - Check ocurrences...
        case LFG_UPDATETYPE_PROPOSAL_BEGIN:
            extrainfo = true;
            break;
        case LFG_UPDATETYPE_GROUP_DISBAND:
        case LFG_UPDATETYPE_GROUP_FOUND:
        case LFG_UPDATETYPE_CLEAR_LOCK_LIST:
        case LFG_UPDATETYPE_REMOVED_FROM_QUEUE:
            quit = true;
            break;
        default:
            break;
    }
    sLFGMgr->SendUpdateStatus(GetPlayer(), updateData.comment, updateData.dungeons, false, quit);
    /*uint64 guid = GetPlayer()->GetGUID();
    uint8 size = uint8(updateData.dungeons.size());

    sLog->outDebug(LOG_FILTER_NETWORKIO, "SMSG_LFG_UPDATE_PLAYER [" UI64FMTD "] updatetype: %u", guid, updateData.updateType);
    WorldPacket data(SMSG_LFG_UPDATE_PLAYER, 1 + 1 + (extrainfo ? 1 : 0) * (1 + 1 + 1 + 1 + size * 4 + updateData.comment.length()));
    data << uint8(updateData.updateType);                 // Lfg Update type
    data << uint8(extrainfo);                             // Extra info
    if (extrainfo)
    {
        data << uint8(queued);                            // Join the queue
        data << uint8(0);                                 // unk - Always 0
        data << uint8(0);                                 // unk - Always 0

        data << uint8(size);
        if (size)
            for (LfgDungeonSet::const_iterator it = updateData.dungeons.begin(); it != updateData.dungeons.end(); ++it)
                data << uint32(*it);
        data << updateData.comment;
    }
    SendPacket(&data);*/
}

void WorldSession::SendLfgUpdateParty(const LfgUpdateData& updateData, uint32 joinTime)
{
    bool join = false;
    bool extrainfo = false;
    bool queued = false;
    bool quit = false;
    bool pause = false;


    switch (updateData.updateType)
    {
        case LFG_UPDATETYPE_JOIN_PROPOSAL:
            extrainfo = true;
            break;
        case LFG_UPDATETYPE_ADDED_TO_QUEUE:
            extrainfo = true;
            join = true;
            queued = true;
            break;
        case LFG_UPDATETYPE_CLEAR_LOCK_LIST:
            // join = true;  // TODO: Sometimes queued and extrainfo - Check ocurrences...
            queued = true;
            quit = true;
            break;
        case LFG_UPDATETYPE_PROPOSAL_BEGIN:
            extrainfo = true;
            join = true;
            break;
        case LFG_UPDATETYPE_GROUP_DISBAND:
        case LFG_UPDATETYPE_GROUP_FOUND:
            quit = true;
            break;
        case LFG_UPDATETYPE_REMOVED_FROM_QUEUE:
            quit = true;
            pause = true;
            break;
        default:
            break;
    }

    uint64 guid = GetPlayer()->GetGUID();
    uint8 size = uint8(updateData.dungeons.size());
    sLFGMgr->SendUpdateStatus(GetPlayer(), updateData.comment, updateData.dungeons, pause, quit);
    sLog->outDebug(LOG_FILTER_NETWORKIO, "SMSG_LFG_UPDATE_PARTY [" UI64FMTD "] updatetype: %u", guid, updateData.updateType);
    /*WorldPacket data(SMSG_LFG_UPDATE_PARTY, 1 + 1 + (extrainfo ? 1 : 0) * (1 + 1 + 1 + 1 + 1 + size * 4 + updateData.comment.length()));
    data << uint8(updateData.updateType);                 // Lfg Update type
    data << uint8(extrainfo);                             // Extra info
    if (extrainfo)
    {
        data << uint8(join);                              // LFG Join
        data << uint8(queued);                            // Join the queue
        data << uint8(0);                                 // unk - Always 0
        data << uint8(0);                                 // unk - Always 0
        for (uint8 i = 0; i < 3; ++i)
            data << uint8(0);                             // unk - Always 0

        data << uint8(size);
        if (size)
            for (LfgDungeonSet::const_iterator it = updateData.dungeons.begin(); it != updateData.dungeons.end(); ++it)
                data << uint32(*it);
        data << updateData.comment;
    }
    SendPacket(&data);*/
}

void WorldSession::SendLfgRoleChosen(uint64 guid, uint8 roles)
{
    sLog->outDebug(LOG_FILTER_NETWORKIO, "SMSG_LFG_ROLE_CHOSEN [" UI64FMTD "] guid: [" UI64FMTD "] roles: %u", GetPlayer()->GetGUID(), guid, roles);

    WorldPacket data(SMSG_LFG_ROLE_CHOSEN, 8 + 1 + 4);
    data << uint64(guid);                                  // Guid
    data << uint8(roles > 0);                              // Ready
    data << uint32(roles);                                 // Roles
    SendPacket(&data);
}

void WorldSession::SendLfgRoleCheckUpdate(const LfgRoleCheck* pRoleCheck, bool updateAll)
{
    ASSERT(pRoleCheck);
    LfgDungeonSet dungeons;
    if (pRoleCheck->rDungeonId)
        dungeons.insert(pRoleCheck->rDungeonId);
    else
        dungeons = pRoleCheck->dungeons;

    sLog->outDebug(LOG_FILTER_NETWORKIO, "SMSG_LFG_ROLE_CHECK_UPDATE [" UI64FMTD "]", GetPlayer()->GetGUID());
    WorldPacket data(SMSG_LFG_ROLE_CHECK_UPDATE, 4 + 1 + 1 + dungeons.size() * 4 + 1 + pRoleCheck->roles.size() * (8 + 1 + 4 + 1));
    ByteBuffer dataBuffer;

    data.WriteBits(dungeons.size(), 24);
    data.WriteBit(pRoleCheck->state == LFG_ROLECHECK_INITIALITING);
    //data.WriteBits(pRoleCheck->roles.size(), 23);
    data.WriteBits(updateAll ?pRoleCheck->roles.size() : 1, 23);
    if (!pRoleCheck->roles.empty())
    {
        // Player info MUST be sent 1st :S
        ObjectGuid guid = GetPlayer()->GetGUID();
        uint8 roles = pRoleCheck->roles.find(guid)->second;
        Player* player = ObjectAccessor::FindPlayer(guid);

        data.WriteBit(guid[1]);
        data.WriteBit(guid[7]);
        data.WriteBit(guid[5]);
        data.WriteBit(guid[6]);
        data.WriteBit(guid[2]);
        data.WriteBit(guid[0]);
        data.WriteBit(roles > 0);
        data.WriteBit(guid[3]);
        data.WriteBit(guid[4]);

        dataBuffer.WriteByteSeq(guid[2]);
        dataBuffer.WriteByteSeq(guid[3]);
        dataBuffer.WriteByteSeq(guid[0]);
        dataBuffer.WriteByteSeq(guid[5]);
        dataBuffer << uint32(roles);                                   // Roles
        dataBuffer << uint8(player ? player->getLevel() : 0);          // Level
        dataBuffer.WriteByteSeq(guid[1]);
        dataBuffer.WriteByteSeq(guid[7]);
        dataBuffer.WriteByteSeq(guid[6]);
        dataBuffer.WriteByteSeq(guid[4]);


        for (LfgRolesMap::const_reverse_iterator it = pRoleCheck->roles.rbegin(); it != pRoleCheck->roles.rend(); ++it)
        {
            if (it->first == GetPlayer()->GetGUID() || !updateAll)
                continue;
        
            guid = it->first;
            roles = it->second;
            player = ObjectAccessor::FindPlayer(guid);

            data.WriteBit(guid[1]);
            data.WriteBit(guid[7]);
            data.WriteBit(guid[5]);
            data.WriteBit(guid[6]);
            data.WriteBit(guid[2]);
            data.WriteBit(guid[0]);
            data.WriteBit(roles > 0);
            data.WriteBit(guid[3]);
            data.WriteBit(guid[4]);

            dataBuffer.WriteByteSeq(guid[2]);
            dataBuffer.WriteByteSeq(guid[3]);
            dataBuffer.WriteByteSeq(guid[0]);
            dataBuffer.WriteByteSeq(guid[5]);
            dataBuffer << uint32(roles);                                   // Roles
            dataBuffer << uint8(player ? player->getLevel() : 0);          // Level
            dataBuffer.WriteByteSeq(guid[1]);
            dataBuffer.WriteByteSeq(guid[7]);
            dataBuffer.WriteByteSeq(guid[6]);
            dataBuffer.WriteByteSeq(guid[4]);
        }
    }
    data.append(dataBuffer);
    data << uint8(0);
    data << uint8(pRoleCheck->state);

    if (!dungeons.empty())
    {
        for (LfgDungeonSet::iterator it = dungeons.begin(); it != dungeons.end(); ++it)
        {
            LFGDungeonEntry const* dungeon = sLFGDungeonStore.LookupEntry(*it);
            data << uint32(dungeon ? dungeon->Entry() : 0); // Dungeon
        }
    }
    /*data << uint32(pRoleCheck->state);                     // Check result
    data << uint8(pRoleCheck->state == LFG_ROLECHECK_INITIALITING);
    data << uint8(dungeons.size());                        // Number of dungeons
    if (!dungeons.empty())
    {
        for (LfgDungeonSet::iterator it = dungeons.begin(); it != dungeons.end(); ++it)
        {
            LFGDungeonEntry const* dungeon = sLFGDungeonStore.LookupEntry(*it);
            data << uint32(dungeon ? dungeon->Entry() : 0); // Dungeon
        }
    }

    data << uint8(pRoleCheck->roles.size());               // Players in group
    if (!pRoleCheck->roles.empty())
    {
        // Leader info MUST be sent 1st :S
        uint64 guid = pRoleCheck->leader;
        uint8 roles = pRoleCheck->roles.find(guid)->second;
        data << uint64(guid);                              // Guid
        data << uint8(roles > 0);                          // Ready
        Player* player = ObjectAccessor::FindPlayer(guid);
        data << uint8(player ? player->getLevel() : 0);          // Level

        for (LfgRolesMap::const_iterator it = pRoleCheck->roles.begin(); it != pRoleCheck->roles.end(); ++it)
        {
            if (it->first == pRoleCheck->leader)
                continue;

            guid = it->first;
            roles = it->second;
            data << uint64(guid);                          // Guid
            data << uint8(roles > 0);                      // Ready
            data << uint32(roles);                         // Roles
            player = ObjectAccessor::FindPlayer(guid);
            data << uint8(player ? player->getLevel() : 0);      // Level
        }
    }*/
    SendPacket(&data);
}

void WorldSession::SendLfgJoinResult(const LfgJoinResultData& joinData)
{
    uint32 size = 0;
    for (LfgLockPartyMap::const_iterator it = joinData.lockmap.begin(); it != joinData.lockmap.end(); ++it)
        size += 8 + 4 + uint32(it->second.size()) * (4 + 4 + 4 + 4);

    sLog->outDebug(LOG_FILTER_NETWORKIO, "SMSG_LFG_JOIN_RESULT [" UI64FMTD "] checkResult: %u checkValue: %u", GetPlayer()->GetGUID(), joinData.result, joinData.state);
    WorldPacket data(SMSG_LFG_JOIN_RESULT, 4 + 4 + size);
    data << uint32(joinData.state);                        // Check Value
    data << uint8(0);
    data << uint8(0);
    data << uint32(joinData.result);                       // Check Result
    data.WriteBit(0);
    data.WriteBit(0);
    data.WriteBit(0);
    data.WriteBit(0);
    data.WriteBit(0);
    data.WriteBit(0);
    data.WriteBit(0);
    if (!joinData.lockmap.empty())
        BuildPartyLockDungeonBlock(data, joinData.lockmap, GetPlayer());

    SendPacket(&data);
}

void WorldSession::SendLfgQueueStatus(uint32 dungeon, int32 waitTime, int32 avgWaitTime, int32 waitTimeTanks, int32 waitTimeHealer, int32 waitTimeDps, uint32 queuedTime, uint8 tanks, uint8 healers, uint8 dps)
{
    sLog->outDebug(LOG_FILTER_NETWORKIO, "SMSG_LFG_QUEUE_STATUS [" UI64FMTD "] dungeon: %u - waitTime: %d - avgWaitTime: %d - waitTimeTanks: %d - waitTimeHealer: %d - waitTimeDps: %d - queuedTime: %u - tanks: %u - healers: %u - dps: %u", GetPlayer()->GetGUID(), dungeon, waitTime, avgWaitTime, waitTimeTanks, waitTimeHealer, waitTimeDps, queuedTime, tanks, healers, dps);
    ObjectGuid guid = GetPlayer()->GetGUID();

    LfgQueueInfo* info = sLFGMgr->GetLfgQueueInfo(GetPlayer()->GetGroup() ? GetPlayer()->GetGroup()->GetGUID() : GetPlayer()->GetGUID());
    if (!info)
        return;

    WorldPacket data(SMSG_LFG_QUEUE_STATUS, 4 + 4 + 4 + 4 + 4 +4 + 1 + 1 + 1 + 4);
    data << uint32(dungeon);                               // Dungeon

    data << int32(waitTimeTanks);                          // Wait Tanks
    data << uint8(tanks);                                  // Tanks needed
    
    data << int32(waitTimeHealer);                         // Wait Healers
    data << uint8(healers);                                // Healers needed
    
    data << int32(waitTimeDps);                            // Wait Dps
    data << uint8(dps);                                    // Dps needed

    data << uint32(GetPlayer()->GetTeam()); //Queueid
    data << int32(info->joinTime); //Time
    data << int32(waitTime); //-1

    data << int32(avgWaitTime); //-1
    data << uint32(3); //4
    data << uint32(3); //
    
    data.WriteBit(guid[4]);
    data.WriteBit(guid[5]);
    data.WriteBit(guid[2]);
    data.WriteBit(guid[6]);
    data.WriteBit(guid[0]);
    data.WriteBit(guid[3]);
    data.WriteBit(guid[7]);
    data.WriteBit(guid[1]);

    data.WriteByteSeq(guid[7]);
    data.WriteByteSeq(guid[5]);
    data.WriteByteSeq(guid[0]);
    data.WriteByteSeq(guid[4]);
    data.WriteByteSeq(guid[1]);
    data.WriteByteSeq(guid[3]);
    data.WriteByteSeq(guid[2]);
    data.WriteByteSeq(guid[6]);

    /*data << int32(avgWaitTime);                            // Average Wait time
    data << int32(waitTime);                               // Wait Time
    data << uint32(queuedTime);                            // Player wait time in queue*/
    SendPacket(&data);
}

void WorldSession::SendLfgPlayerReward(uint32 rdungeonEntry, uint32 sdungeonEntry, uint8 done, const LfgReward* reward, const Quest* qRew)
{
    if (!rdungeonEntry || !sdungeonEntry || !qRew)
        return;

    uint8 itemNum = uint8(qRew ? qRew->GetRewItemsCount() : 0);

    sLog->outDebug(LOG_FILTER_NETWORKIO, "SMSG_LFG_PLAYER_REWARD [" UI64FMTD "] rdungeonEntry: %u - sdungeonEntry: %u - done: %u", GetPlayer()->GetGUID(), rdungeonEntry, sdungeonEntry, done);
    WorldPacket data(SMSG_LFG_PLAYER_REWARD, 4 + 4 + 1 + 4 + 4 + 4 + 4 + 4 + 1 + itemNum * (4 + 4 + 4));
    data << uint32(rdungeonEntry);                         // Random Dungeon Finished
    data << uint32(sdungeonEntry);                         // Dungeon Finished
    /*data << uint8(done);
    data << uint32(1);*/
    data << uint32(qRew->GetRewOrReqMoney());
    data << uint32(qRew->XPValue(GetPlayer()));
    /*data << uint32(reward->reward[done].variableMoney);
    data << uint32(reward->reward[done].variableXP);*/
    data << uint8(itemNum);
    if (itemNum)
    {
        ItemTemplate const* iProto = NULL;
        for (uint8 i = 0; i < QUEST_REWARDS_COUNT; ++i)
        {
            if (!qRew->RewardItemId[i])
                continue;

            iProto = sObjectMgr->GetItemTemplate(qRew->RewardItemId[i]);

            data << uint32(qRew->RewardItemId[i]);
            data << uint32(0); //unk
            data << uint32(iProto ? iProto->DisplayInfoID : 0);

            data << uint8(qRew->RewardItemIdCount[i]);
        }
    }
    SendPacket(&data);
}

void WorldSession::SendLfgBootPlayer(const LfgPlayerBoot* pBoot)
{
    uint64 guid = GetPlayer()->GetGUID();
    LfgAnswer playerVote = pBoot->votes.find(guid)->second;
    uint8 votesNum = 0;
    uint8 agreeNum = 0;
    uint32 secsleft = uint8((pBoot->cancelTime - time(NULL)) / 1000);
    for (LfgAnswerMap::const_iterator it = pBoot->votes.begin(); it != pBoot->votes.end(); ++it)
    {
        if (it->second != LFG_ANSWER_PENDING)
        {
            ++votesNum;
            if (it->second == LFG_ANSWER_AGREE)
                ++agreeNum;
        }
    }
    sLog->outDebug(LOG_FILTER_NETWORKIO, "SMSG_LFG_BOOT_PROPOSAL_UPDATE [" UI64FMTD "] inProgress: %u - didVote: %u - agree: %u - victim: [" UI64FMTD "] votes: %u - agrees: %u - left: %u - needed: %u - reason %s",
        guid, uint8(pBoot->inProgress), uint8(playerVote != LFG_ANSWER_PENDING), uint8(playerVote == LFG_ANSWER_AGREE), pBoot->victim, votesNum, agreeNum, secsleft, pBoot->votedNeeded, pBoot->reason.c_str());
    WorldPacket data(SMSG_LFG_BOOT_PROPOSAL_UPDATE, 1 + 1 + 1 + 8 + 4 + 4 + 4 + 4 + pBoot->reason.length());
    data << uint8(pBoot->inProgress);                      // Vote in progress
    data << uint8(playerVote != LFG_ANSWER_PENDING);       // Did Vote
    data << uint8(playerVote == LFG_ANSWER_AGREE);         // Agree
    data << uint8(0);                                      // Unknown 4.2.2
    data << uint64(pBoot->victim);                         // Victim GUID
    data << uint32(votesNum);                              // Total Votes
    data << uint32(agreeNum);                              // Agree Count
    data << uint32(secsleft);                              // Time Left
    data << uint32(pBoot->votedNeeded);                    // Needed Votes
    data << pBoot->reason.c_str();                         // Kick reason
    SendPacket(&data);
}

void WorldSession::SendLfgUpdateProposal(uint32 proposalId, const LfgProposal* pProp)
{
    if (!pProp)
        return;

    uint64 guid = GetPlayer()->GetGUID();
    LfgProposalPlayerMap::const_iterator itPlayer = pProp->players.find(guid);
    if (itPlayer == pProp->players.end())                  // Player MUST be in the proposal
        return;

    LfgProposalPlayer* ppPlayer = itPlayer->second;
    uint32 pLowGroupGuid = ppPlayer->groupLowGuid;
    uint32 dLowGuid = pProp->groupLowGuid;
    uint32 dungeonId = pProp->dungeonId;
    bool isSameDungeon = false;
    bool isContinue = false;
    Group* grp = dLowGuid ? sGroupMgr->GetGroupByGUID(dLowGuid) : NULL;
    uint32 completedEncounters = 0;
    if (grp)
    {
        uint64 gguid = grp->GetGUID();
        isContinue = grp->isLFGGroup() && sLFGMgr->GetState(gguid) != LFG_STATE_FINISHED_DUNGEON;
        isSameDungeon = GetPlayer()->GetGroup() == grp && isContinue;
    }

    sLog->outDebug(LOG_FILTER_NETWORKIO, "SMSG_LFG_PROPOSAL_UPDATE [" UI64FMTD "] state: %u", GetPlayer()->GetGUID(), pProp->state);
    WorldPacket data(SMSG_LFG_PROPOSAL_UPDATE, 4 + 1 + 4 + 4 + 1 + 1 + pProp->players.size() * (4 + 1 + 1 + 1 + 1 +1));

    if (!isContinue)                                       // Only show proposal dungeon if it's continue
    {
        LfgDungeonSet playerDungeons = sLFGMgr->GetSelectedDungeons(guid);
        if (playerDungeons.size() == 1)
            dungeonId = (*playerDungeons.begin());
    }

    if (LFGDungeonEntry const* dungeon = sLFGDungeonStore.LookupEntry(dungeonId))
    {
        dungeonId = dungeon->Entry();

        // Select a player inside to be get completed encounters from
        if (grp)
        {
            for (GroupReference* itr = grp->GetFirstMember(); itr != NULL; itr = itr->next())
            {
                Player* groupMember = itr->getSource();
                if (groupMember && groupMember->GetMapId() == uint32(dungeon->map))
                {
                    if (InstanceScript* instance = groupMember->GetInstanceScript())
                        completedEncounters = instance->GetCompletedEncounterMask();
                    break;
                }
            }
        }
    }

    ObjectGuid playerGUID = guid;
    ObjectGuid InstanceSaveGUID = MAKE_NEW_GUID(dungeonId, 0, HIGHGUID_INSTANCE_SAVE);

    data << uint8(pProp->state);                           // Result state
    data << uint32(GetPlayer()->GetTeam());                // Queue Id
    data << uint32(completedEncounters);                   // Bosses killed
    data << uint32(getMSTime());                           // Date
    data << uint32(0x03);                                  // unk id or flags ? always 3
    data << uint32(proposalId);                            // Proposal Id
    data << uint32(dungeonId);                             // Dungeon

    data.WriteBit(playerGUID[2]);
    data.WriteBit(playerGUID[0]);
    data.WriteBit(InstanceSaveGUID[0]);
    data.WriteBit(InstanceSaveGUID[6]);
    data.WriteBit(playerGUID[4]);
    data.WriteBit(playerGUID[5]);
    data.WriteBit(InstanceSaveGUID[2]);
    data.WriteBit(InstanceSaveGUID[1]);
    data.WriteBit(playerGUID[7]);
    data.WriteBit(InstanceSaveGUID[7]);
    data.WriteBit(InstanceSaveGUID[5]);
    data.WriteBit(playerGUID[1]);
    data.WriteBit(InstanceSaveGUID[3]);

    data.WriteBits(pProp->players.size(), 23);

    data.WriteBit(playerGUID[3]);
    data.WriteBit(isSameDungeon);

    for (itPlayer = pProp->players.begin(); itPlayer != pProp->players.end(); ++itPlayer)
    {
        data.WriteBit(itPlayer->first == guid);            // Self player
        data.WriteBit(itPlayer->second->accept == LFG_ANSWER_AGREE); // Accepted

        if (!itPlayer->second->groupLowGuid)                       // Player not it a group
        {
            data.WriteBit(0);                              // Not in dungeon
            data.WriteBit(0);                              // Not same group
        }
        else
        {
            data.WriteBit(itPlayer->second->groupLowGuid == dLowGuid);  // In dungeon (silent)
            data.WriteBit(itPlayer->second->groupLowGuid == pLowGroupGuid); // Same Group than player
        }

        data.WriteBit(itPlayer->second->accept!= LFG_ANSWER_PENDING); // Answered
    }

    data.WriteBit(InstanceSaveGUID[4]);
    data.WriteBit(playerGUID[6]);

    data.WriteByteSeq(InstanceSaveGUID[1]);
    data.WriteByteSeq(playerGUID[1]);
    data.WriteByteSeq(InstanceSaveGUID[0]);
    data.WriteByteSeq(playerGUID[7]);
    data.WriteByteSeq(InstanceSaveGUID[7]);
    data.WriteByteSeq(playerGUID[5]);
    data.WriteByteSeq(InstanceSaveGUID[3]);


    for (itPlayer = pProp->players.begin(); itPlayer != pProp->players.end(); ++itPlayer)
        data << uint32(itPlayer->second->role);                    // Role

    data.WriteByteSeq(playerGUID[2]);
    data.WriteByteSeq(InstanceSaveGUID[4]);
    data.WriteByteSeq(playerGUID[3]);
    data.WriteByteSeq(InstanceSaveGUID[6]);
    data.WriteByteSeq(InstanceSaveGUID[5]);
    data.WriteByteSeq(playerGUID[6]);
    data.WriteByteSeq(playerGUID[0]);
    data.WriteByteSeq(InstanceSaveGUID[2]);
    data.WriteByteSeq(playerGUID[4]);

    SendPacket(&data);
}

void WorldSession::SendLfgUpdateSearch(bool update)
{
    sLog->outDebug(LOG_FILTER_NETWORKIO, "SMSG_LFG_UPDATE_SEARCH [" UI64FMTD "] update: %u", GetPlayer()->GetGUID(), update ? 1 : 0);
    WorldPacket data(SMSG_LFG_UPDATE_SEARCH, 1);
    data << uint8(update);                                 // In Lfg Queue?
    SendPacket(&data);
}

void WorldSession::SendLfgDisabled()
{
    sLog->outDebug(LOG_FILTER_NETWORKIO, "SMSG_LFG_DISABLED [" UI64FMTD "]", GetPlayer()->GetGUID());
    WorldPacket data(SMSG_LFG_DISABLED, 0);
    SendPacket(&data);
}

void WorldSession::SendLfgOfferContinue(uint32 dungeonEntry)
{
    sLog->outDebug(LOG_FILTER_NETWORKIO, "SMSG_LFG_OFFER_CONTINUE [" UI64FMTD "] dungeon entry: %u", GetPlayer()->GetGUID(), dungeonEntry);
    WorldPacket data(SMSG_LFG_OFFER_CONTINUE, 4);
    data << uint32(dungeonEntry);
    SendPacket(&data);
}

void WorldSession::SendLfgTeleportError(uint8 err)
{
    sLog->outDebug(LOG_FILTER_NETWORKIO, "SMSG_LFG_TELEPORT_DENIED [" UI64FMTD "] reason: %u", GetPlayer()->GetGUID(), err);
    WorldPacket data(SMSG_LFG_TELEPORT_DENIED, 4);
    //Not sure it is no 4bits.
    data.WriteBits(err, 4);                                   // Error
    data.FlushBits();
    SendPacket(&data);
}

/*
void WorldSession::SendLfrUpdateListOpcode(uint32 dungeonEntry)
{
    sLog->outDebug(LOG_FILTER_PACKETIO, "SMSG_LFG_UPDATE_LIST [" UI64FMTD "] dungeon entry: %u", GetPlayer()->GetGUID(), dungeonEntry);
    WorldPacket data(SMSG_LFG_UPDATE_LIST);
    SendPacket(&data);
}
*/
