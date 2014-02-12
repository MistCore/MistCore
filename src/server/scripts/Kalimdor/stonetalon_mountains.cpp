/*
 * Copyright (C) 2008-2012 TrinityCore <http://www.trinitycore.org/>
 * Copyright (C) 2006-2009 ScriptDev2 <https://scriptdev2.svn.sourceforge.net/>
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

/* ScriptData
SDName: Stonetalon_Mountains
SD%Complete: 0
SDComment: Quest support:
SDCategory: Stonetalon Mountains
EndScriptData */

/* ContentData
EndContentData */

#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "ScriptedGossip.h"
#include "ScriptedEscortAI.h"

enum Rein
{
    KOBOLD_CREDIT   =   42024,
    KOBOLD_SERVANT  =   42026
};

class npc_subjugator_devo : public CreatureScript
{
public:
    npc_subjugator_devo() : CreatureScript("npc_subjugator_devo") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_subjugator_devoAI(creature);
    }

    struct npc_subjugator_devoAI : public ScriptedAI
    {
        npc_subjugator_devoAI(Creature* creature) : ScriptedAI(creature) {}

        void MoveInLineOfSight(Unit* who)
        {
            ScriptedAI::MoveInLineOfSight(who);

            if (who->GetEntry() == KOBOLD_SERVANT && me->IsWithinDistInMap(who, 10.0f))
            {
                if (Player* owner = who->GetOwner()->ToPlayer())
                {                    
                    if (owner->GetQuestStatus(26066) == QUEST_STATUS_INCOMPLETE)
                        owner->KilledMonsterCredit(KOBOLD_CREDIT,0);

                    who->ToCreature()->DespawnOrUnsummon();

                    if (owner->GetQuestStatus(26066) == QUEST_STATUS_COMPLETE)
                        owner->RemoveAllMinionsByEntry(KOBOLD_SERVANT);
                }                
            }
        }
    };
};

class npc_kaya_flathoof : public CreatureScript
{
    public:
        npc_kaya_flathoof() : CreatureScript("npc_kaya_flathoof")
        {
        }

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_kaya_flathoofAI(creature);
        }

        struct npc_kaya_flathoofAI : public ScriptedAI
        {
            npc_kaya_flathoofAI(Creature* creature) : ScriptedAI(creature)
            {
            }

            EventMap events;

            void Reset()
            {
                events.Reset();
            }

            void UpdateAI(const uint32 diff)
            {
            }
        };
};

void AddSC_stonetalon_mountains()
{
    new npc_kaya_flathoof();
    new npc_subjugator_devo();
}
