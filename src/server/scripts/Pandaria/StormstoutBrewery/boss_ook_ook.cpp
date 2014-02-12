/*
    Dungeon : Template of the Jade Serpent 85-87
    Wise mari first boss
    Jade servers
*/

#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "stormstout_brewery.h"
#include "Vehicle.h"

class boss_ook_ook : public CreatureScript
{
    public:
        boss_ook_ook() : CreatureScript("boss_ook_ook") { }

        CreatureAI* GetAI(Creature* creature) const
        {
            return new boss_ook_ook_AI(creature);
        }

        struct boss_ook_ook_AI : public BossAI
        {
            boss_ook_ook_AI(Creature* creature) : BossAI(creature, DATA_OOK_OOK)
            {}

            void Reset()
            {}

            void EnterCombat(Unit* /*who*/)
            {}

            void DoAction(const int32 action)
            {
            }

            void KilledUnit(Unit* /*victim*/)
            {
            }

            void JustDied(Unit* /*killer*/)
            {
                _JustDied();
            }

            void DamageTaken(Unit* /*attacker*/, uint32& /*damage*/)
            {

            }

            void MoveInLineOfSight(Unit* who)
            {}

            void UpdateAI(const uint32 diff)
            {}
        };
};

enum eSpells
{
    SPELL_BAREL_EXPLOSION           = 106769,
    SPELL_FORCECAST_BARREL_DROP     = 122385,
};

class npc_barrel : public CreatureScript
{
    public:
        npc_barrel() : CreatureScript("npc_barrel") { }

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_barrel_AI(creature);
        }

        struct npc_barrel_AI : public ScriptedAI
        {
            npc_barrel_AI(Creature* creature) : ScriptedAI(creature)
            {}

            void Reset()
            {            
                me->GetMotionMaster()->MovePoint(100, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ());
            }

            void MovementInform(uint32 type, uint32 id)
            {
                if (id != 100)
                    return;

                float x = 0, y = 0;
                GetPositionWithDistInOrientation(me, 5.0f, me->GetOrientation(), x, y);
            
                me->GetMotionMaster()->MovePoint(100, x, y, me->GetPositionZ());
            }

            bool CheckIfAgainstWall()
            {                
                float x = 0, y = 0;
                GetPositionWithDistInOrientation(me, 5.0f,  me->GetOrientation(),x, y);

                if (!me->IsWithinLOS(x, y, me->GetPositionZ()))
                    return true;

                return false;
            }

            bool CheckIfAgainstUnit()
            {
                if (me->SelectNearbyTarget(NULL, 1.0f))
                    return true;

                return false;
            }

            void DoExplode()
            {
                if (Vehicle* barrel = me->GetVehicleKit())
                    barrel->RemoveAllPassengers();

                me->Kill(me);
                me->CastSpell(me, SPELL_BAREL_EXPLOSION, true);
            }

            void UpdateAI(const uint32 diff)
            {
                if (CheckIfAgainstWall() || CheckIfAgainstUnit())
                    DoExplode();
            }
        };
};

class spell_ook_ook_barrel_ride : public SpellScriptLoader
{
    public:
        spell_ook_ook_barrel_ride() :  SpellScriptLoader("spell_ook_ook_barrel_ride") { }

        class spell_ook_ook_barrel_ride_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_ook_ook_barrel_ride_AuraScript);

            void OnApply(constAuraEffectPtr /*aurEff*/, AuraEffectHandleModes /*mode*/)
            {
                if (GetTarget())
                    if (Unit* barrelBase = GetTarget())
                        barrelBase->GetMotionMaster()->MoveIdle();
            }

            void Register()
            {
                OnEffectApply += AuraEffectApplyFn(spell_ook_ook_barrel_ride_AuraScript::OnApply, EFFECT_0, SPELL_AURA_CONTROL_VEHICLE, AURA_EFFECT_HANDLE_REAL_OR_REAPPLY_MASK);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_ook_ook_barrel_ride_AuraScript();
        }
};

class spell_ook_ook_barrel : public SpellScriptLoader
{
    public:
        spell_ook_ook_barrel() :  SpellScriptLoader("spell_ook_ook_barrel") { }

        class spell_ook_ook_barrel_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_ook_ook_barrel_AuraScript);

            bool CheckIfAgainstWall(Unit* caster)
            {                
                float x = caster->GetPositionX() + (2 * cos(caster->GetOrientation()));
                float y = caster->GetPositionY() + (2 * sin(caster->GetOrientation()));

                if (!caster->IsWithinLOS(x, y, caster->GetPositionZ()))
                    return true;

                return false;
            }

            bool CheckIfAgainstUnit(Unit* caster)
            {
                if (caster->SelectNearbyTarget(NULL, 1.0f))
                    return true;

                return false;
            }

            void OnUpdate(uint32 diff)
            {
                Unit* caster = GetCaster();
                if (!caster)
                    return;

                if (CheckIfAgainstWall(caster) || CheckIfAgainstUnit(caster))
                {
                    if (Vehicle* barrel = caster->GetVehicle())
                    {
                        barrel->RemoveAllPassengers();

                        if (Unit* barrelBase = barrel->GetBase())
                        {
                            barrelBase->CastSpell(barrelBase, SPELL_BAREL_EXPLOSION, true);
                            barrelBase->Kill(barrelBase);
                        }
                    }

                    caster->CastSpell(caster, SPELL_FORCECAST_BARREL_DROP, true);
                    caster->RemoveAurasDueToSpell(GetSpellInfo()->Id);
                }
            }

            void Register()
            {
                OnAuraUpdate += AuraUpdateFn(spell_ook_ook_barrel_AuraScript::OnUpdate);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_ook_ook_barrel_AuraScript();
        }
};

void AddSC_boss_ook_ook()
{
    new boss_ook_ook();
    new npc_barrel();
    new spell_ook_ook_barrel_ride();
    new spell_ook_ook_barrel();
}
