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
#include "DatabaseEnv.h"
#include "Opcodes.h"
#include "Log.h"
#include "Player.h"
#include "WorldPacket.h"
#include "WorldSession.h"
#include "ObjectAccessor.h"
#include "UpdateMask.h"

void WorldSession::HandleSetSpecialization(WorldPacket& recvData)
{
    uint32 tab = recvData.read<uint32>();
    uint8 classId = _player->getClass();

    // Avoid cheat - hack
    if(_player->GetSpecializationId(_player->GetActiveSpec()))
        return;

    uint32 specializationId = 0;
    uint32 specializationSpell = 0;

    for (uint32 i = 0; i < sChrSpecializationsStore.GetNumRows(); i++)
    {
        ChrSpecializationsEntry const* specialization = sChrSpecializationsStore.LookupEntry(i);
        if (!specialization)
            continue;

        if (specialization->classId == classId && specialization->tabId == tab)
        {
            specializationId = specialization->entry;
            specializationSpell = specialization->specializationSpell;
            break;
        }
    }

    if (specializationId)
    {
        _player->SetSpecializationId(_player->GetActiveSpec(), specializationId);
        _player->SendTalentsInfoData(false);
        if (specializationSpell)
            _player->learnSpell(specializationSpell, false);
        _player->InitSpellForLevel();
        _player->UpdateMasteryPercentage();
    }
}

void WorldSession::HandleLearnTalents(WorldPacket& recvData)
{
    uint32 count = recvData.ReadBits(25);
    recvData.FlushBits();

    // Cheat - Hack check
    if (count > 6)
        return;

    if (count > _player->GetFreeTalentPoints())
        return;

    for (uint32 i = 0; i < count; i++)
    {
        uint16 talentId = recvData.read<uint16>();
        _player->LearnTalent(talentId);
    }

    _player->SendTalentsInfoData(false);
}

void WorldSession::HandleTalentWipeConfirmOpcode(WorldPacket& recvData)
{
    sLog->outDebug(LOG_FILTER_NETWORKIO, "MSG_TALENT_WIPE_CONFIRM");

    uint8 specializationReset = recvData.read<uint8>();

    recvData.rfinish();
    // remove fake death
    if (GetPlayer()->HasUnitState(UNIT_STATE_DIED))
        GetPlayer()->RemoveAurasByType(SPELL_AURA_FEIGN_DEATH);

    if(!specializationReset)
    {
        if (!_player->ResetTalents())
        {
            WorldPacket data(SMSG_RESPEC_WIPE_CONFIRM, 8+4);    //you have not any talent
            data << uint8(0); // 0 guid bit
            data << uint8(0);
            data << uint32(0);
            SendPacket(&data);
            return;
        }
    }
    else
    {
        _player->ResetSpec();
    }

    _player->SendTalentsInfoData(false);

    if(Unit* unit = _player->GetSelectedUnit())
        unit->CastSpell(_player, 14867, true);                  //spell: "Untalent Visual Effect"
}

void WorldSession::HandleUnlearnSkillOpcode(WorldPacket& recvData)
{
    uint32 skillId;
    recvData >> skillId;

    if (!IsPrimaryProfessionSkill(skillId))
        return;

    GetPlayer()->SetSkill(skillId, 0, 0, 0);
}
