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
#include "Object.h"
#include "SharedDefines.h"
#include "GuildFinderMgr.h"
#include "GuildMgr.h"

void WorldSession::HandleGuildFinderAddRecruit(WorldPacket& recvPacket)
{
    sLog->outDebug(LOG_FILTER_NETWORKIO, "WORLD: Received CMSG_LF_GUILD_ADD_RECRUIT");

    if (sGuildFinderMgr->GetAllMembershipRequestsForPlayer(GetPlayer()->GetGUIDLow()).size() == 10)
        return;

    uint32 classRoles = 0;
    uint32 availability = 0;
    uint32 guildInterests = 0;

    recvPacket >> classRoles >> guildInterests >> availability;

    ObjectGuid guid;
    uint16 commentLength = recvPacket.ReadBits(11);

    uint8 bitOrder[8] = {7, 2, 6, 5, 0, 3, 4, 1};
    recvPacket.ReadBitInOrder(guid, bitOrder);

    uint8 nameLength = recvPacket.ReadBits(7);
    
    recvPacket.ReadByteSeq(guid[3]);
    recvPacket.ReadByteSeq(guid[0]);
    recvPacket.ReadByteSeq(guid[2]);
    std::string playerName = recvPacket.ReadString(nameLength);
    std::string comment = recvPacket.ReadString(commentLength);
    recvPacket.ReadByteSeq(guid[4]);
    recvPacket.ReadByteSeq(guid[7]);
    recvPacket.ReadByteSeq(guid[1]);
    recvPacket.ReadByteSeq(guid[5]);
    recvPacket.ReadByteSeq(guid[6]);

    uint32 guildLowGuid = GUID_LOPART(uint64(guid));

    if (!IS_GUILD_GUID(guid))
        return;
    if (!(classRoles & GUILDFINDER_ALL_ROLES) || classRoles > GUILDFINDER_ALL_ROLES)
        return;
    if (!(availability & ALL_WEEK) || availability > ALL_WEEK)
        return;
    if (!(guildInterests & ALL_INTERESTS) || guildInterests > ALL_INTERESTS)
        return;

    MembershipRequest request = MembershipRequest(GetPlayer()->GetGUIDLow(), guildLowGuid, availability, classRoles, guildInterests, comment, time(NULL));
    sGuildFinderMgr->AddMembershipRequest(guildLowGuid, request);
}

void WorldSession::HandleGuildFinderBrowse(WorldPacket& recvPacket)
{
    sLog->outDebug(LOG_FILTER_NETWORKIO, "WORLD: Received CMSG_LF_GUILD_BROWSE");
    uint32 classRoles = 0;
    uint32 availability = 0;
    uint32 guildInterests = 0;
    uint32 playerLevel = 0; // Raw player level (1-90), do they use MAX_FINDER_LEVEL when on level 90 ?

    recvPacket >> guildInterests >> availability >> classRoles >> playerLevel;
    
    if (!(classRoles & GUILDFINDER_ALL_ROLES) || classRoles > GUILDFINDER_ALL_ROLES)
        return;
    if (!(availability & ALL_WEEK) || availability > ALL_WEEK)
        return;
    if (!(guildInterests & ALL_INTERESTS) || guildInterests > ALL_INTERESTS)
        return;
    if (playerLevel > sWorld->getIntConfig(CONFIG_MAX_PLAYER_LEVEL) || playerLevel < 1)
        return;

    Player* player = GetPlayer();

    LFGuildPlayer settings(player->GetGUIDLow(), classRoles, availability, guildInterests, ANY_FINDER_LEVEL);
    LFGuildStore guildList = sGuildFinderMgr->GetGuildsMatchingSetting(settings, player->GetTeamId());
    uint32 guildCount = guildList.size();

    if (guildCount == 0)
    {
        WorldPacket packet(SMSG_LF_GUILD_BROWSE_UPDATED, 0);
        player->SendDirectMessage(&packet);
        return;
    }

    ByteBuffer bufferData(65 * guildCount);
    WorldPacket data(SMSG_LF_GUILD_BROWSE_UPDATED, 3 + guildCount * 65); // Estimated size
    data.WriteBits(guildCount, 19);

    for (LFGuildStore::const_iterator itr = guildList.begin(); itr != guildList.end(); ++itr)
    {
        LFGuildSettings guildSettings = itr->second;
        Guild* guild = sGuildMgr->GetGuildById(itr->first);

        ObjectGuid guildGUID = ObjectGuid(guild->GetGUID());
        
        data.WriteBit(guildGUID[3]);
        data.WriteBits(guild->GetName().size(), 8);
        data.WriteBits(guildSettings.GetComment().size(), 11);
        data.WriteBit(guildGUID[2]);
        data.WriteBit(guildGUID[0]);
        data.WriteBit(guildGUID[6]);
        data.WriteBit(guildGUID[4]);
        data.WriteBit(guildGUID[1]);
        data.WriteBit(guildGUID[5]);
        data.WriteBit(guildGUID[7]);
        
        bufferData << int32(guild->GetEmblemInfo().GetBackgroundColor());
        bufferData << guild->GetLevel();
        bufferData << uint32(guildSettings.GetInterests()); // Guild Interests
        bufferData.WriteByteSeq(guildGUID[5]);
        bufferData.WriteByteSeq(guildGUID[1]);
        bufferData.WriteByteSeq(guildGUID[2]);
        bufferData << int32(guild->GetEmblemInfo().GetBorderColor());
        bufferData << int32(0); // guild->GetAchievementMgr().GetAchievementPoints()
        bufferData << uint8(sGuildFinderMgr->HasRequest(player->GetGUIDLow(), guild->GetGUID())); // Request pending
        bufferData << int32(guild->GetEmblemInfo().GetBorderStyle()); // Guessed
        bufferData.WriteByteSeq(guildGUID[0]);
        bufferData << uint32(guildSettings.GetAvailability());
        bufferData.WriteByteSeq(guildGUID[4]);
        bufferData << int32(guild->GetMembersCount());
        bufferData << uint32(0); // Unk Int 2 (+ 128) // Always 0 or 1
        bufferData.WriteByteSeq(guildGUID[7]);
        bufferData << uint32(guildSettings.GetClassRoles());
        bufferData << uint8(0); // Cached ? Idk
        bufferData.WriteByteSeq(guildGUID[6]);
        bufferData.WriteString(guild->GetName());
        bufferData << int32(guild->GetEmblemInfo().GetColor());
        bufferData.WriteByteSeq(guildGUID[3]);
        bufferData.WriteString(guildSettings.GetComment());
        bufferData << int32(guild->GetEmblemInfo().GetStyle());
    }

    data.FlushBits();
    data.append(bufferData);

    player->SendDirectMessage(&data);
}

void WorldSession::HandleGuildFinderDeclineRecruit(WorldPacket& recvPacket)
{
    sLog->outDebug(LOG_FILTER_NETWORKIO, "WORLD: Received CMSG_LF_GUILD_DECLINE_RECRUIT");

    ObjectGuid playerGuid;

    uint8 bitOrder[8] = {5, 1, 3, 7, 6, 2, 0, 4};
    recvPacket.ReadBitInOrder(playerGuid, bitOrder);

    uint8 byteOrder[8] = {4, 2, 3, 7, 6, 0, 1, 5};
    recvPacket.ReadBytesSeq(playerGuid, byteOrder);

    if (!IS_PLAYER_GUID(playerGuid))
        return;

    sGuildFinderMgr->RemoveMembershipRequest(GUID_LOPART(playerGuid), GetPlayer()->GetGuildId());
}

void WorldSession::HandleGuildFinderGetApplications(WorldPacket& /*recvPacket*/)
{
    sLog->outDebug(LOG_FILTER_NETWORKIO, "WORLD: Received CMSG_LF_GUILD_GET_APPLICATIONS"); // Empty opcode

    std::list<MembershipRequest> applicatedGuilds = sGuildFinderMgr->GetAllMembershipRequestsForPlayer(GetPlayer()->GetGUIDLow());
    uint32 applicationsCount = applicatedGuilds.size();
    WorldPacket data(SMSG_LF_GUILD_MEMBERSHIP_LIST_UPDATED, 7 + 54 * applicationsCount);
    data << uint32(10 - sGuildFinderMgr->CountRequestsFromPlayer(GetPlayer()->GetGUIDLow())); // Applications count left
    data.WriteBits(applicationsCount, 20);

    if (applicationsCount > 0)
    {
        ByteBuffer bufferData(54 * applicationsCount);
        for (std::list<MembershipRequest>::const_iterator itr = applicatedGuilds.begin(); itr != applicatedGuilds.end(); ++itr)
        {
            Guild* guild = sGuildMgr->GetGuildById(itr->GetGuildId());

            if (!guild)
                continue;

            LFGuildSettings guildSettings = sGuildFinderMgr->GetGuildSettings(itr->GetGuildId());
            MembershipRequest request = *itr;

            ObjectGuid guildGuid = ObjectGuid(guild->GetGUID());

            data.WriteBit(guildGuid[6]);
            data.WriteBit(guildGuid[2]);
            data.WriteBits(guild->GetName().size(), 8);
            data.WriteBit(guildGuid[4]);
            data.WriteBit(guildGuid[3]);
            data.WriteBit(guildGuid[5]);
            data.WriteBits(request.GetComment().size(), 11);
            data.WriteBit(guildGuid[7]);
            data.WriteBit(guildGuid[0]);
            data.WriteBit(guildGuid[1]);

            bufferData.WriteByteSeq(guildGuid[5]);
            bufferData.WriteByteSeq(guildGuid[7]);
            bufferData.WriteString(guild->GetName());
            bufferData.WriteByteSeq(guildGuid[1]);
            bufferData.WriteByteSeq(guildGuid[6]);
            bufferData << uint32(request.GetExpiryTime() - time(NULL)); // Time left to application expiry (seconds)
            bufferData.WriteString(request.GetComment());
            bufferData << uint32(time(NULL) - request.GetSubmitTime()); // Time since application (seconds)
            bufferData.WriteByteSeq(guildGuid[0]);
            bufferData << uint32(guildSettings.GetClassRoles());
            bufferData << uint32(guildSettings.GetInterests());
            bufferData << uint32(guildSettings.GetAvailability());
            bufferData.WriteByteSeq(guildGuid[2]);
            bufferData.WriteByteSeq(guildGuid[3]);
            bufferData.WriteByteSeq(guildGuid[4]);
        }

        data.FlushBits();
        data.append(bufferData);
    }

    GetPlayer()->SendDirectMessage(&data);
}

// Lists all recruits for a guild - Misses times
void WorldSession::HandleGuildFinderGetRecruits(WorldPacket& recvPacket)
{
    sLog->outDebug(LOG_FILTER_NETWORKIO, "WORLD: Received CMSG_LF_GUILD_GET_RECRUITS");

    uint32 unkTime = 0;
    //recvPacket >> unkTime;

    Player* player = GetPlayer();
    if (!player->GetGuildId())
        return;

    std::vector<MembershipRequest> recruitsList = sGuildFinderMgr->GetAllMembershipRequestsForGuild(player->GetGuildId());
    uint32 recruitCount = recruitsList.size();

    ByteBuffer dataBuffer(53 * recruitCount);
    WorldPacket data(SMSG_LF_GUILD_RECRUIT_LIST_UPDATED, 7 + 26 * recruitCount + 53 * recruitCount);
    data.WriteBits(recruitCount, 20);

    for (std::vector<MembershipRequest>::const_iterator itr = recruitsList.begin(); itr != recruitsList.end(); ++itr)
    {
        MembershipRequest request = *itr;
        ObjectGuid playerGuid(MAKE_NEW_GUID(request.GetPlayerGUID(), 0, HIGHGUID_PLAYER));
        
        data.WriteBit(playerGuid[1]);
        data.WriteBit(playerGuid[4]);
        data.WriteBit(playerGuid[2]);
        data.WriteBit(playerGuid[6]);
        data.WriteBits(request.GetName().size(), 7);
        data.WriteBit(playerGuid[3]);
        data.WriteBit(playerGuid[7]);
        data.WriteBit(playerGuid[5]);
        data.WriteBits(request.GetComment().size(), 11);
        data.WriteBit(playerGuid[0]);
        
        dataBuffer << int32(request.GetAvailability());
        dataBuffer.WriteByteSeq(playerGuid[1]);
        dataBuffer << int32(time(NULL) <= request.GetExpiryTime());
        dataBuffer << int32(request.GetInterests());
        dataBuffer << int32(request.GetClassRoles());
        dataBuffer << int32(time(NULL) - request.GetSubmitTime()); // Time in seconds since application submitted.
        dataBuffer.WriteString(request.GetName());
        dataBuffer.WriteByteSeq(playerGuid[4]);
        dataBuffer.WriteByteSeq(playerGuid[6]);
        dataBuffer.WriteByteSeq(playerGuid[3]);
        dataBuffer.WriteByteSeq(playerGuid[7]);
        dataBuffer.WriteString(request.GetComment());
        dataBuffer << int32(request.GetLevel());
        dataBuffer << int32(request.GetExpiryTime() - time(NULL)); // TIme in seconds until application expires.
        dataBuffer.WriteByteSeq(playerGuid[2]);
        dataBuffer.WriteByteSeq(playerGuid[0]);
        dataBuffer << int32(request.GetClass());
        dataBuffer.WriteByteSeq(playerGuid[5]);
    }

    data.FlushBits();
    data.append(dataBuffer);
    data << uint32(time(NULL)); // Unk time

    player->SendDirectMessage(&data);
}

void WorldSession::HandleGuildFinderPostRequest(WorldPacket& recvPacket)
{
    sLog->outDebug(LOG_FILTER_NETWORKIO, "WORLD: Received CMSG_LF_GUILD_POST_REQUEST"); // Empty opcode

    Player* player = GetPlayer();

    if (!player->GetGuildId()) // Player must be in guild
        return;

    bool isGuildMaster = true;
    if (Guild* guild = sGuildMgr->GetGuildById(player->GetGuildId()))
        if (guild->GetLeaderGUID() != player->GetGUID())
            isGuildMaster = false;

    LFGuildSettings settings = sGuildFinderMgr->GetGuildSettings(player->GetGuildId());

    WorldPacket data(SMSG_LF_GUILD_POST_UPDATED, 35);
    data.WriteBit(isGuildMaster); // Guessed

    if (isGuildMaster)
    {
        data.WriteBit(settings.IsListed());
        data.WriteBits(settings.GetComment().size(), 11);
        data << uint32(settings.GetLevel());
        data << uint32(0); // Unk Int32
        data << uint32(settings.GetAvailability());
        data.WriteString(settings.GetComment());
        data << uint32(settings.GetClassRoles());
        data << uint32(settings.GetInterests());
    }
    else
        data.FlushBits();
    player->SendDirectMessage(&data);
}

void WorldSession::HandleGuildFinderRemoveRecruit(WorldPacket& recvPacket)
{
    sLog->outDebug(LOG_FILTER_NETWORKIO, "WORLD: Received CMSG_LF_GUILD_REMOVE_RECRUIT");

    ObjectGuid guildGuid;

    uint8 bitOrder[8] = {3, 7, 4, 2, 6, 1, 0, 5};
    recvPacket.ReadBitInOrder(guildGuid, bitOrder);

    uint8 byteOrder[8] = {6, 2, 7, 1, 5, 4, 0, 3};
    recvPacket.ReadBytesSeq(guildGuid, byteOrder);

    if (!IS_GUILD_GUID(guildGuid))
        return;

    sGuildFinderMgr->RemoveMembershipRequest(GetPlayer()->GetGUIDLow(), GUID_LOPART(guildGuid));
}

// Sent any time a guild master sets an option in the interface and when listing / unlisting his guild
void WorldSession::HandleGuildFinderSetGuildPost(WorldPacket& recvPacket)
{
    sLog->outDebug(LOG_FILTER_NETWORKIO, "WORLD: Received CMSG_LF_GUILD_SET_GUILD_POST");

    uint32 classRoles = 0;
    uint32 availability = 0;
    uint32 guildInterests =  0;
    uint32 level = 0;

    recvPacket >> guildInterests >> availability >> level >> classRoles;
    bool listed = recvPacket.ReadBit();
    // Level sent is zero if untouched, force to any (from interface). Idk why
    if (!level)
        level = ANY_FINDER_LEVEL;

    uint16 length = recvPacket.ReadBits(11);
    std::string comment = recvPacket.ReadString(length);

    if (!(classRoles & GUILDFINDER_ALL_ROLES) || classRoles > GUILDFINDER_ALL_ROLES)
        return;
    if (!(availability & ALL_WEEK) || availability > ALL_WEEK)
        return;
    if (!(guildInterests & ALL_INTERESTS) || guildInterests > ALL_INTERESTS)
        return;
    if (!(level & ALL_GUILDFINDER_LEVELS) || level > ALL_GUILDFINDER_LEVELS)
        return;

    Player* player = GetPlayer();

    if (!player->GetGuildId()) // Player must be in guild
        return;

    if (Guild* guild = sGuildMgr->GetGuildById(player->GetGuildId())) // Player must be guild master
        if (guild->GetLeaderGUID() != player->GetGUID())
            return;

    LFGuildSettings settings(listed, player->GetTeamId(), player->GetGuildId(), classRoles, availability, guildInterests, level, comment);
    sGuildFinderMgr->SetGuildSettings(player->GetGuildId(), settings);
}