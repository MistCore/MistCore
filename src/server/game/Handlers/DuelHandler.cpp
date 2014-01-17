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
#include "WorldSession.h"
#include "Log.h"
#include "Opcodes.h"
#include "UpdateData.h"
#include "Player.h"
#include "SocialMgr.h"
#include "ScriptMgr.h"
#include "GameObject.h"
#include "ObjectAccessor.h"
#include "ObjectMgr.h"

void WorldSession::HandleSendDuelRequest(WorldPacket& recvPacket)
{
    ObjectGuid guid;

    uint8 bitOrder[8] = {2, 7, 0, 5, 6, 3, 1, 4};
    recvPacket.ReadBitInOrder(guid, bitOrder);
    
    uint8 byteOrder[8] = {3, 4, 1, 5, 0, 2, 7, 6};
    recvPacket.ReadBytesSeq(guid, byteOrder);

    Player* caster = GetPlayer();
    Unit* unitTarget = NULL;

    unitTarget = sObjectAccessor->GetUnit(*caster, guid);

    if (!unitTarget || caster->GetTypeId() != TYPEID_PLAYER || unitTarget->GetTypeId() != TYPEID_PLAYER)
        return;
    Player* target = unitTarget->ToPlayer();
    // caster or target already have requested duel
    if (caster->duel || target->duel || !target->GetSocial() || target->GetSocial()->HasIgnore(caster->GetGUIDLow()))
        return;
    caster->CastSpell(unitTarget, 7266, false);
    // Players can only fight a duel in zones with this flag
    /*AreaTableEntry const* casterAreaEntry = GetAreaEntryByAreaID(caster->GetAreaId());
    if (casterAreaEntry && !(casterAreaEntry->flags & AREA_FLAG_ALLOW_DUELS))
    {
        //SendCastResult(SPELL_FAILED_NO_DUELING);            // Dueling isn't allowed here
        return;
    }

    AreaTableEntry const* targetAreaEntry = GetAreaEntryByAreaID(target->GetAreaId());
    if (targetAreaEntry && !(targetAreaEntry->flags & AREA_FLAG_ALLOW_DUELS))
    {
        //SendCastResult(SPELL_FAILED_NO_DUELING);            // Dueling isn't allowed here
        return;
    }

    //CREATE DUEL FLAG OBJECT
    GameObject* pGameObj = new GameObject;

    uint32 gameobject_id = 21680;//m_spellInfo->Effects[effIndex].MiscValue;

    Map* map = caster->GetMap();
    if (!pGameObj->Create(sObjectMgr->GenerateLowGuid(HIGHGUID_GAMEOBJECT), gameobject_id,
        map, caster->GetPhaseMask(),
        caster->GetPositionX()+(unitTarget->GetPositionX()-caster->GetPositionX())/2,
        caster->GetPositionY()+(unitTarget->GetPositionY()-caster->GetPositionY())/2,
        caster->GetPositionZ(),
        caster->GetOrientation(), 0.0f, 0.0f, 0.0f, 0.0f, 0, GO_STATE_READY))
    {
        delete pGameObj;
        return;
    }

    pGameObj->SetUInt32Value(GAMEOBJECT_FACTION, caster->getFaction());
    pGameObj->SetUInt32Value(GAMEOBJECT_LEVEL, caster->getLevel()+1);
    pGameObj->SetRespawnTime(0);

    caster->AddGameObject(pGameObj);
    map->AddToMap(pGameObj);
    //END

    // Send request
    WorldPacket data(SMSG_DUEL_REQUESTED, 8 + 8);
    data << uint64(pGameObj->GetGUID());
    data << uint64(caster->GetGUID());
    caster->GetSession()->SendPacket(&data);
    target->GetSession()->SendPacket(&data);

    // create duel-info
    DuelInfo* duel   = new DuelInfo;
    duel->initiator  = caster;
    duel->opponent   = target;
    duel->startTime  = 0;
    duel->startTimer = 0;
    duel->isMounted  = 0;//(GetSpellInfo()->Id == 62875); // Mounted Duel
    caster->duel     = duel;

    DuelInfo* duel2   = new DuelInfo;
    duel2->initiator  = caster;
    duel2->opponent   = caster;
    duel2->startTime  = 0;
    duel2->startTimer = 0;
    duel2->isMounted  = 0;//(GetSpellInfo()->Id == 62875); // Mounted Duel
    target->duel      = duel2;

    caster->SetUInt64Value(PLAYER_DUEL_ARBITER, pGameObj->GetGUID());
    target->SetUInt64Value(PLAYER_DUEL_ARBITER, pGameObj->GetGUID());

    sScriptMgr->OnPlayerDuelRequest(target, caster);*/
}

void WorldSession::HandleDuelAcceptedOpcode(WorldPacket& recvPacket)
{
    uint64 guid;
    Player* player;
    Player* plTarget;

    recvPacket >> guid;

    if (!GetPlayer()->duel)                                  // ignore accept from duel-sender
        return;

    player       = GetPlayer();
    plTarget = player->duel->opponent;

    if (player == player->duel->initiator || !plTarget || player == plTarget || player->duel->startTime != 0 || plTarget->duel->startTime != 0)
        return;

    //sLog->outDebug(LOG_FILTER_PACKETIO, "WORLD: Received CMSG_DUEL_ACCEPTED");
    sLog->outDebug(LOG_FILTER_NETWORKIO, "Player 1 is: %u (%s)", player->GetGUIDLow(), player->GetName());
    sLog->outDebug(LOG_FILTER_NETWORKIO, "Player 2 is: %u (%s)", plTarget->GetGUIDLow(), plTarget->GetName());

    time_t now = time(NULL);
    player->duel->startTimer = now;
    plTarget->duel->startTimer = now;

    player->SendDuelCountdown(3000);
    plTarget->SendDuelCountdown(3000);
}

void WorldSession::HandleDuelCancelledOpcode(WorldPacket& recvPacket)
{
    sLog->outDebug(LOG_FILTER_NETWORKIO, "WORLD: Received CMSG_DUEL_CANCELLED");
    uint64 guid;
    recvPacket >> guid;

    // no duel requested
    if (!GetPlayer()->duel)
        return;

    // player surrendered in a duel using /forfeit
    if (GetPlayer()->duel->startTime != 0)
    {
        GetPlayer()->CombatStopWithPets(true);
        if (GetPlayer()->duel->opponent)
            GetPlayer()->duel->opponent->CombatStopWithPets(true);

        GetPlayer()->CastSpell(GetPlayer(), 7267, true);    // beg
        GetPlayer()->DuelComplete(DUEL_WON);
        return;
    }

    GetPlayer()->DuelComplete(DUEL_INTERRUPTED);
}
