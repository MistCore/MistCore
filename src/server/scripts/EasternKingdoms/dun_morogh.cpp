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

#include "ScriptedEscortAI.h"
#include "Vehicle.h"

/*######
## npc_gnomeregan_survivor
######*/

class npc_gnomeregan_survivor : public CreatureScript
{
public:
    npc_gnomeregan_survivor() : CreatureScript("npc_gnomeregan_survivor") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_gnomeregan_survivorAI (creature);
    }

    struct npc_gnomeregan_survivorAI : public ScriptedAI
    {
        npc_gnomeregan_survivorAI(Creature* creature) : ScriptedAI(creature) {}
        
        void Reset() {}

        void SpellHit(Unit* Caster, const SpellInfo* Spell)
        {
            if (Spell->Id == 86264)
            {
                if (Caster->ToPlayer())
                    Caster->ToPlayer()->KilledMonsterCredit(46268, 0);

                me->ForcedDespawn(1000);
                me->SetRespawnDelay(15);
            }
        }
    };
};

/*######
## npc_flying_target_machin
######*/

class npc_flying_target_machin : public CreatureScript
{
public:
    npc_flying_target_machin() : CreatureScript("npc_flying_target_machin") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_flying_target_machinAI (creature);
    }

    struct npc_flying_target_machinAI : public ScriptedAI
    {
        npc_flying_target_machinAI(Creature* creature) : ScriptedAI(creature) {}

        void Reset()
        {
            me->SetSpeed(MOVE_FLIGHT, 0.5f);
        }

        void EnterCombat(Unit* /*who*/)
        {
            return;
        }
    };
};

/*######
## npc_carvo_blastbolt
######*/

#define QUEST_WITHDRAW_TO_THE_LOADING_ROOM  28169
#define NPC_IMUN_AGENT                      47836

class npc_carvo_blastbolt : public CreatureScript
{
public:
    npc_carvo_blastbolt() : CreatureScript("npc_carvo_blastbolt") { }

    bool OnQuestAccept(Player* player, Creature* creature, Quest const* quest)
    {
        if (quest->GetQuestId() == QUEST_WITHDRAW_TO_THE_LOADING_ROOM)
            Creature * imunAgent = creature->SummonCreature(NPC_IMUN_AGENT, -4985.93f, 776.91f, 288.48f, 3.06f, TEMPSUMMON_MANUAL_DESPAWN, 0, player->GetGUID());

        return true;
    }
};

/*######
## npc_imun_agent_escort
######*/

class npc_imun_agent_escort : public CreatureScript
{
public:
    npc_imun_agent_escort() : CreatureScript("npc_imun_agent_escort") { }

    struct npc_imun_agent_escortAI : public npc_escortAI
    {
        npc_imun_agent_escortAI(Creature* creature) : npc_escortAI(creature){}

        uint32 IntroTimer;

        void Reset()
        {
            IntroTimer = 2500;
            SetEscortPaused(true);
        }

        void WaypointReached(uint32 waypointId)
        {
            /*if (waypointId == 10)
                Playemote garde a vous*/
        }

        void UpdateAI(const uint32 diff)
        {
            if (IntroTimer)
            {
                if (IntroTimer <= diff)
                {
                    IntroTimer = 0;
                    Start(false, false);
                }
                else
                    IntroTimer -= diff;
            }

            npc_escortAI::UpdateAI(diff);
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_imun_agent_escortAI(creature);
    }
};

/*######
## npc_sanitron
######*/

#define SPELL_IRRADIE   80653

class npc_sanitron : public CreatureScript
{
public:
    npc_sanitron() : CreatureScript("npc_sanitron") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_sanitronAI (creature);
    }

    struct npc_sanitronAI : public ScriptedAI
    {
        npc_sanitronAI(Creature* creature) : ScriptedAI(creature) {}

        uint32 timer;
        uint8 phase;
        Unit* Passenger;
        
        void Reset()
        {
            timer = 0;
            phase = 0;
            Passenger = NULL;
            me->SetWalk(true);
        }

        void PassengerBoarded(Unit* who, int8 seatId, bool apply)
        {
            timer = 3000;
            phase = 1;
            Passenger = who;
        }

        void MovementInform(uint32 type, uint32 id)
        {
            switch (id)
            {
                case 1:
                    timer = 2000;
                    ++phase;
                    break;
                case 2:
                {
                    timer = 5000;
                    ++phase;

                    std::list<Creature*> canonList;
                    GetCreatureListWithEntryInGrid(canonList, me, 46208, 50.0f);

                    for (auto canon : canonList)
                        canon->CastSpell(me, 1000, false);

                    if (Passenger->ToPlayer())
                        Passenger->ToPlayer()->AreaExploredOrEventHappens(27635); // Decontamination

                    break;
                }
                case 3:
                    timer = 1000;
                    ++phase;
                    me->MonsterSay("Probleme technique, interruption de la sequence", 0, 0);
                    break;
            }
        }

        void UpdateAI(const uint32 diff)
        {
            if (!timer || !phase)
                return;

            if (timer > diff)
            {
                timer -= diff;
                return;
            }
            
            timer = 0;

            switch(phase)
            {
                case 1:
                    me->GetMotionMaster()->MovePoint(1, -5173.5f, 725.193f, 293.668f);
                    break;
                case 2:
                    me->GetMotionMaster()->MovePoint(2, -5173.97f, 716.153f, 293.668f);
                    break;
                case 3:
                    Passenger->RemoveAurasDueToSpell(SPELL_IRRADIE);
                    me->GetMotionMaster()->MovePoint(3, -5175.65f, 699.32f, 293.668f);
                    break;
                case 4:
                    me->Kill(me);
                    me->SetRemoveCorpseDelay(1000);
                    me->SetRespawnDelay(5);
                    break;
            }
        }
    };
};

/*######
## npc_canon_propre
######*/

class npc_canon_propre : public CreatureScript
{
public:
    npc_canon_propre() : CreatureScript("npc_canon_propre") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_canon_propreAI (creature);
    }

    struct npc_canon_propreAI : public ScriptedAI
    {
        npc_canon_propreAI(Creature* creature) : ScriptedAI(creature) {}

        bool hasPassenger;

        void Reset()
        {
            hasPassenger = false;
        }

        void UpdateAI(const uint32 diff)
        {
            if (hasPassenger)
                return;

            if (Creature* imunAgent = me->FindNearestCreature(45847, 10.0f))
            {
                if (me->GetVehicleKit())
                {
                    hasPassenger = true;
                    me->GetVehicleKit()->AddPassenger(imunAgent);
                }
            }
        }
    };
};

/*######
## npc_carvo_blastbolt
######*/

#define GOSSIP_TEXT "Envoyez moi a la surface, Torben !"

class npc_gnomeregan_torben : public CreatureScript
{
public:
    npc_gnomeregan_torben() : CreatureScript("npc_gnomeregan_torben") { }

    bool OnGossipHello(Player* player, Creature* creature)
    {
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
        player->SEND_GOSSIP_MENU(1, creature->GetGUID());

        return true;
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 /*sender*/, uint32 action)
    {
        player->PlayerTalkClass->ClearMenus();
        if (action == GOSSIP_ACTION_INFO_DEF+1)
        {
            player->TeleportTo(0, -5201.58f, 477.98f, 388.47f, 5.13f);
            player->PlayerTalkClass->SendCloseGossip();
        }
        return true;
    }
};

/*######
## npc_gnomeregan_recrue
######*/

class npc_gnomeregan_recrue : public CreatureScript
{
public:
    npc_gnomeregan_recrue() : CreatureScript("npc_gnomeregan_recrue") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_gnomeregan_recrueAI (creature);
    }

    struct npc_gnomeregan_recrueAI : public ScriptedAI
    {
        npc_gnomeregan_recrueAI(Creature* creature) : ScriptedAI(creature) {}

        bool hasTarget;

        void Reset()
        {
            hasTarget = false;
        }

        void DamageTaken(Unit* doneBy, uint32& damage)
        {
            if (doneBy->ToCreature())
                if (me->GetHealth() <= damage || me->GetHealthPct() <= 80.0f)
                    damage = 0;
        }

        void DamageDealt(Unit* target, uint32& damage, DamageEffectType damageType)
        {
            if (target->ToCreature())
                if (target->GetHealth() <= damage || target->GetHealthPct() <= 70.0f)
                    damage = 0;
        }

        void UpdateAI(const uint32 diff)
        {
            if (hasTarget)
            {
                DoMeleeAttackIfReady();
                return;
            }

            float x = 0, y = 0;
            GetPositionWithDistInOrientation(me, 2.5f, me->GetOrientation(), x, y);

            if (Creature* LivingInfection = me->SummonCreature(42185, x, y, me->GetPositionZ()))
            {
                LivingInfection->setFaction(16);
                LivingInfection->SetFacingToObject(me);
                LivingInfection->Attack(me, true);
                hasTarget = true;
            }
        }
    };
};

void AddSC_dun_morogh()
{
    new npc_gnomeregan_survivor();
    new npc_flying_target_machin();
    new npc_carvo_blastbolt();
    new npc_imun_agent_escort();
    new npc_sanitron();
    new npc_canon_propre();
    new npc_gnomeregan_torben();
    new npc_gnomeregan_recrue();
}
