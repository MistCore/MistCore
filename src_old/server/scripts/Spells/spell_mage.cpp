/*
 * Copyright (C) 2008-2012 TrinityCore <http://www.trinitycore.org/>
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

/*
 * Scripts for spells with SPELLFAMILY_MAGE and SPELLFAMILY_GENERIC spells used by mage players.
 * Ordered alphabetically using scriptname.
 * Scriptnames of files in this file should be prefixed with "spell_mage_".
 */

#include "ScriptMgr.h"
#include "SpellScript.h"
#include "SpellAuraEffects.h"
#include "ScriptedCreature.h"

#include "Cell.h"
#include "CellImpl.h"
#include "GridNotifiers.h"
#include "GridNotifiersImpl.h"

enum MageSpells
{
    SPELL_MAGE_COLD_SNAP                         = 11958,
    SPELL_MAGE_GLYPH_OF_ETERNAL_WATER            = 70937,
    SPELL_MAGE_SUMMON_WATER_ELEMENTAL_PERMANENT  = 70908,
    SPELL_MAGE_SUMMON_WATER_ELEMENTAL_TEMPORARY  = 70907,
    SPELL_MAGE_GLYPH_OF_BLAST_WAVE               = 62126,
    SPELL_MAGE_ALTER_TIME_OVERRIDED              = 127140,
    SPELL_MAGE_ALTER_TIME                        = 110909,
    NPC_PAST_SELF                                = 58542,
    SPELL_MAGE_TEMPORAL_DISPLACEMENT             = 80354,
    HUNTER_SPELL_INSANITY                        = 95809,
    SPELL_SHAMAN_SATED                           = 57724,
    SPELL_SHAMAN_EXHAUSTED                       = 57723,
    SPELL_MAGE_CONJURE_REFRESHMENT_R1            = 92739,
    SPELL_MAGE_CONJURE_REFRESHMENT_R2            = 92799,
    SPELL_MAGE_CONJURE_REFRESHMENT_R3            = 92802,
    SPELL_MAGE_CONJURE_REFRESHMENT_R4            = 92805,
    SPELL_MAGE_CONJURE_REFRESHMENT_R5            = 74625,
    SPELL_MAGE_CONJURE_REFRESHMENT_R6            = 42956,
    SPELL_MAGE_CONJURE_REFRESHMENT_R7            = 92727,
    SPELL_MAGE_CONJURE_REFRESHMENT_R8            = 116130,
    SPELL_MAGE_MANA_GEM_ENERGIZE                 = 10052,
    SPELL_MAGE_ARCANE_BRILLIANCE                 = 1459,
    SPELL_MAGE_INFERNO_BLAST                     = 108853,
    SPELL_MAGE_INFERNO_BLAST_IMPACT              = 118280,
    SPELL_MAGE_IGNITE                            = 12654,
    SPELL_MAGE_PYROBLAST                         = 11366,
    SPELL_MAGE_COMBUSTION_DOT                    = 83853,
    SPELL_MAGE_COMBUSTION_IMPACT                 = 118271,
    SPELL_MAGE_FROSTJAW                          = 102051,
    SPELL_MAGE_NETHER_TEMPEST_DIRECT_DAMAGE      = 114954,
    SPELL_MAGE_NETHER_TEMPEST_VISUAL             = 114924,
    SPELL_MAGE_NETHER_TEMPEST_MISSILE            = 114956,
    SPELL_MAGE_LIVING_BOMB_TRIGGERED             = 44461,
    SPELL_MAGE_FROST_BOMB_TRIGGERED              = 113092,
    SPELL_MAGE_INVOKERS_ENERGY                   = 116257,
    SPELL_MAGE_INVOCATION                        = 114003,
    SPELL_MAGE_GLYPH_OF_EVOCATION                = 56380,
    SPELL_MAGE_BRAIN_FREEZE                      = 44549,
    SPELL_MAGE_BRAIN_FREEZE_TRIGGERED            = 57761,
    SPELL_MAGE_SLOW                              = 31589,
    SPELL_MAGE_ARCANE_CHARGE                     = 36032,
    SPELL_MAGE_ARCANE_BARRAGE_TRIGGERED          = 50273,
    SPELL_MAGE_PYROMANIAC_AURA                   = 132209,
    SPELL_MAGE_PYROMANIAC_DAMAGE_DONE            = 132210,
    SPELL_MAGE_MIRROR_IMAGE_SUMMON               = 58832,
    SPELL_MAGE_CAUTERIZE                         = 87023,
    SPELL_MAGE_ARCANE_MISSILES                   = 79683,
    SPELL_MAGE_INCANTERS_WARD_ENERGIZE           = 113842,
    SPELL_MAGE_INCANTERS_ABSORBTION              = 116267,
    SPELL_MAGE_INCANTERS_ABSORBTION_PASSIVE      = 118858,
    SPELL_MAGE_GLYPH_OF_ICE_BLOCK                = 115723,
    SPELL_MAGE_GLYPH_OF_ICE_BLOCK_IMMUNITY       = 115760,
    SPELL_MAGE_GLYPH_OF_ICE_BLOCK_FROST_NOVA     = 115757,
    SPELL_MAGE_IMPROVED_COUNTERSPELL             = 12598,
    SPELL_MAGE_COUNTERSPELL_SILENCE              = 55021,
    SPELL_MAGE_FINGER_OF_FROST_VISUAL            = 44544,
    SPELL_MAGE_FINGER_OF_FROST_EFFECT            = 126084,
    SPELL_MAGE_GLYPH_OF_SLOW                     = 86209,
    SPELL_MAGE_GREATER_INVISIBILITY_LESS_DAMAGE  = 113862,
    SPELL_MAGE_REMOVE_INVISIBILITY_REMOVED_TIMER = 122293,
    SPELL_MAGE_BLAST_WAVE_SNARE                  = 11113,
    SPELL_MAGE_ICE_BLOCK                         = 45438,
    SPELL_MAGE_CONE_OF_COLD                      = 120,
    SPELL_MAGE_FROST_NOVA                        = 122,
    SPELL_MAGE_FINGERS_OF_FROST_AURA             = 112965,
};

// Flamestrike - 2120
class spell_mage_flamestrike : public SpellScriptLoader
{
    public:
        spell_mage_flamestrike() : SpellScriptLoader("spell_mage_flamestrike") { }

        class spell_mage_flamestrike_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_mage_flamestrike_SpellScript);

            void HandleOnHit()
            {
                if (Player* caster = GetCaster()->ToPlayer())
                {
                    if (Unit* target = GetHitUnit())
                    {
                        if (caster->GetSpecializationId(caster->GetActiveSpec()) == SPEC_MAGE_FIRE)
                            caster->CastSpell(target, SPELL_MAGE_BLAST_WAVE_SNARE, true);
                    }
                }
            }

            void Register()
            {
                OnHit += SpellHitFn(spell_mage_flamestrike_SpellScript::HandleOnHit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_mage_flamestrike_SpellScript();
        }
};

// Greater Invisibility (remove timer) - 122293
class spell_mage_greater_invisibility_removed : public SpellScriptLoader
{
    public:
        spell_mage_greater_invisibility_removed() : SpellScriptLoader("spell_mage_greater_invisibility_removed") { }

        class spell_mage_greater_invisibility_removed_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_mage_greater_invisibility_removed_AuraScript);

            void OnRemove(constAuraEffectPtr /*aurEff*/, AuraEffectHandleModes /*mode*/)
            {
                if (Player* _player = GetTarget()->ToPlayer())
                    if (_player->HasAura(SPELL_MAGE_GREATER_INVISIBILITY_LESS_DAMAGE))
                        _player->RemoveAurasDueToSpell(SPELL_MAGE_GREATER_INVISIBILITY_LESS_DAMAGE);
            }

            void Register()
            {
                OnEffectRemove += AuraEffectRemoveFn(spell_mage_greater_invisibility_removed_AuraScript::OnRemove, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_mage_greater_invisibility_removed_AuraScript();
        }
};

// Greater Invisibility (triggered) - 110960
class spell_mage_greater_invisibility_triggered : public SpellScriptLoader
{
    public:
        spell_mage_greater_invisibility_triggered() : SpellScriptLoader("spell_mage_greater_invisibility_triggered") { }

        class spell_mage_greater_invisibility_triggered_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_mage_greater_invisibility_triggered_AuraScript);

            void OnApply(constAuraEffectPtr /*aurEff*/, AuraEffectHandleModes /*mode*/)
            {
                if (Player* _player = GetTarget()->ToPlayer())
                    _player->CastSpell(_player, SPELL_MAGE_GREATER_INVISIBILITY_LESS_DAMAGE, true);
            }

            void OnRemove(constAuraEffectPtr /*aurEff*/, AuraEffectHandleModes /*mode*/)
            {
                if (Player* _player = GetTarget()->ToPlayer())
                    _player->CastSpell(_player, SPELL_MAGE_REMOVE_INVISIBILITY_REMOVED_TIMER, true);
            }

            void Register()
            {
                OnEffectApply += AuraEffectApplyFn(spell_mage_greater_invisibility_triggered_AuraScript::OnApply, EFFECT_1, SPELL_AURA_MOD_INVISIBILITY, AURA_EFFECT_HANDLE_REAL);
                OnEffectRemove += AuraEffectRemoveFn(spell_mage_greater_invisibility_triggered_AuraScript::OnRemove, EFFECT_1, SPELL_AURA_MOD_INVISIBILITY, AURA_EFFECT_HANDLE_REAL);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_mage_greater_invisibility_triggered_AuraScript();
        }
};

// Called by Arcane Blast - 30451
// Glyph of Slow - 86209
class spell_mage_glyph_of_slow : public SpellScriptLoader
{
    public:
        spell_mage_glyph_of_slow() : SpellScriptLoader("spell_mage_glyph_of_slow") { }

        class spell_mage_glyph_of_slow_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_mage_glyph_of_slow_SpellScript);

            void HandleOnHit()
            {
                if (Unit* caster = GetCaster())
                {
                    if (!caster->HasAura(SPELL_MAGE_GLYPH_OF_SLOW))
                        return;

                    if (Unit* target = GetHitUnit())
                    {
                        std::list<Unit*> targetList;
                        float radius = 50.0f;
                        bool found = false;

                        JadeCore::NearestAttackableUnitInObjectRangeCheck u_check(caster, caster, radius);
                        JadeCore::UnitListSearcher<JadeCore::NearestAttackableUnitInObjectRangeCheck> searcher(caster, targetList, u_check);
                        caster->VisitNearbyObject(radius, searcher);

                        for (auto itr : targetList)
                            if (itr->HasAura(SPELL_MAGE_SLOW))
                                found = true;

                        if (found)
                            return;
                        else
                            caster->CastSpell(target, SPELL_MAGE_SLOW, true);
                    }
                }
            }

            void Register()
            {
                OnHit += SpellHitFn(spell_mage_glyph_of_slow_SpellScript::HandleOnHit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_mage_glyph_of_slow_SpellScript();
        }
};

// Frost Nova (Water Elemental) - 33395
class spell_mage_pet_frost_nova : public SpellScriptLoader
{
    public:
        spell_mage_pet_frost_nova() : SpellScriptLoader("spell_mage_pet_frost_nova") { }

        class spell_mage_pet_frost_nova_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_mage_pet_frost_nova_SpellScript);

            bool Load()
            {
                bool result = true;

                if (!GetCaster())
                    return false;

                result &= GetCaster()->GetTypeId() == TYPEID_UNIT;

                if (!GetCaster()->GetOwner())
                    return false;

                result &= GetCaster()->GetOwner()->GetTypeId() == TYPEID_PLAYER;
                result &= GetCaster()->GetOwner()->getLevel() >= 24;

                return result;
            }

            void HandleOnHit()
            {
                if (Unit* caster = GetCaster())
                {
                    if (caster->GetOwner())
                    {
                        if (Player* _player = caster->GetOwner()->ToPlayer())
                        {
                            if (_player->GetSpecializationId(_player->GetActiveSpec()) != SPEC_MAGE_FROST)
                                return;

                            _player->CastSpell(_player, SPELL_MAGE_FINGER_OF_FROST_VISUAL, true);
                            _player->CastSpell(_player, SPELL_MAGE_FINGER_OF_FROST_EFFECT, true);
                        }
                    }
                }
            }

            void Register()
            {
                OnHit += SpellHitFn(spell_mage_pet_frost_nova_SpellScript::HandleOnHit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_mage_pet_frost_nova_SpellScript();
        }
};

// Counterspell - 2139
class spell_mage_counterspell : public SpellScriptLoader
{
    public:
        spell_mage_counterspell() : SpellScriptLoader("spell_mage_counterspell") { }

        class spell_mage_counterspell_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_mage_counterspell_SpellScript);

            void HandleOnHit()
            {
                if (Player* _player = GetCaster()->ToPlayer())
                    if (Unit* target = GetHitUnit())
                        if (_player->HasAura(SPELL_MAGE_IMPROVED_COUNTERSPELL))
                            _player->CastSpell(target, SPELL_MAGE_COUNTERSPELL_SILENCE, true);
            }

            void Register()
            {
                OnHit += SpellHitFn(spell_mage_counterspell_SpellScript::HandleOnHit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_mage_counterspell_SpellScript();
        }
};

// Called by Ice Block - 45438
// Glyph of Ice Block - 115723
class spell_mage_glyph_of_ice_block : public SpellScriptLoader
{
    public:
        spell_mage_glyph_of_ice_block() : SpellScriptLoader("spell_mage_glyph_of_ice_block") { }

        class spell_mage_glyph_of_ice_block_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_mage_glyph_of_ice_block_AuraScript);

            void OnRemove(constAuraEffectPtr /*aurEff*/, AuraEffectHandleModes /*mode*/)
            {
                if (!GetCaster())
                    return;

                if (Player* _player = GetTarget()->ToPlayer())
                {
                    if (_player->HasAura(SPELL_MAGE_GLYPH_OF_ICE_BLOCK))
                    {
                        _player->CastSpell(_player, SPELL_MAGE_GLYPH_OF_ICE_BLOCK_FROST_NOVA, true);
                        _player->CastSpell(_player, SPELL_MAGE_GLYPH_OF_ICE_BLOCK_IMMUNITY, true);
                    }
                }
            }

            void Register()
            {
                OnEffectRemove += AuraEffectRemoveFn(spell_mage_glyph_of_ice_block_AuraScript::OnRemove, EFFECT_0, SPELL_AURA_MOD_STUN, AURA_EFFECT_HANDLE_REAL);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_mage_glyph_of_ice_block_AuraScript();
        }
};

// Incanter's Ward (Cooldown marker) - 118859
class spell_mage_incanters_ward_cooldown : public SpellScriptLoader
{
    public:
        spell_mage_incanters_ward_cooldown() : SpellScriptLoader("spell_mage_incanters_ward_cooldown") { }

        class spell_mage_incanters_ward_cooldown_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_mage_incanters_ward_cooldown_AuraScript);

            void OnApply(constAuraEffectPtr /*aurEff*/, AuraEffectHandleModes /*mode*/)
            {
                if (Unit* caster = GetCaster())
                    caster->RemoveAura(SPELL_MAGE_INCANTERS_ABSORBTION_PASSIVE);
            }

            void OnRemove(constAuraEffectPtr /*aurEff*/, AuraEffectHandleModes /*mode*/)
            {
                if (Unit* caster = GetCaster())
                    if (!caster->HasAura(SPELL_MAGE_INCANTERS_ABSORBTION_PASSIVE))
                        caster->CastSpell(caster, SPELL_MAGE_INCANTERS_ABSORBTION_PASSIVE, true);
            }

            void Register()
            {
                OnEffectApply += AuraEffectApplyFn(spell_mage_incanters_ward_cooldown_AuraScript::OnApply, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
                OnEffectRemove += AuraEffectRemoveFn(spell_mage_incanters_ward_cooldown_AuraScript::OnRemove, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_mage_incanters_ward_cooldown_AuraScript();
        }
};

// Incanter's Ward - 1463
class spell_mage_incanters_ward : public SpellScriptLoader
{
    public:
        spell_mage_incanters_ward() : SpellScriptLoader("spell_mage_incanters_ward") { }

        class spell_mage_incanters_ward_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_mage_incanters_ward_AuraScript);

            float absorbTotal;
            float absorbtionAmount;

            bool Load()
            {
                absorbTotal = 0.0f;
                absorbtionAmount = 0.0f;
                return true;
            }

            void CalculateAmount(constAuraEffectPtr , int32 & amount, bool & )
            {
                if (Unit* caster = GetCaster())
                    amount += caster->SpellBaseDamageBonusDone(SPELL_SCHOOL_MASK_ARCANE);

                absorbtionAmount = float(amount);
            }

            void OnAbsorb(AuraEffectPtr aurEff, DamageInfo& dmgInfo, uint32& absorbAmount)
            {
                if (Unit* caster = dmgInfo.GetVictim())
                {
                    if (Unit* attacker = dmgInfo.GetAttacker())
                    {
                        absorbTotal += float(dmgInfo.GetDamage());

                        int32 pct = aurEff->GetSpellInfo()->Effects[EFFECT_1].CalcValue(GetCaster());
                        uint32 manaGain = CalculatePct(caster->GetMaxPower(POWER_MANA), CalculatePct(((float(dmgInfo.GetDamage()) / absorbtionAmount) * 100.0f), pct));

                        if (manaGain > caster->CountPctFromMaxMana(pct))
                            manaGain = caster->CountPctFromMaxMana(pct);

                        caster->EnergizeBySpell(caster, SPELL_MAGE_INCANTERS_WARD_ENERGIZE, manaGain, POWER_MANA);
                    }
                }
            }

            void OnRemove(constAuraEffectPtr /*aurEff*/, AuraEffectHandleModes /*mode*/)
            {
                if (Unit* caster = GetCaster())
                {
                    int32 damageGain = CalculatePct(sSpellMgr->GetSpellInfo(SPELL_MAGE_INCANTERS_ABSORBTION)->Effects[0].BasePoints, ((absorbTotal / absorbtionAmount) * 100.0f));
                    if (!damageGain)
                        return;

                    if (damageGain > 30)
                        damageGain = 30;

                    caster->CastCustomSpell(caster, SPELL_MAGE_INCANTERS_ABSORBTION, &damageGain, NULL, NULL, true);
                }
            }

            void Register()
            {
                DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_mage_incanters_ward_AuraScript::CalculateAmount, EFFECT_0, SPELL_AURA_SCHOOL_ABSORB);
                OnEffectAbsorb += AuraEffectAbsorbFn(spell_mage_incanters_ward_AuraScript::OnAbsorb, EFFECT_0);
                OnEffectRemove += AuraEffectRemoveFn(spell_mage_incanters_ward_AuraScript::OnRemove, EFFECT_0, SPELL_AURA_SCHOOL_ABSORB, AURA_EFFECT_HANDLE_REAL);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_mage_incanters_ward_AuraScript();
        }
};

// Arcane Missiles - 5143
class spell_mage_arcane_missile : public SpellScriptLoader
{
    public:
        spell_mage_arcane_missile() : SpellScriptLoader("spell_mage_arcane_missile") { }

        class spell_mage_arcane_missile_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_mage_arcane_missile_AuraScript);

            void OnApply(constAuraEffectPtr /*aurEff*/, AuraEffectHandleModes /*mode*/)
            {
                if (!GetCaster())
                    return;

                GetCaster()->CastSpell(GetCaster(), SPELL_MAGE_ARCANE_CHARGE, true);

                if (Player* _player = GetCaster()->ToPlayer())
                    if (AuraPtr arcaneMissiles = _player->GetAura(SPELL_MAGE_ARCANE_MISSILES))
                        arcaneMissiles->DropCharge();
            }

            void Register()
            {
                OnEffectApply += AuraEffectApplyFn(spell_mage_arcane_missile_AuraScript::OnApply, EFFECT_1, SPELL_AURA_PERIODIC_TRIGGER_SPELL, AURA_EFFECT_HANDLE_REAL);
            }

        };

        AuraScript* GetAuraScript() const
        {
            return new spell_mage_arcane_missile_AuraScript();
        }
};

// Cauterize - 86949
class spell_mage_cauterize : public SpellScriptLoader
{
    public:
        spell_mage_cauterize() : SpellScriptLoader("spell_mage_cauterize") { }

        class spell_mage_cauterize_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_mage_cauterize_AuraScript);

            uint32 absorbChance;
            uint32 healtPct;

            bool Load()
            {
                absorbChance = GetSpellInfo()->Effects[EFFECT_0].CalcValue(GetCaster());
                healtPct = GetSpellInfo()->Effects[EFFECT_1].CalcValue(GetCaster());
                return GetUnitOwner()->ToPlayer();
            }

            void CalculateAmount(constAuraEffectPtr /*auraEffect*/, int32& amount, bool& /*canBeRecalculated*/)
            {
                amount = -1;
            }

            void Absorb(AuraEffectPtr /*auraEffect*/, DamageInfo& dmgInfo, uint32& absorbAmount)
            {
                Unit* target = GetTarget();

                if (dmgInfo.GetDamage() < target->GetHealth())
                    return;

                if (target->ToPlayer()->HasSpellCooldown(SPELL_MAGE_CAUTERIZE))
                    return;

                if (!roll_chance_i(absorbChance))
                    return;

                int bp1 = target->CountPctFromMaxHealth(healtPct);
                target->CastCustomSpell(target, SPELL_MAGE_CAUTERIZE, NULL, &bp1, NULL, true);
                target->ToPlayer()->AddSpellCooldown(SPELL_MAGE_CAUTERIZE, 0, time(NULL) + 60);

                absorbAmount = dmgInfo.GetDamage();
            }

            void Register()
            {
                DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_mage_cauterize_AuraScript::CalculateAmount, EFFECT_0, SPELL_AURA_SCHOOL_ABSORB);
                OnEffectAbsorb += AuraEffectAbsorbFn(spell_mage_cauterize_AuraScript::Absorb, EFFECT_0);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_mage_cauterize_AuraScript();
        }
};

// Called by Nether Tempest - 114923, Frost Bomb - 112948 and Living Bomb - 44457
// Pyromaniac - 132209
class spell_mage_pyromaniac : public SpellScriptLoader
{
    public:
        spell_mage_pyromaniac() : SpellScriptLoader("spell_mage_pyromaniac") { }

        class spell_mage_pyromaniac_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_mage_pyromaniac_SpellScript);

            void HandleOnHit()
            {
                if (Player* _player = GetCaster()->ToPlayer())
                    if (Unit* target = GetHitUnit())
                        if (_player->HasAura(SPELL_MAGE_PYROMANIAC_AURA))
                            _player->CastSpell(target, SPELL_MAGE_PYROMANIAC_DAMAGE_DONE, true);
            }

            void Register()
            {
                OnHit += SpellHitFn(spell_mage_pyromaniac_SpellScript::HandleOnHit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_mage_pyromaniac_SpellScript();
        }
};

class CheckArcaneBarrageImpactPredicate
{
    public:
        CheckArcaneBarrageImpactPredicate(Unit* caster, Unit* mainTarget) : _caster(caster), _mainTarget(mainTarget) {}

        bool operator()(Unit* target)
        {
            if (!_caster || !_mainTarget)
                return true;

            if (!_caster->IsValidAttackTarget(target))
                return true;

            if (!target->IsWithinLOSInMap(_caster))
                return true;

            if (!_caster->isInFront(target))
                return true;

            if (target->GetGUID() == _caster->GetGUID())
                return true;

            if (target->GetGUID() == _mainTarget->GetGUID())
                return true;

            return false;
        }

    private:
        Unit* _caster;
        Unit* _mainTarget;
};

// Arcane Barrage - 44425
class spell_mage_arcane_barrage : public SpellScriptLoader
{
    public:
        spell_mage_arcane_barrage() : SpellScriptLoader("spell_mage_arcane_barrage") { }

        class spell_mage_arcane_barrage_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_mage_arcane_barrage_SpellScript);

            void HandleAfterHit()
            {
                if (Player* _player = GetCaster()->ToPlayer())
                {
                    if (Unit* target = GetHitUnit())
                    {
                        uint8 chargeCount = 0;
                        int32 bp = 0;

                        if (AuraPtr arcaneCharge = _player->GetAura(SPELL_MAGE_ARCANE_CHARGE))
                        {
                            chargeCount = arcaneCharge->GetStackAmount();
                            _player->RemoveAura(SPELL_MAGE_ARCANE_CHARGE);
                        }

                        if (chargeCount)
                        {
                            bp = GetHitDamage() / 2;

                            std::list<Unit*> targetList;

                            target->GetAttackableUnitListInRange(targetList, 10.0f);
                            targetList.remove_if(CheckArcaneBarrageImpactPredicate(_player, target));

                            JadeCore::Containers::RandomResizeList(targetList, chargeCount);

                            for (auto itr : targetList)
                                target->CastCustomSpell(itr, SPELL_MAGE_ARCANE_BARRAGE_TRIGGERED, &bp, NULL, NULL, true, 0, NULLAURA_EFFECT, _player->GetGUID());
                        }
                    }
                }
            }

            void Register()
            {
                AfterHit += SpellHitFn(spell_mage_arcane_barrage_SpellScript::HandleAfterHit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_mage_arcane_barrage_SpellScript();
        }
};

// Arcane Explosion - 1449
class spell_mage_arcane_explosion : public SpellScriptLoader
{
    public:
        spell_mage_arcane_explosion() : SpellScriptLoader("spell_mage_arcane_explosion") { }

        class spell_mage_arcane_explosion_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_mage_arcane_explosion_SpellScript);

            void HandleOnHit()
            {
                if (Player* _player = GetCaster()->ToPlayer())
                    if (Unit* target = GetHitUnit())
                        if (_player->GetSpecializationId(_player->GetActiveSpec()) == SPEC_MAGE_ARCANE)
                            if (AuraPtr arcaneCharge = _player->GetAura(SPELL_MAGE_ARCANE_CHARGE))
                                arcaneCharge->RefreshDuration();
            }

            void Register()
            {
                OnHit += SpellHitFn(spell_mage_arcane_explosion_SpellScript::HandleOnHit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_mage_arcane_explosion_SpellScript();
        }
};

// Frostbolt - 116
class spell_mage_frostbolt : public SpellScriptLoader
{
    public:
        spell_mage_frostbolt() : SpellScriptLoader("spell_mage_frostbolt") { }

        class spell_mage_frostbolt_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_mage_frostbolt_SpellScript);

            SpellCastResult CheckTarget()
            {
                if (!GetExplTargetUnit())
                    return SPELL_FAILED_NO_VALID_TARGETS;
                else if (GetExplTargetUnit()->GetGUID() == GetCaster()->GetGUID())
                    return SPELL_FAILED_BAD_TARGETS;
                else if (GetExplTargetUnit()->GetTypeId() == TYPEID_PLAYER && !GetExplTargetUnit()->IsPvP())
                {
                    if (GetCaster()->ToPlayer() && GetCaster()->ToPlayer()->duel)
                        if (GetCaster()->ToPlayer()->duel->opponent->GetGUID() == GetExplTargetUnit()->GetGUID())
                            return SPELL_CAST_OK;

                    return SPELL_FAILED_BAD_TARGETS;
                }
                else if (GetExplTargetUnit()->GetOwner() != GetCaster())
                {
                    if (GetCaster()->IsValidAttackTarget(GetExplTargetUnit()))
                        return SPELL_CAST_OK;

                    return SPELL_FAILED_BAD_TARGETS;
                }

                return SPELL_CAST_OK;
            }

            void Register()
            {
                OnCheckCast += SpellCheckCastFn(spell_mage_frostbolt_SpellScript::CheckTarget);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_mage_frostbolt_SpellScript();
        }
};

// Called by Evocation - 12051
// Invocation - 114003
class spell_mage_invocation : public SpellScriptLoader
{
    public:
        spell_mage_invocation() : SpellScriptLoader("spell_mage_invocation") { }

        class spell_mage_invocation_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_mage_invocation_AuraScript);

            void AfterRemove(constAuraEffectPtr aurEff, AuraEffectHandleModes /*mode*/)
            {
                AuraRemoveMode removeMode = GetTargetApplication()->GetRemoveMode();
                if (removeMode != AURA_REMOVE_BY_EXPIRE)
                    return;

                if (Unit* caster = GetCaster())
                {
                    if (caster->HasAura(SPELL_MAGE_INVOCATION))
                    {
                        caster->CastSpell(caster, SPELL_MAGE_INVOKERS_ENERGY, true);

                        if (caster->HasAura(SPELL_MAGE_GLYPH_OF_EVOCATION))
                            caster->HealBySpell(caster, sSpellMgr->GetSpellInfo(12051), caster->CountPctFromMaxHealth(40), false);
                    }
                }
            }

            void Register()
            {
                AfterEffectRemove += AuraEffectRemoveFn(spell_mage_invocation_AuraScript::AfterRemove, EFFECT_0, SPELL_AURA_OBS_MOD_POWER, AURA_EFFECT_HANDLE_REAL);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_mage_invocation_AuraScript();
        }
};

// Frost Bomb - 112948
class spell_mage_frost_bomb : public SpellScriptLoader
{
    public:
        spell_mage_frost_bomb() : SpellScriptLoader("spell_mage_frost_bomb") { }

        class spell_mage_frost_bomb_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_mage_frost_bomb_AuraScript);

            void AfterRemove(constAuraEffectPtr aurEff, AuraEffectHandleModes /*mode*/)
            {
                AuraRemoveMode removeMode = GetTargetApplication()->GetRemoveMode();
                if (removeMode != AURA_REMOVE_BY_EXPIRE)
                    return;

                if (Unit* caster = GetCaster())
                {
                    caster->CastSpell(GetTarget(), SPELL_MAGE_FROST_BOMB_TRIGGERED, true);

                    if (caster->HasAura(SPELL_MAGE_BRAIN_FREEZE))
                        caster->CastSpell(caster, SPELL_MAGE_BRAIN_FREEZE_TRIGGERED, true);
                }
            }

            void Register()
            {
                AfterEffectRemove += AuraEffectRemoveFn(spell_mage_frost_bomb_AuraScript::AfterRemove, EFFECT_1, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_mage_frost_bomb_AuraScript();
        }
};

class CheckNetherImpactPredicate
{
    public:
        CheckNetherImpactPredicate(Unit* caster, Unit* mainTarget) : _caster(caster), _mainTarget(mainTarget) {}

        bool operator()(Unit* target)
        {
            if (!_caster || !_mainTarget)
                return true;

            if (!_caster->IsValidAttackTarget(target))
                return true;

            if (!target->IsWithinLOSInMap(_caster))
                return true;

            if (!_caster->isInFront(target))
                return true;

            if (target->GetGUID() == _caster->GetGUID())
                return true;

            if (target->GetGUID() == _mainTarget->GetGUID())
                return true;

            return false;
        }

    private:
        Unit* _caster;
        Unit* _mainTarget;
};

// Nether Tempest - 114923
class spell_mage_nether_tempest : public SpellScriptLoader
{
    public:
        spell_mage_nether_tempest() : SpellScriptLoader("spell_mage_nether_tempest") { }

        class spell_mage_nether_tempest_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_mage_nether_tempest_AuraScript);

            void OnTick(constAuraEffectPtr aurEff)
            {
                if (GetCaster())
                {
                    if (Player* _player = GetCaster()->ToPlayer())
                    {
                        std::list<Unit*> targetList;

                        GetTarget()->GetAttackableUnitListInRange(targetList, 10.0f);
                        targetList.remove_if(CheckNetherImpactPredicate(_player, GetTarget()));

                        JadeCore::Containers::RandomResizeList(targetList, 1);

                        for (auto itr : targetList)
                        {
                            GetCaster()->CastSpell(itr, SPELL_MAGE_NETHER_TEMPEST_DIRECT_DAMAGE, true);
                            GetCaster()->CastSpell(itr, SPELL_MAGE_NETHER_TEMPEST_VISUAL, true);
                            GetTarget()->CastSpell(itr, SPELL_MAGE_NETHER_TEMPEST_MISSILE, true);
                        }

                        if (GetCaster()->HasAura(SPELL_MAGE_BRAIN_FREEZE))
                            if (roll_chance_i(10))
                                GetCaster()->CastSpell(GetCaster(), SPELL_MAGE_BRAIN_FREEZE_TRIGGERED, true);
                    }
                }
            }

            void Register()
            {
                OnEffectPeriodic += AuraEffectPeriodicFn(spell_mage_nether_tempest_AuraScript::OnTick, EFFECT_0, SPELL_AURA_PERIODIC_DAMAGE);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_mage_nether_tempest_AuraScript();
        }
};

// Blazing Speed - 108843
class spell_mage_blazing_speed : public SpellScriptLoader
{
    public:
        spell_mage_blazing_speed() : SpellScriptLoader("spell_mage_blazing_speed") { }

        class spell_mage_blazing_speed_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_mage_blazing_speed_SpellScript);

            void HandleOnHit()
            {
                if (Player* _player = GetCaster()->ToPlayer())
                    _player->RemoveMovementImpairingAuras();
            }

            void Register()
            {
                OnHit += SpellHitFn(spell_mage_blazing_speed_SpellScript::HandleOnHit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_mage_blazing_speed_SpellScript();
        }
};

// Frostjaw - 102051
class spell_mage_frostjaw : public SpellScriptLoader
{
    public:
        spell_mage_frostjaw() : SpellScriptLoader("spell_mage_frostjaw") { }

        class spell_mage_frostjaw_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_mage_frostjaw_SpellScript);

            void HandleOnHit()
            {
                if (Player* _player = GetCaster()->ToPlayer())
                {
                    if (Unit* target = GetHitUnit())
                    {
                        if (target->GetTypeId() == TYPEID_PLAYER)
                        {
                            if (AuraPtr frostjaw = target->GetAura(SPELL_MAGE_FROSTJAW, _player->GetGUID()))
                            {
                                // Only half time against players
                                frostjaw->SetDuration(frostjaw->GetMaxDuration() / 2);
                                frostjaw->SetMaxDuration(frostjaw->GetDuration());
                            }
                        }
                    }
                }
            }

            void Register()
            {
                OnHit += SpellHitFn(spell_mage_frostjaw_SpellScript::HandleOnHit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_mage_frostjaw_SpellScript();
        }
};

// Combustion - 11129
class spell_mage_combustion : public SpellScriptLoader
{
    public:
        spell_mage_combustion() : SpellScriptLoader("spell_mage_combustion") { }

        class spell_mage_combustion_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_mage_combustion_SpellScript);

            void HandleOnHit()
            {
                if (Player* _player = GetCaster()->ToPlayer())
                {
                    if (Unit* target = GetHitUnit())
                    {
                        _player->CastSpell(target, SPELL_MAGE_COMBUSTION_IMPACT, true);

                        if (_player->HasSpellCooldown(SPELL_MAGE_INFERNO_BLAST))
                        {
                            _player->RemoveSpellCooldown(SPELL_MAGE_INFERNO_BLAST, true);
                            _player->RemoveSpellCooldown(SPELL_MAGE_INFERNO_BLAST_IMPACT, true);
                        }

                        int32 combustionBp = 0;

                        Unit::AuraEffectList const& aurasPereodic = target->GetAuraEffectsByType(SPELL_AURA_PERIODIC_DAMAGE);
                        for (Unit::AuraEffectList::const_iterator i = aurasPereodic.begin(); i !=  aurasPereodic.end(); ++i)
                        {
                            if ((*i)->GetCasterGUID() != _player->GetGUID() || (*i)->GetSpellInfo()->SchoolMask != SPELL_SCHOOL_MASK_FIRE)
                                continue;

                            if (!(*i)->GetAmplitude())
                                continue;

                            combustionBp += _player->SpellDamageBonusDone(target, (*i)->GetSpellInfo(), (*i)->GetAmount(), DOT) * 1000 / (*i)->GetAmplitude();
                        }

                        if (combustionBp)
                            _player->CastCustomSpell(target, SPELL_MAGE_COMBUSTION_DOT, &combustionBp, NULL, NULL, true);
                    }
                }
            }

            void Register()
            {
                OnHit += SpellHitFn(spell_mage_combustion_SpellScript::HandleOnHit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_mage_combustion_SpellScript();
        }
};

class CheckInfernoBlastImpactPredicate
{
    public:
        CheckInfernoBlastImpactPredicate(Unit* caster, Unit* mainTarget) : _caster(caster), _mainTarget(mainTarget) {}

        bool operator()(Unit* target)
        {
            if (!_caster || !_mainTarget)
                return true;

            if (!_caster->IsValidAttackTarget(target))
                return true;

            if (!target->IsWithinLOSInMap(_caster))
                return true;

            if (!_caster->isInFront(target))
                return true;

            if (target->GetGUID() == _caster->GetGUID())
                return true;

            if (target->GetGUID() == _mainTarget->GetGUID())
                return true;

            return false;
        }

    private:
        Unit* _caster;
        Unit* _mainTarget;
};

// Inferno Blast - 108853
class spell_mage_inferno_blast : public SpellScriptLoader
{
    public:
        spell_mage_inferno_blast() : SpellScriptLoader("spell_mage_inferno_blast") { }

        class spell_mage_inferno_blast_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_mage_inferno_blast_SpellScript);

            void HandleOnHit()
            {
                if (Player* _player = GetCaster()->ToPlayer())
                {
                    if (Unit* target = GetHitUnit())
                    {
                        std::list<Unit*> targetList;
                        int32 combustionBp = 0;

                        _player->CastSpell(target, SPELL_MAGE_INFERNO_BLAST_IMPACT, true);

                        // Spreads any Pyroblast, Ignite, and Combustion effects to up to 2 nearby enemy targets within 10 yards

                        target->GetAttackableUnitListInRange(targetList, 10.0f);

                        targetList.remove_if(CheckInfernoBlastImpactPredicate(_player, target));

                        if (targetList.size() > 2)
                            JadeCore::Containers::RandomResizeList(targetList, 2);

                        for (auto itr : targetList)
                        {
                            // 1 : Ignite
                            if (target->HasAura(SPELL_MAGE_IGNITE, _player->GetGUID()))
                            {
                                float value = _player->GetFloatValue(PLAYER_MASTERY) * 1.5f / 100.0f;

                                int32 igniteBp = 0;

                                if (itr->HasAura(SPELL_MAGE_IGNITE, _player->GetGUID()))
                                    igniteBp += itr->GetRemainingPeriodicAmount(_player->GetGUID(), SPELL_MAGE_IGNITE, SPELL_AURA_PERIODIC_DAMAGE);

                                igniteBp += int32(GetHitDamage() * value / 2);

                                _player->CastCustomSpell(itr, SPELL_MAGE_IGNITE, &igniteBp, NULL, NULL, true);
                            }

                            // 2 : Pyroblast
                            if (target->HasAura(SPELL_MAGE_PYROBLAST, _player->GetGUID()))
                                _player->AddAura(SPELL_MAGE_PYROBLAST, itr);

                            // 3 : Combustion
                            if (target->HasAura(SPELL_MAGE_COMBUSTION_DOT, _player->GetGUID()))
                            {
                                if (itr->HasAura(SPELL_MAGE_PYROBLAST, _player->GetGUID()))
                                {
                                    combustionBp += _player->CalculateSpellDamage(target, sSpellMgr->GetSpellInfo(SPELL_MAGE_PYROBLAST), 1);
                                    combustionBp = _player->SpellDamageBonusDone(target, sSpellMgr->GetSpellInfo(SPELL_MAGE_PYROBLAST), combustionBp, DOT);
                                }
                                if (itr->HasAura(SPELL_MAGE_IGNITE, _player->GetGUID()))
                                    combustionBp += itr->GetRemainingPeriodicAmount(_player->GetGUID(), SPELL_MAGE_IGNITE, SPELL_AURA_PERIODIC_DAMAGE);

                                if (combustionBp)
                                    _player->CastCustomSpell(itr, SPELL_MAGE_COMBUSTION_DOT, &combustionBp, NULL, NULL, true);
                            }
                        }
                    }
                }
            }

            void Register()
            {
                OnHit += SpellHitFn(spell_mage_inferno_blast_SpellScript::HandleOnHit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_mage_inferno_blast_SpellScript();
        }
};

// Arcane Brillance - 1459
class spell_mage_arcane_brilliance : public SpellScriptLoader
{
    public:
        spell_mage_arcane_brilliance() : SpellScriptLoader("spell_mage_arcane_brilliance") { }

        class spell_mage_arcane_brilliance_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_mage_arcane_brilliance_SpellScript);

            void HandleOnHit()
            {
                if (Player* _player = GetCaster()->ToPlayer())
                {
                    _player->AddAura(SPELL_MAGE_ARCANE_BRILLIANCE, _player);

                    std::list<Unit*> memberList;
                    _player->GetPartyMembers(memberList);

                    for (auto itr : memberList)
                        _player->AddAura(SPELL_MAGE_ARCANE_BRILLIANCE, itr);
                }
            }

            void Register()
            {
                OnHit += SpellHitFn(spell_mage_arcane_brilliance_SpellScript::HandleOnHit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_mage_arcane_brilliance_SpellScript();
        }
};

// Replenish Mana - 5405
class spell_mage_replenish_mana : public SpellScriptLoader
{
    public:
        spell_mage_replenish_mana() : SpellScriptLoader("spell_mage_replenish_mana") { }

        class spell_mage_replenish_mana_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_mage_replenish_mana_SpellScript);

            void HandleOnHit()
            {
                if (Player* _player = GetCaster()->ToPlayer())
                    _player->CastSpell(_player, 10052, true);
            }

            void Register()
            {
                OnHit += SpellHitFn(spell_mage_replenish_mana_SpellScript::HandleOnHit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_mage_replenish_mana_SpellScript();
        }
};

// Evocation - 12051
class spell_mage_evocation : public SpellScriptLoader
{
    public:
        spell_mage_evocation() : SpellScriptLoader("spell_mage_evocation") { }

        class spell_mage_evocation_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_mage_evocation_SpellScript);

            void HandleOnHit()
            {
                if (Player* _player = GetCaster()->ToPlayer())
                    _player->EnergizeBySpell(_player, GetSpellInfo()->Id, int32(_player->GetMaxPower(POWER_MANA) * 0.15), POWER_MANA);
            }

            void Register()
            {
                OnHit += SpellHitFn(spell_mage_evocation_SpellScript::HandleOnHit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_mage_evocation_SpellScript();
        }
};

// Conjure Refreshment - 42955
class spell_mage_conjure_refreshment : public SpellScriptLoader
{
    public:
        spell_mage_conjure_refreshment() : SpellScriptLoader("spell_mage_conjure_refreshment") { }

        class spell_mage_conjure_refreshment_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_mage_conjure_refreshment_SpellScript);

            void HandleOnHit()
            {
                if (Player* _player = GetCaster()->ToPlayer())
                {
                    if (_player->getLevel() < 44)
                        _player->CastSpell(_player, SPELL_MAGE_CONJURE_REFRESHMENT_R1, true);
                    else if (_player->getLevel() < 54)
                        _player->CastSpell(_player, SPELL_MAGE_CONJURE_REFRESHMENT_R2, true);
                    else if (_player->getLevel() < 64)
                        _player->CastSpell(_player, SPELL_MAGE_CONJURE_REFRESHMENT_R3, true);
                    else if (_player->getLevel() < 74)
                        _player->CastSpell(_player, SPELL_MAGE_CONJURE_REFRESHMENT_R4, true);
                    else if (_player->getLevel() < 80)
                        _player->CastSpell(_player, SPELL_MAGE_CONJURE_REFRESHMENT_R5, true);
                    else if (_player->getLevel() < 85)
                        _player->CastSpell(_player, SPELL_MAGE_CONJURE_REFRESHMENT_R6, true);
                    else if (_player->getLevel() < 90)
                        _player->CastSpell(_player, SPELL_MAGE_CONJURE_REFRESHMENT_R7, true);
                    else
                        _player->CastSpell(_player, SPELL_MAGE_CONJURE_REFRESHMENT_R8, true);
                }
            }

            void Register()
            {
                OnHit += SpellHitFn(spell_mage_conjure_refreshment_SpellScript::HandleOnHit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_mage_conjure_refreshment_SpellScript();
        }
};

// Time Warp - 80353
class spell_mage_time_warp : public SpellScriptLoader
{
    public:
        spell_mage_time_warp() : SpellScriptLoader("spell_mage_time_warp") { }

        class spell_mage_time_warp_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_mage_time_warp_SpellScript);

            void RemoveInvalidTargets(std::list<WorldObject*>& targets)
            {
                targets.remove_if(JadeCore::UnitAuraCheck(true, HUNTER_SPELL_INSANITY));
                targets.remove_if(JadeCore::UnitAuraCheck(true, SPELL_SHAMAN_EXHAUSTED));
                targets.remove_if(JadeCore::UnitAuraCheck(true, SPELL_SHAMAN_SATED));
                targets.remove_if(JadeCore::UnitAuraCheck(true, SPELL_MAGE_TEMPORAL_DISPLACEMENT));
            }

            void ApplyDebuff()
            {
                if (Unit* target = GetHitUnit())
                    target->CastSpell(target, SPELL_MAGE_TEMPORAL_DISPLACEMENT, true);
            }

            void Register()
            {
                OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_mage_time_warp_SpellScript::RemoveInvalidTargets, EFFECT_0, TARGET_UNIT_CASTER_AREA_RAID);
                OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_mage_time_warp_SpellScript::RemoveInvalidTargets, EFFECT_1, TARGET_UNIT_CASTER_AREA_RAID);
                OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_mage_time_warp_SpellScript::RemoveInvalidTargets, EFFECT_2, TARGET_UNIT_CASTER_AREA_RAID);
                AfterHit += SpellHitFn(spell_mage_time_warp_SpellScript::ApplyDebuff);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_mage_time_warp_SpellScript();
        }
};

// Alter Time - 127140 (overrided)
class spell_mage_alter_time_overrided : public SpellScriptLoader
{
    public:
        spell_mage_alter_time_overrided() : SpellScriptLoader("spell_mage_alter_time_overrided") { }

        class spell_mage_alter_time_overrided_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_mage_alter_time_overrided_SpellScript);

            void HandleAfterCast()
            {
                if (Player* _player = GetCaster()->ToPlayer())
                    if (_player->HasAura(SPELL_MAGE_ALTER_TIME))
                        _player->RemoveAura(SPELL_MAGE_ALTER_TIME);
            }

            void Register()
            {
                AfterCast += SpellCastFn(spell_mage_alter_time_overrided_SpellScript::HandleAfterCast);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_mage_alter_time_overrided_SpellScript();
        }
};

// Alter Time - 110909
class spell_mage_alter_time : public SpellScriptLoader
{
    public:
        spell_mage_alter_time() : SpellScriptLoader("spell_mage_alter_time") { }

        class spell_mage_alter_time_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_mage_alter_time_AuraScript);

            void OnRemove(constAuraEffectPtr /*aurEff*/, AuraEffectHandleModes /*mode*/)
            {
                if (Player* _player = GetTarget()->ToPlayer())
                {
                    AuraRemoveMode removeMode = GetTargetApplication()->GetRemoveMode();
                    if (removeMode == AURA_REMOVE_BY_DEATH)
                        return;

                    std::list<Creature*> mirrorList;
                    _player->GetCreatureListWithEntryInGrid(mirrorList, NPC_PAST_SELF, 50.0f);

                    if (mirrorList.empty())
                        return;

                    for (std::list<Creature*>::const_iterator itr = mirrorList.begin(); itr != mirrorList.end(); ++itr)
                        if (Creature* pMirror = (*itr)->ToCreature())
                            if (TempSummon* pastSelf = pMirror->ToTempSummon())
                                if (pastSelf->isAlive() && pastSelf->IsInWorld())
                                    if (pastSelf->GetSummoner() && pastSelf->GetSummoner()->GetGUID() == _player->GetGUID())
                                        pastSelf->AI()->DoAction(1);
                }
            }

            void Register()
            {
                OnEffectRemove += AuraEffectRemoveFn(spell_mage_alter_time_AuraScript::OnRemove, EFFECT_0, SPELL_AURA_OVERRIDE_ACTIONBAR_SPELLS, AURA_EFFECT_HANDLE_REAL);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_mage_alter_time_AuraScript();
        }
};

// Cold Snap - 11958
class spell_mage_cold_snap : public SpellScriptLoader
{
    public:
        spell_mage_cold_snap() : SpellScriptLoader("spell_mage_cold_snap") { }

        class spell_mage_cold_snap_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_mage_cold_snap_SpellScript);

            bool Load()
            {
                return GetCaster()->GetTypeId() == TYPEID_PLAYER;
            }

            void HandleDummy(SpellEffIndex /*effIndex*/)
            {
                if (Player* player = GetCaster()->ToPlayer())
                {
                    // Resets cooldown of Ice Block, Frost Nova and Cone of Cold
                    player->RemoveSpellCooldown(SPELL_MAGE_ICE_BLOCK, true);
                    player->RemoveSpellCooldown(SPELL_MAGE_FROST_NOVA, true);
                    player->RemoveSpellCooldown(SPELL_MAGE_CONE_OF_COLD, true);
                }
            }

            void Register()
            {
                // add dummy effect spell handler to Cold Snap
                OnEffectHit += SpellEffectFn(spell_mage_cold_snap_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_mage_cold_snap_SpellScript();
        }
};

class spell_mage_incanters_absorbtion_base_AuraScript : public AuraScript
{
    public:
        enum Spells
        {
            SPELL_MAGE_INCANTERS_ABSORBTION_TRIGGERED = 44413,
            SPELL_MAGE_INCANTERS_ABSORBTION_R1 = 44394,
        };

        bool Validate(SpellInfo const* /*spellEntry*/)
        {
            return sSpellMgr->GetSpellInfo(SPELL_MAGE_INCANTERS_ABSORBTION_TRIGGERED)
                && sSpellMgr->GetSpellInfo(SPELL_MAGE_INCANTERS_ABSORBTION_R1);
        }

        void Trigger(AuraEffectPtr aurEff, DamageInfo & /*dmgInfo*/, uint32 & absorbAmount)
        {
            Unit* target = GetTarget();

            if (AuraEffectPtr talentAurEff = target->GetAuraEffectOfRankedSpell(SPELL_MAGE_INCANTERS_ABSORBTION_R1, EFFECT_0))
            {
                int32 bp = CalculatePct(absorbAmount, talentAurEff->GetAmount());
                target->CastCustomSpell(target, SPELL_MAGE_INCANTERS_ABSORBTION_TRIGGERED, &bp, NULL, NULL, true, NULL, aurEff);
            }
        }
};

// Incanter's Absorption
class spell_mage_incanters_absorbtion_absorb : public SpellScriptLoader
{
    public:
        spell_mage_incanters_absorbtion_absorb() : SpellScriptLoader("spell_mage_incanters_absorbtion_absorb") { }

        class spell_mage_incanters_absorbtion_absorb_AuraScript : public spell_mage_incanters_absorbtion_base_AuraScript
        {
            PrepareAuraScript(spell_mage_incanters_absorbtion_absorb_AuraScript);

            void Register()
            {
                 AfterEffectAbsorb += AuraEffectAbsorbFn(spell_mage_incanters_absorbtion_absorb_AuraScript::Trigger, EFFECT_0);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_mage_incanters_absorbtion_absorb_AuraScript();
        }
};

// Incanter's Absorption
class spell_mage_incanters_absorbtion_manashield : public SpellScriptLoader
{
    public:
        spell_mage_incanters_absorbtion_manashield() : SpellScriptLoader("spell_mage_incanters_absorbtion_manashield") { }

        class spell_mage_incanters_absorbtion_manashield_AuraScript : public spell_mage_incanters_absorbtion_base_AuraScript
        {
            PrepareAuraScript(spell_mage_incanters_absorbtion_manashield_AuraScript);

            void Register()
            {
                 AfterEffectManaShield += AuraEffectManaShieldFn(spell_mage_incanters_absorbtion_manashield_AuraScript::Trigger, EFFECT_0);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_mage_incanters_absorbtion_manashield_AuraScript();
        }
};

// Living Bomb - 44457
class spell_mage_living_bomb : public SpellScriptLoader
{
    public:
        spell_mage_living_bomb() : SpellScriptLoader("spell_mage_living_bomb") { }

        class spell_mage_living_bomb_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_mage_living_bomb_AuraScript);

            void AfterRemove(constAuraEffectPtr aurEff, AuraEffectHandleModes /*mode*/)
            {
                AuraRemoveMode removeMode = GetTargetApplication()->GetRemoveMode();
                if (removeMode != AURA_REMOVE_BY_DEATH && removeMode != AURA_REMOVE_BY_EXPIRE)
                    return;

                if (Unit* caster = GetCaster())
                {
                    caster->CastSpell(GetTarget(), SPELL_MAGE_LIVING_BOMB_TRIGGERED, true);

                    if (caster->HasAura(SPELL_MAGE_BRAIN_FREEZE))
                        caster->CastSpell(caster, SPELL_MAGE_BRAIN_FREEZE_TRIGGERED, true);
                }
            }

            void Register()
            {
                AfterEffectRemove += AuraEffectRemoveFn(spell_mage_living_bomb_AuraScript::AfterRemove, EFFECT_1, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_mage_living_bomb_AuraScript();
        }
};

void AddSC_mage_spell_scripts()
{
    new spell_mage_flamestrike();
    new spell_mage_greater_invisibility_removed();
    new spell_mage_greater_invisibility_triggered();
    new spell_mage_glyph_of_slow();
    new spell_mage_pet_frost_nova();
    new spell_mage_counterspell();
    new spell_mage_glyph_of_ice_block();
    new spell_mage_incanters_ward_cooldown();
    new spell_mage_incanters_ward();
    new spell_mage_arcane_missile();
    new spell_mage_cauterize();
    new spell_mage_pyromaniac();
    new spell_mage_arcane_barrage();
    new spell_mage_arcane_explosion();
    new spell_mage_frostbolt();
    new spell_mage_invocation();
    new spell_mage_frost_bomb();
    new spell_mage_nether_tempest();
    new spell_mage_blazing_speed();
    new spell_mage_frostjaw();
    new spell_mage_combustion();
    new spell_mage_inferno_blast();
    new spell_mage_arcane_brilliance();
    new spell_mage_replenish_mana();
    new spell_mage_evocation();
    new spell_mage_conjure_refreshment();
    new spell_mage_time_warp();
    new spell_mage_alter_time_overrided();
    new spell_mage_alter_time();
    new spell_mage_cold_snap();
    new spell_mage_incanters_absorbtion_absorb();
    new spell_mage_incanters_absorbtion_manashield();
    new spell_mage_living_bomb();
}
