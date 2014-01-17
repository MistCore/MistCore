/*
 * Copyright (C) 2008-2012 TrinityCore <http://www.trinitycore.org/>
 * Copyright (C) 2005-2009 MaNGOS <http://getmangos.com/>
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

#include "Common.h"
#include "WorldPacket.h"
#include "Log.h"
#include "Corpse.h"
#include "GameObject.h"
#include "Player.h"
#include "ObjectAccessor.h"
#include "WorldSession.h"
#include "LootMgr.h"
#include "Object.h"
#include "Group.h"
#include "World.h"
#include "Util.h"
#include "GuildMgr.h"

void WorldSession::HandleAutostoreLootItemOpcode(WorldPacket & recvData)
{
    sLog->outDebug(LOG_FILTER_NETWORKIO, "WORLD: CMSG_AUTOSTORE_LOOT_ITEM");
    Player* player = GetPlayer();
    uint64 lguid = player->GetLootGUID();
    Loot* loot = NULL;
    uint8 lootSlot = 0;

    uint32 count = recvData.ReadBits(25);
    ObjectGuid guids[8];

    uint8 bitOrder[8] = {4, 0, 2, 1, 5, 6, 7, 3};
    for (uint32 i = 0; i < count; i++)
        recvData.ReadBitInOrder(guids[i], bitOrder);

    recvData.FlushBits();

    uint8 byteOrder[8] = {2, 0, 5, 4, 6, 1, 3, 7};
    for (uint32 i = 0; i < count; i++)
    {
        recvData >> lootSlot;

        recvData.ReadBytesSeq(guids[i], byteOrder);

        if (IS_GAMEOBJECT_GUID(lguid))
        {
            GameObject* go = player->GetMap()->GetGameObject(lguid);

            // not check distance for GO in case owned GO (fishing bobber case, for example) or Fishing hole GO
            if (!go || ((go->GetOwnerGUID() != _player->GetGUID() && go->GetGoType() != GAMEOBJECT_TYPE_FISHINGHOLE) && !go->IsWithinDistInMap(_player, INTERACTION_DISTANCE)))
            {
                player->SendLootRelease(lguid);
                return;
            }

            loot = &go->loot;
        }
        else if (IS_ITEM_GUID(lguid))
        {
            Item* pItem = player->GetItemByGuid(lguid);

            if (!pItem)
            {
                player->SendLootRelease(lguid);
                return;
            }

            loot = &pItem->loot;
        }
        else if (IS_CORPSE_GUID(lguid))
        {
            Corpse* bones = ObjectAccessor::GetCorpse(*player, lguid);
            if (!bones)
            {
                player->SendLootRelease(lguid);
                return;
            }

            loot = &bones->loot;
        }
        else
        {
            Creature* creature = GetPlayer()->GetMap()->GetCreature(lguid);

            bool lootAllowed = creature && creature->isAlive() == (player->getClass() == CLASS_ROGUE && creature->lootForPickPocketed);

            if (!lootAllowed || (!creature->IsWithinDistInMap(_player, INTERACTION_DISTANCE) && !_player->HasSpell(125048)))
            {
                player->SendLootRelease(lguid);
                return;
            }

            loot = &creature->loot;
        }

        player->StoreLootItem(lootSlot, loot);
    }
}

void WorldSession::HandleLootMoneyOpcode(WorldPacket& /*recvData*/)
{
    sLog->outDebug(LOG_FILTER_NETWORKIO, "WORLD: CMSG_LOOT_MONEY");

    Player* player = GetPlayer();
    uint64 guid = player->GetLootGUID();
    if (!guid)
        return;

    Loot* loot = NULL;
    bool shareMoney = true;

    switch (GUID_HIPART(guid))
    {
        case HIGHGUID_GAMEOBJECT:
        {
            GameObject* go = GetPlayer()->GetMap()->GetGameObject(guid);

            // do not check distance for GO if player is the owner of it (ex. fishing bobber)
            if (go && ((go->GetOwnerGUID() == player->GetGUID() || go->IsWithinDistInMap(player, INTERACTION_DISTANCE))))
                loot = &go->loot;

            break;
        }
        case HIGHGUID_CORPSE:                               // remove insignia ONLY in BG
        {
            Corpse* bones = ObjectAccessor::GetCorpse(*player, guid);

            if (bones && bones->IsWithinDistInMap(player, INTERACTION_DISTANCE))
            {
                loot = &bones->loot;
                shareMoney = false;
            }

            break;
        }
        case HIGHGUID_ITEM:
        {
            if (Item* item = player->GetItemByGuid(guid))
            {
                loot = &item->loot;
                shareMoney = false;
            }
            break;
        }
        case HIGHGUID_UNIT:
        case HIGHGUID_VEHICLE:
        {
            Creature* creature = player->GetMap()->GetCreature(guid);
            bool lootAllowed = creature && creature->isAlive() == (player->getClass() == CLASS_ROGUE && creature->lootForPickPocketed);
            if (lootAllowed && creature->IsWithinDistInMap(player, INTERACTION_DISTANCE))
            {
                loot = &creature->loot;
                if (creature->isAlive())
                    shareMoney = false;
            }
            break;
        }
        default:
            return;                                         // unlootable type
    }

    if (loot)
    {
        if (shareMoney && player->GetGroup())      //item, pickpocket and players can be looted only single player
        {
            Group* group = player->GetGroup();

            std::vector<Player*> playersNear;
            for (GroupReference* itr = group->GetFirstMember(); itr != NULL; itr = itr->next())
            {
                Player* member = itr->getSource();
                if (!member)
                    continue;

                if (player->IsWithinDistInMap(member, sWorld->getFloatConfig(CONFIG_GROUP_XP_DISTANCE), false))
                    playersNear.push_back(member);
            }
             /*@todo: check me for 5.0.5*/
            uint32 goldPerPlayer = uint32((loot->gold) / (playersNear.size()));
            
            loot->NotifyMoneyRemoved(goldPerPlayer);
            for (std::vector<Player*>::const_iterator i = playersNear.begin(); i != playersNear.end(); ++i)
            {
                (*i)->ModifyMoney(goldPerPlayer);
                (*i)->UpdateAchievementCriteria(ACHIEVEMENT_CRITERIA_TYPE_LOOT_MONEY, goldPerPlayer);

                if (Guild* guild = sGuildMgr->GetGuildById((*i)->GetGuildId()))
                    if (uint32 guildGold = CalculatePct(goldPerPlayer, (*i)->GetTotalAuraModifier(SPELL_AURA_DEPOSIT_BONUS_MONEY_IN_GUILD_BANK_ON_LOOT)))
                        guild->HandleMemberDepositMoney(this, guildGold, true);

                WorldPacket data(SMSG_LOOT_MONEY_NOTIFY, 4 + 1);
                data.WriteBit(playersNear.size() <= 1); // Controls the text displayed in chat. 0 is "Your share is..." and 1 is "You loot..."
                data << uint32(goldPerPlayer);
                (*i)->GetSession()->SendPacket(&data);
            }
        }
        else
        {
            player->ModifyMoney(loot->gold);
            player->UpdateAchievementCriteria(ACHIEVEMENT_CRITERIA_TYPE_LOOT_MONEY, loot->gold);

            if (Guild* guild = sGuildMgr->GetGuildById(player->GetGuildId()))
                if (uint32 guildGold = CalculatePct(loot->gold, player->GetTotalAuraModifier(SPELL_AURA_DEPOSIT_BONUS_MONEY_IN_GUILD_BANK_ON_LOOT)))
                    guild->HandleMemberDepositMoney(this, guildGold, true);

            loot->NotifyMoneyRemoved(loot->gold);
            WorldPacket data(SMSG_LOOT_MONEY_NOTIFY, 4 + 1);
            data.WriteBit(1);   // "You loot..."
            data << uint32(loot->gold);
            SendPacket(&data);
        }

        loot->gold = 0;
    }
}

void WorldSession::HandleLootOpcode(WorldPacket & recvData)
{
    sLog->outDebug(LOG_FILTER_NETWORKIO, "WORLD: CMSG_LOOT");

    ObjectGuid guid;
    
    uint8 bitOrder[8] = {0, 3, 1, 7, 6, 4, 2, 5};
    recvData.ReadBitInOrder(guid, bitOrder);

    uint8 byteOrder[8] = {0, 1, 4, 2, 3, 7, 6, 5};
    recvData.ReadBytesSeq(guid, byteOrder);

    // Check possible cheat
    if (!_player->isAlive())
        return;

    GetPlayer()->SendLoot(guid, LOOT_CORPSE);

    // interrupt cast
    if (GetPlayer()->IsNonMeleeSpellCasted(false))
        GetPlayer()->InterruptNonMeleeSpells(false);
}

void WorldSession::HandleLootReleaseOpcode(WorldPacket& recvData)
{
    sLog->outDebug(LOG_FILTER_NETWORKIO, "WORLD: CMSG_LOOT_RELEASE");

    // cheaters can modify lguid to prevent correct apply loot release code and re-loot
    // use internal stored guid
    ObjectGuid guid;

    uint8 bitOrder[8] = {0, 4, 2, 5, 7, 3, 6, 1};
    recvData.ReadBitInOrder(guid, bitOrder);

    uint8 byteOrder[8] = {3, 5, 4, 2, 6, 1, 0, 7};
    recvData.ReadBytesSeq(guid, byteOrder);

    if (uint64 lguid = GetPlayer()->GetLootGUID())
        if (lguid == guid)
            DoLootRelease(lguid);
}

void WorldSession::DoLootRelease(uint64 lguid)
{
    Player  *player = GetPlayer();
    Loot    *loot;

    player->SetLootGUID(0);
    player->SendLootRelease(lguid);

    player->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_LOOTING);

    if (!player->IsInWorld())
        return;

    if (IS_GAMEOBJECT_GUID(lguid))
    {
        GameObject* go = GetPlayer()->GetMap()->GetGameObject(lguid);

        // not check distance for GO in case owned GO (fishing bobber case, for example) or Fishing hole GO
        if (!go || ((go->GetOwnerGUID() != _player->GetGUID() && go->GetGoType() != GAMEOBJECT_TYPE_FISHINGHOLE) && !go->IsWithinDistInMap(_player, INTERACTION_DISTANCE)))
            return;

        loot = &go->loot;

        if (go->GetGoType() == GAMEOBJECT_TYPE_DOOR)
        {
            // locked doors are opened with spelleffect openlock, prevent remove its as looted
            go->UseDoorOrButton();
        }
        else if (loot->isLooted() || go->GetGoType() == GAMEOBJECT_TYPE_FISHINGNODE)
        {
            if (go->GetGoType() == GAMEOBJECT_TYPE_FISHINGHOLE)
            {                                               // The fishing hole used once more
                go->AddUse();                               // if the max usage is reached, will be despawned in next tick

                if (go->GetUseCount() >= urand(go->GetGOInfo()->fishinghole.minSuccessOpens, go->GetGOInfo()->fishinghole.maxSuccessOpens))
                    go->SetLootState(GO_JUST_DEACTIVATED);
                else
                    go->SetLootState(GO_READY);
            }
            else
                go->SetLootState(GO_JUST_DEACTIVATED);

            loot->clear();
        }
        else
        {
            // not fully looted object
            go->SetLootState(GO_ACTIVATED, player);

            // if the round robin player release, reset it.
            if (player->GetGUID() == loot->roundRobinPlayer)
            {
                if (Group* group = player->GetGroup())
                {
                    if (group->GetLootMethod() != MASTER_LOOT)
                        loot->roundRobinPlayer = 0;
                }
                else
                    loot->roundRobinPlayer = 0;
            }
        }
    }
    else if (IS_CORPSE_GUID(lguid))        // ONLY remove insignia at BG
    {
        Corpse* corpse = ObjectAccessor::GetCorpse(*player, lguid);
        if (!corpse || !corpse->IsWithinDistInMap(_player, INTERACTION_DISTANCE))
            return;

        loot = &corpse->loot;

        if (loot->isLooted())
        {
            loot->clear();
            corpse->RemoveFlag(CORPSE_FIELD_DYNAMIC_FLAGS, CORPSE_DYNFLAG_LOOTABLE);
        }
    }
    else if (IS_ITEM_GUID(lguid))
    {
        Item* pItem = player->GetItemByGuid(lguid);
        if (!pItem)
            return;

        ItemTemplate const* proto = pItem->GetTemplate();

        // destroy only 5 items from stack in case prospecting and milling
        if (proto->Flags & (ITEM_PROTO_FLAG_PROSPECTABLE | ITEM_PROTO_FLAG_MILLABLE))
        {
            pItem->m_lootGenerated = false;
            pItem->loot.clear();

            uint32 count = pItem->GetCount();

            // >=5 checked in spell code, but will work for cheating cases also with removing from another stacks.
            if (count > 5)
                count = 5;

            player->DestroyItemCount(pItem, count, true);
        }
        else
            // FIXME: item must not be deleted in case not fully looted state. But this pre-request implement loot saving in DB at item save. Or cheating possible.
            player->DestroyItem(pItem->GetBagSlot(), pItem->GetSlot(), true);
        return;                                             // item can be looted only single player
    }
    else
    {
        Creature* creature = GetPlayer()->GetMap()->GetCreature(lguid);

        bool lootAllowed = creature && creature->isAlive() == (player->getClass() == CLASS_ROGUE && creature->lootForPickPocketed);
        if (!lootAllowed || !creature->IsWithinDistInMap(_player, INTERACTION_DISTANCE))
            return;

        loot = &creature->loot;
        if (loot->isLooted())
        {
            // skip pickpocketing loot for speed, skinning timer reduction is no-op in fact
            if (!creature->isAlive())
                creature->AllLootRemovedFromCorpse();

            creature->RemoveFlag(UNIT_DYNAMIC_FLAGS, UNIT_DYNFLAG_LOOTABLE);
            loot->clear();
        }
        else
        {
            // if the round robin player release, reset it.
            if (player->GetGUID() == loot->roundRobinPlayer)
            {
                if (Group* group = player->GetGroup())
                {
                    if (group->GetLootMethod() != MASTER_LOOT)
                    {
                        loot->roundRobinPlayer = 0;
                        group->SendLooter(creature, NULL);

                        // force update of dynamic flags, otherwise other group's players still not able to loot.
                        creature->ForceValuesUpdateAtIndex(UNIT_DYNAMIC_FLAGS);
                    }
                }
                else
                    loot->roundRobinPlayer = 0;
            }
        }
    }

    //Player is not looking at loot list, he doesn't need to see updates on the loot list
    loot->RemoveLooter(player->GetGUID());
}

void WorldSession::HandleLootMasterAskForRoll(WorldPacket& recvData)
{
    ObjectGuid guid = 0;
    uint8 slot = 0;

    recvData >> slot;

    uint8 bitOrder[8] = {4, 3, 7, 6, 5, 1, 0, 2};
    recvData.ReadBitInOrder(guid, bitOrder);

    uint8 byteOrder[8] = {4, 1, 0, 2, 5, 6, 7, 3};
    recvData.ReadBytesSeq(guid, byteOrder);

    if (!_player->GetGroup() || _player->GetGroup()->GetLooterGuid() != _player->GetGUID())
    {
        _player->SendLootRelease(GetPlayer()->GetLootGUID());
        return;
    }

    Loot* loot = NULL;

    if (IS_CRE_OR_VEH_GUID(GetPlayer()->GetLootGUID()))
    {
        Creature* creature = GetPlayer()->GetMap()->GetCreature(guid);
        if (!creature)
            return;

        loot = &creature->loot;
    }
    else if (IS_GAMEOBJECT_GUID(GetPlayer()->GetLootGUID()))
    {
        GameObject* pGO = GetPlayer()->GetMap()->GetGameObject(guid);
        if (!pGO)
            return;

        loot = &pGO->loot;
    }

    if (!loot || loot->alreadyAskedForRoll)
        return;

    if (slot >= loot->items.size() + loot->quest_items.size())
    {
        sLog->outDebug(LOG_FILTER_LOOT, "MasterLootItem: Player %s might be using a hack! (slot %d, size %lu)", GetPlayer()->GetName(), slot, (unsigned long)loot->items.size());
        return;
    }

    LootItem& item = slot >= loot->items.size() ? loot->quest_items[slot - loot->items.size()] : loot->items[slot];

    loot->alreadyAskedForRoll = true;

    _player->GetGroup()->DoRollForAllMembers(guid, slot, _player->GetMapId(), loot, item, _player);
}

void WorldSession::HandleLootMasterGiveOpcode(WorldPacket& recvData)
{
    ObjectGuid target_playerguid = 0;

    target_playerguid[6] = recvData.ReadBit();
    target_playerguid[2] = recvData.ReadBit();
    target_playerguid[1] = recvData.ReadBit();
    target_playerguid[3] = recvData.ReadBit();
    target_playerguid[7] = recvData.ReadBit();
    target_playerguid[5] = recvData.ReadBit();

    uint32 count = recvData.ReadBits(25);
    if (count > 40)
        return;

    std::vector<ObjectGuid> guids(count);
    std::vector<uint8> types(count);

    uint8 bitOrder[8] = {4, 6, 7, 5, 0, 1, 3, 2};
    for (uint32 i = 0; i < count; ++i)
        recvData.ReadBitInOrder(guids[i], bitOrder);
    
    target_playerguid[4] = recvData.ReadBit();
    target_playerguid[0] = recvData.ReadBit();
    recvData.FlushBits();

    uint8 byteOrder[8] = {6, 7, 3, 1, 0, 5, 4, 2};
    for (uint32 i = 0; i < count; ++i)
    {
        recvData.ReadBytesSeq(guids[i], byteOrder);
        recvData >> types[i];
    }

    uint8 byteOrder2[8] = {7, 0, 5, 6, 4, 3, 2, 1};
    recvData.ReadBytesSeq(target_playerguid, byteOrder2);
    //recvData >> lootguid >> slotid >> target_playerguid;

    if (!_player->GetGroup() || _player->GetGroup()->GetLooterGuid() != _player->GetGUID())
    {
        _player->SendLootRelease(GetPlayer()->GetLootGUID());
        return;
    }

    Player* target = ObjectAccessor::FindPlayer(MAKE_NEW_GUID(target_playerguid, 0, HIGHGUID_PLAYER));
    if (!target)
        return;

    sLog->outDebug(LOG_FILTER_NETWORKIO, "WorldSession::HandleLootMasterGiveOpcode (CMSG_LOOT_MASTER_GIVE, 0x02A3) Target = [%s].", target->GetName());

    for (uint32 i = 0; i < count; ++i)
    {
        ObjectGuid lootguid = guids[i];
        uint8 slotid = types[i];
        Loot* loot = NULL;

        if (IS_CRE_OR_VEH_GUID(GetPlayer()->GetLootGUID()))
        {
            Creature* creature = GetPlayer()->GetMap()->GetCreature(lootguid);
            if (!creature)
                return;

            loot = &creature->loot;
        }
        else if (IS_GAMEOBJECT_GUID(GetPlayer()->GetLootGUID()))
        {
            GameObject* pGO = GetPlayer()->GetMap()->GetGameObject(lootguid);
            if (!pGO)
                return;

            loot = &pGO->loot;
        }

        if (!loot)
            return;

        if (slotid >= loot->items.size() + loot->quest_items.size())
        {
            sLog->outDebug(LOG_FILTER_LOOT, "MasterLootItem: Player %s might be using a hack! (slot %d, size %lu)", GetPlayer()->GetName(), slotid, (unsigned long)loot->items.size());
            return;
        }

        LootItem& item = slotid >= loot->items.size() ? loot->quest_items[slotid - loot->items.size()] : loot->items[slotid];

        ItemPosCountVec dest;
        InventoryResult msg = target->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, item.itemid, item.count);
        if (item.follow_loot_rules && !item.AllowedForPlayer(target))
            msg = EQUIP_ERR_CANT_EQUIP_EVER;
        if (msg != EQUIP_ERR_OK)
        {
            target->SendEquipError(msg, NULL, NULL, item.itemid);
            // send duplicate of error massage to master looter
            _player->SendEquipError(msg, NULL, NULL, item.itemid);
            return;
        }

        // list of players allowed to receive this item in trade
        AllowedLooterSet looters = item.GetAllowedLooters();

        // not move item from loot to target inventory
        Item* newitem = target->StoreNewItem(dest, item.itemid, true, item.randomPropertyId, looters);
        target->SendNewItem(newitem, uint32(item.count), false, false, true);
        target->UpdateAchievementCriteria(ACHIEVEMENT_CRITERIA_TYPE_LOOT_ITEM, item.itemid, item.count);
        target->UpdateAchievementCriteria(ACHIEVEMENT_CRITERIA_TYPE_LOOT_TYPE, loot->loot_type, item.count);
        target->UpdateAchievementCriteria(ACHIEVEMENT_CRITERIA_TYPE_LOOT_EPIC_ITEM, item.itemid, item.count);

        // mark as looted
        item.count=0;
        item.is_looted=true;

        loot->NotifyItemRemoved(slotid);
        --loot->unlootedCount;
    }
}
