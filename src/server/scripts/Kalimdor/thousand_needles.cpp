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
SDName: Thousand Needles
SD%Complete: 0
SDComment: Support for Quest:
SDCategory: Thousand Needles
EndScriptData */

/* ContentData
EndContentData */

#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "ScriptedGossip.h"
#include "ScriptedEscortAI.h"

class npc_pao_ka_swiftmountain : public CreatureScript
{
    public:
        npc_pao_ka_swiftmountain() : CreatureScript("npc_pao_ka_swiftmountain")
        {
        }

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_pao_ka_swiftmountainAI(creature);
        }

        struct npc_pao_ka_swiftmountainAI : public ScriptedAI
        {
            npc_pao_ka_swiftmountainAI(Creature* creature) : ScriptedAI(creature)
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

class npc_kanati_greycloud : public CreatureScript
{
    public:
        npc_kanati_greycloud() : CreatureScript("npc_kanati_greycloud")
        {
        }

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_kanati_greycloudAI(creature);
        }

        struct npc_kanati_greycloudAI : public ScriptedAI
        {
            npc_kanati_greycloudAI(Creature* creature) : ScriptedAI(creature)
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

class npc_lakota_windsong : public CreatureScript
{
    public:
        npc_lakota_windsong() : CreatureScript("npc_lakota_windsong")
        {
        }

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_lakota_windsongAI(creature);
        }

        struct npc_lakota_windsongAI : public ScriptedAI
        {
            npc_lakota_windsongAI(Creature* creature) : ScriptedAI(creature)
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

void AddSC_thousand_needles()
{
    new npc_lakota_windsong();
    new npc_kanati_greycloud();
    new npc_pao_ka_swiftmountain();
}
