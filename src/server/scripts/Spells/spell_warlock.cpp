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
 * Scripts for spells with SPELLFAMILY_WARLOCK and SPELLFAMILY_GENERIC spells used by warlock players.
 * Ordered alphabetically using scriptname.
 * Scriptnames of files in this file should be prefixed with "spell_warl_".
 */

#include "ScriptMgr.h"
#include "SpellScript.h"
#include "SpellAuraEffects.h"

enum WarlockSpells
{
    WARLOCK_DEMONIC_EMPOWERMENT_SUCCUBUS    = 54435,
    WARLOCK_DEMONIC_EMPOWERMENT_VOIDWALKER  = 54443,
    WARLOCK_DEMONIC_EMPOWERMENT_FELGUARD    = 54508,
    WARLOCK_DEMONIC_EMPOWERMENT_FELHUNTER   = 54509,
    WARLOCK_DEMONIC_EMPOWERMENT_IMP         = 54444,
    WARLOCK_DEMONIC_CIRCLE_SUMMON           = 48018,
    WARLOCK_DEMONIC_CIRCLE_TELEPORT         = 48020,
    WARLOCK_DEMONIC_CIRCLE_ALLOW_CAST       = 62388,
    WARLOCK_UNSTABLE_AFFLICTION_DISPEL      = 31117,
    WARLOCK_GLYPH_OF_FEAR                   = 56244,
    WARLOCK_FEAR_EFFECT                     = 118699,
    WARLOCK_GLYPH_OF_FEAR_EFFECT            = 130616,
    WARLOCK_CREATE_HEALTHSTONE              = 23517,
    WARLOCK_HARVEST_LIFE_HEAL               = 125314,
    WARLOCK_DRAIN_LIFE_HEAL                 = 89653,
    WARLOCK_SOULBURN_AURA                   = 74434,
    WARLOCK_CORRUPTION                      = 172,
    WARLOCK_AGONY                           = 980,
    WARLOCK_DOOM                            = 603,
    WARLOCK_UNSTABLE_AFFLICTION             = 30108,
    WARLOCK_IMMOLATE                        = 348,
    WARLOCK_SHADOWBURN_ENERGIZE             = 125882,
    WARLOCK_CONFLAGRATE                     = 17962,
    WARLOCK_CONFLAGRATE_FIRE_AND_BRIMSTONE  = 108685,
    WARLOCK_IMMOLATE_FIRE_AND_BRIMSTONE     = 108686,
    WARLOCK_FIRE_AND_BRIMSTONE              = 108683,
    WARLOCK_BACKDRAFT                       = 117828,
    WARLOCK_PYROCLASM                       = 123686,
    WARLOCK_RAIN_OF_FIRE                    = 104232,
    WARLOCK_RAIN_OF_FIRE_TRIGGERED          = 42223,
    WARLOCK_SPAWN_PURPLE_DEMONIC_GATEWAY    = 113890,
    WARLOCK_DEMONIC_GATEWAY_TELEPORT_GREEN  = 113896,
    WARLOCK_DEMONIC_GATEWAY_TELEPORT_PURPLE = 120729,
    WARLOCK_DEMONIC_GATEWAY_PERIODIC_CHARGE = 113901,
    WARLOCK_NIGHTFALL                       = 108558,
    WARLOCK_SOUL_SWAP_AURA                  = 86211,
    WARLOCK_SOUL_SWAP_VISUAL                = 92795,
    WARLOCK_GRIMOIRE_OF_SACRIFICE           = 108503,
    WARLOCK_METAMORPHOSIS                   = 103958,
    WARLOCK_DEMONIC_LEAP_JUMP               = 54785,
    WARLOCK_ITEM_S12_TIER_4                 = 131632,
    WARLOCK_TWILIGHT_WARD_S12               = 131623,
    WARLOCK_TWILIGHT_WARD_METAMORPHOSIS_S12 = 131624,
    WARLOCK_SHADOWFLAME                     = 47960,
    WARLOCK_SOUL_LEECH_HEAL                 = 108366,
    WARLOCK_DARK_REGENERATION               = 108359,
    WARLOCK_DARK_BARGAIN_DOT                = 110914,
    WARLOCK_MOLTEN_CORE                     = 122355,
    WARLOCK_MOLTEN_CORE_AURA                = 122351,
    WARLOCK_WILD_IMP_SUMMON                 = 104317,
    WARLOCK_DEMONIC_CALL                    = 114925,
    WARLOCK_DECIMATE_AURA                   = 108869,
    WARLOCK_SOUL_LEECH_AURA                 = 108370,
    WARLOCK_ARCHIMONDES_VENGEANCE_COOLDOWN  = 116405,
    WARLOCK_ARCHIMONDES_VENGEANCE_DAMAGE    = 124051,
    WARLOCK_ARCHIMONDES_VENGEANCE_PASSIVE   = 116403,
    WARLOCK_SOUL_LINK_DUMMY_AURA            = 108446,
    WARLOCK_GLYPH_OF_CONFLAGRATE            = 56235,
    WARLOCK_SHIELD_OF_SHADOW                = 115232,
    WARLOCK_THREATENING_PRESENCE            = 112042,
    WARLOCK_SUPPLANT_DEMONIC_COMMAND        = 119904,
    WARLOCK_KIL_JAEDENS_CUNNING_PASSIVE     = 108507,
    WARLOCK_AFTERMATH_STUN                  = 85387,
    WARLOCK_IMP_SWARM                       = 104316,
    WARLOCK_DISRUPTED_NETHER                = 114736,
    WARLOCK_GLYPH_OF_SIPHON_LIFE            = 56218,
    WARLOCK_GLYPH_OF_SOULWELL               = 58094,
    WARLOCK_GLYPH_OF_SOULWELL_VISUAL        = 34145,
    WARLOCK_SOULBURN_OVERRIDE_1             = 93312,
    WARLOCK_SOULBURN_OVERRIDE_2             = 93313,
    WARLOCK_SOULBURN_OVERRIDE_3             = 104245,
    WARLOCK_SOULBURN_OVERRIDE_4             = 104249,
    WARLOCK_SOULBURN_OVERRIDE_5             = 104250,
    WARLOCK_SOULBURN_OVERRIDE_6             = 104251,
    WARLOCK_SOULBURN_OVERRIDE_7             = 114787,
    WARLOCK_SEED_OF_CORRUPTION_DUMMY        = 86664,
    WARLOCK_SOULBURN_DEMONIC_CIRCLE_TELE    = 114794,
    WARLOCK_GRIMOIRE_OF_SUPREMACY_TALENT    = 108499,
    WARLOCK_SUMMON_FEL_IMP                  = 112866,
    WARLOCK_SUMMON_VOIDLORD                 = 112867,
    WARLOCK_SUMMON_SHIVARRA                 = 112868,
    WARLOCK_SUMMON_OBSERVER                 = 112869,
    WARLOCK_SUMMON_WRATHGUARD               = 112870,
    WARLOCK_SUMMON_ABYSSAL                  = 112921,
    WARLOCK_SUMMON_TERRORGUARD              = 112927
};

// Grimoire of Supremacy - 108499
class spell_warl_grimoire_of_supremacy : public SpellScriptLoader
{
    public:
        spell_warl_grimoire_of_supremacy() : SpellScriptLoader("spell_warl_grimoire_of_supremacy") { }

        class spell_warl_grimoire_of_supremacy_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_warl_grimoire_of_supremacy_AuraScript);

            void OnApply(constAuraEffectPtr /*aurEff*/, AuraEffectHandleModes /*mode*/)
            {
                if (Player* _player = GetTarget()->ToPlayer())
                {
                    _player->learnSpell(WARLOCK_SUMMON_FEL_IMP, false);
                    _player->learnSpell(WARLOCK_SUMMON_VOIDLORD, false);
                    _player->learnSpell(WARLOCK_SUMMON_SHIVARRA, false);
                    _player->learnSpell(WARLOCK_SUMMON_OBSERVER, false);
                    _player->learnSpell(WARLOCK_SUMMON_ABYSSAL, false);
                    _player->learnSpell(WARLOCK_SUMMON_TERRORGUARD, false);

                    if (_player->GetSpecializationId(_player->GetActiveSpec()) == SPEC_WARLOCK_DEMONOLOGY)
                        _player->learnSpell(WARLOCK_SUMMON_WRATHGUARD, false);
                }
            }

            void OnRemove(constAuraEffectPtr /*aurEff*/, AuraEffectHandleModes /*mode*/)
            {
                if (Player* _player = GetTarget()->ToPlayer())
                {
                    if (_player->HasSpell(WARLOCK_SUMMON_FEL_IMP))
                        _player->removeSpell(WARLOCK_SUMMON_FEL_IMP, false, false);

                    if (_player->HasSpell(WARLOCK_SUMMON_VOIDLORD))
                        _player->removeSpell(WARLOCK_SUMMON_VOIDLORD, false, false);

                    if (_player->HasSpell(WARLOCK_SUMMON_SHIVARRA))
                        _player->removeSpell(WARLOCK_SUMMON_SHIVARRA, false, false);

                    if (_player->HasSpell(WARLOCK_SUMMON_OBSERVER))
                        _player->removeSpell(WARLOCK_SUMMON_OBSERVER, false, false);

                    if (_player->HasSpell(WARLOCK_SUMMON_WRATHGUARD))
                        _player->removeSpell(WARLOCK_SUMMON_WRATHGUARD, false, false);

                    if (_player->HasSpell(WARLOCK_SUMMON_ABYSSAL))
                        _player->removeSpell(WARLOCK_SUMMON_ABYSSAL, false, false);

                    if (_player->HasSpell(WARLOCK_SUMMON_TERRORGUARD))
                        _player->removeSpell(WARLOCK_SUMMON_TERRORGUARD, false, false);
                }
            }

            void Register()
            {
                OnEffectApply += AuraEffectApplyFn(spell_warl_grimoire_of_supremacy_AuraScript::OnApply, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
                OnEffectRemove += AuraEffectRemoveFn(spell_warl_grimoire_of_supremacy_AuraScript::OnRemove, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_warl_grimoire_of_supremacy_AuraScript();
        }
};

// Soulburn : Drain Life - 89420
class spell_warl_soulburn_drain_life : public SpellScriptLoader
{
    public:
        spell_warl_soulburn_drain_life() : SpellScriptLoader("spell_warl_soulburn_drain_life") { }

        class spell_warl_soulburn_drain_life_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_warl_soulburn_drain_life_AuraScript);

            void HandleApply(constAuraEffectPtr /*aurEff*/, AuraEffectHandleModes mode)
            {
                if (GetCaster())
                    if (GetCaster()->HasAura(WARLOCK_SOULBURN_AURA))
                        GetCaster()->RemoveAura(WARLOCK_SOULBURN_AURA);
            }

            void OnTick(constAuraEffectPtr aurEff)
            {
                if (Unit* caster = GetCaster())
                {
                    Player* _player = GetCaster()->ToPlayer();
                    if (!_player)
                        return;

                    // Restoring 2% of the caster's total health every 1s
                    int32 basepoints = _player->CountPctFromMaxHealth(3);

                    // In Demonology spec : Generates 10 Demonic Fury per second
                    if (_player->GetSpecializationId(_player->GetActiveSpec()) == SPEC_WARLOCK_DEMONOLOGY)
                        _player->EnergizeBySpell(_player, 689, 10, POWER_DEMONIC_FURY);

                    _player->CastCustomSpell(_player, WARLOCK_DRAIN_LIFE_HEAL, &basepoints, NULL, NULL, true);
                }
            }

            void Register()
            {
                OnEffectApply += AuraEffectApplyFn(spell_warl_soulburn_drain_life_AuraScript::HandleApply, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
                OnEffectPeriodic += AuraEffectPeriodicFn(spell_warl_soulburn_drain_life_AuraScript::OnTick, EFFECT_0, SPELL_AURA_PERIODIC_DAMAGE);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_warl_soulburn_drain_life_AuraScript();
        }
};

// Soulburn : Health Funnel - 104220
class spell_warl_soulburn_health_funnel : public SpellScriptLoader
{
    public:
        spell_warl_soulburn_health_funnel() : SpellScriptLoader("spell_warl_soulburn_health_funnel") { }

        class spell_warl_soulburn_health_funnel_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warl_soulburn_health_funnel_SpellScript);

            void HandleOnHit()
            {
                if (Player* player = GetCaster()->ToPlayer())
                    if (player->HasAura(WARLOCK_SOULBURN_AURA))
                        player->RemoveAurasDueToSpell(WARLOCK_SOULBURN_AURA);
            }

            void Register()
            {
                OnHit += SpellHitFn(spell_warl_soulburn_health_funnel_SpellScript::HandleOnHit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warl_soulburn_health_funnel_SpellScript();
        }
};

// Soulburn : Seed of Corruption - Damage - 87385
class spell_warl_soulburn_seed_of_corruption_damage : public SpellScriptLoader
{
    public:
        spell_warl_soulburn_seed_of_corruption_damage() : SpellScriptLoader("spell_warl_soulburn_seed_of_corruption_damage") { }

        class spell_warl_soulburn_seed_of_corruption_damage_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warl_soulburn_seed_of_corruption_damage_SpellScript);

            void FilterTargets(std::list<WorldObject*>& targets)
            {
                if (GetExplTargetUnit())
                    targets.remove(GetExplTargetUnit());
            }

            void HandleScript()
            {
                if (!GetCaster())
                    return;

                // Remove Soul Burn aura
                if (GetCaster()->HasAura(WARLOCK_SEED_OF_CORRUPTION_DUMMY))
                    GetCaster()->RemoveAurasDueToSpell(WARLOCK_SEED_OF_CORRUPTION_DUMMY);
            }

            void Register()
            {
                OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_warl_soulburn_seed_of_corruption_damage_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_DEST_AREA_ENEMY);
                AfterHit += SpellHitFn(spell_warl_soulburn_seed_of_corruption_damage_SpellScript::HandleScript);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warl_soulburn_seed_of_corruption_damage_SpellScript();
        }
};

// Called by Soulburn : Seed of Corruption - 114790
class spell_warl_soulburn_seed_of_corruption : public SpellScriptLoader
{
    public:
        spell_warl_soulburn_seed_of_corruption() : SpellScriptLoader("spell_warl_soulburn_seed_of_corruption") { }

        class spell_warl_soulburn_seed_of_corruption_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warl_soulburn_seed_of_corruption_SpellScript);

            void HandleOnHit()
            {
                if (Player* player = GetCaster()->ToPlayer())
                {
                    player->CastSpell(player, WARLOCK_SEED_OF_CORRUPTION_DUMMY, true);

                    if (player->HasAura(WARLOCK_SOULBURN_AURA))
                        player->RemoveAurasDueToSpell(WARLOCK_SOULBURN_AURA);
                }
            }

            void Register()
            {
                OnHit += SpellHitFn(spell_warl_soulburn_seed_of_corruption_SpellScript::HandleOnHit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warl_soulburn_seed_of_corruption_SpellScript();
        }
};

// Called by Soulburn : Curse of Enfeeblement - 109468, Soulburn : Curse of Elements - 104225 and Soulburn : Curse of Exhaustion - 104223
// Soulburn aura - Remove - 74434
class spell_warl_soulburn_remove : public SpellScriptLoader
{
    public:
        spell_warl_soulburn_remove() : SpellScriptLoader("spell_warl_soulburn_remove") { }

        class spell_warl_soulburn_remove_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warl_soulburn_remove_SpellScript);

            void HandleOnHit()
            {
                if (Player* player = GetCaster()->ToPlayer())
                    if (player->HasAura(WARLOCK_SOULBURN_AURA))
                        player->RemoveAurasDueToSpell(WARLOCK_SOULBURN_AURA);
            }

            void Register()
            {
                OnHit += SpellHitFn(spell_warl_soulburn_remove_SpellScript::HandleOnHit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warl_soulburn_remove_SpellScript();
        }
};

// Soulburn - 74434
class spell_warl_soulburn_override : public SpellScriptLoader
{
    public:
        spell_warl_soulburn_override() : SpellScriptLoader("spell_warl_soulburn_override") { }

        class spell_warl_soulburn_override_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_warl_soulburn_override_AuraScript);

            void OnApply(constAuraEffectPtr /*aurEff*/, AuraEffectHandleModes /*mode*/)
            {
                if (!GetCaster())
                    return;

                if (Player* player = GetCaster()->ToPlayer())
                {
                    // Overrides Drain Life, Undending Breath and Harvest Life
                    player->CastSpell(player, WARLOCK_SOULBURN_OVERRIDE_1, true);
                    // Overrides Seed of Corruption
                    player->CastSpell(player, WARLOCK_SOULBURN_OVERRIDE_2, true);
                    // Overrides Curse of Enfeeblement and Curse of Elements
                    player->CastSpell(player, WARLOCK_SOULBURN_OVERRIDE_3, true);
                    // Overrides Demonic Circle : Teleport
                    player->CastSpell(player, WARLOCK_SOULBURN_OVERRIDE_4, true);
                    // Overrides Curse of Exhaustion
                    player->CastSpell(player, WARLOCK_SOULBURN_OVERRIDE_5, true);
                    // Overrides Soul Swap
                    player->CastSpell(player, WARLOCK_SOULBURN_OVERRIDE_6, true);
                    // Overrides Health Funnel
                    player->CastSpell(player, WARLOCK_SOULBURN_OVERRIDE_7, true);
                }
            }

            void OnRemove(constAuraEffectPtr /*aurEff*/, AuraEffectHandleModes /*mode*/)
            {
                if (!GetCaster())
                    return;

                if (Player* player = GetCaster()->ToPlayer())
                {
                    // Overrides Drain Life, Undending Breath and Harvest Life
                    player->RemoveAura(WARLOCK_SOULBURN_OVERRIDE_1);
                    // Overrides Seed of Corruption
                    player->RemoveAura(WARLOCK_SOULBURN_OVERRIDE_2);
                    // Overrides Curse of Enfeeblement and Curse of Elements
                    player->RemoveAura(WARLOCK_SOULBURN_OVERRIDE_3);
                    // Overrides Demonic Circle : Teleport
                    player->RemoveAura(WARLOCK_SOULBURN_OVERRIDE_4);
                    // Overrides Curse of Exhaustion
                    player->RemoveAura(WARLOCK_SOULBURN_OVERRIDE_5);
                    // Overrides Soul Swap
                    player->RemoveAura(WARLOCK_SOULBURN_OVERRIDE_6);
                    // Overrides Health Funnel
                    player->RemoveAura(WARLOCK_SOULBURN_OVERRIDE_7);
                }
            }

            void Register()
            {
                OnEffectApply += AuraEffectApplyFn(spell_warl_soulburn_override_AuraScript::OnApply, EFFECT_0, SPELL_AURA_ADD_PCT_MODIFIER, AURA_EFFECT_HANDLE_REAL);
                OnEffectRemove += AuraEffectRemoveFn(spell_warl_soulburn_override_AuraScript::OnRemove, EFFECT_0, SPELL_AURA_ADD_PCT_MODIFIER, AURA_EFFECT_HANDLE_REAL);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_warl_soulburn_override_AuraScript();
        }
};

// Called by Create Soulwell - 29893
// Glyph of Soulwell - 58094
class spell_warl_glyph_of_soulwell : public SpellScriptLoader
{
    public:
        spell_warl_glyph_of_soulwell() : SpellScriptLoader("spell_warl_glyph_of_soulwell") { }

        class spell_warl_glyph_of_soulwell_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warl_glyph_of_soulwell_SpellScript);

            void HandleAfterCast()
            {
                if (!GetCaster())
                    return;

                if (!GetExplTargetDest())
                    return;

                if (!GetCaster()->HasAura(WARLOCK_GLYPH_OF_SOULWELL))
                    return;

                GetCaster()->CastSpell(GetExplTargetDest()->GetPositionX(), GetExplTargetDest()->GetPositionY(), GetExplTargetDest()->GetPositionZ(), WARLOCK_GLYPH_OF_SOULWELL_VISUAL, true);
            }

            void Register()
            {
                AfterCast += SpellCastFn(spell_warl_glyph_of_soulwell_SpellScript::HandleAfterCast);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warl_glyph_of_soulwell_SpellScript();
        }
};

// Imp Swarm - 104316
class spell_warl_imp_swarm : public SpellScriptLoader
{
    public:
        spell_warl_imp_swarm() : SpellScriptLoader("spell_warl_imp_swarm") { }

        class spell_warl_imp_swarm_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warl_imp_swarm_SpellScript);

            SpellCastResult CheckSpec()
            {
                if (!GetCaster())
                    return SPELL_FAILED_DONT_REPORT;

                if (GetCaster()->GetTypeId() != TYPEID_PLAYER)
                    return SPELL_FAILED_DONT_REPORT;

                Player* _plr = GetCaster()->ToPlayer();
                if (_plr->GetSpecializationId(_plr->GetActiveSpec()) != SPEC_WARLOCK_DEMONOLOGY)
                    return SPELL_FAILED_DONT_REPORT;

                return SPELL_CAST_OK;
            }

            void HandleDummy(SpellEffIndex /*effIndex*/)
            {
                if (Player* _plr = GetCaster()->ToPlayer())
                {
                    if (Unit* target = GetHitUnit())
                    {
                        _plr->AddAura(WARLOCK_DEMONIC_CALL, _plr);
                        _plr->CastSpell(target, WARLOCK_WILD_IMP_SUMMON, true);
                        _plr->AddAura(WARLOCK_DEMONIC_CALL, _plr);
                        _plr->CastSpell(target, WARLOCK_WILD_IMP_SUMMON, true);
                        _plr->AddAura(WARLOCK_DEMONIC_CALL, _plr);
                        _plr->CastSpell(target, WARLOCK_WILD_IMP_SUMMON, true);
                        _plr->AddAura(WARLOCK_DEMONIC_CALL, _plr);
                        _plr->CastSpell(target, WARLOCK_WILD_IMP_SUMMON, true);
                        _plr->AddAura(WARLOCK_DEMONIC_CALL, _plr);
                        _plr->CastSpell(target, WARLOCK_WILD_IMP_SUMMON, true);
                        _plr->RemoveAura(WARLOCK_DEMONIC_CALL);
                    }
                }
            }

            void Register()
            {
                OnCheckCast += SpellCheckCastFn(spell_warl_imp_swarm_SpellScript::CheckSpec);
                OnEffectHitTarget += SpellEffectFn(spell_warl_imp_swarm_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warl_imp_swarm_SpellScript();
        }
};

// Glyph of Imp Swarm - 56242
class spell_warl_glyph_of_imp_swarm : public SpellScriptLoader
{
    public:
        spell_warl_glyph_of_imp_swarm() : SpellScriptLoader("spell_warl_glyph_of_imp_swarm") { }

        class spell_warl_glyph_of_imp_swarm_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_warl_glyph_of_imp_swarm_AuraScript);

            void OnApply(constAuraEffectPtr /*aurEff*/, AuraEffectHandleModes /*mode*/)
            {
                if (Player* _player = GetTarget()->ToPlayer())
                    _player->learnSpell(WARLOCK_IMP_SWARM, false);
            }

            void OnRemove(constAuraEffectPtr /*aurEff*/, AuraEffectHandleModes /*mode*/)
            {
                if (Player* _player = GetTarget()->ToPlayer())
                    if (_player->HasSpell(WARLOCK_IMP_SWARM))
                        _player->removeSpell(WARLOCK_IMP_SWARM, false, false);
            }

            void Register()
            {
                OnEffectApply += AuraEffectApplyFn(spell_warl_glyph_of_imp_swarm_AuraScript::OnApply, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
                OnEffectRemove += AuraEffectRemoveFn(spell_warl_glyph_of_imp_swarm_AuraScript::OnRemove, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_warl_glyph_of_imp_swarm_AuraScript();
        }
};

// Unbound Will - 108482
class spell_warl_unbound_will : public SpellScriptLoader
{
    public:
        spell_warl_unbound_will() : SpellScriptLoader("spell_warl_unbound_will") { }

        class spell_warl_unbound_will_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warl_unbound_will_SpellScript);

            SpellCastResult CheckHealth()
            {
                if (Unit* caster = GetCaster())
                {
                    if (caster->GetHealthPct() <= 20.0f)
                    {
                        SetCustomCastResultMessage(SPELL_CUSTOM_ERROR_NOT_ENOUGH_HEALTH);
                        return SPELL_FAILED_CUSTOM_ERROR;
                    }
                    else
                        return SPELL_CAST_OK;
                }
                else
                    return SPELL_FAILED_DONT_REPORT;

                return SPELL_CAST_OK;
            }

            void HandleOnHit()
            {
                if (Player* player = GetCaster()->ToPlayer())
                {
                    player->ModifyHealth(-int32(player->CountPctFromMaxHealth(20)));
                    player->RemoveMovementImpairingAuras();
                    player->RemoveAurasByType(SPELL_AURA_MOD_CONFUSE);
                    player->RemoveAurasByType(SPELL_AURA_MOD_FEAR);
                    player->RemoveAurasByType(SPELL_AURA_MOD_FEAR_2);
                    player->RemoveAurasByType(SPELL_AURA_MOD_STUN);
                    player->RemoveAurasByType(SPELL_AURA_MOD_ROOT);
                    player->RemoveAurasByType(SPELL_AURA_TRANSFORM);
                }
            }

            void Register()
            {
                OnCheckCast += SpellCheckCastFn(spell_warl_unbound_will_SpellScript::CheckHealth);
                OnHit += SpellHitFn(spell_warl_unbound_will_SpellScript::HandleOnHit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warl_unbound_will_SpellScript();
        }
};

// Rain of Fire (damage) - 42223
class spell_warl_rain_of_fire_damage : public SpellScriptLoader
{
    public:
        spell_warl_rain_of_fire_damage() : SpellScriptLoader("spell_warl_rain_of_fire_damage") { }

        class spell_warl_rain_of_fire_damage_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warl_rain_of_fire_damage_SpellScript);

            void HandleOnHit()
            {
                if (Player* player = GetCaster()->ToPlayer())
                {
                    if (Unit* target = GetHitUnit())
                    {
                        if (player->GetSpecializationId(player->GetActiveSpec()) == SPEC_WARLOCK_DESTRUCTION)
                        {
                            if (target->HasAura(WARLOCK_IMMOLATE) || target->HasAura(WARLOCK_IMMOLATE_FIRE_AND_BRIMSTONE))
                            {
                                int32 damage = GetHitDamage();

                                AddPct(damage, 50);

                                SetHitDamage(damage);

                                if (roll_chance_i(25))
                                    player->EnergizeBySpell(player, GetSpellInfo()->Id, 1, POWER_BURNING_EMBERS);
                            }
                        }
                    }
                }
            }

            void Register()
            {
                OnHit += SpellHitFn(spell_warl_rain_of_fire_damage_SpellScript::HandleOnHit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warl_rain_of_fire_damage_SpellScript();
        }
};

// Kil'Jaeden's Cunning (passive with cooldown) - 119048
class spell_warl_kil_jaedens_cunning : public SpellScriptLoader
{
    public:
        spell_warl_kil_jaedens_cunning() : SpellScriptLoader("spell_warl_kil_jaedens_cunning") { }

        class spell_warl_kil_jaedens_cunning_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_warl_kil_jaedens_cunning_AuraScript);

            void HandleApply(constAuraEffectPtr /*aurEff*/, AuraEffectHandleModes mode)
            {
                if (GetCaster())
                    GetCaster()->RemoveAura(WARLOCK_KIL_JAEDENS_CUNNING_PASSIVE);
            }

            void HandleRemove(constAuraEffectPtr /*aurEff*/, AuraEffectHandleModes mode)
            {
                if (GetCaster())
                    GetCaster()->CastSpell(GetCaster(), WARLOCK_KIL_JAEDENS_CUNNING_PASSIVE, true);
            }

            void Register()
            {
                OnEffectApply += AuraEffectApplyFn(spell_warl_kil_jaedens_cunning_AuraScript::HandleApply, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
                OnEffectRemove += AuraEffectRemoveFn(spell_warl_kil_jaedens_cunning_AuraScript::HandleRemove, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_warl_kil_jaedens_cunning_AuraScript();
        }
};

// Voidwalker : Shield of Shadow - 103130
class spell_warl_shield_of_shadow : public SpellScriptLoader
{
    public:
        spell_warl_shield_of_shadow() : SpellScriptLoader("spell_warl_shield_of_shadow") { }

        class spell_warl_shield_of_shadow_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_warl_shield_of_shadow_AuraScript);

            void OnUpdate(uint32 diff, AuraEffectPtr aurEff)
            {
                if (Player* _player = GetCaster()->ToPlayer())
                {
                    if (Pet* pet = _player->GetPet())
                    {
                        if (pet->GetEntry() == 1860) // Voidwalker
                        {
                            if (!pet->HasSpell(WARLOCK_SHIELD_OF_SHADOW))
                                pet->addSpell(WARLOCK_SHIELD_OF_SHADOW);
                            if (!pet->HasSpell(WARLOCK_THREATENING_PRESENCE))
                                pet->addSpell(WARLOCK_THREATENING_PRESENCE);
                        }
                    }
                }
            }

            void Register()
            {
                OnEffectUpdate += AuraEffectUpdateFn(spell_warl_shield_of_shadow_AuraScript::OnUpdate, EFFECT_0, SPELL_AURA_DUMMY);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_warl_shield_of_shadow_AuraScript();
        }
};

// Agony - 980
class spell_warl_agony : public SpellScriptLoader
{
    public:
        spell_warl_agony() : SpellScriptLoader("spell_warl_agony") { }

        class spell_warl_agony_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_warl_agony_AuraScript);

            void OnTick(constAuraEffectPtr aurEff)
            {
                if (GetCaster())
                    if (GetTarget())
                        if (AuraPtr agony = GetTarget()->GetAura(aurEff->GetSpellInfo()->Id, GetCaster()->GetGUID()))
                            agony->ModStackAmount(1);
            }

            void Register()
            {
                OnEffectPeriodic += AuraEffectPeriodicFn(spell_warl_agony_AuraScript::OnTick, EFFECT_0, SPELL_AURA_PERIODIC_DAMAGE);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_warl_agony_AuraScript();
        }
};

// Grimoire of Sacrifice - 108503
class spell_warl_grimoire_of_sacrifice : public SpellScriptLoader
{
    public:
        spell_warl_grimoire_of_sacrifice() : SpellScriptLoader("spell_warl_grimoire_of_sacrifice") { }

        class spell_warl_grimoire_of_sacrifice_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warl_grimoire_of_sacrifice_SpellScript);

            void HandleAfterCast()
            {
                if (Player* player = GetCaster()->ToPlayer())
                {
                    if (Pet* pet = player->GetPet())
                    {
                        // Supplant Command Demon
                        if (player->getLevel() >= 56)
                        {
                            int32 bp = 0;

                            player->RemoveAura(WARLOCK_SUPPLANT_DEMONIC_COMMAND);

                            switch (pet->GetEntry())
                            {
                                case ENTRY_IMP:
                                    bp = 132411;// Single Magic
                                    break;
                                case ENTRY_VOIDWALKER:
                                    bp = 132413;// Shadow Bulwark
                                    break;
                                case ENTRY_SUCCUBUS:
                                    bp = 137706;// Whiplash
                                    break;
                                case ENTRY_FELHUNTER:
                                    bp = 132409;// Spell Lock
                                    break;
                                case ENTRY_FELGUARD:
                                    bp = 132410;// Pursuit
                                    break;
                                default:
                                    break;
                            }

                            if (bp)
                                player->CastCustomSpell(player, WARLOCK_SUPPLANT_DEMONIC_COMMAND, &bp, NULL, NULL, true);
                        }
                    }
                }
            }

            void HandleOnHit()
            {
                if (Player* player = GetCaster()->ToPlayer())
                {
                    // EFFECT_0 : Instakill
                    // EFFECT_1 : 2% health every 5s
                    // EFFECT_2 : +50% DOT damage for Malefic Grasp, Drain Life and Drain Soul
                    // EFFECT_3 : +30% damage for Shadow Bolt, Hand of Gul'Dan, Soul Fire, Wild Imps and Fel Flame
                    // EFFECT_4 : +25% damage for Incinerate, Conflagrate, Chaos Bolt, Shadowburn and Fel Flame
                    // EFFECT_5 : +50% damage for Fel Flame
                    // EFFECT_6 : +20% Health if Soul Link talent is also chosen
                    // EFFECT_7 : +50% on EFFECT_2 of Malefic Grasp
                    // EFFECT_8 : +50% on EFFECT_4 and EFFECT_5 of Drain Soul -> Always set to 0
                    // EFFECT_9 : Always set to 0
                    // EFFECT_10 : Always set to 0
                    if (AuraPtr grimoireOfSacrifice = player->GetAura(WARLOCK_GRIMOIRE_OF_SACRIFICE))
                    {
                        if (grimoireOfSacrifice->GetEffect(EFFECT_10))
                            grimoireOfSacrifice->GetEffect(EFFECT_10)->SetAmount(0);
                        if (grimoireOfSacrifice->GetEffect(EFFECT_9))
                            grimoireOfSacrifice->GetEffect(EFFECT_9)->SetAmount(0);
                        if (grimoireOfSacrifice->GetEffect(EFFECT_8))
                            grimoireOfSacrifice->GetEffect(EFFECT_8)->SetAmount(0);

                        switch (player->GetSpecializationId(player->GetActiveSpec()))
                        {
                            case SPEC_WARLOCK_AFFLICTION:
                                if (grimoireOfSacrifice->GetEffect(EFFECT_3))
                                    grimoireOfSacrifice->GetEffect(EFFECT_3)->SetAmount(0);
                                if (grimoireOfSacrifice->GetEffect(EFFECT_4))
                                    grimoireOfSacrifice->GetEffect(EFFECT_4)->SetAmount(0);
                                break;
                            case SPEC_WARLOCK_DEMONOLOGY:
                                if (grimoireOfSacrifice->GetEffect(EFFECT_2))
                                    grimoireOfSacrifice->GetEffect(EFFECT_2)->SetAmount(0);
                                if (grimoireOfSacrifice->GetEffect(EFFECT_4))
                                    grimoireOfSacrifice->GetEffect(EFFECT_4)->SetAmount(0);
                                if (grimoireOfSacrifice->GetEffect(EFFECT_5))
                                    grimoireOfSacrifice->GetEffect(EFFECT_5)->SetAmount(0);
                                if (grimoireOfSacrifice->GetEffect(EFFECT_7))
                                    grimoireOfSacrifice->GetEffect(EFFECT_7)->SetAmount(0);
                                break;
                            case SPEC_WARLOCK_DESTRUCTION:
                                if (grimoireOfSacrifice->GetEffect(EFFECT_2))
                                    grimoireOfSacrifice->GetEffect(EFFECT_2)->SetAmount(0);
                                if (grimoireOfSacrifice->GetEffect(EFFECT_3))
                                    grimoireOfSacrifice->GetEffect(EFFECT_3)->SetAmount(0);
                                if (grimoireOfSacrifice->GetEffect(EFFECT_5))
                                    grimoireOfSacrifice->GetEffect(EFFECT_5)->SetAmount(0);
                                if (grimoireOfSacrifice->GetEffect(EFFECT_7))
                                    grimoireOfSacrifice->GetEffect(EFFECT_7)->SetAmount(0);
                                break;
                            case SPEC_NONE:
                                if (grimoireOfSacrifice->GetEffect(EFFECT_2))
                                    grimoireOfSacrifice->GetEffect(EFFECT_2)->SetAmount(0);
                                if (grimoireOfSacrifice->GetEffect(EFFECT_3))
                                    grimoireOfSacrifice->GetEffect(EFFECT_3)->SetAmount(0);
                                if (grimoireOfSacrifice->GetEffect(EFFECT_4))
                                    grimoireOfSacrifice->GetEffect(EFFECT_4)->SetAmount(0);
                                if (grimoireOfSacrifice->GetEffect(EFFECT_5))
                                    grimoireOfSacrifice->GetEffect(EFFECT_5)->SetAmount(0);
                                if (grimoireOfSacrifice->GetEffect(EFFECT_7))
                                    grimoireOfSacrifice->GetEffect(EFFECT_7)->SetAmount(0);
                            default:
                                break;
                        }
                    }
                }
            }

            void Register()
            {
                AfterCast += SpellCastFn(spell_warl_grimoire_of_sacrifice_SpellScript::HandleAfterCast);
                OnHit += SpellHitFn(spell_warl_grimoire_of_sacrifice_SpellScript::HandleOnHit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warl_grimoire_of_sacrifice_SpellScript();
        }

        class spell_warl_grimoire_of_sacrifice_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_warl_grimoire_of_sacrifice_AuraScript);

            void HandleRemove(constAuraEffectPtr /*aurEff*/, AuraEffectHandleModes mode)
            {
                if (!GetTarget())
                    return;

                if (Player* _player = GetTarget()->ToPlayer())
                    if (_player->HasAura(WARLOCK_SUPPLANT_DEMONIC_COMMAND))
                        _player->RemoveAura(WARLOCK_SUPPLANT_DEMONIC_COMMAND);
            }

            void Register()
            {
                OnEffectRemove += AuraEffectApplyFn(spell_warl_grimoire_of_sacrifice_AuraScript::HandleRemove, EFFECT_1, SPELL_AURA_OBS_MOD_HEALTH, AURA_EFFECT_HANDLE_REAL);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_warl_grimoire_of_sacrifice_AuraScript();
        }
};

// Flames of Xoroth - 120451
class spell_warl_flames_of_xoroth : public SpellScriptLoader
{
    public:
        spell_warl_flames_of_xoroth() : SpellScriptLoader("spell_warl_flames_of_xoroth") { }

        class spell_warl_flames_of_xoroth_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warl_flames_of_xoroth_SpellScript);

            bool Load()
            {
                return GetCaster()->GetTypeId() == TYPEID_PLAYER;
            }

            SpellCastResult CheckPet()
            {
                if (!GetCaster())
                    return SPELL_FAILED_DONT_REPORT;

                Player* _plr = GetCaster()->ToPlayer();
                if (!_plr)
                    return SPELL_FAILED_DONT_REPORT;

                if (Pet* pet = _plr->GetPet())
                    return SPELL_FAILED_ALREADY_HAVE_PET;

                return SPELL_CAST_OK;
            }

            void HandleDummy(SpellEffIndex /*effIndex*/)
            {
                if (!GetCaster())
                    return;

                Player* player = GetCaster()->ToPlayer();
                if (player->GetLastPetNumber())
                {
                    PetType newPetType = (player->getClass() == CLASS_HUNTER) ? HUNTER_PET : SUMMON_PET;
                    if (Pet* newPet = new Pet(player, newPetType))
                    {
                        if (newPet->LoadPetFromDB(player, 0, player->GetLastPetNumber(), true))
                        {
                            // revive the pet if it is dead
                            if (newPet->getDeathState() == DEAD || newPet->getDeathState() == CORPSE)
                                newPet->setDeathState(ALIVE);

                            newPet->ClearUnitState(uint32(UNIT_STATE_ALL_STATE));
                            newPet->SetFullHealth();
                            newPet->SetPower(newPet->getPowerType(), newPet->GetMaxPower(newPet->getPowerType()));

                            switch (newPet->GetEntry())
                            {
                                case 11859: // Doomguard
                                case 89:    // Inferno
                                    newPet->SetEntry(416);
                                    break;
                                default:
                                    break;
                            }
                        }
                        else
                            delete newPet;
                    }
                }
            }

            void Register()
            {
                OnCheckCast += SpellCheckCastFn(spell_warl_flames_of_xoroth_SpellScript::CheckPet);
                OnEffectHitTarget += SpellEffectFn(spell_warl_flames_of_xoroth_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warl_flames_of_xoroth_SpellScript();
        }
};

// Soul Link - 108446
class spell_warl_soul_link_dummy : public SpellScriptLoader
{
    public:
        spell_warl_soul_link_dummy() : SpellScriptLoader("spell_warl_soul_link_dummy") { }

        class spell_warl_soul_link_dummy_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_warl_soul_link_dummy_AuraScript);

            void HandleRemove(constAuraEffectPtr /*aurEff*/, AuraEffectHandleModes mode)
            {
                if (!GetCaster() || !GetTarget())
                    return;

                if (Player* _player = GetCaster()->ToPlayer())
                {
                    if (GetTarget()->GetGUID() == _player->GetGUID())
                        if (Pet* pet = _player->GetPet())
                            if (pet->HasAura(WARLOCK_SOUL_LINK_DUMMY_AURA))
                                pet->RemoveAura(WARLOCK_SOUL_LINK_DUMMY_AURA);

                    if (_player->HasAura(WARLOCK_SOUL_LINK_DUMMY_AURA))
                        _player->RemoveAura(WARLOCK_SOUL_LINK_DUMMY_AURA);

                    if (AuraPtr grimoireOfSacrifice = _player->GetAura(WARLOCK_GRIMOIRE_OF_SACRIFICE))
                        if (grimoireOfSacrifice->GetEffect(EFFECT_6))
                                grimoireOfSacrifice->GetEffect(EFFECT_6)->SetAmount(0);
                }
            }

            void Register()
            {
                OnEffectRemove += AuraEffectApplyFn(spell_warl_soul_link_dummy_AuraScript::HandleRemove, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_warl_soul_link_dummy_AuraScript();
        }
};

// Soul Link - 108415
class spell_warl_soul_link : public SpellScriptLoader
{
    public:
        spell_warl_soul_link() : SpellScriptLoader("spell_warl_soul_link") { }

        class spell_warl_soul_link_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warl_soul_link_SpellScript);

            void HandleOnHit()
            {
                if (Player* _player = GetCaster()->ToPlayer())
                {
                    if (Unit* target = GetHitUnit())
                    {
                        if (!target->HasAura(WARLOCK_SOUL_LINK_DUMMY_AURA))
                        {
                            uint32 health = target->CountPctFromMaxHealth(50);

                            if (target->GetHealth() > health)
                                target->SetHealth(health);
                            target->SetMaxHealth(health);

                            _player->CastSpell(_player, WARLOCK_SOUL_LINK_DUMMY_AURA, true);
                        }
                        else
                        {
                            target->SetMaxHealth(target->GetMaxHealth() * 2);
                            target->SetHealth(target->GetHealth() * 2);
                            _player->RemoveAura(WARLOCK_SOUL_LINK_DUMMY_AURA);
                            target->RemoveAura(WARLOCK_SOUL_LINK_DUMMY_AURA);
                        }
                    }
                }
            }

            void Register()
            {
                OnHit += SpellHitFn(spell_warl_soul_link_SpellScript::HandleOnHit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warl_soul_link_SpellScript();
        }
};

// Archimonde's Vengeance (Cooldown marker) - 108505
class spell_warl_archimondes_vengeance_cooldown : public SpellScriptLoader
{
    public:
        spell_warl_archimondes_vengeance_cooldown() : SpellScriptLoader("spell_warl_archimondes_vengeance_cooldown") { }

        class spell_warl_archimondes_vengeance_cooldown_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warl_archimondes_vengeance_cooldown_SpellScript);

            void HandleOnHit()
            {
                if (Player* _player = GetCaster()->ToPlayer())
                    if (Unit* target = GetHitUnit())
                        if (!_player->HasSpellCooldown(WARLOCK_ARCHIMONDES_VENGEANCE_PASSIVE))
                            _player->AddSpellCooldown(WARLOCK_ARCHIMONDES_VENGEANCE_PASSIVE, 0, time(NULL) + 120);
            }

            void Register()
            {
                OnHit += SpellHitFn(spell_warl_archimondes_vengeance_cooldown_SpellScript::HandleOnHit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warl_archimondes_vengeance_cooldown_SpellScript();
        }
};

// Archimonde's Vengeance - 108505
class spell_warl_archimondes_vengance : public SpellScriptLoader
{
    public:
        spell_warl_archimondes_vengance() : SpellScriptLoader("spell_warl_archimondes_vengance") { }

        class spell_warl_archimondes_vengance_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_warl_archimondes_vengance_AuraScript);

            void OnProc(constAuraEffectPtr aurEff, ProcEventInfo& eventInfo)
            {
                PreventDefaultAction();

                if (!GetCaster())
                    return;

                if (!GetTarget())
                    return;

                std::list<Unit*> tempList;
                std::list<Unit*> targetList;
                Unit* target = NULL;

                GetCaster()->GetAttackableUnitListInRange(tempList, 100.0f);

                if (tempList.empty())
                    return;

                for (auto itr : tempList)
                {
                    if (itr->GetGUID() == GetCaster()->GetGUID())
                        continue;

                    if (itr->HasAura(aurEff->GetSpellInfo()->Id, GetCaster()->GetGUID()))
                        targetList.push_back(itr);
                }

                if (targetList.empty())
                    return;

                if (targetList.size() > 1)
                    return;

                for (auto itr : targetList)
                    target = itr;

                if (!target)
                    return;

                if (eventInfo.GetActor()->GetGUID() == GetTarget()->GetGUID())
                    return;

                if (!eventInfo.GetDamageInfo()->GetDamage())
                    return;

                if (Player* _player = GetCaster()->ToPlayer())
                {
                    if (target->HasAura(aurEff->GetSpellInfo()->Id, _player->GetGUID()))
                    {
                        int32 bp = int32(eventInfo.GetDamageInfo()->GetDamage() / 4);

                        if (!bp)
                            return;

                        _player->CastCustomSpell(target, WARLOCK_ARCHIMONDES_VENGEANCE_DAMAGE, &bp, NULL, NULL, true);
                    }
                }

                tempList.clear();
                targetList.clear();
            }

            void Register()
            {
                OnEffectProc += AuraEffectProcFn(spell_warl_archimondes_vengance_AuraScript::OnProc, EFFECT_1, SPELL_AURA_DUMMY);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_warl_archimondes_vengance_AuraScript();
        }
};

// Archimonde's Vengeance (5% passive) - 116403
class spell_warl_archimondes_vengance_passive : public SpellScriptLoader
{
    public:
        spell_warl_archimondes_vengance_passive() : SpellScriptLoader("spell_warl_archimondes_vengance_passive") { }

        class spell_warl_archimondes_vengance_passive_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_warl_archimondes_vengance_passive_AuraScript);

            void OnProc(constAuraEffectPtr aurEff, ProcEventInfo& eventInfo)
            {
                PreventDefaultAction();

                if (!GetCaster())
                    return;

                if (eventInfo.GetActor()->GetGUID() == GetTarget()->GetGUID())
                    return;

                if (!eventInfo.GetDamageInfo()->GetDamage())
                    return;

                if (Player* _player = GetCaster()->ToPlayer())
                {
                    if (_player->HasSpellCooldown(WARLOCK_ARCHIMONDES_VENGEANCE_PASSIVE))
                        return;

                    if (GetTarget()->HasAura(aurEff->GetSpellInfo()->Id, _player->GetGUID()))
                    {
                        int32 bp = int32(eventInfo.GetDamageInfo()->GetDamage() / 20);

                        if (!bp)
                            return;

                        _player->CastCustomSpell(eventInfo.GetActor(), WARLOCK_ARCHIMONDES_VENGEANCE_DAMAGE, &bp, NULL, NULL, true);
                    }
                }
            }

            void Register()
            {
                OnEffectProc += AuraEffectProcFn(spell_warl_archimondes_vengance_passive_AuraScript::OnProc, EFFECT_0, SPELL_AURA_DUMMY);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_warl_archimondes_vengance_passive_AuraScript();
        }
};

// Called by Shadowflame - 47960
// Molten Core - 122351
class spell_warl_molten_core_dot : public SpellScriptLoader
{
    public:
        spell_warl_molten_core_dot() : SpellScriptLoader("spell_warl_molten_core_dot") { }

        class spell_warl_molten_core_dot_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_warl_molten_core_dot_AuraScript);

            void OnTick(constAuraEffectPtr aurEff)
            {
                if (GetCaster())
                {
                    if (GetCaster()->HasAura(WARLOCK_MOLTEN_CORE_AURA) && GetCaster()->getLevel() >= 69)
                        if (roll_chance_i(8))
                            GetCaster()->CastSpell(GetCaster(), WARLOCK_MOLTEN_CORE, true);

                    GetCaster()->EnergizeBySpell(GetCaster(), aurEff->GetSpellInfo()->Id, 2, POWER_DEMONIC_FURY);
                }
            }

            void Register()
            {
                OnEffectPeriodic += AuraEffectPeriodicFn(spell_warl_molten_core_dot_AuraScript::OnTick, EFFECT_0, SPELL_AURA_PERIODIC_DAMAGE);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_warl_molten_core_dot_AuraScript();
        }
};

// Called by Shadow Bolt - 686 and Soul Fire - 6353
// Decimate - 108869
class spell_warl_decimate : public SpellScriptLoader
{
    public:
        spell_warl_decimate() : SpellScriptLoader("spell_warl_decimate") { }

        class spell_warl_decimate_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warl_decimate_SpellScript);

            void HandleOnHit()
            {
                if (Player* _player = GetCaster()->ToPlayer())
                {
                    if (Unit* target = GetHitUnit())
                        if (_player->HasAura(WARLOCK_DECIMATE_AURA) && _player->getLevel() >= 73)
                            if (target->GetHealthPct() < 25.0f)
                                _player->CastSpell(_player, WARLOCK_MOLTEN_CORE, true);

                    if (_player->GetSpecializationId(_player->GetActiveSpec()) == SPEC_WARLOCK_DEMONOLOGY)
                        _player->EnergizeBySpell(_player, GetSpellInfo()->Id, GetSpellInfo()->Id == 686 ? 25 : 30, POWER_DEMONIC_FURY);
                }
            }

            void Register()
            {
                OnHit += SpellHitFn(spell_warl_decimate_SpellScript::HandleOnHit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warl_decimate_SpellScript();
        }
};

// Called by Shadow Bolt - 686, Soul Fire - 6353 and Touch of Chaos - 103964
// Demonic Call - 114925
class spell_warl_demonic_call : public SpellScriptLoader
{
    public:
        spell_warl_demonic_call() : SpellScriptLoader("spell_warl_demonic_call") { }

        class spell_warl_demonic_call_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warl_demonic_call_SpellScript);

            void HandleOnHit()
            {
                if (Player* _player = GetCaster()->ToPlayer())
                {
                    if (Unit* target = GetHitUnit())
                    {
                        if (_player->HasAura(WARLOCK_DEMONIC_CALL) && !_player->HasAura(WARLOCK_DISRUPTED_NETHER))
                        {
                            _player->CastSpell(_player, WARLOCK_WILD_IMP_SUMMON, true);
                            _player->RemoveAura(WARLOCK_DEMONIC_CALL);
                        }
                    }
                }
            }

            void Register()
            {
                OnHit += SpellHitFn(spell_warl_demonic_call_SpellScript::HandleOnHit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warl_demonic_call_SpellScript();
        }
};

// Void Ray - 115422 and Touch of Chaos - 103964
class spell_warl_void_ray : public SpellScriptLoader
{
    public:
        spell_warl_void_ray() : SpellScriptLoader("spell_warl_void_ray") { }

        class spell_warl_void_ray_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warl_void_ray_SpellScript);

            void HandleOnHit()
            {
                if (Player* _player = GetCaster()->ToPlayer())
                {
                    if (Unit* target = GetHitUnit())
                    {
                        if (AuraPtr corruption = target->GetAura(WARLOCK_CORRUPTION, _player->GetGUID()))
                        {
                            corruption->SetDuration(corruption->GetDuration() + 4000);
                            corruption->SetNeedClientUpdateForTargets();
                        }
                    }
                }
            }

            void Register()
            {
                OnHit += SpellHitFn(spell_warl_void_ray_SpellScript::HandleOnHit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warl_void_ray_SpellScript();
        }
};

// Chaos Wave - 124916
class spell_warl_chaos_wave : public SpellScriptLoader
{
    public:
        spell_warl_chaos_wave() : SpellScriptLoader("spell_warl_chaos_wave") { }

        class spell_warl_chaos_wave_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warl_chaos_wave_SpellScript);

            void HandleAfterCast()
            {
                if (Player* _player = GetCaster()->ToPlayer())
                    if (_player->HasAura(WARLOCK_MOLTEN_CORE_AURA) && _player->getLevel() >= 69)
                        _player->CastSpell(_player, WARLOCK_MOLTEN_CORE, true);
            }

            void Register()
            {
                AfterCast += SpellCastFn(spell_warl_chaos_wave_SpellScript::HandleAfterCast);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warl_chaos_wave_SpellScript();
        }
};

// Metamorphosis - 103958
class spell_warl_metamorphosis_cost : public SpellScriptLoader
{
    public:
        spell_warl_metamorphosis_cost() : SpellScriptLoader("spell_warl_metamorphosis_cost") { }

        class spell_warl_metamorphosis_cost_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_warl_metamorphosis_cost_AuraScript);

            void OnTick(constAuraEffectPtr aurEff)
            {
                if (GetCaster())
                    GetCaster()->EnergizeBySpell(GetCaster(), WARLOCK_METAMORPHOSIS, -6, POWER_DEMONIC_FURY);
            }

            void Register()
            {
                OnEffectPeriodic += AuraEffectPeriodicFn(spell_warl_metamorphosis_cost_AuraScript::OnTick, EFFECT_2, SPELL_AURA_PERIODIC_DUMMY);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_warl_metamorphosis_cost_AuraScript();
        }
};

// Immolation Aura - 104025
class spell_warl_immolation_aura : public SpellScriptLoader
{
    public:
        spell_warl_immolation_aura() : SpellScriptLoader("spell_warl_immolation_aura") { }

        class spell_warl_immolation_aura_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_warl_immolation_aura_AuraScript);

            void OnTick(constAuraEffectPtr aurEff)
            {
                if (GetCaster())
                    GetCaster()->EnergizeBySpell(GetCaster(), GetSpellInfo()->Id, -25, POWER_DEMONIC_FURY);
            }

            void Register()
            {
                OnEffectPeriodic += AuraEffectPeriodicFn(spell_warl_immolation_aura_AuraScript::OnTick, EFFECT_0, SPELL_AURA_PERIODIC_TRIGGER_SPELL);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_warl_immolation_aura_AuraScript();
        }
};

// Dark Bargain - 110013
class spell_warl_dark_bargain_on_absorb : public SpellScriptLoader
{
    public:
        spell_warl_dark_bargain_on_absorb() : SpellScriptLoader("spell_warl_dark_bargain_on_absorb") { }

        class spell_warl_dark_bargain_on_absorb_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_warl_dark_bargain_on_absorb_AuraScript);

            uint32 totalAbsorbAmount;

            bool Load()
            {
                totalAbsorbAmount = 0;
                return true;
            }

            void CalculateAmount(constAuraEffectPtr /*aurEff*/, int32 & amount, bool & /*canBeRecalculated*/)
            {
                amount = int32(100000000);
            }

            void OnAbsorb(AuraEffectPtr aurEff, DamageInfo& dmgInfo, uint32& absorbAmount)
            {
                totalAbsorbAmount += dmgInfo.GetDamage();
            }

            void OnRemove(constAuraEffectPtr aurEff, AuraEffectHandleModes /*mode*/)
            {
                // (totalAbsorbAmount / 16) it's for totalAbsorbAmount 50% & totalAbsorbAmount / 8 (for each tick of custom spell)
                if (Unit* caster = GetCaster())
                    caster->CastCustomSpell(WARLOCK_DARK_BARGAIN_DOT, SPELLVALUE_BASE_POINT0, (totalAbsorbAmount / 16) , caster, true);
            }

            void Register()
            {
                DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_warl_dark_bargain_on_absorb_AuraScript::CalculateAmount, EFFECT_0, SPELL_AURA_SCHOOL_ABSORB);
                OnEffectAbsorb += AuraEffectAbsorbFn(spell_warl_dark_bargain_on_absorb_AuraScript::OnAbsorb, EFFECT_0);
                AfterEffectRemove += AuraEffectRemoveFn(spell_warl_dark_bargain_on_absorb_AuraScript::OnRemove, EFFECT_1, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_warl_dark_bargain_on_absorb_AuraScript();
        }
};

// Dark Regeneration - 108359
class spell_warl_dark_regeneration : public SpellScriptLoader
{
    public:
        spell_warl_dark_regeneration() : SpellScriptLoader("spell_warl_dark_regeneration") { }

        class spell_warl_dark_regeneration_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_warl_dark_regeneration_AuraScript);

            void HandleApply(constAuraEffectPtr /*aurEff*/, AuraEffectHandleModes mode)
            {
                if (GetTarget())
                    if (Guardian* pet = GetTarget()->GetGuardianPet())
                        pet->CastSpell(pet, WARLOCK_DARK_REGENERATION, true);
            }

            void Register()
            {
                OnEffectApply += AuraEffectApplyFn(spell_warl_dark_regeneration_AuraScript::HandleApply, EFFECT_0, SPELL_AURA_OBS_MOD_HEALTH, AURA_EFFECT_HANDLE_REAL);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_warl_dark_regeneration_AuraScript();
        }
};

// Called by Haunt - 48181, Fel Flame - 77799, Shadow Bolt - 686, Incinerate - 29722, Chaos Bolt - 116858
// Touch of Chaos - 103964, Demonic Slash - 114175, Soul Fire - 6353, Soul Fire (Metamorphosis) - 104027
// Void Ray - 115422 and Shadow Burn - 17877
// Soul Leech - 108370
class spell_warl_soul_leech : public SpellScriptLoader
{
    public:
        spell_warl_soul_leech() : SpellScriptLoader("spell_warl_soul_leech") { }

        class spell_warl_soul_leech_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warl_soul_leech_SpellScript);

            void HandleAfterHit()
            {
                if (Player* _player = GetCaster()->ToPlayer())
                {
                    if (Unit* target = GetHitUnit())
                    {
                        if (_player->HasAura(WARLOCK_SOUL_LEECH_AURA))
                        {
                            int32 bp = int32(GetHitDamage() / 10);

                            _player->CastCustomSpell(_player, WARLOCK_SOUL_LEECH_HEAL, &bp, NULL, NULL, true);

                            if (Pet* pet = _player->GetPet())
                                _player->CastCustomSpell(pet, WARLOCK_SOUL_LEECH_HEAL, &bp, NULL, NULL, true);
                        }
                    }
                }
            }

            void Register()
            {
                AfterHit += SpellHitFn(spell_warl_soul_leech_SpellScript::HandleAfterHit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warl_soul_leech_SpellScript();
        }
};

// Sacrificial Pact - 108416
class spell_warl_sacrificial_pact : public SpellScriptLoader
{
    public:
        spell_warl_sacrificial_pact() : SpellScriptLoader("spell_warl_sacrificial_pact") { }

        class spell_warl_sacrificial_pact_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_warl_sacrificial_pact_AuraScript);

            void CalculateAmount(constAuraEffectPtr , int32 & amount, bool & )
            {
                if (Unit* caster = GetCaster())
                {
                    if (!GetCaster()->GetGuardianPet())
                    {
                        int32 sacrifiedHealth = GetCaster()->CountPctFromCurHealth(50);
                        GetCaster()->ModifyHealth(-sacrifiedHealth);
                        amount = sacrifiedHealth * 2;
                    }
                    else if (GetCaster()->GetGuardianPet())
                    {
                        int32 sacrifiedHealth = GetCaster()->GetGuardianPet()->CountPctFromCurHealth(50);
                        GetCaster()->GetGuardianPet()->ModifyHealth(-sacrifiedHealth);
                        amount = sacrifiedHealth * 2;
                    }
                }
            }
            void Register()
            {
                DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_warl_sacrificial_pact_AuraScript::CalculateAmount, EFFECT_0, SPELL_AURA_SCHOOL_ABSORB);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_warl_sacrificial_pact_AuraScript();
        }
};

// Hand of Gul'Dan - 86040
class spell_warl_hand_of_guldan : public SpellScriptLoader
{
    public:
        spell_warl_hand_of_guldan() : SpellScriptLoader("spell_warl_hand_of_guldan") { }

        class spell_warl_hand_of_guldan_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warl_hand_of_guldan_SpellScript);

            void HandleOnHit()
            {
                if (Player* _player = GetCaster()->ToPlayer())
                    if (Unit* target = GetHitUnit())
                        _player->CastSpell(target, WARLOCK_SHADOWFLAME, true);
            }

            void Register()
            {
                OnHit += SpellHitFn(spell_warl_hand_of_guldan_SpellScript::HandleOnHit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warl_hand_of_guldan_SpellScript();
        }
};

// Twilight Ward - 6229 and Twilight Ward (Metamorphosis) - 104048
class spell_warl_twilight_ward_s12 : public SpellScriptLoader
{
    public:
        spell_warl_twilight_ward_s12() : SpellScriptLoader("spell_warl_twilight_ward_s12") { }

        class spell_warl_twilight_ward_s12_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warl_twilight_ward_s12_SpellScript);

            void HandleOnHit()
            {
                if (Player* _player = GetCaster()->ToPlayer())
                {
                    if (_player->HasAura(WARLOCK_ITEM_S12_TIER_4))
                    {
                        if (GetSpellInfo()->Id == 6229)
                        {
                            if (_player->HasAura(GetSpellInfo()->Id))
                                _player->RemoveAura(GetSpellInfo()->Id);

                            _player->CastSpell(_player, WARLOCK_TWILIGHT_WARD_S12, true);
                        }
                        else if (GetSpellInfo()->Id == 104048)
                        {
                            if (_player->HasAura(GetSpellInfo()->Id))
                                _player->RemoveAura(GetSpellInfo()->Id);

                            _player->CastSpell(_player, WARLOCK_TWILIGHT_WARD_METAMORPHOSIS_S12, true);
                        }
                    }
                }
            }

            void Register()
            {
                OnHit += SpellHitFn(spell_warl_twilight_ward_s12_SpellScript::HandleOnHit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warl_twilight_ward_s12_SpellScript();
        }
};

// Hellfire - 5857
class spell_warl_hellfire : public SpellScriptLoader
{
    public:
        spell_warl_hellfire() : SpellScriptLoader("spell_warl_hellfire") { }

        class spell_warl_hellfire_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warl_hellfire_SpellScript);

            void HandleOnHit()
            {
                if (Player* _player = GetCaster()->ToPlayer())
                    if (Unit* target = GetHitUnit())
                        _player->EnergizeBySpell(_player, GetSpellInfo()->Id, 4, POWER_DEMONIC_FURY);
            }

            void Register()
            {
                OnHit += SpellHitFn(spell_warl_hellfire_SpellScript::HandleOnHit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warl_hellfire_SpellScript();
        }
};

// Demonic Leap (jump) - 54785
class spell_warl_demonic_leap_jump : public SpellScriptLoader
{
    public:
        spell_warl_demonic_leap_jump() : SpellScriptLoader("spell_warl_demonic_leap_jump") { }

        class spell_warl_demonic_leap_jump_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warl_demonic_leap_jump_SpellScript);

            SpellCastResult CheckElevation()
            {
                Unit* caster = GetCaster();
                if (!caster)
                    return SPELL_FAILED_DONT_REPORT;

                Position pos;
                caster->GetFirstCollisionPosition(pos, GetSpellInfo()->Effects[0].CalcRadius(caster), 0.0f);

                if (pos.GetPositionX() > caster->GetPositionZ() + 5.0f)
                {
                    caster->RemoveAura(WARLOCK_METAMORPHOSIS);
                    return SPELL_FAILED_NOPATH;
                }
                else if (!caster->IsWithinLOS(pos.GetPositionX(), pos.GetPositionY(), pos.GetPositionZ()))
                {
                    caster->RemoveAura(WARLOCK_METAMORPHOSIS);
                    return SPELL_FAILED_NOPATH;
                }
                else if (caster->HasAuraType(SPELL_AURA_MOD_ROOT))
                {
                    caster->RemoveAura(WARLOCK_METAMORPHOSIS);
                    return SPELL_FAILED_ROOTED;
                }

                return SPELL_CAST_OK;
            }

            void Register()
            {
                OnCheckCast += SpellCheckCastFn(spell_warl_demonic_leap_jump_SpellScript::CheckElevation);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warl_demonic_leap_jump_SpellScript();
        }
};

// Demonic Leap - 109151
class spell_warl_demonic_leap : public SpellScriptLoader
{
    public:
        spell_warl_demonic_leap() : SpellScriptLoader("spell_warl_demonic_leap") { }

        class spell_warl_demonic_leap_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warl_demonic_leap_SpellScript);

            void HandleAfterCast()
            {
                if (Player* _player = GetCaster()->ToPlayer())
                {
                    _player->CastSpell(_player, WARLOCK_METAMORPHOSIS, true);
                    _player->CastSpell(_player, WARLOCK_DEMONIC_LEAP_JUMP, true);
                }
            }

            void Register()
            {
                AfterCast += SpellCastFn(spell_warl_demonic_leap_SpellScript::HandleAfterCast);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warl_demonic_leap_SpellScript();
        }
};

// Burning Rush - 111400
class spell_warl_burning_rush : public SpellScriptLoader
{
    public:
        spell_warl_burning_rush() : SpellScriptLoader("spell_warl_burning_rush") { }

        class spell_warl_burning_rush_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_warl_burning_rush_AuraScript);

            void OnTick(constAuraEffectPtr aurEff)
            {
                if (GetCaster())
                {
                    // Drain 4% of health every second
                    int32 basepoints = GetCaster()->CountPctFromMaxHealth(4);

                    GetCaster()->DealDamage(GetCaster(), basepoints, NULL, NODAMAGE, SPELL_SCHOOL_MASK_NORMAL, NULL, false);
                }
            }

            void Register()
            {
                OnEffectPeriodic += AuraEffectPeriodicFn(spell_warl_burning_rush_AuraScript::OnTick, EFFECT_1, SPELL_AURA_PERIODIC_DUMMY);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_warl_burning_rush_AuraScript();
        }
};

// Soul Swap : Soulburn - 119678
class spell_warl_soul_swap_soulburn : public SpellScriptLoader
{
    public:
        spell_warl_soul_swap_soulburn() : SpellScriptLoader("spell_warl_soul_swap_soulburn") { }

        class spell_warl_soul_swap_soulburn_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warl_soul_swap_soulburn_SpellScript);

            void HandleOnHit()
            {
                if (Player* _player = GetCaster()->ToPlayer())
                {
                    if (Unit* target = GetHitUnit())
                    {
                        // Apply instantly corruption, unstable affliction and agony on the target
                        _player->AddAura(WARLOCK_CORRUPTION, target);
                        _player->AddAura(WARLOCK_UNSTABLE_AFFLICTION, target);
                        _player->AddAura(WARLOCK_AGONY, target);
                        _player->RemoveAura(WARLOCK_SOULBURN_AURA);
                    }
                }
            }

            void Register()
            {
                OnHit += SpellHitFn(spell_warl_soul_swap_soulburn_SpellScript::HandleOnHit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warl_soul_swap_soulburn_SpellScript();
        }
};

// Soul Swap - 86121 or Soul Swap : Exhale - 86213
class spell_warl_soul_swap : public SpellScriptLoader
{
    public:
        spell_warl_soul_swap() : SpellScriptLoader("spell_warl_soul_swap") { }

        class spell_warl_soul_swap_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warl_soul_swap_SpellScript);

            void HandleOnHit()
            {
                if (Unit* caster = GetCaster())
                {
                    if (Unit* target = GetHitUnit())
                    {
                        if (GetSpellInfo()->Id == 86121)
                        {
                            // Soul Swap override spell
                            caster->CastSpell(caster, WARLOCK_SOUL_SWAP_AURA, true);
                            caster->RemoveSoulSwapDOT(target);
                        }
                        else if (GetSpellInfo()->Id == 86213)
                        {
                            caster->CastSpell(target, WARLOCK_SOUL_SWAP_VISUAL, true);
                            caster->ApplySoulSwapDOT(target);
                            caster->RemoveAurasDueToSpell(WARLOCK_SOUL_SWAP_AURA);

                            if (caster->HasAura(56226) && caster->ToPlayer()) // Glyph of Soul Swap
                                caster->ToPlayer()->AddSpellCooldown(86121, 0, time(NULL) + 30);
                        }
                    }
                }
            }

            void Register()
            {
                OnHit += SpellHitFn(spell_warl_soul_swap_SpellScript::HandleOnHit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warl_soul_swap_SpellScript();
        }
};

// Called by Corruption - 172
// Nightfall - 108558
class spell_warl_nightfall : public SpellScriptLoader
{
    public:
        spell_warl_nightfall() : SpellScriptLoader("spell_warl_nightfall") { }

        class spell_warl_nightfall_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_warl_nightfall_AuraScript);

            void OnTick(constAuraEffectPtr aurEff)
            {
                if (!GetCaster())
                    return;

                if (Player* _player = GetCaster()->ToPlayer())
                {
                    if (_player->HasAura(WARLOCK_NIGHTFALL))
                        if (roll_chance_i(5))
                            _player->SetPower(POWER_SOUL_SHARDS, _player->GetPower(POWER_SOUL_SHARDS) + 100);

                    if (_player->HasAura(WARLOCK_GLYPH_OF_SIPHON_LIFE))
                        _player->HealBySpell(_player, sSpellMgr->GetSpellInfo(WARLOCK_GLYPH_OF_SIPHON_LIFE), int32(_player->GetMaxHealth() / 200), false);
                }
            }

            void Register()
            {
                OnEffectPeriodic += AuraEffectPeriodicFn(spell_warl_nightfall_AuraScript::OnTick, EFFECT_0, SPELL_AURA_PERIODIC_DAMAGE);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_warl_nightfall_AuraScript();
        }
};

// Drain Soul - 1120
class spell_warl_drain_soul : public SpellScriptLoader
{
    public:
        spell_warl_drain_soul() : SpellScriptLoader("spell_warl_drain_soul") { }

        class spell_warl_drain_soul_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_warl_drain_soul_AuraScript);

            void HandleRemove(constAuraEffectPtr /*aurEff*/, AuraEffectHandleModes mode)
            {
                if (GetCaster())
                {
                    AuraRemoveMode removeMode = GetTargetApplication()->GetRemoveMode();
                    if (removeMode == AURA_REMOVE_BY_DEATH)
                        GetCaster()->SetPower(POWER_SOUL_SHARDS, GetCaster()->GetPower(POWER_SOUL_SHARDS) + 300);
                }
            }

            void Register()
            {
                OnEffectRemove += AuraEffectApplyFn(spell_warl_drain_soul_AuraScript::HandleRemove, EFFECT_4, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_warl_drain_soul_AuraScript();
        }
};

// Demonic Gateway (periodic add charge) - 113901
class spell_warl_demonic_gateway_charges : public SpellScriptLoader
{
    public:
        spell_warl_demonic_gateway_charges() : SpellScriptLoader("spell_warl_demonic_gateway_charges") { }

        class spell_warl_demonic_gateway_charges_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_warl_demonic_gateway_charges_AuraScript);

            void OnTick(constAuraEffectPtr aurEff)
            {
                if (Unit* target = GetTarget())
                    if (AuraPtr demonicGateway = target->GetAura(WARLOCK_DEMONIC_GATEWAY_PERIODIC_CHARGE))
                        demonicGateway->ModCharges(1);
            }

            void Register()
            {
                OnEffectPeriodic += AuraEffectPeriodicFn(spell_warl_demonic_gateway_charges_AuraScript::OnTick, EFFECT_1, SPELL_AURA_PERIODIC_DUMMY);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_warl_demonic_gateway_charges_AuraScript();
        }
};

// Demonic Gateway - 111771
class spell_warl_demonic_gateway : public SpellScriptLoader
{
    public:
        spell_warl_demonic_gateway() : SpellScriptLoader("spell_warl_demonic_gateway") { }

        class spell_warl_demonic_gateway_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warl_demonic_gateway_SpellScript);

            void HandleAfterCast()
            {
                if (Player* _player = GetCaster()->ToPlayer())
                    _player->CastSpell(_player, WARLOCK_SPAWN_PURPLE_DEMONIC_GATEWAY, true);
            }

            void Register()
            {
                AfterCast += SpellCastFn(spell_warl_demonic_gateway_SpellScript::HandleAfterCast);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warl_demonic_gateway_SpellScript();
        }
};

// Rain of Fire - 104232
class spell_warl_rain_of_fire : public SpellScriptLoader
{
    public:
        spell_warl_rain_of_fire() : SpellScriptLoader("spell_warl_rain_of_fire") { }

        class spell_warl_rain_of_fire_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_warl_rain_of_fire_AuraScript);

            void OnTick(constAuraEffectPtr aurEff)
            {
                if (GetCaster())
                    if (DynamicObject* dynObj = GetCaster()->GetDynObject(WARLOCK_RAIN_OF_FIRE))
                        GetCaster()->CastSpell(dynObj->GetPositionX(), dynObj->GetPositionY(), dynObj->GetPositionZ(), WARLOCK_RAIN_OF_FIRE_TRIGGERED, true);
            }

            void Register()
            {
                OnEffectPeriodic += AuraEffectPeriodicFn(spell_warl_rain_of_fire_AuraScript::OnTick, EFFECT_1, SPELL_AURA_PERIODIC_DUMMY);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_warl_rain_of_fire_AuraScript();
        }
};

// Chaos Bolt - 116858
class spell_warl_chaos_bolt : public SpellScriptLoader
{
    public:
        spell_warl_chaos_bolt() : SpellScriptLoader("spell_warl_chaos_bolt") { }

        class spell_warl_chaos_bolt_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warl_chaos_bolt_SpellScript);

            void HandleAfterCast()
            {
                if (Player* _player = GetCaster()->ToPlayer())
                    if (_player->HasAura(WARLOCK_PYROCLASM))
                        if(AuraPtr backdraft = _player->GetAura(WARLOCK_BACKDRAFT))
                            backdraft->ModCharges(-3);
            }

            void Register()
            {
                AfterCast += SpellCastFn(spell_warl_chaos_bolt_SpellScript::HandleAfterCast);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warl_chaos_bolt_SpellScript();
        }
};

// Ember Tap - 114635
class spell_warl_ember_tap : public SpellScriptLoader
{
    public:
        spell_warl_ember_tap() : SpellScriptLoader("spell_warl_ember_tap") { }

        class spell_warl_ember_tap_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warl_ember_tap_SpellScript);

            void HandleOnHit()
            {
                if (Player* _player = GetCaster()->ToPlayer())
                {
                    if (Unit* target = GetHitUnit())
                    {
                        int32 healAmount;
                        float pct;
                        float Mastery;

                        Mastery = 3.0f * _player->GetFloatValue(PLAYER_MASTERY) / 100.0f;

                        pct = 0.15f * (1 + Mastery);

                        healAmount = int32(_player->GetMaxHealth() * pct);

                        SetHitHeal(healAmount);
                    }
                }
            }

            void Register()
            {
                OnHit += SpellHitFn(spell_warl_ember_tap_SpellScript::HandleOnHit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warl_ember_tap_SpellScript();
        }
};

// Called By : Incinerate (Fire and Brimstone) - 114654, Conflagrate (Fire and Brimstone) - 108685
// Curse of the Elements (Fire and Brimstone) - 104225, Curse of Enfeeblement (Fire and Brimstone) - 109468
// Immolate (Fire and Brimstone) - 108686
// Fire and Brimstone - 108683
class spell_warl_fire_and_brimstone : public SpellScriptLoader
{
    public:
        spell_warl_fire_and_brimstone() : SpellScriptLoader("spell_warl_fire_and_brimstone") { }

        class spell_warl_fire_and_brimstone_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warl_fire_and_brimstone_SpellScript);

            void HandleOnHit()
            {
                if (Player* _player = GetCaster()->ToPlayer())
                    if (Unit* target = GetHitUnit())
                        if (_player->HasAura(WARLOCK_FIRE_AND_BRIMSTONE))
                            _player->RemoveAura(WARLOCK_FIRE_AND_BRIMSTONE);
            }

            void Register()
            {
                OnHit += SpellHitFn(spell_warl_fire_and_brimstone_SpellScript::HandleOnHit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warl_fire_and_brimstone_SpellScript();
        }
};

// Conflagrate - 17962 and Conflagrate (Fire and Brimstone) - 108685
class spell_warl_conflagrate_aura : public SpellScriptLoader
{
    public:
        spell_warl_conflagrate_aura() : SpellScriptLoader("spell_warl_conflagrate_aura") { }

        class spell_warl_conflagrate_aura_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warl_conflagrate_aura_SpellScript);

            void HandleOnHit()
            {
                if (Player* _player = GetCaster()->ToPlayer())
                {
                    if (Unit* target = GetHitUnit())
                    {
                        if (!target->HasAura(WARLOCK_IMMOLATE) && !_player->HasAura(WARLOCK_GLYPH_OF_CONFLAGRATE))
                            if (AuraPtr conflagrate = target->GetAura(WARLOCK_CONFLAGRATE))
                                target->RemoveAura(WARLOCK_CONFLAGRATE);
                        if (!target->HasAura(WARLOCK_IMMOLATE_FIRE_AND_BRIMSTONE))
                            if (AuraPtr conflagrate = target->GetAura(WARLOCK_CONFLAGRATE_FIRE_AND_BRIMSTONE))
                                target->RemoveAura(WARLOCK_CONFLAGRATE_FIRE_AND_BRIMSTONE);
                    }
                }
            }

            void Register()
            {
                OnHit += SpellHitFn(spell_warl_conflagrate_aura_SpellScript::HandleOnHit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warl_conflagrate_aura_SpellScript();
        }
};

// Shadowburn - 29341
class spell_warl_shadowburn : public SpellScriptLoader
{
    public:
        spell_warl_shadowburn() : SpellScriptLoader("spell_warl_shadowburn") { }

        class spell_warl_shadowburn_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_warl_shadowburn_AuraScript);

            void HandleRemove(constAuraEffectPtr /*aurEff*/, AuraEffectHandleModes mode)
            {
                if (GetCaster())
                {
                    AuraRemoveMode removeMode = GetTargetApplication()->GetRemoveMode();
                    if (removeMode == AURA_REMOVE_BY_DEATH)
                        GetCaster()->SetPower(POWER_BURNING_EMBERS, GetCaster()->GetPower(POWER_BURNING_EMBERS) + 20); // Give 2 Burning Embers
                    else if (removeMode == AURA_REMOVE_BY_EXPIRE)
                        GetCaster()->CastSpell(GetCaster(), WARLOCK_SHADOWBURN_ENERGIZE, true);
                }
            }

            void Register()
            {
                OnEffectRemove += AuraEffectApplyFn(spell_warl_shadowburn_AuraScript::HandleRemove, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_warl_shadowburn_AuraScript();
        }
};

// Called By : Incinerate - 29722 and Incinerate (Fire and Brimstone) - 114654
// Conflagrate - 17962 and Conflagrate (Fire and Brimstone) - 108685
// Burning Embers generate
class spell_warl_burning_embers : public SpellScriptLoader
{
    public:
        spell_warl_burning_embers() : SpellScriptLoader("spell_warl_burning_embers") { }

        class spell_warl_burning_embers_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warl_burning_embers_SpellScript);

            void HandleOnHit()
            {
                if (Player* _player = GetCaster()->ToPlayer())
                {
                    if (Unit* target = GetHitUnit())
                    {
                        if (GetSpell()->IsCritForTarget(target))
                            _player->SetPower(POWER_BURNING_EMBERS, _player->GetPower(POWER_BURNING_EMBERS) + 2);
                        else
                            _player->SetPower(POWER_BURNING_EMBERS, _player->GetPower(POWER_BURNING_EMBERS) + 1);
                    }
                }
            }

            void Register()
            {
                OnHit += SpellHitFn(spell_warl_burning_embers_SpellScript::HandleOnHit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warl_burning_embers_SpellScript();
        }
};

// Fel Flame - 77799
class spell_warl_fel_flame : public SpellScriptLoader
{
    public:
        spell_warl_fel_flame() : SpellScriptLoader("spell_warl_fel_flame") { }

        class spell_warl_fel_flame_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warl_fel_flame_SpellScript);

            void HandleOnHit()
            {
                if (Player* _player = GetCaster()->ToPlayer())
                {
                    if (Unit* target = GetHitUnit())
                    {
                        _player->EnergizeBySpell(_player, GetSpellInfo()->Id, 15, POWER_DEMONIC_FURY);

                        // Increases the duration of Corruption and Unstable Affliction by 6s
                        if (_player->GetSpecializationId(_player->GetActiveSpec()) == SPEC_WARLOCK_AFFLICTION)
                        {
                            if (AuraPtr unstableAffliction = target->GetAura(WARLOCK_UNSTABLE_AFFLICTION, _player->GetGUID()))
                            {
                                unstableAffliction->SetDuration(unstableAffliction->GetDuration() + 6000);
                                unstableAffliction->SetNeedClientUpdateForTargets();
                            }
                            if (AuraPtr corruption = target->GetAura(WARLOCK_CORRUPTION, _player->GetGUID()))
                            {
                                corruption->SetDuration(corruption->GetDuration() + 6000);
                                corruption->SetNeedClientUpdateForTargets();
                            }
                        }
                        // Increases the duration of Corruption by 6s
                        else if (_player->GetSpecializationId(_player->GetActiveSpec()) == SPEC_WARLOCK_DEMONOLOGY)
                        {
                            if (AuraPtr corruption = target->GetAura(WARLOCK_CORRUPTION, _player->GetGUID()))
                            {
                                corruption->SetDuration(corruption->GetDuration() + 6000);
                                corruption->SetNeedClientUpdateForTargets();
                            }
                            else if (AuraPtr doom = target->GetAura(WARLOCK_DOOM, _player->GetGUID()))
                            {
                                doom->SetDuration(doom->GetDuration() + 6000);
                                doom->SetNeedClientUpdateForTargets();
                            }
                        }
                        // Increases the duration of Immolate by 6s
                        else if (_player->GetSpecializationId(_player->GetActiveSpec()) == SPEC_WARLOCK_DESTRUCTION)
                        {
                            if (AuraPtr corruption = target->GetAura(WARLOCK_IMMOLATE, _player->GetGUID()))
                            {
                                corruption->SetDuration(corruption->GetDuration() + 6000);
                                corruption->SetNeedClientUpdateForTargets();
                            }

                            if (GetSpell()->IsCritForTarget(target))
                                _player->SetPower(POWER_BURNING_EMBERS, _player->GetPower(POWER_BURNING_EMBERS) + 2);
                            else
                                _player->SetPower(POWER_BURNING_EMBERS, _player->GetPower(POWER_BURNING_EMBERS) + 1);
                        }
                        // Increases the duration of Corruption by 6s
                        else
                        {
                            if (AuraPtr corruption = target->GetAura(WARLOCK_CORRUPTION, _player->GetGUID()))
                            {
                                corruption->SetDuration(corruption->GetDuration() + 6000);
                                corruption->SetNeedClientUpdateForTargets();
                            }
                        }
                    }
                }
            }

            void Register()
            {
                OnHit += SpellHitFn(spell_warl_fel_flame_SpellScript::HandleOnHit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warl_fel_flame_SpellScript();
        }
};

// Drain Life - 689
class spell_warl_drain_life : public SpellScriptLoader
{
    public:
        spell_warl_drain_life() : SpellScriptLoader("spell_warl_drain_life") { }

        class spell_warl_drain_life_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_warl_drain_life_AuraScript);

            void OnTick(constAuraEffectPtr aurEff)
            {
                if (Unit* caster = GetCaster())
                {
                    Player* _player = GetCaster()->ToPlayer();
                    if (!_player)
                        return;

                    // Restoring 2% of the caster's total health every 1s
                    int32 basepoints = _player->GetMaxHealth() / 50;

                    // In Demonology spec : Generates 10 Demonic Fury per second
                    if (_player->GetSpecializationId(_player->GetActiveSpec()) == SPEC_WARLOCK_DEMONOLOGY)
                        _player->EnergizeBySpell(_player, 689, 10, POWER_DEMONIC_FURY);

                    _player->CastCustomSpell(_player, WARLOCK_DRAIN_LIFE_HEAL, &basepoints, NULL, NULL, true);
                }
            }

            void Register()
            {
                OnEffectPeriodic += AuraEffectPeriodicFn(spell_warl_drain_life_AuraScript::OnTick, EFFECT_0, SPELL_AURA_PERIODIC_DAMAGE);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_warl_drain_life_AuraScript();
        }
};

// Soul Harvest - 101976
class spell_warl_soul_harverst : public SpellScriptLoader
{
    public:
        spell_warl_soul_harverst() : SpellScriptLoader("spell_warl_soul_harverst") { }

        class spell_warl_soul_harverst_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_warl_soul_harverst_AuraScript);

            uint32 update;

            bool Validate(SpellInfo const* /*spell*/)
            {
                update = 0;

                if (!sSpellMgr->GetSpellInfo(101976))
                    return false;
                return true;
            }

            void OnUpdate(uint32 diff)
            {
                update += diff;

                if (update >= 1000)
                {
                    if (Player* _player = GetCaster()->ToPlayer())
                    {
                        if (!_player->isInCombat() && !_player->InArena() && _player->isAlive())
                        {
                            _player->SetHealth(_player->GetHealth() + int32(_player->GetMaxHealth() / 50));

                            if (Pet* pet = _player->GetPet())
                                pet->SetHealth(pet->GetHealth() + int32(pet->GetMaxHealth() / 50));
                        }
                    }

                    update = 0;
                }
            }

            void Register()
            {
                OnAuraUpdate += AuraUpdateFn(spell_warl_soul_harverst_AuraScript::OnUpdate);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_warl_soul_harverst_AuraScript();
        }
};

// Life Tap - 1454
class spell_warl_life_tap : public SpellScriptLoader
{
    public:
        spell_warl_life_tap() : SpellScriptLoader("spell_warl_life_tap") { }

        class spell_warl_life_tap_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warl_life_tap_SpellScript);

            SpellCastResult CheckLife()
            {
                if (GetCaster()->GetHealthPct() > 15.0f)
                    return SPELL_CAST_OK;
                return SPELL_FAILED_FIZZLE;
            }

            void HandleOnHit()
            {
                if (Player* _player = GetCaster()->ToPlayer())
                {
                    int32 healthCost = int32(_player->GetMaxHealth() * 0.15f);

                    _player->SetHealth(_player->GetHealth() - healthCost);
                    _player->EnergizeBySpell(_player, 1454, healthCost, POWER_MANA);
                }
            }

            void Register()
            {
                OnCheckCast += SpellCheckCastFn(spell_warl_life_tap_SpellScript::CheckLife);
                OnHit += SpellHitFn(spell_warl_life_tap_SpellScript::HandleOnHit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warl_life_tap_SpellScript();
        }
};

// Soulburn : Harvest Life - 115707
class spell_warl_soulburn_harvest_life : public SpellScriptLoader
{
    public:
        spell_warl_soulburn_harvest_life() : SpellScriptLoader("spell_warl_soulburn_harvest_life") { }

        class spell_warl_soulburn_harvest_life_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_warl_soulburn_harvest_life_AuraScript);

            void OnApply(constAuraEffectPtr /*aurEff*/, AuraEffectHandleModes /*mode*/)
            {
                if (!GetCaster())
                    return;

                if (Player* player = GetCaster()->ToPlayer())
                    if (player->HasAura(WARLOCK_SOULBURN_AURA))
                        player->RemoveAurasDueToSpell(WARLOCK_SOULBURN_AURA);
            }

            void OnTick(constAuraEffectPtr aurEff)
            {
                if (!GetCaster())
                    return;

                if (Player* _player = GetCaster()->ToPlayer())
                {
                    // Restoring 3-4.5% of the caster's total health every 1s - With 33% bonus
                    int32 basepoints = int32(frand(0.03f, 0.045f) * _player->GetMaxHealth());

                    AddPct(basepoints, 33);

                    if (!_player->HasSpellCooldown(WARLOCK_HARVEST_LIFE_HEAL))
                    {
                        _player->CastCustomSpell(_player, WARLOCK_HARVEST_LIFE_HEAL, &basepoints, NULL, NULL, true);
                        // prevent the heal to proc off for each targets
                        _player->AddSpellCooldown(WARLOCK_HARVEST_LIFE_HEAL, 0, time(NULL) + 1);
                    }

                    _player->EnergizeBySpell(_player, aurEff->GetSpellInfo()->Id, 4, POWER_DEMONIC_FURY);
                }
            }

            void Register()
            {
                OnEffectApply += AuraEffectApplyFn(spell_warl_soulburn_harvest_life_AuraScript::OnApply, EFFECT_2, SPELL_AURA_PERIODIC_DAMAGE, AURA_EFFECT_HANDLE_REAL);
                OnEffectPeriodic += AuraEffectPeriodicFn(spell_warl_soulburn_harvest_life_AuraScript::OnTick, EFFECT_2, SPELL_AURA_PERIODIC_DAMAGE);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_warl_soulburn_harvest_life_AuraScript();
        }
};

// Harvest Life - 108371
class spell_warl_harvest_life : public SpellScriptLoader
{
    public:
        spell_warl_harvest_life() : SpellScriptLoader("spell_warl_harvest_life") { }

        class spell_warl_harvest_life_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_warl_harvest_life_AuraScript);

            void OnTick(constAuraEffectPtr aurEff)
            {
                if (!GetCaster())
                    return;

                if (Player* _player = GetCaster()->ToPlayer())
                {
                    // Restoring 3-4.5% of the caster's total health every 1s - With 33% bonus
                    int32 basepoints = int32(frand(0.03f, 0.045f) * _player->GetMaxHealth());

                    AddPct(basepoints, 33);

                    if (!_player->HasSpellCooldown(WARLOCK_HARVEST_LIFE_HEAL))
                    {
                        _player->CastCustomSpell(_player, WARLOCK_HARVEST_LIFE_HEAL, &basepoints, NULL, NULL, true);
                        // prevent the heal to proc off for each targets
                        _player->AddSpellCooldown(WARLOCK_HARVEST_LIFE_HEAL, 0, time(NULL) + 1);
                    }

                    _player->EnergizeBySpell(_player, aurEff->GetSpellInfo()->Id, 4, POWER_DEMONIC_FURY);
                }
            }

            void Register()
            {
                OnEffectPeriodic += AuraEffectPeriodicFn(spell_warl_harvest_life_AuraScript::OnTick, EFFECT_2, SPELL_AURA_PERIODIC_DAMAGE);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_warl_harvest_life_AuraScript();
        }
};

// Fear - 5782 and Bloody Fear - 111397
class spell_warl_fear : public SpellScriptLoader
{
    public:
        spell_warl_fear() : SpellScriptLoader("spell_warl_fear") { }

        class spell_warl_fear_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warl_fear_SpellScript);

            void HandleAfterHit()
            {
                if (Player* _player = GetCaster()->ToPlayer())
                {
                    if (Unit* target = GetHitUnit())
                    {
                        if (_player->HasAura(WARLOCK_GLYPH_OF_FEAR))
                        {
                            _player->CastSpell(target, WARLOCK_GLYPH_OF_FEAR_EFFECT, true);
                            _player->AddSpellCooldown(5782, 0, time(NULL) + 5);
                        }
                        else
                            _player->CastSpell(target, WARLOCK_FEAR_EFFECT, true);
                    }
                }
            }

            void Register()
            {
                AfterHit += SpellHitFn(spell_warl_fear_SpellScript::HandleAfterHit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warl_fear_SpellScript();
        }
};

// Updated 4.3.4
class spell_warl_banish : public SpellScriptLoader
{
    public:
        spell_warl_banish() : SpellScriptLoader("spell_warl_banish") { }

        class spell_warl_banish_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warl_banish_SpellScript);

            bool Load()
            {
                _removed = false;
                return true;
            }

            void HandleBanish()
            {
                // Casting Banish on a banished target will cancel the effect
                // Check if the target already has Banish, if so, do nothing.

                if (Unit* target = GetHitUnit())
                {
                    if (target->GetAuraEffect(SPELL_AURA_SCHOOL_IMMUNITY, SPELLFAMILY_WARLOCK, 0, 0x08000000, 0))
                    {
                        // No need to remove old aura since its removed due to not stack by current Banish aura
                        PreventHitDefaultEffect(EFFECT_0);
                        PreventHitDefaultEffect(EFFECT_1);
                        PreventHitDefaultEffect(EFFECT_2);
                        _removed = true;
                    }
                }
            }

            void RemoveAura()
            {
                if (_removed)
                    PreventHitAura();
            }

            void Register()
            {
                BeforeHit += SpellHitFn(spell_warl_banish_SpellScript::HandleBanish);
                AfterHit += SpellHitFn(spell_warl_banish_SpellScript::RemoveAura);
            }

            bool _removed;
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warl_banish_SpellScript();
        }
};

// Create Healthstone - 6201
class spell_warl_create_healthstone : public SpellScriptLoader
{
    public:
        spell_warl_create_healthstone() : SpellScriptLoader("spell_warl_create_healthstone") { }

        class spell_warl_create_healthstone_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warl_create_healthstone_SpellScript);

            void HandleAfterCast()
            {
                GetCaster()->CastSpell(GetCaster(), WARLOCK_CREATE_HEALTHSTONE, true);
            }

            void Register()
            {
                AfterCast += SpellCastFn(spell_warl_create_healthstone_SpellScript::HandleAfterCast);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warl_create_healthstone_SpellScript();
        }
};

class spell_warl_seed_of_corruption : public SpellScriptLoader
{
    public:
        spell_warl_seed_of_corruption() : SpellScriptLoader("spell_warl_seed_of_corruption") { }

        class spell_warl_seed_of_corruption_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warl_seed_of_corruption_SpellScript);

            void FilterTargets(std::list<WorldObject*>& targets)
            {
                if (GetExplTargetUnit())
                    targets.remove(GetExplTargetUnit());
            }

            void Register()
            {
                OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_warl_seed_of_corruption_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_DEST_AREA_ENEMY);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warl_seed_of_corruption_SpellScript();
        }
};

enum Soulshatter
{
    SPELL_SOULSHATTER   = 32835,
};

class spell_warl_soulshatter : public SpellScriptLoader
{
    public:
        spell_warl_soulshatter() : SpellScriptLoader("spell_warl_soulshatter") { }

        class spell_warl_soulshatter_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warl_soulshatter_SpellScript);

            bool Validate(SpellInfo const* /*spell*/)
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_SOULSHATTER))
                    return false;
                return true;
            }

            void HandleDummy(SpellEffIndex /*effIndex*/)
            {
                Unit* caster = GetCaster();
                if (Unit* target = GetHitUnit())
                {
                    if (target->CanHaveThreatList() && target->getThreatManager().getThreat(caster) > 0.0f)
                        caster->CastSpell(target, SPELL_SOULSHATTER, true);
                }
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_warl_soulshatter_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warl_soulshatter_SpellScript();
        }
};

// Demonic Circle : Summon - 48018
class spell_warl_demonic_circle_summon : public SpellScriptLoader
{
    public:
        spell_warl_demonic_circle_summon() : SpellScriptLoader("spell_warl_demonic_circle_summon") { }

        class spell_warl_demonic_circle_summon_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_warl_demonic_circle_summon_AuraScript);

            void HandleRemove(constAuraEffectPtr aurEff, AuraEffectHandleModes mode)
            {
                if (GetTarget())
                {
                    // If effect is removed by expire remove the summoned demonic circle too.
                    if (!(mode & AURA_EFFECT_HANDLE_REAPPLY))
                        GetTarget()->RemoveGameObject(GetId(), true);

                    if (GetTarget()->GetAuraApplication(aurEff->GetSpellInfo()->Id, GetTarget()->GetGUID()))
                        GetTarget()->GetAuraApplication(aurEff->GetSpellInfo()->Id, GetTarget()->GetGUID())->SendFakeAuraUpdate(WARLOCK_DEMONIC_CIRCLE_ALLOW_CAST, true);
                }
            }

            void HandleDummyTick(constAuraEffectPtr aurEff)
            {
                if (GetTarget())
                {
                    if (GameObject* circle = GetTarget()->GetGameObject(GetId()))
                    {
                        // Here we check if player is in demonic circle teleport range, if so add
                        // WARLOCK_DEMONIC_CIRCLE_ALLOW_CAST; allowing him to cast the WARLOCK_DEMONIC_CIRCLE_TELEPORT.
                        // If not in range remove the WARLOCK_DEMONIC_CIRCLE_ALLOW_CAST.

                        SpellInfo const* spellInfo = sSpellMgr->GetSpellInfo(WARLOCK_DEMONIC_CIRCLE_TELEPORT);

                        if (GetTarget()->IsWithinDist(circle, spellInfo->GetMaxRange(true)))
                            GetTarget()->GetAuraApplication(aurEff->GetSpellInfo()->Id, GetTarget()->GetGUID())->SendFakeAuraUpdate(WARLOCK_DEMONIC_CIRCLE_ALLOW_CAST, false);
                        else
                            GetTarget()->GetAuraApplication(aurEff->GetSpellInfo()->Id, GetTarget()->GetGUID())->SendFakeAuraUpdate(WARLOCK_DEMONIC_CIRCLE_ALLOW_CAST, true);
                    }
                }
            }

            void Register()
            {
                OnEffectRemove += AuraEffectApplyFn(spell_warl_demonic_circle_summon_AuraScript::HandleRemove, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY, AURA_EFFECT_HANDLE_REAL_OR_REAPPLY_MASK);
                OnEffectPeriodic += AuraEffectPeriodicFn(spell_warl_demonic_circle_summon_AuraScript::HandleDummyTick, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_warl_demonic_circle_summon_AuraScript();
        }
};

// Demonic Circle : Teleport - 48020 and Soulburn : Demonic Circle : Teleport - 114794
class spell_warl_demonic_circle_teleport : public SpellScriptLoader
{
    public:
        spell_warl_demonic_circle_teleport() : SpellScriptLoader("spell_warl_demonic_circle_teleport") { }

        class spell_warl_demonic_circle_teleport_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_warl_demonic_circle_teleport_AuraScript);

            void HandleTeleport(constAuraEffectPtr aurEff, AuraEffectHandleModes /*mode*/)
            {
                if (Player* player = GetTarget()->ToPlayer())
                {
                    if (GameObject* circle = player->GetGameObject(WARLOCK_DEMONIC_CIRCLE_SUMMON))
                    {
                        player->NearTeleportTo(circle->GetPositionX(), circle->GetPositionY(), circle->GetPositionZ(), circle->GetOrientation());
                        player->RemoveMovementImpairingAuras();
                        player->Relocate(circle->GetPositionX(), circle->GetPositionY(), circle->GetPositionZ(), circle->GetOrientation());

                        if (aurEff->GetSpellInfo()->Id == WARLOCK_SOULBURN_DEMONIC_CIRCLE_TELE)
                            if (player->HasAura(WARLOCK_SOULBURN_AURA))
                                player->RemoveAurasDueToSpell(WARLOCK_SOULBURN_AURA);

                        WorldPacket data(SMSG_MOVE_UPDATE);
                        player->m_movementInfo.pos.m_positionX = player->GetPositionX();
                        player->m_movementInfo.pos.m_positionY = player->GetPositionY();
                        player->m_movementInfo.pos.m_positionZ = player->GetPositionZ();
                        player->m_movementInfo.pos.m_orientation = player->GetOrientation();
                        WorldSession::WriteMovementInfo(data, &player->m_movementInfo);
                        player->SendMessageToSet(&data, player);
                    }
                }
            }

            void Register()
            {
                OnEffectApply += AuraEffectApplyFn(spell_warl_demonic_circle_teleport_AuraScript::HandleTeleport, EFFECT_0, SPELL_AURA_MECHANIC_IMMUNITY, AURA_EFFECT_HANDLE_REAL);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_warl_demonic_circle_teleport_AuraScript();
        }
};

class spell_warl_unstable_affliction : public SpellScriptLoader
{
    public:
        spell_warl_unstable_affliction() : SpellScriptLoader("spell_warl_unstable_affliction") { }

        class spell_warl_unstable_affliction_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_warl_unstable_affliction_AuraScript);

            bool Validate(SpellInfo const* /*spell*/)
            {
                if (!sSpellMgr->GetSpellInfo(WARLOCK_UNSTABLE_AFFLICTION_DISPEL))
                    return false;
                return true;
            }

            void HandleDispel(DispelInfo* dispelInfo)
            {
                if (Unit* caster = GetCaster())
                    if (constAuraEffectPtr aurEff = GetEffect(EFFECT_0))
                    {
                        int32 damage = aurEff->GetAmount() * 7;
                        // backfire damage and silence
                        caster->CastCustomSpell(dispelInfo->GetDispeller(), WARLOCK_UNSTABLE_AFFLICTION_DISPEL, &damage, NULL, NULL, true, NULL, aurEff);
                    }
            }

            void Register()
            {
                AfterDispel += AuraDispelFn(spell_warl_unstable_affliction_AuraScript::HandleDispel);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_warl_unstable_affliction_AuraScript();
        }
};

void AddSC_warlock_spell_scripts()
{
    new spell_warl_grimoire_of_supremacy();
    new spell_warl_soulburn_drain_life();
    new spell_warl_soulburn_health_funnel();
    new spell_warl_soulburn_seed_of_corruption_damage();
    new spell_warl_soulburn_seed_of_corruption();
    new spell_warl_soulburn_remove();
    new spell_warl_soulburn_override();
    new spell_warl_glyph_of_soulwell();
    new spell_warl_imp_swarm();
    new spell_warl_glyph_of_imp_swarm();
    new spell_warl_unbound_will();
    new spell_warl_rain_of_fire_damage();
    new spell_warl_kil_jaedens_cunning();
    new spell_warl_shield_of_shadow();
    new spell_warl_agony();
    new spell_warl_grimoire_of_sacrifice();
    new spell_warl_flames_of_xoroth();
    new spell_warl_soul_link_dummy();
    new spell_warl_soul_link();
    new spell_warl_archimondes_vengeance_cooldown();
    new spell_warl_archimondes_vengance();
    new spell_warl_archimondes_vengance_passive();
    new spell_warl_molten_core_dot();
    new spell_warl_decimate();
    new spell_warl_demonic_call();
    new spell_warl_void_ray();
    new spell_warl_chaos_wave();
    new spell_warl_metamorphosis_cost();
    new spell_warl_immolation_aura();
    new spell_warl_dark_bargain_on_absorb();
    new spell_warl_dark_regeneration();
    new spell_warl_soul_leech();
    new spell_warl_sacrificial_pact();
    new spell_warl_hand_of_guldan();
    new spell_warl_twilight_ward_s12();
    new spell_warl_hellfire();
    new spell_warl_demonic_leap_jump();
    new spell_warl_demonic_leap();
    new spell_warl_burning_rush();
    new spell_warl_soul_swap_soulburn();
    new spell_warl_soul_swap();
    new spell_warl_nightfall();
    new spell_warl_drain_soul();
    new spell_warl_demonic_gateway_charges();
    new spell_warl_demonic_gateway();
    new spell_warl_rain_of_fire();
    new spell_warl_chaos_bolt();
    new spell_warl_ember_tap();
    new spell_warl_fire_and_brimstone();
    new spell_warl_conflagrate_aura();
    new spell_warl_shadowburn();
    new spell_warl_burning_embers();
    new spell_warl_fel_flame();
    new spell_warl_drain_life();
    new spell_warl_soul_harverst();
    new spell_warl_life_tap();
    new spell_warl_soulburn_harvest_life();
    new spell_warl_harvest_life();
    new spell_warl_fear();
    new spell_warl_banish();
    new spell_warl_create_healthstone();
    new spell_warl_seed_of_corruption();
    new spell_warl_soulshatter();
    new spell_warl_demonic_circle_summon();
    new spell_warl_demonic_circle_teleport();
    new spell_warl_unstable_affliction();
}
