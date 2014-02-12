#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "ScriptedGossip.h"
#include "ScriptedEscortAI.h"

enum eHighRoadScoutSpells
{
    SPELL_THROW        = 38557,
};

enum eHighRoadScoutEvents
{
    EVENT_THROW        = 1,
};

class mob_high_road_scout : public CreatureScript
{
    public:
        mob_high_road_scout() : CreatureScript("mob_high_road_scout") { }

        struct mob_high_road_scoutAI : public ScriptedAI
        {
            mob_high_road_scoutAI(Creature* creature) : ScriptedAI(creature)
            {
            }

            EventMap events;

            void Reset()
            {
                events.Reset();
                
                events.ScheduleEvent(EVENT_THROW,      7000);
            }

            void JustDied(Unit* /*killer*/)
            {
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
                        case EVENT_THROW:
                            if (Unit* target = SelectTarget(SELECT_TARGET_TOPAGGRO))
                                me->CastSpell(target, SPELL_THROW, false);
                            events.ScheduleEvent(EVENT_THROW,      7000);
                            break;

                        default:
                            break;
                    }
                }

                DoMeleeAttackIfReady();
            }
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new mob_high_road_scoutAI(creature);
        }
};

enum eSabersnoutSpells
{
    SPELL_ENRAGE                          = 8599,
    SPELL_FEAR                            = 70171,
    SPELL_IMPENETRABLE_SHIELD_WALL        = 70166,
    SPELL_QUILBOAR_RUSH                   = 82610,
    SPELL_STRIKE                          = 11976,
};

enum eSabersnoutEvents
{
    EVENT_ENRAGE                          = 1,
    EVENT_FEARW                           = 2,
    EVENT_IMPENETRABLE_SHIELD_WALL        = 3,
    EVENT_QUILBOAR_RUSH                   = 4,
    EVENT_STRIKE                          = 5,
};

class mob_sabersnout : public CreatureScript
{
    public:
        mob_sabersnout() : CreatureScript("mob_sabersnout") { }

        struct mob_sabersnoutAI : public ScriptedAI
        {
            mob_sabersnoutAI(Creature* creature) : ScriptedAI(creature)
            {
            }

            EventMap events;

            void Reset()
            {
                events.Reset();

                events.ScheduleEvent(EVENT_ENRAGE,      10000);
                events.ScheduleEvent(EVENT_FEARW,      20000);
                events.ScheduleEvent(EVENT_IMPENETRABLE_SHIELD_WALL,      30000);
                events.ScheduleEvent(EVENT_QUILBOAR_RUSH,      40000);
                events.ScheduleEvent(EVENT_STRIKE,      50000);
            }

            void JustDied(Unit* /*killer*/)
            {
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
                        case EVENT_ENRAGE:
                            if (Unit* target = SelectTarget(SELECT_TARGET_TOPAGGRO))
                                me->CastSpell(target, SPELL_ENRAGE, false);
                            events.ScheduleEvent(EVENT_ENRAGE,      10000);
                            break;
                        case EVENT_FEARW:
                            if (Unit* target = SelectTarget(SELECT_TARGET_TOPAGGRO))
                                me->CastSpell(target, SPELL_FEAR, false);
                            events.ScheduleEvent(EVENT_FEARW,      20000);
                            break;
                        case EVENT_IMPENETRABLE_SHIELD_WALL:
                            if (Unit* target = SelectTarget(SELECT_TARGET_TOPAGGRO))
                                me->CastSpell(target, SPELL_IMPENETRABLE_SHIELD_WALL, false);
                            events.ScheduleEvent(EVENT_IMPENETRABLE_SHIELD_WALL,      30000);
                            break;
                        case EVENT_QUILBOAR_RUSH:
                            if (Unit* target = SelectTarget(SELECT_TARGET_TOPAGGRO))
                                me->CastSpell(target, SPELL_QUILBOAR_RUSH, false);
                            events.ScheduleEvent(EVENT_QUILBOAR_RUSH,      40000);
                            break;
                        case EVENT_STRIKE:
                            if (Unit* target = SelectTarget(SELECT_TARGET_TOPAGGRO))
                                me->CastSpell(target, SPELL_STRIKE, false);
                            events.ScheduleEvent(EVENT_STRIKE,      50000);
                            break;
                        default:
                            break;
                    }
                }

                DoMeleeAttackIfReady();
            }
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new mob_sabersnoutAI(creature);
        }
};

void AddSC_southern_barrens()
{
    new mob_high_road_scout();
    new mob_sabersnout();
}