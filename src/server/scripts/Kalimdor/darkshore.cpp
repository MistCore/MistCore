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
SDName: Darkshore
SD%Complete: 0
SDComment: Quest support:
SDCategory: Darkshore
EndScriptData */

/* ContentData
EndContentData */

#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "ScriptedGossip.h"
#include "ScriptedEscortAI.h"
#include "ScriptedFollowerAI.h"

class npc_prospector_remtravel : public CreatureScript
{
    public:
        npc_prospector_remtravel() : CreatureScript("npc_prospector_remtravel")
        {
        }

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_prospector_remtravelAI(creature);
        }

        struct npc_prospector_remtravelAI : public ScriptedAI
        {
            npc_prospector_remtravelAI(Creature* creature) : ScriptedAI(creature)
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

void AddSC_darkshore()
{
    new npc_prospector_remtravel();
}
