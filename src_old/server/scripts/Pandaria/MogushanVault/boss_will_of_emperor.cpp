/*
 * Copyright (C) 2012-2013 JadeCore <http://www.pandashan.com/>
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

#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "mogu_shan_vault.h"

enum eSpells
{
    // Jan Xi & Qin Xi
    SPELL_STOMP                 = 116969,
    SPELL_DEVASTATING_ARC       = 117006,
    SPELL_ARC_VISUAL            = 116968,
    SPELL_MAGNETIC_ARMOR        = 116815,

    SPELL_TITAN_GAS             = 116779,
    SPELL_OPPORTUNISTIC_STRIKE  = 116808,

    // Rage
    SPELL_FOCALISED_ASSAULT     = 116525,
    SPELL_WITHOUT_ARMOR         = 116535,

    // Courage
    SPELL_FOCALISED_DEFENSE     = 116778,
    SPELL_IMPEDING_THRUST       = 117485,
    SPELL_HALF_PLATE            = 116537,

    // Force
    SPELL_ENERGIZING_SMASH      = 116550,
    SPELL_FULL_PLATE            = 116540,

    // Titan Spark
    SPELL_SUMMON_TITAN_SPARK    = 117746,
    SPELL_FOCALISED_ENERGY      = 116829,
    SPELL_ENERGY_OF_CREATION    = 116805
};

enum eEvents
{
    // Jan & Qin
    EVENT_DEVASTATING_COMBO     = 1,
    EVENT_CHECK_MAGNETIC_ARMOR  = 2,

    // Shared
    EVENT_CHECK_TARGET          = 10,

    // Courage
    EVENT_IMPEDING_THRUST       = 12,
    
    // Strenght
    EVENT_ENERGIZING_SMASH      = 13,
};

enum eDevastatingComboPhase
{
    PHASE_NOT_STARTED           = 0,
};

class boss_jin_qin_xi : public CreatureScript
{
    public:
        boss_jin_qin_xi() : CreatureScript("boss_jin_qin_xi") {}

        struct boss_jin_qin_xiAI : public ScriptedAI
        {
            boss_jin_qin_xiAI(Creature* creature) : ScriptedAI(creature), summons(creature)
            {
                pInstance = creature->GetInstanceScript();
            }

            InstanceScript* pInstance;
            EventMap events;
            SummonList summons;

            uint8 devastatingComboPhase;
            uint64 victimWithMagneticArmor;

            std::list<Player*> playerList;

            void Reset()
            {
                if (!me->isAlive())
                    return;

                me->ResetLootMode();
                events.Reset();
                summons.DespawnAll();

                devastatingComboPhase = 0;
                victimWithMagneticArmor = 0;

                if (pInstance)
                {
                    pInstance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
                    pInstance->DoRemoveAurasDueToSpellOnPlayers(SPELL_MAGNETIC_ARMOR);
                }

                playerList.clear();

                events.ScheduleEvent(EVENT_DEVASTATING_COMBO, 10000);
                events.ScheduleEvent(EVENT_CHECK_MAGNETIC_ARMOR, 1000);
            }

            void EnterCombat(Unit* /*who*/)
            {
                DoZoneInCombat();

                if (pInstance)
                    pInstance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, me);
            }

            void JustDied(Unit* /*killer*/)
            {
                events.Reset();
                summons.DespawnAll();

                if (pInstance)
                    pInstance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
            }

            void DoAction(const int32 action)
            {
            }

            void SpellHitTarget(Unit* target, SpellInfo const* spell)
            {
                if (spell->Id != SPELL_DEVASTATING_ARC &&
                    spell->Id != SPELL_STOMP)
                    return;

                for (Player* player: playerList)
                {
                    if (player->GetGUID() == target->GetGUID())
                    {
                        playerList.remove(player);
                        break;
                    }
                }
            }

            Creature* getOtherBoss()
            {
                if (pInstance)
                    return pInstance->instance->GetCreature(pInstance->GetData64(me->GetEntry() == NPC_QIN_XI ? NPC_JAN_XI: NPC_QIN_XI));
                else
                    return NULL;
            }

            void DamageTaken(Unit* attacker, uint32& damage)
            {
                Creature* otherBoss = getOtherBoss();

                if (attacker != otherBoss)
                    me->DealDamage(otherBoss, damage);
                else
                    me->LowerPlayerDamageReq(damage);
            }

            void UpdateAI(const uint32 diff)
            {
                if (!UpdateVictim())
                    return;

                if (me->HasUnitState(UNIT_STATE_CASTING))
                    return;

                events.Update(diff);

                switch(events.ExecuteEvent())
                {
                    case EVENT_DEVASTATING_COMBO:
                    {
                        if (!devastatingComboPhase)
                        {
                            // We check wich players are in zone on combo beginning
                            GetPlayerListInGrid(playerList, me, 12.0f);
                        }

                        if (devastatingComboPhase % 2)
                        {
                            me->SetOrientation(frand(0.0f, 6.28f));
                            if (urand(0, 1))
                            {
                                me->CastSpell(me, SPELL_ARC_VISUAL, false);
                                ++devastatingComboPhase; // Pair phase are for arc damages
                            }
                            else
                            {
                                me->CastSpell(me, SPELL_STOMP, false);
                                devastatingComboPhase += 2;
                            }
                        }
                        else
                        {
                            if (Unit* target = SelectTarget(SELECT_TARGET_TOPAGGRO))
                                me->CastSpell(target, SPELL_DEVASTATING_ARC, true);
                            ++devastatingComboPhase;
                        }

                        uint8 maxComboPhase = pInstance->instance->IsHeroic() ? 20: 10; // 10 & 5 but we use pair phase to devastating arc damages

                        if (devastatingComboPhase < maxComboPhase)
                            events.ScheduleEvent(EVENT_DEVASTATING_COMBO, 100); // Dont' update while casting
                        else
                        {
                            devastatingComboPhase = 0;

                            for (Player* player: playerList)
                                player->AddAura(SPELL_OPPORTUNISTIC_STRIKE, player);

                            events.ScheduleEvent(EVENT_DEVASTATING_COMBO, 15000);
                        }
                        break;
                    }
                    case EVENT_CHECK_MAGNETIC_ARMOR:
                    {
                        if (Unit* victim = me->getVictim())
                        {
                            if (!victim->HasAura(SPELL_MAGNETIC_ARMOR))
                            {
                                if (Player* player = ObjectAccessor::FindPlayer(victimWithMagneticArmor))
                                    player->RemoveAurasDueToSpell(SPELL_MAGNETIC_ARMOR);

                                me->AddAura(SPELL_MAGNETIC_ARMOR, victim);
                                victimWithMagneticArmor = victim->GetGUID();
                            }
                        }
                        events.ScheduleEvent(EVENT_CHECK_MAGNETIC_ARMOR, 1000);
                        break;
                    }
                    default:
                        break;
                }

                DoMeleeAttackIfReady();
            }
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new boss_jin_qin_xiAI(creature);
        }
};

class mob_woe_add_generic : public CreatureScript
{
    public:
        mob_woe_add_generic() : CreatureScript("mob_woe_add_generic") {}

        struct mob_woe_add_genericAI : public ScriptedAI
        {
            mob_woe_add_genericAI(Creature* creature) : ScriptedAI(creature)
            {
                pInstance = creature->GetInstanceScript();
            }

            uint64 targetGuid;
            EventMap events;
            InstanceScript* pInstance;

            void Reset()
            {
                if (!pInstance)
                    return;

                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE|UNIT_FLAG_NOT_SELECTABLE);

                float x = me->GetPositionX() + (15 * cos(me->GetOrientation()));
                float y = me->GetPositionY() + (15 * sin(me->GetOrientation()));

                me->GetMotionMaster()->MoveJump(x, y, 362.19f, 20.0f, 20.0f, 1);
            }

            void MovementInform(uint32 uiType, uint32 id)
            {
                if (uiType != POINT_MOTION_TYPE
                 && uiType != EFFECT_MOTION_TYPE)
                    return;

                if (id == 1)
                {
                    DoZoneInCombat();
                    targetGuid = 0;
                    
                    me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE|UNIT_FLAG_NOT_SELECTABLE);
                    switch (me->GetEntry())
                    {
                        case NPC_EMPEROR_RAGE:
                        {
                            if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM))
                            {
                                targetGuid = target->GetGUID();
                                AttackStart(target);
                                me->getThreatManager().addThreat(target, 1000000.0f);

                                me->CastSpell(target, SPELL_FOCALISED_ASSAULT, false);
                            }

                            me->AddAura(SPELL_WITHOUT_ARMOR, me);

                            events.ScheduleEvent(EVENT_CHECK_TARGET, 2000);
                            break;
                        }
                        case NPC_EMPEROR_COURAGE:
                        {
                            if (Unit* randomBoss = pInstance->instance->GetCreature(pInstance->GetData64(urand(0, 1) ? NPC_QIN_XI: NPC_JAN_XI)))
                            {
                                if (Unit* tank = randomBoss->getVictim())
                                {
                                    targetGuid = tank->GetGUID();
                                    AttackStart(tank);
                                    me->getThreatManager().addThreat(tank, 1000000.0f);

                                    me->CastSpell(tank, SPELL_FOCALISED_DEFENSE, false);
                                }
                                else if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM))
                                {
                                    targetGuid = target->GetGUID();
                                    AttackStart(target);
                                    me->getThreatManager().addThreat(target, 1000000.0f);

                                    me->CastSpell(target, SPELL_FOCALISED_DEFENSE, false);
                                }
                            }

                            me->AddAura(SPELL_HALF_PLATE, me);

                            events.ScheduleEvent(EVENT_IMPEDING_THRUST, 5000);
                            events.ScheduleEvent(EVENT_CHECK_TARGET, 2000);
                            break;
                        }
                        case NPC_EMPEROR_STRENGHT:
                        {
                            events.ScheduleEvent(EVENT_ENERGIZING_SMASH, urand(5000, 10000));
                            me->AddAura(SPELL_FULL_PLATE, me);
                            break;
                        }
                    }
                }
            }

            void JustDied(Unit* attacker)
            {
                me->CastSpell(me, SPELL_SUMMON_TITAN_SPARK, true);
            }
            
            void DamageTaken(Unit* attacker, uint32& damage)
            {
                if (me->GetEntry() == NPC_EMPEROR_COURAGE)
                    if (me->isInFront(attacker))
                        damage = 0;
            }

            void UpdateAI(const uint32 diff)
            {
                if (!UpdateVictim())
                    return;

                events.Update(diff);

                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_CHECK_TARGET:
                        {
                            bool shouldSwitchVictim = false;

                            if (me->getVictim())
                            {
                                if (me->getVictim()->GetGUID() != targetGuid)
                                {
                                    if (Unit* target = ObjectAccessor::FindUnit(targetGuid))
                                    {
                                        if (!target->isAlive())
                                            shouldSwitchVictim = true;
                                    }
                                    else
                                        shouldSwitchVictim = true;
                                }
                                else
                                {
                                    if (Unit* target = ObjectAccessor::FindUnit(targetGuid))
                                    {
                                        if (target->isAlive())
                                        {
                                            me->getThreatManager().resetAllAggro();
                                            targetGuid = target->GetGUID();
                                            AttackStart(target);
                                            me->getThreatManager().addThreat(target, 1000000.0f);
                                            me->CastSpell(target, SPELL_FOCALISED_ASSAULT, false);
                                        }
                                    }
                                }
                            }

                            if (shouldSwitchVictim)
                            {
                                me->getThreatManager().resetAllAggro();
                                DoZoneInCombat();
                                if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM))
                                {
                                    targetGuid = target->GetGUID();
                                    AttackStart(target);
                                    me->getThreatManager().addThreat(target, 1000000.0f);
                                    me->CastSpell(target, SPELL_FOCALISED_ASSAULT, false);
                                }
                            }
                            events.ScheduleEvent(EVENT_CHECK_TARGET, 2000);
                            break;
                        }
                        // Courage
                        case EVENT_IMPEDING_THRUST:
                        {
                            if (Unit* victim = me->getVictim())
                            {
                                if (me->IsWithinMeleeRange(victim))
                                {
                                    me->CastSpell(victim, SPELL_IMPEDING_THRUST, false);
                                    events.ScheduleEvent(EVENT_IMPEDING_THRUST, 10000);
                                }
                                else
                                    events.ScheduleEvent(EVENT_IMPEDING_THRUST, 2000);
                            }
                            else
                                events.ScheduleEvent(EVENT_IMPEDING_THRUST, 2000);
                            break;
                        }
                        // Strenght
                        case EVENT_ENERGIZING_SMASH:
                        {
                            me->CastSpell(me, SPELL_ENERGIZING_SMASH, false);
                            events.ScheduleEvent(EVENT_ENERGIZING_SMASH, urand(5000, 10000));
                            break;
                        }
                    }
                }
            }
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new mob_woe_add_genericAI(creature);
        }
};

class mob_woe_titan_spark : public CreatureScript
{
    public:
        mob_woe_titan_spark() : CreatureScript("mob_woe_titan_spark") {}

        struct mob_woe_titan_sparkAI : public ScriptedAI
        {
            mob_woe_titan_sparkAI(Creature* creature) : ScriptedAI(creature)
            {
                pInstance = creature->GetInstanceScript();
            }

            InstanceScript* pInstance;
            uint32 distanceCheckTimer;
            uint64 targetGuid;

            void Reset()
            {
                targetGuid = 0;
                distanceCheckTimer = 500;

                DoZoneInCombat();
                if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM))
                {
                    targetGuid = target->GetGUID();
                    AttackStart(target);
                    me->getThreatManager().addThreat(target, 1000000.0f);
                    me->CastSpell(target, SPELL_FOCALISED_ENERGY, false);
                }
            }

            void JustDied(Unit* attacker)
            {
                me->CastSpell(me, SPELL_ENERGY_OF_CREATION, false);
            }

            void UpdateAI(const uint32 diff) 
            {
                if (distanceCheckTimer <= diff)
                {
                    if (me->SelectNearestPlayerNotGM())
                        me->Kill(me);
                    distanceCheckTimer = 500;
                }
                else
                    distanceCheckTimer -= diff;
            }
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new mob_woe_titan_sparkAI(creature);
        }
};

void AddSC_boss_will_of_emperor()
{
    new boss_jin_qin_xi();
    new mob_woe_add_generic();
    new mob_woe_titan_spark();
}
