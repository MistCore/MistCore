#include "ScriptPCH.h"
#include "baradin_hold.h"

enum ScriptTexts
{
    
    SAY_AGGRO           = 0,
    SAY_DEATH           = 1,
    SAY_INTRO           = 2,
    SAY_WIPE            = 3, 
    SAY_KILL            = 4,
    SAY_SEETHING_HATE   = 5,
    SAY_SKEWER          = 6,
};

enum Spells
{
    SPELL_SKEWER                = 104936,
    SPELL_SEETHING_HATE_DUMMY   = 105065,
    SPELL_SEETHING_HATE         = 105067,
    SPELL_SEETHING_HATE_DMG_10  = 105069,
    SPELL_SEETHING_HATE_DMG_25  = 108094,
    SPELL_BLADE_DANCE_CHARGE    = 105726,
    SPELL_BLADE_DANCE_DUMMY     = 106248,
    SPELL_BLADE_DANCE_SELF      = 105828,
    SPELL_BLADE_DANCE           = 105784,
    SPELL_BERSERK               = 47008,
};

enum Events
{
    EVENT_SKEWER                = 1,
    EVENT_SEETHING_HATE         = 2,
    EVENT_BLADE_DANCE           = 3,
    EVENT_BERSERK               = 4,
    EVENT_BLADE_DANCE_CHARGE    = 5,
};

class boss_alizabal : public CreatureScript
{
    public:
        boss_alizabal() : CreatureScript("boss_alizabal") { }

        CreatureAI* GetAI(Creature* pCreature) const
        {
            return new boss_alizabalAI(pCreature);
        }

        struct boss_alizabalAI : public BossAI
        {
            boss_alizabalAI(Creature* pCreature) : BossAI(pCreature, DATA_ALIZABAL) 
            {
                me->ApplySpellImmune(0, IMMUNITY_EFFECT, SPELL_EFFECT_KNOCK_BACK, true);
				me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_GRIP, true);
				me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_STUN, true);
				me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_FEAR, true);
				me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_ROOT, true);
				me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_FREEZE, true);
				me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_POLYMORPH, true);
				me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_HORROR, true);
				me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_SAPPED, true);
				me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_CHARM, true);
				me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_DISORIENTED, true);
				me->ApplySpellImmune(0, IMMUNITY_STATE, SPELL_AURA_MOD_CONFUSE, true);
                introDone = false;
            }

            bool introDone;
            uint8 uiCharges;

            void InitializeAI()
            {
                if (!instance || static_cast<InstanceMap*>(me->GetMap())->GetScriptId() != sObjectMgr->GetScriptId(BHScriptName))
                    me->IsAIEnabled = false;
                else if (!me->isDead())
                    Reset();
            }

            void Reset()
            {
                _Reset();
                
                events.Reset();
            }

            void MoveInLineOfSight(Unit* who)
            {
                if (!introDone && me->IsWithinDistInMap(who, 70.0f))
                {
                    Talk(SAY_INTRO);
                    introDone = true;
                }
            }

            void JustReachedHome()
            {
                _JustReachedHome();
                Talk(SAY_WIPE);
            }

            void EnterCombat(Unit* attacker)
            {
                uiCharges = 0;
                events.ScheduleEvent(EVENT_BERSERK, 300000);
                events.ScheduleEvent(EVENT_BLADE_DANCE, 35000);
                if (urand(0, 1))
                {
                    events.ScheduleEvent(EVENT_SKEWER, 8000);
                    events.ScheduleEvent(EVENT_SEETHING_HATE, 16000);
                }
                else
                {
                    events.ScheduleEvent(EVENT_SKEWER, 16000);
                    events.ScheduleEvent(EVENT_SEETHING_HATE, 8000);
                }
                Talk(SAY_AGGRO);
                instance->SetBossState(DATA_ALIZABAL, IN_PROGRESS);
            }

            void KilledUnit(Unit* victim)
            {
                Talk(SAY_KILL);
            }

            void JustDied(Unit* killer)
            {
                _JustDied();
                Talk(SAY_DEATH);
            }

            void UpdateAI(const uint32 diff)
            {
                if (!UpdateVictim())
                    return;

                events.Update(diff);

                if (me->HasUnitState(UNIT_STATE_CASTING))
                    return;

                while (uint32 eventId = events.ExecuteEvent())
				{
					switch (eventId)
					{
                        case EVENT_BERSERK:
                            DoCast(me, SPELL_BERSERK, true);
                            break;
                        case EVENT_SKEWER:
                            Talk(SAY_SKEWER);
                            DoCast(me->getVictim(), SPELL_SKEWER);
                            events.ScheduleEvent(EVENT_SKEWER, 20500);
                            break;
                        case EVENT_SEETHING_HATE:
                            Talk(SAY_SEETHING_HATE);
                            DoCastAOE(SPELL_SEETHING_HATE_DUMMY);
                            events.ScheduleEvent(EVENT_SEETHING_HATE, 20500);
                            break;
                        case EVENT_BLADE_DANCE:
                            events.CancelEvent(EVENT_SKEWER);
                            events.CancelEvent(EVENT_SEETHING_HATE);
                            DoCast(me, SPELL_BLADE_DANCE_SELF);
                            DoCast(me, SPELL_BLADE_DANCE, true);
                            DoCastAOE(SPELL_BLADE_DANCE_DUMMY, true);
                            events.ScheduleEvent(EVENT_BLADE_DANCE, 60000);
                            events.ScheduleEvent(EVENT_BLADE_DANCE_CHARGE, 4000);
                            if (urand(0, 1))
                            {
                                events.RescheduleEvent(EVENT_SKEWER, 23000);
                                events.RescheduleEvent(EVENT_SEETHING_HATE, 31000);
                            }
                            else
                            {
                                events.RescheduleEvent(EVENT_SKEWER, 31000);
                                events.RescheduleEvent(EVENT_SEETHING_HATE, 23000);
                            }
                            break;
                        case EVENT_BLADE_DANCE_CHARGE:
                            DoCastAOE(SPELL_BLADE_DANCE_DUMMY);
                            uiCharges++;
                            if (uiCharges > 3)
                                uiCharges = 0;
                            else
                                events.ScheduleEvent(EVENT_BLADE_DANCE, 4000);
                            break;
                    }
                }

                DoMeleeAttackIfReady();
            }
        };
};

class spell_alizabal_seething_hate : public SpellScriptLoader
{
    public:
        spell_alizabal_seething_hate() : SpellScriptLoader("spell_alizabal_seething_hate") { }

        class spell_alizabal_seething_hate_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_alizabal_seething_hate_SpellScript);

            void HandleDummy(SpellEffIndex /*effIndex*/)
			{
				if(!GetCaster() || !GetHitUnit())
					return;

                GetCaster()->CastSpell(GetHitUnit(), SPELL_SEETHING_HATE, true);
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_alizabal_seething_hate_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_alizabal_seething_hate_SpellScript();
        }
};

class spell_alizabal_blade_dance : public SpellScriptLoader
{
    public:
        spell_alizabal_blade_dance() : SpellScriptLoader("spell_alizabal_blade_dance") { }

        class spell_alizabal_blade_dance_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_alizabal_blade_dance_SpellScript);

            void HandleDummy(SpellEffIndex /*effIndex*/)
			{
				if(!GetCaster() || !GetHitUnit())
					return;

                GetCaster()->CastSpell(GetHitUnit(), SPELL_BLADE_DANCE_CHARGE, true);
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_alizabal_blade_dance_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_alizabal_blade_dance_SpellScript();
        }
};

void AddSC_boss_alizabal()
{
    new boss_alizabal();
    new spell_alizabal_seething_hate();
    new spell_alizabal_blade_dance();
}
