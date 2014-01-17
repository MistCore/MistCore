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
 * Scripts for spells with SPELLFAMILY_DRUID and SPELLFAMILY_GENERIC spells used by druid players.
 * Ordered alphabetically using scriptname.
 * Scriptnames of files in this file should be prefixed with "spell_dru_".
 */

#include "ScriptMgr.h"
#include "SpellScript.h"
#include "SpellAuraEffects.h"
#include "Containers.h"

enum DruidSpells
{
    DRUID_INCREASED_MOONFIRE_DURATION       = 38414,
    DRUID_NATURES_SPLENDOR                  = 57865,
    DRUID_SURVIVAL_INSTINCTS                = 50322,
    DRUID_SAVAGE_ROAR                       = 62071,
    SPELL_DRUID_ITEM_T8_BALANCE_RELIC       = 64950,
    SPELL_DRUID_WRATH                       = 5176,
    SPELL_DRUID_STARFIRE                    = 2912,
    SPELL_DRUID_STARSURGE                   = 78674,
    SPELL_DRUID_ECLIPSE_GENERAL_ENERGIZE    = 81070,
    SPELL_DRUID_STARSURGE_ENERGIZE          = 86605,
    SPELL_DRUID_SOLAR_ECLIPSE               = 48517,
    SPELL_DRUID_LUNAR_ECLIPSE               = 48518,
    SPELL_DRUID_LUNAR_ECLIPSE_OVERRIDE      = 107095,
    SPELL_DRUID_STARFALL                    = 48505,
    SPELL_DRUID_NATURES_GRACE               = 16886,
    SPELL_DRUID_EUPHORIA                    = 81062,
    SPELL_DRUID_PROWL                       = 5215,
    SPELL_DRUID_WEAKENED_ARMOR              = 113746,
    SPELL_DRUID_GLYPH_OF_FRENZIED_REGEN     = 54810,
    SPELL_DRUID_FRENZIED_REGEN_HEAL_TAKE    = 124769,
    SPELL_DRUID_CELESTIAL_ALIGNMENT         = 112071,
    SPELL_DRUID_ASTRAL_COMMUNION            = 127663,
    SPELL_DRUID_SUNFIRE                     = 93402,
    SPELL_DRUID_MOONFIRE                    = 8921,
    SPELL_DRUID_SWIFTMEND                   = 81262,
    SPELL_DRUID_SWIFTMEND_TICK              = 81269,
    DRUID_NPC_WILD_MUSHROOM                 = 47649,
    DRUID_SPELL_FUNGAL_GROWTH_SUMMON        = 81283,
    DRUID_SPELL_MUSHROOM_BIRTH_VISUAL       = 94081,
    DRUID_SPELL_WILD_MUSHROOM_DEATH_VISUAL  = 92701,
    DRUID_SPELL_WILD_MUSHROOM_SUICIDE       = 92853,
    DRUID_SPELL_WILD_MUSHROOM_DAMAGE        = 78777,
    SPELL_DRUID_WILD_MUSHROOM_HEAL          = 102792,
    SPELL_DRUID_FAERIE_DECREASE_SPEED       = 102354,
    SPELL_DRUID_SKULL_BASH_MANA_COST        = 82365,
    SPELL_DRUID_SKULL_BASH_INTERUPT         = 93985,
    SPELL_DRUID_SKULL_BASH_CHARGE           = 93983,
    SPELL_DRUID_FORM_CAT_INCREASE_SPEED     = 113636,
    SPELL_DRUID_GLYPH_OF_REGROWTH           = 116218,
    SPELL_DRUID_REGROWTH                    = 8936,
    SPELL_DRUID_MARK_OF_THE_WILD            = 1126,
    SPELL_DRUID_OMEN_OF_CLARITY             = 113043,
    SPELL_DRUID_CLEARCASTING                = 16870,
    SPELL_DRUID_LIFEBLOOM                   = 33763,
    SPELL_DRUID_LIFEBLOOM_FINAL_HEAL        = 33778,
    SPELL_DRUID_KILLER_INSTINCT             = 108299,
    SPELL_DRUID_KILLER_INSTINCT_MOD_STAT    = 108300,
    SPELL_DRUID_CAT_FORM                    = 768,
    SPELL_DRUID_BEAR_FORM                   = 5487,
    SPELL_DRUID_BEAR_FORM_RAGE_GAIN         = 17057,
    SPELL_DRUID_INFECTED_WOUNDS             = 58180,
    SPELL_DRUID_BEAR_HUG                    = 102795,
    SPELL_DRUID_RIP                         = 1079,
    SPELL_DRUID_SAVAGE_DEFENSE_DODGE_PCT    = 132402,
    SPELL_DRUID_DASH                        = 1850,
    SPELL_DRUID_BERSERK_BEAR                = 50334,
    SPELL_DRUID_BERSERK_CAT                 = 106951,
    SPELL_DRUID_STAMPEDING_ROAR             = 106898,
    SPELL_DRUID_SOLAR_BEAM                  = 78675,
    SPELL_DRUID_SOLAR_BEAM_SILENCE          = 81261,
    SPELL_DRUID_URSOLS_VORTEX_AREA_TRIGGER  = 102793,
    SPELL_DRUID_URSOLS_VORTEX_SNARE         = 127797,
    SPELL_DRUID_URSOLS_VORTEX_JUMP_DEST     = 118283,
    SPELL_DRUID_CENARION_WARD               = 102352,
    SPELL_DRUID_NATURES_VIGIL_HEAL          = 124988,
    SPELL_DRUID_NATURES_VIGIL_DAMAGE        = 124991,
    SPELL_DRUID_SYMBIOSIS_FOR_CASTER        = 110309,
    SPELL_DRUID_SYMBIOSIS_DEATH_KNIGHT      = 110478,
    SPELL_DRUID_SYMBIOSIS_HUNTER            = 110479,
    SPELL_DRUID_SYMBIOSIS_MAGE              = 110482,
    SPELL_DRUID_SYMBIOSIS_MONK              = 110483,
    SPELL_DRUID_SYMBIOSIS_PALADIN           = 110484,
    SPELL_DRUID_SYMBIOSIS_PRIEST            = 110485,
    SPELL_DRUID_SYMBIOSIS_ROGUE             = 110486,
    SPELL_DRUID_SYMBIOSIS_SHAMAN            = 110488,
    SPELL_DRUID_SYMBIOSIS_WARLOCK           = 110490,
    SPELL_DRUID_SYMBIOSIS_WARRIOR           = 110491,
    SPELL_DRUID_SHATTERING_BLOW             = 112997,
    WARLOCK_DEMONIC_CIRCLE_SUMMON           = 48018,
    SPELL_DRUID_RAKE                        = 1822,
    SPELL_DRUID_CONSECRATION_DUMMY          = 81298,
    SPELL_DRUID_CONSECRATION_DAMAGE         = 110705,
    SPELL_DRUID_SHOOTING_STARS              = 93400,
    SPELL_DRUID_TIGERS_FURY                 = 5217,
    SPELL_DRUID_SOUL_OF_THE_FOREST          = 114107,
    SPELL_DRUID_SOUL_OF_THE_FOREST_HASTE    = 114108,
    SPELL_DRUID_SWIPE_CAT                   = 62078,
    SPELL_DRUID_MANGLE_BEAR                 = 33878,
    SPELL_DRUID_STAMPEDE                    = 81022,
    SPELL_DRUID_INCARNATION_KING_OF_JUNGLE  = 102543,
    SPELL_DRUID_GLYPH_OF_SHRED              = 114234,
    SPELL_DRUID_GLYPH_OF_SHRED_OVERRIDE     = 114235,
    SPELL_DRUID_INCARNATION_CHOSEN_OF_ELUNE = 122114,
    SPELL_DRUID_GLYPH_OF_BLOOMING           = 121840,
    SPELL_DRUID_GLYPH_OF_THE_TREANT         = 114282,
};

// Glyph of the Treant - 125047
class spell_dru_glyph_of_the_treant : public SpellScriptLoader
{
    public:
        spell_dru_glyph_of_the_treant() : SpellScriptLoader("spell_dru_glyph_of_the_treant") { }

        class spell_dru_glyph_of_the_treant_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_dru_glyph_of_the_treant_AuraScript);

            void OnApply(constAuraEffectPtr /*aurEff*/, AuraEffectHandleModes /*mode*/)
            {
                if (Player* _player = GetTarget()->ToPlayer())
                    _player->learnSpell(SPELL_DRUID_GLYPH_OF_THE_TREANT, false);
            }

            void OnRemove(constAuraEffectPtr /*aurEff*/, AuraEffectHandleModes /*mode*/)
            {
                if (Player* _player = GetTarget()->ToPlayer())
                    if (_player->HasSpell(SPELL_DRUID_GLYPH_OF_THE_TREANT))
                        _player->removeSpell(SPELL_DRUID_GLYPH_OF_THE_TREANT, false, false);
            }

            void Register()
            {
                OnEffectApply += AuraEffectApplyFn(spell_dru_glyph_of_the_treant_AuraScript::OnApply, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
                OnEffectRemove += AuraEffectRemoveFn(spell_dru_glyph_of_the_treant_AuraScript::OnRemove, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_dru_glyph_of_the_treant_AuraScript();
        }
};

// Incarnation : Chosen of Elune - 102560
class spell_dru_incarnation_chosen_of_elune : public SpellScriptLoader
{
    public:
        spell_dru_incarnation_chosen_of_elune() : SpellScriptLoader("spell_dru_incarnation_chosen_of_elune") { }

        class spell_dru_incarnation_chosen_of_elune_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_dru_incarnation_chosen_of_elune_AuraScript);

            void OnApply(constAuraEffectPtr /*aurEff*/, AuraEffectHandleModes /*mode*/)
            {
                if (Player* _player = GetTarget()->ToPlayer())
                    _player->CastSpell(_player, SPELL_DRUID_INCARNATION_CHOSEN_OF_ELUNE, true);
            }

            void OnRemove(constAuraEffectPtr /*aurEff*/, AuraEffectHandleModes /*mode*/)
            {
                if (Player* _player = GetTarget()->ToPlayer())
                    _player->RemoveAura(SPELL_DRUID_INCARNATION_CHOSEN_OF_ELUNE);
            }

            void Register()
            {
                OnEffectApply += AuraEffectApplyFn(spell_dru_incarnation_chosen_of_elune_AuraScript::OnApply, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
                OnEffectRemove += AuraEffectRemoveFn(spell_dru_incarnation_chosen_of_elune_AuraScript::OnRemove, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_dru_incarnation_chosen_of_elune_AuraScript();
        }
};

// Called by Incarnation : Chosen of Elune - 102560, Incarnation : Son of Ursoc - 102558 and Incarnation : King of the Jungle - 102543
// Incarnation - Skins
class spell_dru_incarnation_skins : public SpellScriptLoader
{
    public:
        spell_dru_incarnation_skins() : SpellScriptLoader("spell_dru_incarnation_skins") { }

        class spell_dru_incarnation_skins_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_dru_incarnation_skins_AuraScript);

            void OnApply(constAuraEffectPtr /*aurEff*/, AuraEffectHandleModes /*mode*/)
            {
                if (Player* _player = GetTarget()->ToPlayer())
                    _player->SetDisplayId(_player->GetModelForForm(_player->GetShapeshiftForm()));
            }

            void OnRemove(constAuraEffectPtr /*aurEff*/, AuraEffectHandleModes /*mode*/)
            {
                if (Player* _player = GetTarget()->ToPlayer())
                    _player->SetDisplayId(_player->GetModelForForm(_player->GetShapeshiftForm()));
            }

            void Register()
            {
                switch (m_scriptSpellId)
                {
                    case 102543:// King of the Jungle
                        OnEffectApply += AuraEffectApplyFn(spell_dru_incarnation_skins_AuraScript::OnApply, EFFECT_0, SPELL_AURA_OVERRIDE_ACTIONBAR_SPELLS, AURA_EFFECT_HANDLE_REAL);
                        OnEffectRemove += AuraEffectRemoveFn(spell_dru_incarnation_skins_AuraScript::OnRemove, EFFECT_0, SPELL_AURA_OVERRIDE_ACTIONBAR_SPELLS, AURA_EFFECT_HANDLE_REAL);
                        break;
                    case 102558:// Son of Ursoc
                        OnEffectApply += AuraEffectApplyFn(spell_dru_incarnation_skins_AuraScript::OnApply, EFFECT_0, SPELL_AURA_ADD_PCT_MODIFIER, AURA_EFFECT_HANDLE_REAL);
                        OnEffectRemove += AuraEffectRemoveFn(spell_dru_incarnation_skins_AuraScript::OnRemove, EFFECT_0, SPELL_AURA_ADD_PCT_MODIFIER, AURA_EFFECT_HANDLE_REAL);
                        break;
                    case 102560:// Chosen of Elune
                        OnEffectApply += AuraEffectApplyFn(spell_dru_incarnation_skins_AuraScript::OnApply, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
                        OnEffectRemove += AuraEffectRemoveFn(spell_dru_incarnation_skins_AuraScript::OnRemove, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
                        break;
                    default:
                        break;
                }
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_dru_incarnation_skins_AuraScript();
        }
};

// Called by Berserk (cat) - 106951 and Tiger's Fury - 5217
// Glyph of Shred - 114234
class spell_dru_glyph_of_shred : public SpellScriptLoader
{
    public:
        spell_dru_glyph_of_shred() : SpellScriptLoader("spell_dru_glyph_of_shred") { }

        class spell_dru_glyph_of_shred_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_dru_glyph_of_shred_AuraScript);

            void OnApply(constAuraEffectPtr /*aurEff*/, AuraEffectHandleModes /*mode*/)
            {
                GetTarget()->CastSpell(GetTarget(), SPELL_DRUID_GLYPH_OF_SHRED_OVERRIDE, true);
            }

            void OnRemove(constAuraEffectPtr aurEff, AuraEffectHandleModes /*mode*/)
            {
                if (aurEff->GetSpellInfo()->Id == SPELL_DRUID_BERSERK_CAT && !GetTarget()->HasAura(SPELL_DRUID_TIGERS_FURY))
                    GetTarget()->RemoveAurasDueToSpell(SPELL_DRUID_GLYPH_OF_SHRED_OVERRIDE);
                else if (aurEff->GetSpellInfo()->Id == SPELL_DRUID_TIGERS_FURY && !GetTarget()->HasAura(SPELL_DRUID_BERSERK_CAT))
                    GetTarget()->RemoveAurasDueToSpell(SPELL_DRUID_GLYPH_OF_SHRED_OVERRIDE);
            }

            void Register()
            {
                switch (m_scriptSpellId)
                {
                    case SPELL_DRUID_BERSERK_CAT:
                        OnEffectApply += AuraEffectApplyFn(spell_dru_glyph_of_shred_AuraScript::OnApply, EFFECT_0, SPELL_AURA_ADD_PCT_MODIFIER, AURA_EFFECT_HANDLE_REAL);
                        OnEffectRemove += AuraEffectRemoveFn(spell_dru_glyph_of_shred_AuraScript::OnRemove, EFFECT_0, SPELL_AURA_ADD_PCT_MODIFIER, AURA_EFFECT_HANDLE_REAL);
                        break;
                    case SPELL_DRUID_TIGERS_FURY:
                        OnEffectApply += AuraEffectApplyFn(spell_dru_glyph_of_shred_AuraScript::OnApply, EFFECT_0, SPELL_AURA_MOD_DAMAGE_PERCENT_DONE, AURA_EFFECT_HANDLE_REAL);
                        OnEffectRemove += AuraEffectRemoveFn(spell_dru_glyph_of_shred_AuraScript::OnRemove, EFFECT_0, SPELL_AURA_MOD_DAMAGE_PERCENT_DONE, AURA_EFFECT_HANDLE_REAL);
                        break;
                    default:
                        break;
                }
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_dru_glyph_of_shred_AuraScript();
        }
};

 // Item - PvP Feral 4P Bonus - 131537
class spell_dru_item_pvp_feral_4p : public SpellScriptLoader
{
    public:
        spell_dru_item_pvp_feral_4p() : SpellScriptLoader("spell_dru_item_pvp_feral_4p") { }

        class spell_dru_item_pvp_feral_4p_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_dru_item_pvp_feral_4p_AuraScript);

            uint32 update;

            bool Validate(SpellInfo const* /*spell*/)
            {
                update = 0;

                if (!sSpellMgr->GetSpellInfo(101976))
                    return false;
                return true;
            }

            void OnUpdate(uint32 diff, AuraEffectPtr aurEff)
            {
                if (!GetCaster())
                    return;

                if (GetCaster()->HasAura(SPELL_DRUID_STAMPEDE))
                    return;

                update += diff;

                if (GetCaster()->HasAura(SPELL_DRUID_INCARNATION_KING_OF_JUNGLE))
                    return;

                if (update >= 30000)
                {
                    if (Player* _player = GetCaster()->ToPlayer())
                        _player->CastSpell(_player, SPELL_DRUID_STAMPEDE, true);

                    update = 0;
                }
            }

            void Register()
            {
                OnEffectUpdate += AuraEffectUpdateFn(spell_dru_item_pvp_feral_4p_AuraScript::OnUpdate, EFFECT_0, SPELL_AURA_DUMMY);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_dru_item_pvp_feral_4p_AuraScript();
        }
};

// Wild Charge (Moonkin) - 102383
class spell_dru_wild_charge_moonkin : public SpellScriptLoader
{
    public:
        spell_dru_wild_charge_moonkin() : SpellScriptLoader("spell_dru_wild_charge_moonkin") { }

        class spell_dru_wild_charge_moonkin_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_dru_wild_charge_moonkin_SpellScript);

            SpellCastResult CheckFight()
            {
                if (GetCaster())
                {
                    if (!GetCaster()->isInCombat())
                        return SPELL_FAILED_DONT_REPORT;
                }
                else
                    return SPELL_FAILED_DONT_REPORT;

                return SPELL_CAST_OK;
            }

            void Register()
            {
                OnCheckCast += SpellCheckCastFn(spell_dru_wild_charge_moonkin_SpellScript::CheckFight);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_dru_wild_charge_moonkin_SpellScript();
        }
};

// Thrash (bear) - 77758
class spell_dru_thrash_bear : public SpellScriptLoader
{
    public:
        spell_dru_thrash_bear() : SpellScriptLoader("spell_dru_thrash_bear") { }

        class spell_dru_thrash_bear_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_dru_thrash_bear_AuraScript);

            void OnTick(constAuraEffectPtr aurEff)
            {
                if (!GetCaster())
                    return;

                // Each tick has 25% chance to remove cooldown on Mangle
                if (Player* _plr = GetCaster()->ToPlayer())
                    if (roll_chance_i(25))
                        if (_plr->HasSpellCooldown(SPELL_DRUID_MANGLE_BEAR))
                            _plr->RemoveSpellCooldown(SPELL_DRUID_MANGLE_BEAR, true);
            }

            void Register()
            {
                OnEffectPeriodic += AuraEffectPeriodicFn(spell_dru_thrash_bear_AuraScript::OnTick, EFFECT_1, SPELL_AURA_PERIODIC_DAMAGE);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_dru_thrash_bear_AuraScript();
        }
};

// Swipe (cat) - 62078, Swipe (bear) - 779 and Maul - 6807
class spell_dru_swipe_and_maul : public SpellScriptLoader
{
    public:
        spell_dru_swipe_and_maul() : SpellScriptLoader("spell_dru_swipe_and_maul") { }

        class spell_dru_swipe_and_maul_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_dru_swipe_and_maul_SpellScript);

            void HandleOnHit()
            {
                if (Player* _player = GetCaster()->ToPlayer())
                {
                    if (Unit* target = GetHitUnit())
                    {
                        int32 damage = GetHitDamage();

                        // Swipe and Maul deals 20% more damage if target is bleeding
                        if (target->HasAuraState(AURA_STATE_BLEEDING))
                        {
                            AddPct(damage, 20);
                            SetHitDamage(damage);
                        }
                    }
                }
            }

            void Register()
            {
                OnHit += SpellHitFn(spell_dru_swipe_and_maul_SpellScript::HandleOnHit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_dru_swipe_and_maul_SpellScript();
        }
};

// Called by Lunar Eclipse - 48518 and Solar Eclipse - 48517
// Soul of the Forest - 114107
class spell_dru_soul_of_the_forest_eclipse : public SpellScriptLoader
{
    public:
        spell_dru_soul_of_the_forest_eclipse() : SpellScriptLoader("spell_dru_soul_of_the_forest_eclipse") { }

        class spell_dru_soul_of_the_forest_eclipse_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_dru_soul_of_the_forest_eclipse_AuraScript);

            void HandleEffectRemove(constAuraEffectPtr aurEff, AuraEffectHandleModes /*mode*/)
            {
                if (!GetTarget())
                    return;

                if (Player* _player = GetTarget()->ToPlayer())
                {
                    if (_player->HasAura(SPELL_DRUID_SOUL_OF_THE_FOREST_HASTE))
                    {
                        if (aurEff->GetSpellInfo()->Id == SPELL_DRUID_SOLAR_ECLIPSE)
                            _player->SetEclipsePower(int32(_player->GetEclipsePower() - 20));
                        else if (aurEff->GetSpellInfo()->Id == SPELL_DRUID_LUNAR_ECLIPSE)
                            _player->SetEclipsePower(int32(_player->GetEclipsePower() + 20));
                    }
                }
            }

            void Register()
            {
                AfterEffectRemove += AuraEffectRemoveFn(spell_dru_soul_of_the_forest_eclipse_AuraScript::HandleEffectRemove, EFFECT_0, SPELL_AURA_MOD_DAMAGE_PERCENT_DONE, AURA_EFFECT_HANDLE_REAL);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_dru_soul_of_the_forest_eclipse_AuraScript();
        }
};

// Called by Swiftmend - 18562 and Mangle (Bear) - 33878
// Soul of the Forest - 114107
class spell_dru_soul_of_the_forest : public SpellScriptLoader
{
    public:
        spell_dru_soul_of_the_forest() : SpellScriptLoader("spell_dru_soul_of_the_forest") { }

        class spell_dru_soul_of_the_forest_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_dru_soul_of_the_forest_SpellScript);

            void HandleOnHit()
            {
                if (Player* _player = GetCaster()->ToPlayer())
                {
                    if (_player->HasAura(SPELL_DRUID_SOUL_OF_THE_FOREST))
                    {
                        if (GetSpellInfo()->Id == 18562)
                            _player->CastSpell(_player, SPELL_DRUID_SOUL_OF_THE_FOREST_HASTE, true);
                        else
                            _player->EnergizeBySpell(_player, SPELL_DRUID_SOUL_OF_THE_FOREST, 40, POWER_RAGE);
                    }
                }
            }

            void Register()
            {
                OnHit += SpellHitFn(spell_dru_soul_of_the_forest_SpellScript::HandleOnHit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_dru_soul_of_the_forest_SpellScript();
        }
};

// Tiger's Fury - 5217
class spell_dru_tigers_fury : public SpellScriptLoader
{
    public:
        spell_dru_tigers_fury() : SpellScriptLoader("spell_dru_tigers_fury") { }

        class spell_dru_tigers_fury_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_dru_tigers_fury_SpellScript);

            SpellCastResult CheckBerzerk()
            {
                if (GetCaster())
                {
                    if (GetCaster()->HasAura(SPELL_DRUID_BERSERK_CAT))
                        return SPELL_FAILED_DONT_REPORT;
                }
                else
                    return SPELL_FAILED_DONT_REPORT;

                return SPELL_CAST_OK;
            }

            void Register()
            {
                OnCheckCast += SpellCheckCastFn(spell_dru_tigers_fury_SpellScript::CheckBerzerk);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_dru_tigers_fury_SpellScript();
        }
};

// Play Death - 110597
class spell_dru_play_death : public SpellScriptLoader
{
    public:
        spell_dru_play_death() : SpellScriptLoader("spell_dru_play_death") { }

        class spell_dru_play_death_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_dru_play_death_AuraScript);

            int32 health;
            int32 mana;

            void HandleEffectApply(constAuraEffectPtr /*aurEff*/, AuraEffectHandleModes /*mode*/)
            {
                health = GetTarget()->GetHealth();
                mana = GetTarget()->GetPower(POWER_MANA);
            }

            void HandleEffectRemove(constAuraEffectPtr /*aurEff*/, AuraEffectHandleModes /*mode*/)
            {
                if (health && mana)
                {
                    GetTarget()->SetHealth(health);
                    GetTarget()->SetPower(POWER_MANA, mana);
                }
            }

            void Register()
            {
                AfterEffectApply += AuraEffectApplyFn(spell_dru_play_death_AuraScript::HandleEffectApply, EFFECT_0, SPELL_AURA_FEIGN_DEATH, AURA_EFFECT_HANDLE_REAL);
                AfterEffectRemove += AuraEffectRemoveFn(spell_dru_play_death_AuraScript::HandleEffectRemove, EFFECT_0, SPELL_AURA_FEIGN_DEATH, AURA_EFFECT_HANDLE_REAL);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_dru_play_death_AuraScript();
        }
};

// Consecration - 110701 (periodic dummy)
class spell_dru_consecration : public SpellScriptLoader
{
    public:
        spell_dru_consecration() : SpellScriptLoader("spell_dru_consecration") { }

        class spell_dru_consecration_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_dru_consecration_AuraScript);

            void OnTick(constAuraEffectPtr aurEff)
            {
                if (DynamicObject* dynObj = GetCaster()->GetDynObject(SPELL_DRUID_CONSECRATION_DUMMY))
                    GetCaster()->CastSpell(dynObj->GetPositionX(), dynObj->GetPositionY(), dynObj->GetPositionZ(), SPELL_DRUID_CONSECRATION_DAMAGE, true);
            }

            void Register()
            {
                OnEffectPeriodic += AuraEffectPeriodicFn(spell_dru_consecration_AuraScript::OnTick, EFFECT_1, SPELL_AURA_PERIODIC_DUMMY);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_dru_consecration_AuraScript();
        }
};

// Consecration - 110701 (Symbiosis)
class spell_dru_consecration_area : public SpellScriptLoader
{
    public:
        spell_dru_consecration_area() : SpellScriptLoader("spell_dru_consecration_area") { }

        class spell_dru_consecration_area_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_dru_consecration_area_SpellScript);

            void HandleAfterCast()
            {
                if (Player* _player = GetCaster()->ToPlayer())
                    _player->CastSpell(_player, SPELL_DRUID_CONSECRATION_DUMMY, true);
            }

            void Register()
            {
                AfterCast += SpellCastFn(spell_dru_consecration_area_SpellScript::HandleAfterCast);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_dru_consecration_area_SpellScript();
        }
};

// Life Tap - 122290
class spell_dru_life_tap : public SpellScriptLoader
{
    public:
        spell_dru_life_tap() : SpellScriptLoader("spell_dru_life_tap") { }

        class spell_dru_life_tap_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_dru_life_tap_SpellScript);

            void HandleOnHit()
            {
                if (Player* _player = GetCaster()->ToPlayer())
                    _player->ModifyHealth(-1 * int32(_player->CountPctFromMaxHealth(20)));
            }

            void Register()
            {
                OnHit += SpellHitFn(spell_dru_life_tap_SpellScript::HandleOnHit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_dru_life_tap_SpellScript();
        }
};

// Binary predicate for sorting Units based on value of duration of an Aura
class AuraDurationCompareOrderPred
{
    public:
        AuraDurationCompareOrderPred(uint64 caster, uint32 auraId, bool ascending = true) : m_caster(caster), m_aura(auraId), m_ascending(ascending) {}
        bool operator() (const Unit* a, const Unit* b) const
        {
            return m_ascending ? a->GetAura(m_aura, m_caster)->GetDuration() < b->GetAura(m_aura, m_caster)->GetDuration() :
                                    a->GetAura(m_aura, m_caster)->GetDuration() > b->GetAura(m_aura, m_caster)->GetDuration();
        }
    private:
        uint64 m_caster;
        uint32 m_aura;
        const bool m_ascending;
};

// Soul Swap - 110810
class spell_dru_soul_swap : public SpellScriptLoader
{
    public:
        spell_dru_soul_swap() : SpellScriptLoader("spell_dru_soul_swap") { }

        class spell_dru_soul_swap_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_dru_soul_swap_SpellScript);

            void HandleOnHit()
            {
                if (Player* _player = GetCaster()->ToPlayer())
                {
                    if (Unit* target = GetHitUnit())
                    {
                        std::list<Unit*> tempList;
                        std::list<Unit*> targetList;

                        _player->GetAttackableUnitListInRange(tempList, 15.0f);

                        for (auto itr : tempList)
                        {
                            if (itr->GetGUID() == target->GetGUID())
                                continue;

                            if (itr->GetGUID() == _player->GetGUID())
                                continue;

                            if (!_player->IsValidAttackTarget(itr))
                                continue;

                            if (itr->HasAura(SPELL_DRUID_RIP, _player->GetGUID()) && itr->HasAura(SPELL_DRUID_RAKE, _player->GetGUID()))
                                targetList.push_back(itr);
                        }

                        if (!targetList.empty())
                        {
                            targetList.sort(AuraDurationCompareOrderPred(_player->GetGUID(), SPELL_DRUID_RIP));

                            for (auto itr : targetList)
                            {
                                int32 ripDuration;
                                int32 ripMaxDuration;
                                int32 ripAmount;
                                int32 rakeDuration;
                                int32 rakeMaxDuration;
                                int32 rakeAmount;

                                if (AuraPtr rip = itr->GetAura(SPELL_DRUID_RIP, _player->GetGUID()))
                                {
                                    ripDuration = rip->GetDuration();
                                    ripMaxDuration = rip->GetMaxDuration();
                                    ripAmount = rip->GetEffect(0)->GetAmount();
                                }
                                if (AuraPtr rake = itr->GetAura(SPELL_DRUID_RAKE, _player->GetGUID()))
                                {
                                    rakeDuration = rake->GetDuration();
                                    rakeMaxDuration = rake->GetMaxDuration();
                                    rakeAmount = rake->GetEffect(1)->GetAmount();
                                }

                                itr->RemoveAura(SPELL_DRUID_RIP, _player->GetGUID());
                                itr->RemoveAura(SPELL_DRUID_RAKE, _player->GetGUID());

                                _player->AddAura(SPELL_DRUID_RIP, target);
                                _player->AddAura(SPELL_DRUID_RAKE, target);

                                if (AuraPtr rip = target->GetAura(SPELL_DRUID_RIP, _player->GetGUID()))
                                {
                                    rip->SetDuration(ripDuration);
                                    rip->SetMaxDuration(ripMaxDuration);
                                    rip->GetEffect(0)->SetAmount(ripAmount);
                                }
                                if (AuraPtr rake = target->GetAura(SPELL_DRUID_RAKE, _player->GetGUID()))
                                {
                                    rake->SetDuration(rakeDuration);
                                    rake->SetMaxDuration(rakeMaxDuration);
                                    rake->GetEffect(1)->SetAmount(rakeAmount);
                                }

                                break;
                            }
                        }
                    }
                }
            }

            void Register()
            {
                OnHit += SpellHitFn(spell_dru_soul_swap_SpellScript::HandleOnHit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_dru_soul_swap_SpellScript();
        }
};

// Demonic Circle : Teleport - 112970
class spell_dru_demonic_circle_teleport : public SpellScriptLoader
{
    public:
        spell_dru_demonic_circle_teleport() : SpellScriptLoader("spell_dru_demonic_circle_teleport") { }

        class spell_dru_demonic_circle_teleport_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_dru_demonic_circle_teleport_SpellScript);

            void HandleOnHit()
            {
                if (Player* _player = GetCaster()->ToPlayer())
                {
                    std::list<Unit*> groupList;

                    _player->GetPartyMembers(groupList);

                    if (!groupList.empty())
                    {
                        for (auto itr : groupList)
                        {
                            if (itr->HasAura(SPELL_DRUID_SYMBIOSIS_WARLOCK, _player->GetGUID()))
                            {
                                if (GameObject* circle = itr->GetGameObject(WARLOCK_DEMONIC_CIRCLE_SUMMON))
                                {
                                    _player->NearTeleportTo(circle->GetPositionX(), circle->GetPositionY(), circle->GetPositionZ(), circle->GetOrientation());
                                    _player->RemoveMovementImpairingAuras();
                                }
                            }
                        }
                    }
                }
            }

            void Register()
            {
                OnHit += SpellHitFn(spell_dru_demonic_circle_teleport_SpellScript::HandleOnHit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_dru_demonic_circle_teleport_SpellScript();
        }
};

// Shattering Blow - 112997
class spell_dru_shattering_blow : public SpellScriptLoader
{
    public:
        spell_dru_shattering_blow() : SpellScriptLoader("spell_dru_shattering_blow") { }

        class spell_dru_shattering_blow_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_dru_shattering_blow_SpellScript);

            void HandleOnHit()
            {
                if (Player* _player = GetCaster()->ToPlayer())
                {
                    if (Unit* target = GetHitUnit())
                    {
                        if (target->HasAuraWithMechanic(1<<MECHANIC_IMMUNE_SHIELD))
                        {
                            target->RemoveAura(SPELL_DRUID_SHATTERING_BLOW);
                            target->RemoveAurasWithMechanic(1<<MECHANIC_IMMUNE_SHIELD, AURA_REMOVE_BY_ENEMY_SPELL);
                        }

                        _player->CastSpell(_player, SPELL_DRUID_CAT_FORM, true);
                    }
                }
            }

            void Register()
            {
                OnHit += SpellHitFn(spell_dru_shattering_blow_SpellScript::HandleOnHit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_dru_shattering_blow_SpellScript();
        }
};

// Symbiosis Aura - 110478/110479/110482/110483/110484/110485/110486/110488/110490/110491
 class spell_dru_symbiosis_aura : public SpellScriptLoader
{
    public:
        spell_dru_symbiosis_aura() : SpellScriptLoader("spell_dru_symbiosis_aura") { }

        class spell_dru_symbiosis_aura_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_dru_symbiosis_aura_AuraScript);

            void OnUpdate(uint32 diff)
            {
                if (!GetCaster() && GetUnitOwner())
                {
                    if (Player* target = GetUnitOwner()->ToPlayer())
                    {
                        switch (target->getClass())
                        {
                            case CLASS_WARRIOR:
                                target->RemoveAura(SPELL_DRUID_SYMBIOSIS_WARRIOR);
                                break;
                            case CLASS_PALADIN:
                                target->RemoveAura(SPELL_DRUID_SYMBIOSIS_PALADIN);
                                break;
                            case CLASS_HUNTER:
                                target->RemoveAura(SPELL_DRUID_SYMBIOSIS_HUNTER);
                                break;
                            case CLASS_ROGUE:
                                target->RemoveAura(SPELL_DRUID_SYMBIOSIS_ROGUE);
                                break;
                            case CLASS_PRIEST:
                                target->RemoveAura(SPELL_DRUID_SYMBIOSIS_PRIEST);
                                break;
                            case CLASS_DEATH_KNIGHT:
                                target->RemoveAura(SPELL_DRUID_SYMBIOSIS_DEATH_KNIGHT);
                                break;
                            case CLASS_SHAMAN:
                                target->RemoveAura(SPELL_DRUID_SYMBIOSIS_SHAMAN);
                                break;
                            case CLASS_MAGE:
                                target->RemoveAura(SPELL_DRUID_SYMBIOSIS_MAGE);
                                break;
                            case CLASS_WARLOCK:
                                target->RemoveAura(SPELL_DRUID_SYMBIOSIS_WARLOCK);
                                break;
                            case CLASS_MONK:
                                target->RemoveAura(SPELL_DRUID_SYMBIOSIS_MONK);
                                break;
                            default:
                                break;
                        }
                    }
                }
                else if (GetCaster() && !GetUnitOwner())
                {
                    if (Player* caster = GetCaster()->ToPlayer())
                        caster->RemoveAura(SPELL_DRUID_SYMBIOSIS_FOR_CASTER);
                }
                else if (GetCaster() && GetUnitOwner())
                {
                    Player* caster = GetCaster()->ToPlayer();
                    Player* target = GetUnitOwner()->ToPlayer();
                    if (!target || !caster)
                        return;

                    if (!(target->IsInSameGroupWith(caster) && target->IsInSameRaidWith(caster)) ||
                        (target->GetMapId() != caster->GetMapId()))
                    {
                        switch (target->getClass())
                        {
                            case CLASS_WARRIOR:
                                target->RemoveAura(SPELL_DRUID_SYMBIOSIS_WARRIOR);
                                break;
                            case CLASS_PALADIN:
                                target->RemoveAura(SPELL_DRUID_SYMBIOSIS_PALADIN);
                                break;
                            case CLASS_HUNTER:
                                target->RemoveAura(SPELL_DRUID_SYMBIOSIS_HUNTER);
                                break;
                            case CLASS_ROGUE:
                                target->RemoveAura(SPELL_DRUID_SYMBIOSIS_ROGUE);
                                break;
                            case CLASS_PRIEST:
                                target->RemoveAura(SPELL_DRUID_SYMBIOSIS_PRIEST);
                                break;
                            case CLASS_DEATH_KNIGHT:
                                target->RemoveAura(SPELL_DRUID_SYMBIOSIS_DEATH_KNIGHT);
                                break;
                            case CLASS_SHAMAN:
                                target->RemoveAura(SPELL_DRUID_SYMBIOSIS_SHAMAN);
                                break;
                            case CLASS_MAGE:
                                target->RemoveAura(SPELL_DRUID_SYMBIOSIS_MAGE);
                                break;
                            case CLASS_WARLOCK:
                                target->RemoveAura(SPELL_DRUID_SYMBIOSIS_WARLOCK);
                                break;
                            case CLASS_MONK:
                                target->RemoveAura(SPELL_DRUID_SYMBIOSIS_MONK);
                                break;
                            default:
                                break;
                        }

                        caster->RemoveAura(SPELL_DRUID_SYMBIOSIS_FOR_CASTER);
                    }
                }
            }

            void Register()
            {
                OnAuraUpdate += AuraUpdateFn(spell_dru_symbiosis_aura_AuraScript::OnUpdate);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_dru_symbiosis_aura_AuraScript();
        }
};

// Symbiosis - 110309
class spell_dru_symbiosis : public SpellScriptLoader
{
    public:
        spell_dru_symbiosis() : SpellScriptLoader("spell_dru_symbiosis") { }

        class spell_dru_symbiosis_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_dru_symbiosis_SpellScript);

            void HandleScriptEffect(SpellEffIndex effIndex)
            {
                if (Player* _player = GetCaster()->ToPlayer())
                {
                    if (!GetHitUnit())
                        return;

                    if (GetCaster() == GetHitUnit())
                        return;

                    if (Player* target = GetHitUnit()->ToPlayer())
                    {
                        if (AuraPtr symbiosis = _player->GetAura(SPELL_DRUID_SYMBIOSIS_FOR_CASTER))
                        {
                            int32  spellCaster  = 0;
                            uint32 spellTarget  = 0;
                            uint32 specId       = _player->GetSpecializationId(target->GetActiveSpec());
                            int32  bpTarget     = 0;

                            if (target->GetSpecializationId(target->GetActiveSpec()) == SPEC_NONE ||
                                _player->GetSpecializationId(target->GetActiveSpec()) == SPEC_NONE)
                                return;

                            switch (target->getClass())
                            {
                                case CLASS_DEATH_KNIGHT:
                                {
                                    spellTarget = SPELL_DRUID_SYMBIOSIS_DEATH_KNIGHT;

                                    switch (specId)
                                    {
                                        case SPEC_DROOD_BALANCE:
                                            spellCaster = 110570;   // Anti-Magic Shell
                                            break;
                                        case SPEC_DROOD_BEAR:
                                            spellCaster = 122285;   // Bone Shield
                                            break;
                                        case SPEC_DROOD_CAT:
                                            spellCaster = 122282;   // Death Coil
                                            break;
                                        case SPEC_DROOD_RESTORATION:
                                            spellCaster = 110575;   // Icebound Fortitude
                                            break;
                                        default:
                                            break;
                                    }

                                    if (target->GetRoleForGroup(target->GetSpecializationId(target->GetActiveSpec())) == ROLES_TANK)
                                        bpTarget = 113516;      // Wild Mushroom : Plague
                                    else if (target->GetRoleForGroup(target->GetSpecializationId(target->GetActiveSpec())) == ROLES_DPS)
                                        bpTarget = 113072;      // Might of Ursoc

                                    break;
                                }
                                case CLASS_HUNTER:
                                {
                                    bpTarget = 113073;          // Dash
                                    spellTarget = SPELL_DRUID_SYMBIOSIS_HUNTER;

                                    switch (specId)
                                    {
                                        case SPEC_DROOD_BALANCE:
                                            spellCaster = 110588;   // Misdirection
                                            break;
                                        case SPEC_DROOD_BEAR:
                                            spellCaster = 110600;   // Ice Trap
                                            break;
                                        case SPEC_DROOD_CAT:
                                            spellCaster = 110597;   // Play Dead
                                            break;
                                        case SPEC_DROOD_RESTORATION:
                                            spellCaster = 110617;   // Deterrence
                                            break;
                                        default:
                                            break;
                                    }

                                    break;
                                }
                                case CLASS_MAGE:
                                {
                                    bpTarget = 113074;          // Healing Touch
                                    spellTarget = SPELL_DRUID_SYMBIOSIS_MAGE;

                                    switch (specId)
                                    {
                                        case SPEC_DROOD_BALANCE:
                                            spellCaster = 110621;   // Mirror Image
                                            break;
                                        case SPEC_DROOD_BEAR:
                                            spellCaster = 110694;   // Frost Armor
                                            break;
                                        case SPEC_DROOD_CAT:
                                            spellCaster = 110693;   // Frost Nova
                                            break;
                                        case SPEC_DROOD_RESTORATION:
                                            spellCaster = 110696;   // Ice Block
                                            break;
                                        default:
                                            break;
                                    }

                                    break;
                                }
                                case CLASS_MONK:
                                {
                                    spellTarget = SPELL_DRUID_SYMBIOSIS_MONK;

                                    switch (specId)
                                    {
                                        case SPEC_DROOD_BALANCE:
                                            spellCaster = 126458;   // Grapple Weapon
                                            break;
                                        case SPEC_DROOD_BEAR:
                                            spellCaster = 126453;   // Elusive Brew
                                            break;
                                        case SPEC_DROOD_CAT:
                                            spellCaster = 126449;   // Clash
                                            break;
                                        case SPEC_DROOD_RESTORATION:
                                            spellCaster = 126456;   // Fortifying Brew
                                            break;
                                        default:
                                            break;
                                    }

                                    if (target->GetRoleForGroup(target->GetSpecializationId(target->GetActiveSpec())) == ROLES_TANK)
                                        bpTarget = 113306;      // Survival Instincts
                                    else if (target->GetRoleForGroup(target->GetSpecializationId(target->GetActiveSpec())) == ROLES_DPS)
                                        bpTarget = 127361;      // Bear Hug
                                    else if (target->GetRoleForGroup(target->GetSpecializationId(target->GetActiveSpec())) == ROLES_HEALER)
                                        bpTarget = 113275;      // Entangling Roots

                                    break;
                                }
                                case CLASS_PALADIN:
                                {
                                    spellTarget = SPELL_DRUID_SYMBIOSIS_PALADIN;

                                    switch (specId)
                                    {
                                        case SPEC_DROOD_BALANCE:
                                            spellCaster = 110698;   // Hammer of Justice
                                            break;
                                        case SPEC_DROOD_BEAR:
                                            spellCaster = 110701;   // Consecration
                                            break;
                                        case SPEC_DROOD_CAT:
                                            spellCaster = 110700;   // Divine Shield
                                            break;
                                        case SPEC_DROOD_RESTORATION:
                                            spellCaster = 122288;   // Cleanse
                                            break;
                                        default:
                                            break;
                                    }

                                    if (target->GetRoleForGroup(target->GetSpecializationId(target->GetActiveSpec())) == ROLES_TANK)
                                        bpTarget = 113075;      // Barkskin
                                    else if (target->GetRoleForGroup(target->GetSpecializationId(target->GetActiveSpec())) == ROLES_DPS)
                                        bpTarget = 122287;      // Wrath
                                    else if (target->GetRoleForGroup(target->GetSpecializationId(target->GetActiveSpec())) == ROLES_HEALER)
                                        bpTarget = 113269;      // Rebirth

                                    break;
                                }
                                case CLASS_PRIEST:
                                {
                                    spellTarget = SPELL_DRUID_SYMBIOSIS_PRIEST;

                                    switch (specId)
                                    {
                                        case SPEC_DROOD_BALANCE:
                                            spellCaster = 110707;   // Mass Dispel
                                            break;
                                        case SPEC_DROOD_BEAR:
                                            spellCaster = 110717;   // Fear Ward
                                            break;
                                        case SPEC_DROOD_CAT:
                                            spellCaster = 110715;   // Dispersion
                                            break;
                                        case SPEC_DROOD_RESTORATION:
                                            spellCaster = 110718;   // Leap of Faith
                                            break;
                                        default:
                                            break;
                                    }

                                    if (target->GetRoleForGroup(target->GetSpecializationId(target->GetActiveSpec())) == ROLES_DPS)
                                        bpTarget = 113277;      // Tranquility
                                    else if (target->GetRoleForGroup(target->GetSpecializationId(target->GetActiveSpec())) == ROLES_HEALER)
                                        bpTarget = 113506;      // Cyclone

                                    break;
                                }
                                case CLASS_ROGUE:
                                {
                                    bpTarget = 113613;          // Growl
                                    spellTarget = SPELL_DRUID_SYMBIOSIS_ROGUE;

                                    switch (specId)
                                    {
                                        case SPEC_DROOD_BALANCE:
                                            spellCaster = 110788;   // Cloak of Shadows
                                            break;
                                        case SPEC_DROOD_BEAR:
                                            spellCaster = 122289;   // Feint
                                            break;
                                        case SPEC_DROOD_CAT:
                                            spellCaster = 110730;   // Redirect
                                            break;
                                        case SPEC_DROOD_RESTORATION:
                                            spellCaster = 110791;   // Evasion
                                            break;
                                        default:
                                            break;
                                    }

                                    break;
                                }
                                case CLASS_SHAMAN:
                                {
                                    spellTarget = SPELL_DRUID_SYMBIOSIS_SHAMAN;

                                    switch (specId)
                                    {
                                        case SPEC_DROOD_BALANCE:
                                            spellCaster = 110802;   // Purge
                                            break;
                                        case SPEC_DROOD_BEAR:
                                            spellCaster = 110803;   // Lightning Shield
                                            break;
                                        case SPEC_DROOD_CAT:
                                            spellCaster = 110807;   // Feral Spirit
                                            break;
                                        case SPEC_DROOD_RESTORATION:
                                            spellCaster = 110806;   // Spiritwalker's Grace
                                            break;
                                        default:
                                            break;
                                    }

                                    if (target->GetRoleForGroup(target->GetSpecializationId(target->GetActiveSpec())) == ROLES_HEALER)
                                        bpTarget = 113289;      // Prowl
                                    else if (target->GetRoleForGroup(target->GetSpecializationId(target->GetActiveSpec())) == ROLES_DPS)
                                        bpTarget = 113286;      // Solar Beam

                                    break;
                                }
                                case CLASS_WARLOCK:
                                {
                                    bpTarget = 113295;      // Rejuvenation
                                    spellTarget = SPELL_DRUID_SYMBIOSIS_WARLOCK;

                                    switch (specId)
                                    {
                                        case SPEC_DROOD_BALANCE:
                                            spellCaster = 122291;   // Unending Resolve
                                            break;
                                        case SPEC_DROOD_BEAR:
                                            spellCaster = 122290;   // Life Tap
                                            break;
                                        case SPEC_DROOD_CAT:
                                            spellCaster = 110810;   // Soul Swap
                                            break;
                                        case SPEC_DROOD_RESTORATION:
                                            spellCaster = 112970;   // Demonic Circle : Teleport
                                            break;
                                        default:
                                            break;
                                    }

                                    break;
                                }
                                case CLASS_WARRIOR:
                                {
                                    spellTarget = SPELL_DRUID_SYMBIOSIS_WARRIOR;

                                    switch (specId)
                                    {
                                        case SPEC_DROOD_BALANCE:
                                            spellCaster = 122292;   // Intervene
                                            break;
                                        case SPEC_DROOD_BEAR:
                                            spellCaster = 113002;   // Spell Reflection
                                            break;
                                        case SPEC_DROOD_CAT:
                                            spellCaster = 112997;   // Shattering Blow
                                            break;
                                        case SPEC_DROOD_RESTORATION:
                                            spellCaster = 113004;   // Intimidating Roar
                                            break;
                                        default:
                                            break;
                                    }

                                    if (target->GetRoleForGroup(target->GetSpecializationId(target->GetActiveSpec())) == ROLES_TANK)
                                        bpTarget = 122286;      // Savage Defense
                                    else if (target->GetRoleForGroup(target->GetSpecializationId(target->GetActiveSpec())) == ROLES_DPS)
                                        bpTarget = 122294;      // Stampeding Shout

                                    break;
                                }
                                default:
                                    break;
                            }

                            if (spellCaster)
                                _player->CastCustomSpell(_player, SPELL_DRUID_SYMBIOSIS_FOR_CASTER, &spellCaster, NULL, NULL, true);

                            if (bpTarget && spellTarget)
                                _player->CastCustomSpell(target, spellTarget, &bpTarget, NULL, NULL, true);
                        }
                    }
                }
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_dru_symbiosis_SpellScript::HandleScriptEffect, EFFECT_1, SPELL_EFFECT_SCRIPT_EFFECT);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_dru_symbiosis_SpellScript();
        }
};

// Moonfire - 8921
class spell_dru_moonfire : public SpellScriptLoader
{
    public:
        spell_dru_moonfire() : SpellScriptLoader("spell_dru_moonfire") { }

        class spell_dru_moonfire_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_dru_moonfire_SpellScript);

            void HandleOnHit()
            {
                if (Player* _player = GetCaster()->ToPlayer())
                    if (Unit* target = GetHitUnit())
                        if (_player->HasAura(SPELL_DRUID_CELESTIAL_ALIGNMENT))
                            _player->CastSpell(target, SPELL_DRUID_SUNFIRE, true);
            }

            void Register()
            {
                OnHit += SpellHitFn(spell_dru_moonfire_SpellScript::HandleOnHit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_dru_moonfire_SpellScript();
        }
};

// Nature's Vigil - 124974
class spell_dru_natures_vigil : public SpellScriptLoader
{
    public:
        spell_dru_natures_vigil() : SpellScriptLoader("spell_dru_natures_vigil") { }

        class spell_dru_natures_vigil_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_dru_natures_vigil_AuraScript);

            void OnProc(constAuraEffectPtr aurEff, ProcEventInfo& eventInfo)
            {
                PreventDefaultAction();

                if (!GetCaster())
                    return;

                Player* _player = GetCaster()->ToPlayer();
                if (!_player)
                    return;

                if (eventInfo.GetActor()->GetGUID() != _player->GetGUID())
                    return;

                if (!eventInfo.GetDamageInfo()->GetSpellInfo())
                    return;

                bool singleTarget = false;
                for (uint8 i = 0; i < MAX_SPELL_EFFECTS; ++i)
                    if ((eventInfo.GetDamageInfo()->GetSpellInfo()->Effects[i].TargetA.GetTarget() == TARGET_UNIT_TARGET_ALLY ||
                        eventInfo.GetDamageInfo()->GetSpellInfo()->Effects[i].TargetA.GetTarget() == TARGET_UNIT_TARGET_ENEMY) &&
                        eventInfo.GetDamageInfo()->GetSpellInfo()->Effects[i].TargetB.GetTarget() == 0)
                        singleTarget = true;

                if (!singleTarget)
                    return;

                if (eventInfo.GetDamageInfo()->GetSpellInfo()->Id == SPELL_DRUID_NATURES_VIGIL_HEAL ||
                    eventInfo.GetDamageInfo()->GetSpellInfo()->Id == SPELL_DRUID_NATURES_VIGIL_DAMAGE)
                    return;

                if (!(eventInfo.GetDamageInfo()->GetDamage()) && !(eventInfo.GetHealInfo()->GetHeal()))
                    return;

                if (!(eventInfo.GetDamageInfo()->GetDamageType() == SPELL_DIRECT_DAMAGE) && !(eventInfo.GetDamageInfo()->GetDamageType() == HEAL))
                    return;

                int32 bp = 0;
                Unit* target = NULL;
                uint32 spellId = 0;

                if (!eventInfo.GetDamageInfo()->GetSpellInfo()->IsPositive())
                {
                    bp = eventInfo.GetDamageInfo()->GetDamage() / 4;
                    spellId = SPELL_DRUID_NATURES_VIGIL_HEAL;
                    target = _player->SelectNearbyAlly(_player, 25.0f);
                }
                else
                {
                    bp = eventInfo.GetHealInfo()->GetHeal() / 4;
                    spellId = SPELL_DRUID_NATURES_VIGIL_DAMAGE;
                    target = _player->SelectNearbyTarget(_player, 25.0f);
                }

                if (!target || !spellId || !bp)
                    return;

                _player->CastCustomSpell(target, spellId, &bp, NULL, NULL, true);
            }

            void Register()
            {
                OnEffectProc += AuraEffectProcFn(spell_dru_natures_vigil_AuraScript::OnProc, EFFECT_2, SPELL_AURA_DUMMY);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_dru_natures_vigil_AuraScript();
        }
};

// Cenarion Ward - 102351
class spell_dru_cenarion_ward : public SpellScriptLoader
{
    public:
        spell_dru_cenarion_ward() : SpellScriptLoader("spell_dru_cenarion_ward") { }

        class spell_dru_cenarion_ward_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_dru_cenarion_ward_AuraScript);

            void OnRemove(constAuraEffectPtr aurEff, AuraEffectHandleModes mode)
            {
                if (Unit* caster = GetCaster())
                {
                    if (Unit* target = GetTarget())
                    {
                        AuraRemoveMode removeMode = GetTargetApplication()->GetRemoveMode();
                        if (removeMode == AURA_REMOVE_BY_DEFAULT)
                            caster->CastSpell(target, SPELL_DRUID_CENARION_WARD, true);
                    }
                }
            }

            void Register()
            {
                AfterEffectRemove += AuraEffectRemoveFn(spell_dru_cenarion_ward_AuraScript::OnRemove, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_dru_cenarion_ward_AuraScript();
        }
};

// Ursol's Vortex (snare) - 127797
class spell_dru_ursols_vortex_snare : public SpellScriptLoader
{
    public:
        spell_dru_ursols_vortex_snare() : SpellScriptLoader("spell_dru_ursols_vortex_snare") { }

        class spell_dru_ursols_vortex_snare_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_dru_ursols_vortex_snare_AuraScript);

            std::list<Unit*> targetList;

            void OnUpdate(uint32 diff, AuraEffectPtr aurEff)
            {
                aurEff->GetTargetList(targetList);

                for (auto itr : targetList)
                {
                    if (Unit* caster = GetCaster())
                        if (AreaTrigger* areaTrigger = caster->GetAreaTrigger(SPELL_DRUID_URSOLS_VORTEX_AREA_TRIGGER))
                            if (itr->GetDistance(areaTrigger) > 8.0f && !itr->HasAura(SPELL_DRUID_URSOLS_VORTEX_JUMP_DEST))
                                itr->CastSpell(areaTrigger->GetPositionX(), areaTrigger->GetPositionY(), areaTrigger->GetPositionZ(), SPELL_DRUID_URSOLS_VORTEX_JUMP_DEST, true);
                }

                targetList.clear();
            }

            void Register()
            {
                OnEffectUpdate += AuraEffectUpdateFn(spell_dru_ursols_vortex_snare_AuraScript::OnUpdate, EFFECT_0, SPELL_AURA_MOD_DECREASE_SPEED);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_dru_ursols_vortex_snare_AuraScript();
        }
};

// Ursol's Vortex - 102793
class spell_dru_ursols_vortex : public SpellScriptLoader
{
    public:
        spell_dru_ursols_vortex() : SpellScriptLoader("spell_dru_ursols_vortex") { }

        class spell_dru_ursols_vortex_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_dru_ursols_vortex_SpellScript);

            void HandleOnHit()
            {
                if (Player* _player = GetCaster()->ToPlayer())
                    if (Unit* target = GetHitUnit())
                        if (!target->HasAura(SPELL_DRUID_URSOLS_VORTEX_AREA_TRIGGER))
                            _player->CastSpell(target, SPELL_DRUID_URSOLS_VORTEX_SNARE, true);
            }

            void Register()
            {
                OnHit += SpellHitFn(spell_dru_ursols_vortex_SpellScript::HandleOnHit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_dru_ursols_vortex_SpellScript();
        }

        class spell_dru_ursols_vortex_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_dru_ursols_vortex_AuraScript);

            std::list<Unit*> targetList;

            void OnUpdate(uint32 diff, AuraEffectPtr aurEff)
            {
                aurEff->GetTargetList(targetList);

                for (auto itr : targetList)
                {
                    if (Unit* caster = GetCaster())
                        if (DynamicObject* dynObj = caster->GetDynObject(SPELL_DRUID_URSOLS_VORTEX_AREA_TRIGGER))
                            if (itr->GetDistance(dynObj) > 8.0f && !itr->HasAura(SPELL_DRUID_URSOLS_VORTEX_JUMP_DEST))
                                itr->CastSpell(dynObj->GetPositionX(), dynObj->GetPositionY(), dynObj->GetPositionZ(), SPELL_DRUID_URSOLS_VORTEX_JUMP_DEST, true);
                }

                targetList.clear();
            }

            void Register()
            {
                OnEffectUpdate += AuraEffectUpdateFn(spell_dru_ursols_vortex_AuraScript::OnUpdate, EFFECT_0, SPELL_AURA_MOD_DECREASE_SPEED);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_dru_ursols_vortex_AuraScript();
        }
};

// Solar beam - 78675
class spell_dru_solar_beam : public SpellScriptLoader
{
    public:
        spell_dru_solar_beam() : SpellScriptLoader("spell_dru_solar_beam") { }

        class spell_dru_solar_beam_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_dru_solar_beam_AuraScript);

            void OnTick(constAuraEffectPtr aurEff)
            {
                if (DynamicObject* dynObj = GetCaster()->GetDynObject(SPELL_DRUID_SOLAR_BEAM))
                    GetCaster()->CastSpell(dynObj->GetPositionX(), dynObj->GetPositionY(), dynObj->GetPositionZ(), SPELL_DRUID_SOLAR_BEAM_SILENCE, true);
            }

            void Register()
            {
                OnEffectPeriodic += AuraEffectPeriodicFn(spell_dru_solar_beam_AuraScript::OnTick, EFFECT_2, SPELL_AURA_PERIODIC_DUMMY);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_dru_solar_beam_AuraScript();
        }
};

// Dash - 1850
class spell_dru_dash : public SpellScriptLoader
{
    public:
        spell_dru_dash() : SpellScriptLoader("spell_dru_dash") { }

        class spell_dru_dash_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_dru_dash_SpellScript);

            void HandleOnHit()
            {
                if (Player* _player = GetCaster()->ToPlayer())
                {
                    if (_player->HasAura(SPELL_DRUID_STAMPEDING_ROAR))
                        _player->RemoveAura(SPELL_DRUID_STAMPEDING_ROAR);

                    _player->RemoveMovementImpairingAuras();
                }
            }

            void Register()
            {
                OnHit += SpellHitFn(spell_dru_dash_SpellScript::HandleOnHit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_dru_dash_SpellScript();
        }
};

// Called by Mangle (bear) - 33878, Mangle (cat) - 33876, Ravage - 6785 and Shred - 5221
// Rip - 1079
class spell_dru_rip_duration : public SpellScriptLoader
{
    public:
        spell_dru_rip_duration() : SpellScriptLoader("spell_dru_rip_duration") { }

        class spell_dru_rip_duration_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_dru_rip_duration_SpellScript);

            void HandleOnHit()
            {
                if (Player* _player = GetCaster()->ToPlayer())
                {
                    if (Unit* target = GetHitUnit())
                    {
                        // Each time you Shred, Ravage, or Mangle the target while in Cat Form ...
                        if (_player->GetShapeshiftForm() == FORM_CAT)
                        {
                            if (AuraPtr rip = target->GetAura(SPELL_DRUID_RIP, _player->GetGUID()))
                            {
                                int32 duration = rip->GetDuration();
                                int32 maxDuration = rip->GetMaxDuration();

                                int32 countMin = maxDuration;
                                int32 countMax = sSpellMgr->GetSpellInfo(SPELL_DRUID_RIP)->GetMaxDuration() + 6000;

                                // ... the duration of your Rip on that target is extended by 2 sec, up to a maximum of 6 sec.
                                if ((countMin + 2000) < countMax)
                                {
                                    rip->SetDuration(duration + 2000);
                                    rip->SetMaxDuration(countMin + 2000);
                                }
                                else if (countMin < countMax)
                                {
                                    rip->SetDuration(duration + 2000);
                                    rip->SetMaxDuration(countMax);
                                }
                            }
                        }
                    }
                }
            }

            void Register()
            {
                OnHit += SpellHitFn(spell_dru_rip_duration_SpellScript::HandleOnHit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_dru_rip_duration_SpellScript();
        }
};

// Savage Defense - 62606
class spell_dru_savage_defense : public SpellScriptLoader
{
    public:
        spell_dru_savage_defense() : SpellScriptLoader("spell_dru_savage_defense") { }

        class spell_dru_savage_defense_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_dru_savage_defense_SpellScript);

            void HandleOnHit()
            {
                if (Player* _player = GetCaster()->ToPlayer())
                    _player->CastSpell(_player, SPELL_DRUID_SAVAGE_DEFENSE_DODGE_PCT, true);
            }

            void Register()
            {
                OnHit += SpellHitFn(spell_dru_savage_defense_SpellScript::HandleOnHit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_dru_savage_defense_SpellScript();
        }
};

// Bear Form - 5487
class spell_dru_bear_form : public SpellScriptLoader
{
    public:
        spell_dru_bear_form() : SpellScriptLoader("spell_dru_bear_form") { }

        class spell_dru_bear_form_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_dru_bear_form_SpellScript);

            void HandleOnHit()
            {
                if (Player* _player = GetCaster()->ToPlayer())
                    _player->CastSpell(_player, SPELL_DRUID_BEAR_FORM_RAGE_GAIN, true);
            }

            void Register()
            {
                OnHit += SpellHitFn(spell_dru_bear_form_SpellScript::HandleOnHit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_dru_bear_form_SpellScript();
        }
};

// Ferocious Bite - 22568
class spell_dru_ferocious_bite : public SpellScriptLoader
{
    public:
        spell_dru_ferocious_bite() : SpellScriptLoader("spell_dru_ferocious_bite") { }

        class spell_dru_ferocious_bite_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_dru_ferocious_bite_SpellScript);

            void HandleOnHit()
            {
                if (Player* _player = GetCaster()->ToPlayer())
                    if (Unit* target = GetHitUnit())
                        if (target->GetHealthPct() < 25.0f)
                            if (AuraPtr rip = target->GetAura(SPELL_DRUID_RIP, _player->GetGUID()))
                                rip->RefreshDuration();
            }

            void Register()
            {
                OnHit += SpellHitFn(spell_dru_ferocious_bite_SpellScript::HandleOnHit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_dru_ferocious_bite_SpellScript();
        }
};

// Bear Hug - 102795
class spell_dru_bear_hug : public SpellScriptLoader
{
    public:
        spell_dru_bear_hug() : SpellScriptLoader("spell_dru_bear_hug") { }

        class spell_dru_bear_hug_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_dru_bear_hug_AuraScript);

            void CalculateAmount(constAuraEffectPtr /*aurEff*/, int32& amount, bool& /*canBeRecalculated*/)
            {
                if (Unit* caster = GetCaster())
                {
                    if (caster->GetShapeshiftForm() != FORM_BEAR)
                        caster->CastSpell(caster, SPELL_DRUID_BEAR_FORM, true);

                    amount = caster->CountPctFromMaxHealth(amount);
                }
            }

            void Register()
            {
                DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_dru_bear_hug_AuraScript::CalculateAmount, EFFECT_1, SPELL_AURA_PERIODIC_DAMAGE);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_dru_bear_hug_AuraScript();
        }
};

// Ravage - 6785
class spell_dru_ravage : public SpellScriptLoader
{
    public:
        spell_dru_ravage() : SpellScriptLoader("spell_dru_ravage") { }

        class spell_dru_ravage_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_dru_ravage_SpellScript);

            void HandleOnHit()
            {
                if (Player* _player = GetCaster()->ToPlayer())
                    if (Unit* target = GetHitUnit())
                        _player->CastSpell(target, SPELL_DRUID_INFECTED_WOUNDS, true);
            }

            void Register()
            {
                OnHit += SpellHitFn(spell_dru_ravage_SpellScript::HandleOnHit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_dru_ravage_SpellScript();
        }
};

// Lifebloom - 33763 : Final heal
class spell_dru_lifebloom : public SpellScriptLoader
{
    public:
        spell_dru_lifebloom() : SpellScriptLoader("spell_dru_lifebloom") { }

        class spell_dru_lifebloom_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_dru_lifebloom_AuraScript);

            void AfterRemove(constAuraEffectPtr aurEff, AuraEffectHandleModes /*mode*/)
            {
                // Final heal only on duration end
                if (GetTargetApplication()->GetRemoveMode() != AURA_REMOVE_BY_EXPIRE)
                    return;

                if (!GetCaster())
                    return;

                if (GetCaster()->ToPlayer()->HasSpellCooldown(SPELL_DRUID_LIFEBLOOM_FINAL_HEAL))
                    return;

                // final heal
                int32 stack = GetStackAmount();
                int32 healAmount = aurEff->GetAmount();

                if (Player* _plr = GetCaster()->ToPlayer())
                {
                    healAmount = _plr->SpellHealingBonusDone(GetTarget(), GetSpellInfo(), healAmount, HEAL, stack);
                    healAmount = GetTarget()->SpellHealingBonusTaken(_plr, GetSpellInfo(), healAmount, HEAL, stack);

                    // Increase final heal by 50%
                    if (_plr->HasAura(SPELL_DRUID_GLYPH_OF_BLOOMING))
                        AddPct(healAmount, 50);

                    GetTarget()->CastCustomSpell(GetTarget(), SPELL_DRUID_LIFEBLOOM_FINAL_HEAL, &healAmount, NULL, NULL, true, NULL, aurEff, GetCasterGUID());

                    _plr->AddSpellCooldown(SPELL_DRUID_LIFEBLOOM_FINAL_HEAL, 0, time(NULL) + 1);

                    return;
                }

                // Increase final heal by 50%
                if (GetCaster()->HasAura(SPELL_DRUID_GLYPH_OF_BLOOMING))
                    AddPct(healAmount, 50);

                GetTarget()->CastCustomSpell(GetTarget(), SPELL_DRUID_LIFEBLOOM_FINAL_HEAL, &healAmount, NULL, NULL, true, NULL, aurEff, GetCasterGUID());
                GetCaster()->ToPlayer()->AddSpellCooldown(SPELL_DRUID_LIFEBLOOM_FINAL_HEAL, 0, time(NULL) + 1);
            }

            void HandleDispel(DispelInfo* dispelInfo)
            {
                if (Unit* target = GetUnitOwner())
                {
                    if (constAuraEffectPtr aurEff = GetEffect(EFFECT_1))
                    {
                        // final heal
                        int32 healAmount = aurEff->GetAmount();

                        if (Unit* caster = GetCaster())
                        {
                            healAmount = caster->SpellHealingBonusDone(target, GetSpellInfo(), healAmount, HEAL, dispelInfo->GetRemovedCharges());
                            healAmount = target->SpellHealingBonusTaken(caster, GetSpellInfo(), healAmount, HEAL, dispelInfo->GetRemovedCharges());

                            target->CastCustomSpell(target, SPELL_DRUID_LIFEBLOOM_FINAL_HEAL, &healAmount, NULL, NULL, true, NULL, NULLAURA_EFFECT, GetCasterGUID());

                            return;
                        }
                        target->CastCustomSpell(target, SPELL_DRUID_LIFEBLOOM_FINAL_HEAL, &healAmount, NULL, NULL, true, NULL, NULLAURA_EFFECT, GetCasterGUID());
                    }
                }
            }

            void Register()
            {
                AfterEffectRemove += AuraEffectRemoveFn(spell_dru_lifebloom_AuraScript::AfterRemove, EFFECT_1, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
                AfterDispel += AuraDispelFn(spell_dru_lifebloom_AuraScript::HandleDispel);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_dru_lifebloom_AuraScript();
        }
};

// Called by Cat Form - 768 and Bear Form - 5487
// Killer Instinct - 108299
class spell_dru_killer_instinct : public SpellScriptLoader
{
    public:
        spell_dru_killer_instinct() : SpellScriptLoader("spell_dru_killer_instinct") { }

        class spell_dru_killer_instinct_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_dru_killer_instinct_SpellScript);

            void HandleOnHit()
            {
                if (Player* _player = GetCaster()->ToPlayer())
                {
                    if (_player->HasAura(SPELL_DRUID_KILLER_INSTINCT))
                    {
                        int32 bp = _player->GetStat(STAT_INTELLECT);

                        _player->CastCustomSpell(_player, SPELL_DRUID_KILLER_INSTINCT_MOD_STAT, &bp, NULL, NULL, true);
                    }
                }
            }

            void Register()
            {
                OnHit += SpellHitFn(spell_dru_killer_instinct_SpellScript::HandleOnHit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_dru_killer_instinct_SpellScript();
        }
};

// Called by Regrowth - 8936, Nourish - 50464 and Healing Touch - 5185
// Lifebloom - 33763 : Refresh duration
class spell_dru_lifebloom_refresh : public SpellScriptLoader
{
    public:
        spell_dru_lifebloom_refresh() : SpellScriptLoader("spell_dru_lifebloom_refresh") { }

        class spell_dru_lifebloom_refresh_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_dru_lifebloom_refresh_SpellScript);

            void HandleOnHit()
            {
                if (Player* _player = GetCaster()->ToPlayer())
                    if (Unit* target = GetHitUnit())
                        if (!target->HasAura(SPELL_DRUID_GLYPH_OF_BLOOMING))
                            if (AuraPtr lifebloom = target->GetAura(SPELL_DRUID_LIFEBLOOM, _player->GetGUID()))
                                lifebloom->RefreshDuration();
            }

            void Register()
            {
                OnHit += SpellHitFn(spell_dru_lifebloom_refresh_SpellScript::HandleOnHit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_dru_lifebloom_refresh_SpellScript();
        }
};

// Called by Lifebloom - 33763
// Omen of Clarity - 113043
class spell_dru_omen_of_clarity : public SpellScriptLoader
{
    public:
        spell_dru_omen_of_clarity() : SpellScriptLoader("spell_dru_omen_of_clarity") { }

        class spell_dru_omen_of_clarity_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_dru_omen_of_clarity_AuraScript);

            void HandleEffectPeriodic(constAuraEffectPtr /*aurEff*/)
            {
                if (Unit* caster = GetCaster())
                    if (caster->HasAura(SPELL_DRUID_OMEN_OF_CLARITY))
                        if (roll_chance_i(4))
                            caster->CastSpell(caster, SPELL_DRUID_CLEARCASTING, true);
            }

            void Register()
            {
                OnEffectPeriodic += AuraEffectPeriodicFn(spell_dru_omen_of_clarity_AuraScript::HandleEffectPeriodic, EFFECT_0, SPELL_AURA_PERIODIC_HEAL);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_dru_omen_of_clarity_AuraScript();
        }
};

// Mark of the Wild - 1126
class spell_dru_mark_of_the_wild : public SpellScriptLoader
{
    public:
        spell_dru_mark_of_the_wild() : SpellScriptLoader("spell_dru_mark_of_the_wild") { }

        class spell_dru_mark_of_the_wild_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_dru_mark_of_the_wild_SpellScript);

            void HandleOnHit()
            {
                Unit* caster = GetCaster();
                if (caster && caster->GetTypeId() == TYPEID_PLAYER)
                {
                    caster->AddAura(SPELL_DRUID_MARK_OF_THE_WILD, caster);

                    std::list<Unit*> memberList;
                    Player* plr = caster->ToPlayer();
                    plr->GetPartyMembers(memberList);

                    for (auto itr : memberList)
                        caster->AddAura(SPELL_DRUID_MARK_OF_THE_WILD, (itr));
                }
            }

            void Register()
            {
                OnHit += SpellHitFn(spell_dru_mark_of_the_wild_SpellScript::HandleOnHit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_dru_mark_of_the_wild_SpellScript();
        }
};

// Nature's Cure - 88423 and Remove Corruption - 2782
class spell_dru_natures_cure : public SpellScriptLoader
{
    public:
        spell_dru_natures_cure() : SpellScriptLoader("spell_dru_natures_cure") { }

        class spell_dru_natures_cure_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_dru_natures_cure_SpellScript);

            SpellCastResult CheckCleansing()
            {
                if (Unit* caster = GetCaster())
                {
                    if (Unit* target = GetExplTargetUnit())
                    {
                        // Create dispel mask by dispel type
                        for (int8 i = 0; i < MAX_SPELL_EFFECTS; i++)
                        {
                            uint32 dispel_type = GetSpellInfo()->Effects[i].MiscValue;
                            uint32 dispelMask  = GetSpellInfo()->GetDispelMask(DispelType(dispel_type));

                            // Nature's Cure can dispell all Magic, Curse and poison
                            if (GetSpellInfo()->Id == 88423)
                                dispelMask = ((1<<DISPEL_MAGIC) | (1<<DISPEL_CURSE) | (1<<DISPEL_POISON));

                            DispelChargesList dispelList;
                            target->GetDispellableAuraList(caster, dispelMask, dispelList);

                            if (dispelList.empty())
                                return SPELL_FAILED_NOTHING_TO_DISPEL;

                            return SPELL_CAST_OK;
                        }
                    }
                }

                return SPELL_CAST_OK;
            }

            void Register()
            {
                OnCheckCast += SpellCheckCastFn(spell_dru_natures_cure_SpellScript::CheckCleansing);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_dru_natures_cure_SpellScript();
        }
};

// Called by Regrowth - 8936
// Glyph of Regrowth - 116218
class spell_dru_glyph_of_regrowth : public SpellScriptLoader
{
    public:
        spell_dru_glyph_of_regrowth() : SpellScriptLoader("spell_dru_glyph_of_regrowth") { }

        class spell_dru_glyph_of_regrowth_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_dru_glyph_of_regrowth_AuraScript);

            void HandleApply(constAuraEffectPtr /*aurEff*/, AuraEffectHandleModes mode)
            {
                // Increases the critical strike chance of your Regrowth by 40%, but removes the periodic component of the spell.
                if (GetCaster())
                    if (GetCaster()->HasAura(SPELL_DRUID_GLYPH_OF_REGROWTH))
                        GetTarget()->RemoveAura(SPELL_DRUID_REGROWTH, GetCaster()->GetGUID());
            }

            void HandleEffectPeriodic(constAuraEffectPtr /*aurEff*/)
            {
                // Duration automatically refreshes to 6 sec each time Regrowth heals targets at or below 50% health
                if (Unit* caster = GetCaster())
                    if (Unit* target = GetTarget())
                        if (target->GetHealthPct() < 50)
                            if (AuraPtr regrowth = target->GetAura(SPELL_DRUID_REGROWTH, caster->GetGUID()))
                                regrowth->RefreshDuration();
            }

            void Register()
            {
                OnEffectApply += AuraEffectApplyFn(spell_dru_glyph_of_regrowth_AuraScript::HandleApply, EFFECT_1, SPELL_AURA_PERIODIC_HEAL, AURA_EFFECT_HANDLE_REAL);
                OnEffectPeriodic += AuraEffectPeriodicFn(spell_dru_glyph_of_regrowth_AuraScript::HandleEffectPeriodic, EFFECT_1, SPELL_AURA_PERIODIC_HEAL);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_dru_glyph_of_regrowth_AuraScript();
        }
};

// Cat Form - 768
class spell_dru_cat_form : public SpellScriptLoader
{
    public:
        spell_dru_cat_form() : SpellScriptLoader("spell_dru_cat_form") { }

        class spell_dru_cat_form_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_dru_cat_form_SpellScript);

            void HandleOnHit()
            {
                if (Player* _player = GetCaster()->ToPlayer())
                {
                    if (!_player->HasAura(SPELL_DRUID_FORM_CAT_INCREASE_SPEED))
                    {
                        _player->CastSpell(_player, SPELL_DRUID_FORM_CAT_INCREASE_SPEED, true);
                        _player->RemoveMovementImpairingAuras();
                    }
                }
            }

            void Register()
            {
                OnHit += SpellHitFn(spell_dru_cat_form_SpellScript::HandleOnHit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_dru_cat_form_SpellScript();
        }

        class spell_dru_cat_form_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_dru_cat_form_AuraScript);

            void OnApply(constAuraEffectPtr aurEff, AuraEffectHandleModes /*mode*/)
            {
                if (Unit* caster = GetCaster())
                    if (AuraPtr dash = caster->GetAura(SPELL_DRUID_DASH))
                        if (dash->GetEffect(0))
                            if (dash->GetEffect(0)->GetAmount() == 0)
                                dash->GetEffect(0)->SetAmount(70);
            }

            void OnRemove(constAuraEffectPtr aurEff, AuraEffectHandleModes /*mode*/)
            {
                if (Unit* caster = GetCaster())
                {
                    if (AuraPtr dash = caster->GetAura(SPELL_DRUID_DASH))
                        dash->GetEffect(0)->SetAmount(0);

                    if (caster->HasAura(SPELL_DRUID_PROWL))
                        caster->RemoveAura(SPELL_DRUID_PROWL);
                }
            }

            void Register()
            {
                OnEffectApply += AuraEffectApplyFn(spell_dru_cat_form_AuraScript::OnApply, EFFECT_0, SPELL_AURA_MOD_SHAPESHIFT, AURA_EFFECT_HANDLE_REAL);
                OnEffectRemove += AuraEffectRemoveFn(spell_dru_cat_form_AuraScript::OnRemove, EFFECT_0, SPELL_AURA_MOD_SHAPESHIFT, AURA_EFFECT_HANDLE_REAL);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_dru_cat_form_AuraScript();
        }
};

// Skull Bash (cat) - 80965 and Skull Bash (bear) - 80964
class spell_dru_skull_bash : public SpellScriptLoader
{
    public:
        spell_dru_skull_bash() : SpellScriptLoader("spell_dru_skull_bash") { }

        class spell_dru_skull_bash_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_dru_skull_bash_SpellScript);

            void HandleOnHit()
            {
                if (Player* _player = GetCaster()->ToPlayer())
                {
                    if (Unit* target = GetHitUnit())
                    {
                        _player->CastSpell(target, SPELL_DRUID_SKULL_BASH_MANA_COST, true);
                        _player->CastSpell(target, SPELL_DRUID_SKULL_BASH_INTERUPT, true);
                        _player->CastSpell(target, SPELL_DRUID_SKULL_BASH_CHARGE, true);
                    }
                }
            }

            void Register()
            {
                OnHit += SpellHitFn(spell_dru_skull_bash_SpellScript::HandleOnHit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_dru_skull_bash_SpellScript();
        }
};

// Faerie Swarm - 102355
class spell_dru_faerie_swarm : public SpellScriptLoader
{
    public:
        spell_dru_faerie_swarm() : SpellScriptLoader("spell_dru_faerie_swarm") { }

        class spell_dru_faerie_swarm_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_dru_faerie_swarm_SpellScript);

            void HandleOnHit()
            {
                if (Player* _player = GetCaster()->ToPlayer())
                {
                    if (Unit* target = GetHitUnit())
                    {
                        _player->CastSpell(target, SPELL_DRUID_FAERIE_DECREASE_SPEED, true);
                        _player->CastSpell(target, SPELL_DRUID_WEAKENED_ARMOR, true);
                        _player->CastSpell(target, SPELL_DRUID_WEAKENED_ARMOR, true);
                        _player->CastSpell(target, SPELL_DRUID_WEAKENED_ARMOR, true);
                    }
                }
            }

            void Register()
            {
                OnHit += SpellHitFn(spell_dru_faerie_swarm_SpellScript::HandleOnHit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_dru_faerie_swarm_SpellScript();
        }
};

// Wild Mushroom - 88747
class spell_dru_wild_mushroom : public SpellScriptLoader
{
    public:
        spell_dru_wild_mushroom() : SpellScriptLoader("spell_dru_wild_mushroom") { }

        class spell_dru_wild_mushroom_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_dru_wild_mushroom_SpellScript)

            void HandleSummon(SpellEffIndex effIndex)
            {
                if (Player* player = GetCaster()->ToPlayer())
                {
                    PreventHitDefaultEffect(effIndex);

                    const SpellInfo* spell = GetSpellInfo();
                    std::list<Creature*> tempList;
                    std::list<Creature*> mushroomlist;

                    player->GetCreatureListWithEntryInGrid(tempList, DRUID_NPC_WILD_MUSHROOM, 500.0f);

                    mushroomlist = tempList;

                    // Remove other players mushrooms
                    for (std::list<Creature*>::iterator i = tempList.begin(); i != tempList.end(); ++i)
                    {
                        Unit* owner = (*i)->GetOwner();
                        if (owner && owner == player && (*i)->isSummon())
                            continue;

                        mushroomlist.remove((*i));
                    }

                    // 3 mushrooms max
                    if ((int32)mushroomlist.size() >= spell->Effects[effIndex].BasePoints)
                        mushroomlist.back()->ToTempSummon()->UnSummon();

                    Position pos;
                    GetExplTargetDest()->GetPosition(&pos);
                    const SummonPropertiesEntry* properties = sSummonPropertiesStore.LookupEntry(spell->Effects[effIndex].MiscValueB);
                    TempSummon* summon = player->SummonCreature(spell->Effects[effIndex].MiscValue, pos, TEMPSUMMON_TIMED_OR_CORPSE_DESPAWN, spell->GetDuration());
                    if (!summon)
                        return;

                    summon->SetUInt64Value(UNIT_FIELD_SUMMONEDBY, player->GetGUID());
                    summon->setFaction(player->getFaction());
                    summon->SetUInt32Value(UNIT_CREATED_BY_SPELL, GetSpellInfo()->Id);
                    summon->SetMaxHealth(5);
                    summon->CastSpell(summon, DRUID_SPELL_MUSHROOM_BIRTH_VISUAL, true); // Wild Mushroom : Detonate Birth Visual
                }
            }

            void Register()
            {
                OnEffectHit += SpellEffectFn(spell_dru_wild_mushroom_SpellScript::HandleSummon, EFFECT_1, SPELL_EFFECT_SUMMON);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_dru_wild_mushroom_SpellScript();
        }
};

// Wild Mushroom : Detonate - 88751
class spell_dru_wild_mushroom_detonate : public SpellScriptLoader
{
    public:
        spell_dru_wild_mushroom_detonate() : SpellScriptLoader("spell_dru_wild_mushroom_detonate") { }

        class spell_dru_wild_mushroom_detonate_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_dru_wild_mushroom_detonate_SpellScript)

            // Globals variables
            float spellRange;
            std::list<Creature*> mushroomList;

            bool Load()
            {
                spellRange = GetSpellInfo()->GetMaxRange(true);

                Player* player = GetCaster()->ToPlayer();
                if (!player)
                    return false;

                std::list<Creature*> list;
                player->GetCreatureListWithEntryInGrid(list, DRUID_NPC_WILD_MUSHROOM, 50.0f);

                for (std::list<Creature*>::const_iterator i = list.begin(); i != list.end(); ++i)
                {
                    Unit* owner = (*i)->GetOwner();
                    if (owner && owner == player && (*i)->isSummon())
                    {
                        mushroomList.push_back((*i)->ToTempSummon());
                        continue;
                    }
                }

                if (!spellRange)
                    return false;

                return true;
            }

            SpellCastResult CheckCast()
            {
                Player* player = GetCaster()->ToPlayer();
                if (!player)
                    return SPELL_FAILED_CASTER_DEAD;

                if (mushroomList.empty())
                    return SPELL_FAILED_CANT_DO_THAT_RIGHT_NOW;

                bool inRange = false;

                for (std::list<Creature*>::const_iterator i = mushroomList.begin(); i != mushroomList.end(); ++i)
                {
                    Position shroomPos;
                    (*i)->GetPosition(&shroomPos);
                    if (player->IsWithinDist3d(&shroomPos, spellRange)) // Must have at least one mushroom within 40 yards
                    {
                        inRange = true;
                        break;
                    }
                }

                if (!inRange)
                    return SPELL_FAILED_DONT_REPORT;

                return SPELL_CAST_OK;
            }

            void HandleDummy(SpellEffIndex /*effIndex*/)
            {
                if (Player* player = GetCaster()->ToPlayer())
                {
                    for (std::list<Creature*>::const_iterator i = mushroomList.begin(); i != mushroomList.end(); ++i)
                    {
                        Position shroomPos;
                        (*i)->GetPosition(&shroomPos);
                        if (!player->IsWithinDist3d(&shroomPos, spellRange))
                            continue;

                        (*i)->SetVisible(true);

                        player->CastSpell((*i), DRUID_SPELL_WILD_MUSHROOM_DAMAGE, true);    // Damage

                        player->CastSpell((*i), DRUID_SPELL_FUNGAL_GROWTH_SUMMON, true);    // Fungal Growth

                        (*i)->CastSpell((*i), DRUID_SPELL_WILD_MUSHROOM_DEATH_VISUAL, true);// Explosion visual
                        (*i)->CastSpell((*i), DRUID_SPELL_WILD_MUSHROOM_SUICIDE, true);     // Suicide
                        (*i)->DespawnOrUnsummon(500);
                    }
                }
            }

            void Register()
            {
                OnCheckCast += SpellCheckCastFn(spell_dru_wild_mushroom_detonate_SpellScript::CheckCast);
                OnEffectHitTarget += SpellEffectFn(spell_dru_wild_mushroom_detonate_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_dru_wild_mushroom_detonate_SpellScript();
        }
};

// Wild Mushroom : Bloom - 102791
class spell_dru_wild_mushroom_bloom : public SpellScriptLoader
{
    public:
        spell_dru_wild_mushroom_bloom() : SpellScriptLoader("spell_dru_wild_mushroom_bloom") { }

        class spell_dru_wild_mushroom_bloom_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_dru_wild_mushroom_bloom_SpellScript)

            // Globals variables
            float spellRange;
            std::list<TempSummon*> mushroomList;

            bool Load()
            {
                spellRange = GetSpellInfo()->GetMaxRange(true);

                Player* player = GetCaster()->ToPlayer();
                if (!player)
                    return false;

                std::list<Creature*> list;
                std::list<TempSummon*> summonList;
                player->GetCreatureListWithEntryInGrid(list, DRUID_NPC_WILD_MUSHROOM, 500.0f);

                for (std::list<Creature*>::const_iterator i = list.begin(); i != list.end(); ++i)
                {
                    Unit* owner = (*i)->GetOwner();
                    if (owner && owner == player && (*i)->isSummon())
                    {
                        summonList.push_back((*i)->ToTempSummon());
                        continue;
                    }
                }
                mushroomList = summonList;

                if (!spellRange)
                    return false;

                return true;
            }

            SpellCastResult CheckCast()
            {
                Player* player = GetCaster()->ToPlayer();
                if (!player)
                    return SPELL_FAILED_CASTER_DEAD;

                if (mushroomList.empty())
                    return SPELL_FAILED_CANT_DO_THAT_RIGHT_NOW;

                bool inRange = false;

                for (std::list<TempSummon*>::const_iterator i = mushroomList.begin(); i != mushroomList.end(); ++i)
                {
                    Position shroomPos;
                    (*i)->GetPosition(&shroomPos);
                    if (player->IsWithinDist3d(&shroomPos, spellRange)) // Must have at least one mushroom within 40 yards
                    {
                        inRange = true;
                        break;
                    }
                }

                if (!inRange)
                    return SPELL_FAILED_CUSTOM_ERROR;

                return SPELL_CAST_OK;
            }

            void HandleDummy(SpellEffIndex /*effIndex*/)
            {
                if (Player* player = GetCaster()->ToPlayer())
                {
                    for (std::list<TempSummon*>::const_iterator i = mushroomList.begin(); i != mushroomList.end(); ++i)
                    {
                        Position shroomPos;
                        (*i)->GetPosition(&shroomPos);
                        if (!player->IsWithinDist3d(&shroomPos, spellRange))
                            continue;

                        (*i)->CastSpell((*i), DRUID_SPELL_WILD_MUSHROOM_SUICIDE, true); // Explosion visual and suicide
                        player->CastSpell((*i)->GetPositionX(), (*i)->GetPositionY(), (*i)->GetPositionZ(), SPELL_DRUID_WILD_MUSHROOM_HEAL, true); // heal
                    }
                }
            }

            void Register()
            {
                OnCheckCast += SpellCheckCastFn(spell_dru_wild_mushroom_bloom_SpellScript::CheckCast);
                OnEffectHitTarget += SpellEffectFn(spell_dru_wild_mushroom_bloom_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_dru_wild_mushroom_bloom_SpellScript();
        }
};

// Swiftmend - 81262
class spell_dru_swiftmend : public SpellScriptLoader
{
    public:
        spell_dru_swiftmend() : SpellScriptLoader("spell_dru_swiftmend") { }

        class spell_dru_swiftmend_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_dru_swiftmend_AuraScript);

            void OnTick(constAuraEffectPtr aurEff)
            {
                if (DynamicObject* dynObj = GetCaster()->GetDynObject(SPELL_DRUID_SWIFTMEND))
                    GetCaster()->CastSpell(dynObj->GetPositionX(), dynObj->GetPositionY(), dynObj->GetPositionZ(), SPELL_DRUID_SWIFTMEND_TICK, true);
            }

            void Register()
            {
                OnEffectPeriodic += AuraEffectPeriodicFn(spell_dru_swiftmend_AuraScript::OnTick, EFFECT_1, SPELL_AURA_PERIODIC_DUMMY);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_dru_swiftmend_AuraScript();
        }
};

// Astral Communion - 127663
class spell_dru_astral_communion : public SpellScriptLoader
{
    public:
        spell_dru_astral_communion() : SpellScriptLoader("spell_dru_astral_communion") { }

        class spell_dru_astral_communion_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_dru_astral_communion_AuraScript);

            void OnTick(constAuraEffectPtr aurEff)
            {
                if (!GetCaster())
                    return;

                if (Player* _player = GetTarget()->ToPlayer())
                {
                    int32 eclipse = 25;

                    switch (_player->m_lastEclipseState)
                    {
                        case ECLIPSE_NONE:
                        case ECLIPSE_SOLAR:
                            // If last eclipse is solar, set lunar power ...
                            // .. or if no eclipse since in game, set lunar power
                            _player->SetEclipsePower(int32(_player->GetEclipsePower() - eclipse));
                            break;
                        case ECLIPSE_LUNAR:
                            // If last eclipse is lunar, set solar power
                            _player->SetEclipsePower(int32(_player->GetEclipsePower() + eclipse));
                            break;
                        default:
                            break;
                    }

                    if (_player->GetEclipsePower() == 100 && !_player->HasAura(SPELL_DRUID_SOLAR_ECLIPSE))
                    {
                        _player->CastSpell(_player, SPELL_DRUID_SOLAR_ECLIPSE, true, 0); // Cast Solar Eclipse
                        _player->m_lastEclipseState = ECLIPSE_SOLAR;
                        _player->CastSpell(_player, SPELL_DRUID_NATURES_GRACE, true); // Cast Nature's Grace
                        _player->CastSpell(_player, SPELL_DRUID_ECLIPSE_GENERAL_ENERGIZE, true); // Cast Eclipse - Give 35% of POWER_MANA
                    }
                    else if (_player->GetEclipsePower() == -100 && !_player->HasAura(SPELL_DRUID_LUNAR_ECLIPSE))
                    {
                        _player->CastSpell(_player, SPELL_DRUID_LUNAR_ECLIPSE, true, 0); // Cast Lunar Eclipse
                        _player->m_lastEclipseState = ECLIPSE_LUNAR;
                        _player->CastSpell(_player, SPELL_DRUID_NATURES_GRACE, true); // Cast Nature's Grace
                        _player->CastSpell(_player, SPELL_DRUID_ECLIPSE_GENERAL_ENERGIZE, true); // Cast Eclipse - Give 35% of POWER_MANA
                        _player->CastSpell(_player, SPELL_DRUID_LUNAR_ECLIPSE_OVERRIDE, true);

                        if (_player->HasSpellCooldown(SPELL_DRUID_STARFALL))
                            _player->RemoveSpellCooldown(SPELL_DRUID_STARFALL, true);
                    }
                }
            }

            void Register()
            {
                OnEffectPeriodic += AuraEffectPeriodicFn(spell_dru_astral_communion_AuraScript::OnTick, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_dru_astral_communion_AuraScript();
        }
};

// Celestial Alignment - 112071
class spell_dru_celestial_alignment : public SpellScriptLoader
{
    public:
        spell_dru_celestial_alignment() : SpellScriptLoader("spell_dru_celestial_alignment") { }

        class spell_dru_celestial_alignment_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_dru_celestial_alignment_SpellScript);

            void HandleOnHit()
            {
                if (Player* _player = GetCaster()->ToPlayer())
                {
                    if (Unit* target = GetHitUnit())
                    {
                        _player->SetEclipsePower(0);

                        _player->CastSpell(_player, SPELL_DRUID_SOLAR_ECLIPSE, true, 0); // Cast Solar Eclipse
                        _player->CastSpell(_player, SPELL_DRUID_LUNAR_ECLIPSE, true, 0); // Cast Lunar Eclipse
                        _player->m_lastEclipseState = ECLIPSE_NONE;
                        _player->CastSpell(_player, SPELL_DRUID_NATURES_GRACE, true); // Cast Nature's Grace
                        _player->CastSpell(_player, SPELL_DRUID_ECLIPSE_GENERAL_ENERGIZE, true); // Cast Eclipse - Give 35% of POWER_MANA
                        _player->CastSpell(_player, SPELL_DRUID_LUNAR_ECLIPSE_OVERRIDE, true);

                        if (_player->HasSpellCooldown(SPELL_DRUID_STARFALL))
                            _player->RemoveSpellCooldown(SPELL_DRUID_STARFALL, true);
                    }
                }
            }

            void Register()
            {
                OnHit += SpellHitFn(spell_dru_celestial_alignment_SpellScript::HandleOnHit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_dru_celestial_alignment_SpellScript();
        }

        class spell_dru_celestial_alignment_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_dru_celestial_alignment_AuraScript);

            void OnRemove(constAuraEffectPtr aurEff, AuraEffectHandleModes /*mode*/)
            {
                if (!GetCaster())
                    return;

                if (Player* _player = GetCaster()->ToPlayer())
                {
                    _player->RemoveAura(SPELL_DRUID_SOLAR_ECLIPSE);
                    _player->RemoveAura(SPELL_DRUID_LUNAR_ECLIPSE);
                    _player->RemoveAura(SPELL_DRUID_NATURES_GRACE);
                    _player->RemoveAura(SPELL_DRUID_LUNAR_ECLIPSE_OVERRIDE);
                }
            }

            void Register()
            {
                OnEffectRemove += AuraEffectRemoveFn(spell_dru_celestial_alignment_AuraScript::OnRemove, EFFECT_0, SPELL_AURA_MOD_SHAPESHIFT, AURA_EFFECT_HANDLE_REAL);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_dru_celestial_alignment_AuraScript();
        }
};

// Shooting Stars - 93400
class spell_dru_shooting_stars : public SpellScriptLoader
{
    public:
        spell_dru_shooting_stars() : SpellScriptLoader("spell_dru_shooting_stars") { }

        class spell_dru_shooting_stars_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_dru_shooting_stars_SpellScript);

            void HandleOnHit()
            {
                if (Player* _player = GetCaster()->ToPlayer())
                    if (Unit* target = GetHitUnit())
                        _player->RemoveSpellCooldown(SPELL_DRUID_STARSURGE, true);
            }

            void Register()
            {
                OnHit += SpellHitFn(spell_dru_shooting_stars_SpellScript::HandleOnHit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_dru_shooting_stars_SpellScript();
        }
};

// Frenzied Regeneration - 22842
class spell_dru_frenzied_regeneration : public SpellScriptLoader
{
    public:
        spell_dru_frenzied_regeneration() : SpellScriptLoader("spell_dru_frenzied_regeneration") { }

        class spell_dru_frenzied_regeneration_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_dru_frenzied_regeneration_SpellScript);

            void HandleOnHit()
            {
                if (Player* _player = GetCaster()->ToPlayer())
                {
                    if (Unit* target = GetHitUnit())
                    {
                        if (!_player->HasAura(SPELL_DRUID_GLYPH_OF_FRENZIED_REGEN))
                        {
                            int32 rageused = std::min(600, _player->GetPower(POWER_RAGE));
                            int32 AP = _player->GetTotalAttackPowerValue(BASE_ATTACK);
                            int32 agility = _player->GetStat(STAT_AGILITY);
                            int32 stamina = _player->GetStat(STAT_STAMINA);
                            int32 healAmount;

                            healAmount = std::max(int32(2 * (AP - agility * 2)), int32(stamina * 2.5f));
                            healAmount = rageused * healAmount / 600;

                            SetHitHeal(healAmount);
                            _player->EnergizeBySpell(_player, 22842, -rageused, POWER_RAGE);
                        }
                        else
                        {
                            SetHitHeal(0);
                            _player->CastSpell(_player, SPELL_DRUID_FRENZIED_REGEN_HEAL_TAKE, true);
                        }
                    }
                }
            }

            void Register()
            {
                OnHit += SpellHitFn(spell_dru_frenzied_regeneration_SpellScript::HandleOnHit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_dru_frenzied_regeneration_SpellScript();
        }
};

// Stampeding Roar - 106898, Stampeding Roar (cat) - 77764 and Stampeding Roar(bear) - 77761
class spell_dru_stampeding_roar_speed : public SpellScriptLoader
{
    public:
        spell_dru_stampeding_roar_speed() : SpellScriptLoader("spell_dru_stampeding_roar_speed") { }

        class spell_dru_stampeding_roar_speed_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_dru_stampeding_roar_speed_SpellScript);

            void HandleOnHit()
            {
                if (Player* _player = GetCaster()->ToPlayer())
                    if (_player->HasAura(SPELL_DRUID_DASH))
                        if (_player->HasAura(GetSpellInfo()->Id))
                            _player->RemoveAura(GetSpellInfo()->Id);
            }

            void Register()
            {
                OnHit += SpellHitFn(spell_dru_stampeding_roar_speed_SpellScript::HandleOnHit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_dru_stampeding_roar_speed_SpellScript();
        }
};

// Stampeding Roar - 97993, Stampeding Roar (cat) - 77764 and Stampeding Roar(bear) - 77761
class spell_dru_stampeding_roar : public SpellScriptLoader
{
    public:
        spell_dru_stampeding_roar() : SpellScriptLoader("spell_dru_stampeding_roar") { }

        class spell_dru_stampeding_roar_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_dru_stampeding_roar_SpellScript);

            void HandleOnHit()
            {
                if (Player* _player = GetCaster()->ToPlayer())
                    if (Unit* target = GetHitUnit())
                        target->RemoveMovementImpairingAuras();
            }

            void Register()
            {
                OnHit += SpellHitFn(spell_dru_stampeding_roar_SpellScript::HandleOnHit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_dru_stampeding_roar_SpellScript();
        }
};

// Innervate - 29166
class spell_dru_innervate : public SpellScriptLoader
{
    public:
        spell_dru_innervate() : SpellScriptLoader("spell_dru_innervate") { }

        class spell_dru_innervate_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_dru_innervate_SpellScript);

            void HandleOnHit()
            {
                if (Player* _player = GetCaster()->ToPlayer())
                {
                    if (Unit* target = GetHitUnit())
                    {
                        int32 mana = target->GetMaxPower(POWER_MANA) / 10;

                        if (target->GetGUID() == _player->GetGUID())
                            mana *= 2;

                        if (AuraPtr innervate = target->GetAura(29166))
                            innervate->GetEffect(0)->ChangeAmount(mana / 10);
                    }
                }
            }

            void Register()
            {
                OnHit += SpellHitFn(spell_dru_innervate_SpellScript::HandleOnHit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_dru_innervate_SpellScript();
        }
};

// Lacerate - 33745
class spell_dru_lacerate : public SpellScriptLoader
{
    public:
        spell_dru_lacerate() : SpellScriptLoader("spell_dru_lacerate") { }

        class spell_dru_lacerate_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_dru_lacerate_SpellScript);

            void HandleOnHit()
            {
                if (Player* _player = GetCaster()->ToPlayer())
                    if (Unit* target = GetHitUnit())
                        if (roll_chance_i(25))
                            _player->RemoveSpellCooldown(33917, true);
            }

            void Register()
            {
                OnHit += SpellHitFn(spell_dru_lacerate_SpellScript::HandleOnHit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_dru_lacerate_SpellScript();
        }
};

// Faerie Fire - 770
class spell_dru_faerie_fire : public SpellScriptLoader
{
    public:
        spell_dru_faerie_fire() : SpellScriptLoader("spell_dru_faerie_fire") { }

        class spell_dru_faerie_fire_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_dru_faerie_fire_SpellScript);

            void HandleOnHit()
            {
                if (Player* _player = GetCaster()->ToPlayer())
                {
                    if (Unit* target = GetHitUnit())
                    {
                        _player->CastSpell(target, SPELL_DRUID_WEAKENED_ARMOR, true);
                        _player->CastSpell(target, SPELL_DRUID_WEAKENED_ARMOR, true);
                        _player->CastSpell(target, SPELL_DRUID_WEAKENED_ARMOR, true);

                        if (_player->GetShapeshiftForm() == FORM_BEAR)
                        {
                            if (_player->HasSpellCooldown(SPELL_DRUID_MANGLE_BEAR))
                                _player->RemoveSpellCooldown(SPELL_DRUID_MANGLE_BEAR, true);
                        }
                    }
                }
            }

            void Register()
            {
                OnHit += SpellHitFn(spell_dru_faerie_fire_SpellScript::HandleOnHit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_dru_faerie_fire_SpellScript();
        }
};

// Teleport : Moonglade - 18960
class spell_dru_teleport_moonglade : public SpellScriptLoader
{
    public:
        spell_dru_teleport_moonglade() : SpellScriptLoader("spell_dru_teleport_moonglade") { }

        class spell_dru_teleport_moonglade_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_dru_teleport_moonglade_SpellScript);

            void HandleAfterCast()
            {
                if (Player* _player = GetCaster()->ToPlayer())
                    _player->TeleportTo(1, 7964.063f, -2491.099f, 487.83f, _player->GetOrientation());
            }

            void Register()
            {
                AfterCast += SpellCastFn(spell_dru_teleport_moonglade_SpellScript::HandleAfterCast);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_dru_teleport_moonglade_SpellScript();
        }
};

// Growl - 6795, Might of Ursoc - 106922, Stampeding Roar - 106898
class spell_dru_growl : public SpellScriptLoader
{
    public:
        spell_dru_growl() : SpellScriptLoader("spell_dru_growl") { }

        class spell_dru_growl_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_dru_growl_SpellScript);

            void HandleOnHit()
            {
                // This spell activate the bear form
                if (Player* _player = GetCaster()->ToPlayer())
                {
                    if (GetSpellInfo()->Id == 106898 && _player->GetShapeshiftForm() != FORM_CAT && _player->GetShapeshiftForm() != FORM_BEAR)
                        _player->CastSpell(_player, SPELL_DRUID_BEAR_FORM, true);
                    else if (GetSpellInfo()->Id != 106898)
                        _player->CastSpell(_player, SPELL_DRUID_BEAR_FORM, true);
                }
            }

            void Register()
            {
                OnHit += SpellHitFn(spell_dru_growl_SpellScript::HandleOnHit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_dru_growl_SpellScript();
        }
};

// Prowl - 5212, Prowl - 102547 and Dash - 1850
class spell_dru_prowl : public SpellScriptLoader
{
    public:
        spell_dru_prowl() : SpellScriptLoader("spell_dru_prowl") { }

        class spell_dru_prowl_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_dru_prowl_SpellScript);

            bool Validate(SpellInfo const* /*spellEntry*/)
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_DRUID_PROWL))
                    return false;
                return true;
            }

            void HandleOnHit()
            {
                // This spell activate the cat form
                if (Player* _player = GetCaster()->ToPlayer())
                    _player->CastSpell(_player, SPELL_DRUID_CAT_FORM, true);
            }

            void Register()
            {
                OnHit += SpellHitFn(spell_dru_prowl_SpellScript::HandleOnHit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_dru_prowl_SpellScript();
        }
};

// 5176 - Wrath, 2912 - Starfire and 78674 - Starsurge
class spell_dru_eclipse : public SpellScriptLoader
{
    public:
        spell_dru_eclipse() : SpellScriptLoader("spell_dru_eclipse") { }

        class spell_dru_eclipse_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_dru_eclipse_SpellScript);

            void HandleAfterCast()
            {
                if (Player* _plr = GetCaster()->ToPlayer())
                    if (GetSpellInfo()->Id == SPELL_DRUID_STARSURGE)
                        _plr->RemoveAura(SPELL_DRUID_SHOOTING_STARS);
            }

            void HandleOnHit()
            {
                if (Player* _player = GetCaster()->ToPlayer())
                {
                    if (Unit* target = GetHitUnit())
                    {
                        if (!_player->HasAura(SPELL_DRUID_CELESTIAL_ALIGNMENT) && _player->GetSpecializationId(_player->GetActiveSpec()) == SPEC_DROOD_BALANCE)
                        {
                            float modifier = 1.0f;
                            if (_player->HasAura(SPELL_DRUID_EUPHORIA) && !_player->HasAura(SPELL_DRUID_SOLAR_ECLIPSE) && !_player->HasAura(SPELL_DRUID_LUNAR_ECLIPSE))
                                modifier = 2.0f;

                            switch (GetSpellInfo()->Id)
                            {
                                case SPELL_DRUID_WRATH:
                                {
                                    int32 eclipse = 15 * modifier; // X Lunar energy

                                    _player->SetEclipsePower(int32(_player->GetEclipsePower() - eclipse));

                                    if (_player->GetEclipsePower() == -100 && !_player->HasAura(SPELL_DRUID_LUNAR_ECLIPSE))
                                    {
                                        _player->CastSpell(_player, SPELL_DRUID_LUNAR_ECLIPSE, true, 0); // Cast Lunar Eclipse
                                        _player->m_lastEclipseState = ECLIPSE_LUNAR;
                                        _player->CastSpell(_player, SPELL_DRUID_NATURES_GRACE, true); // Cast Nature's Grace
                                        _player->CastSpell(_player, SPELL_DRUID_ECLIPSE_GENERAL_ENERGIZE, true); // Cast Eclipse - Give 35% of POWER_MANA
                                        _player->CastSpell(_player, SPELL_DRUID_LUNAR_ECLIPSE_OVERRIDE, true);

                                        if (_player->HasSpellCooldown(SPELL_DRUID_STARFALL))
                                            _player->RemoveSpellCooldown(SPELL_DRUID_STARFALL, true);
                                    }

                                    // Your crits with Wrath also increase sunfire duration by 2s
                                    if (GetSpell()->IsCritForTarget(target))
                                    {
                                        if (AuraPtr aura = target->GetAura(SPELL_DRUID_SUNFIRE))
                                        {
                                            aura->SetDuration(aura->GetDuration() + 2000);
                                            if (aura->GetMaxDuration() < aura->GetDuration())
                                                aura->SetMaxDuration(aura->GetDuration());
                                        }
                                    }

                                    break;
                                }
                                case SPELL_DRUID_STARFIRE:
                                {
                                    int32 eclipse = 20 * modifier; // X Solar energy

                                    _player->SetEclipsePower(int32(_player->GetEclipsePower() + eclipse));

                                    if (_player->GetEclipsePower() == 100 && !_player->HasAura(SPELL_DRUID_SOLAR_ECLIPSE))
                                    {
                                        _player->CastSpell(_player, SPELL_DRUID_SOLAR_ECLIPSE, true, 0); // Cast Lunar Eclipse
                                        _player->m_lastEclipseState = ECLIPSE_SOLAR;
                                        _player->CastSpell(_player, SPELL_DRUID_NATURES_GRACE, true); // Cast Nature's Grace
                                        _player->CastSpell(_player, SPELL_DRUID_ECLIPSE_GENERAL_ENERGIZE, true); // Cast Eclipse - Give 35% of POWER_MANA
                                    }

                                    // Your crits with Starfire also increase moonfire duration by 2s
                                    if (GetSpell()->IsCritForTarget(target))
                                    {
                                        if (AuraPtr aura = target->GetAura(SPELL_DRUID_MOONFIRE))
                                        {
                                            aura->SetDuration(aura->GetDuration() + 2000);
                                            if (aura->GetMaxDuration() < aura->GetDuration())
                                                aura->SetMaxDuration(aura->GetDuration());
                                        }
                                    }

                                    break;
                                }
                                case SPELL_DRUID_STARSURGE:
                                {
                                    int32 eclipse = 20 * modifier;

                                    switch (_player->m_lastEclipseState)
                                    {
                                        case ECLIPSE_NONE:
                                        case ECLIPSE_SOLAR:
                                            // If last eclipse is solar, set lunar power ...
                                            // .. or if no eclipse since in game, set lunar power
                                            _player->SetEclipsePower(int32(_player->GetEclipsePower() - eclipse));
                                            break;
                                        case ECLIPSE_LUNAR:
                                            // If last eclipse is lunar, set solar power
                                            _player->SetEclipsePower(int32(_player->GetEclipsePower() + eclipse));
                                            break;
                                        default:
                                            break;
                                    }

                                    if (_player->GetEclipsePower() == 100 && !_player->HasAura(SPELL_DRUID_SOLAR_ECLIPSE))
                                    {
                                        _player->CastSpell(_player, SPELL_DRUID_SOLAR_ECLIPSE, true, 0); // Cast Lunar Eclipse
                                        _player->m_lastEclipseState = ECLIPSE_SOLAR;
                                        _player->CastSpell(_player, SPELL_DRUID_NATURES_GRACE, true); // Cast Nature's Grace
                                        _player->CastSpell(_player, SPELL_DRUID_ECLIPSE_GENERAL_ENERGIZE, true); // Cast Eclipse - Give 35% of POWER_MANA
                                    }
                                    else if (_player->GetEclipsePower() == -100 && !_player->HasAura(SPELL_DRUID_LUNAR_ECLIPSE))
                                    {
                                        _player->CastSpell(_player, SPELL_DRUID_LUNAR_ECLIPSE, true, 0); // Cast Lunar Eclipse
                                        _player->m_lastEclipseState = ECLIPSE_LUNAR;
                                        _player->CastSpell(_player, SPELL_DRUID_NATURES_GRACE, true); // Cast Nature's Grace
                                        _player->CastSpell(_player, SPELL_DRUID_ECLIPSE_GENERAL_ENERGIZE, true); // Cast Eclipse - Give 35% of POWER_MANA
                                        _player->CastSpell(_player, SPELL_DRUID_LUNAR_ECLIPSE_OVERRIDE, true);

                                        if (_player->HasSpellCooldown(SPELL_DRUID_STARFALL))
                                            _player->RemoveSpellCooldown(SPELL_DRUID_STARFALL, true);
                                    }

                                    // Your crits with Starsurge also increase sunfire duration by 2s
                                    if (GetSpell()->IsCritForTarget(target))
                                    {
                                        if (AuraPtr aura = target->GetAura(SPELL_DRUID_SUNFIRE))
                                        {
                                            aura->SetDuration(aura->GetDuration() + 2000);
                                            if (aura->GetMaxDuration() < aura->GetDuration())
                                                aura->SetMaxDuration(aura->GetDuration());
                                        }
                                    }
                                    // Your crits with Starsurge also increase moonfire duration by 2s
                                    if (GetSpell()->IsCritForTarget(target))
                                    {
                                        if (AuraPtr aura = target->GetAura(SPELL_DRUID_MOONFIRE))
                                        {
                                            aura->SetDuration(aura->GetDuration() + 2000);
                                            if (aura->GetMaxDuration() < aura->GetDuration())
                                                aura->SetMaxDuration(aura->GetDuration());
                                        }
                                    }

                                    break;
                                }
                            }
                        }
                    }
                }
            }

            void Register()
            {
                OnHit += SpellHitFn(spell_dru_eclipse_SpellScript::HandleOnHit);
                AfterCast += SpellCastFn(spell_dru_eclipse_SpellScript::HandleAfterCast);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_dru_eclipse_SpellScript();
        }
};

class spell_dru_t10_restoration_4p_bonus : public SpellScriptLoader
{
    public:
        spell_dru_t10_restoration_4p_bonus() : SpellScriptLoader("spell_dru_t10_restoration_4p_bonus") { }

        class spell_dru_t10_restoration_4p_bonus_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_dru_t10_restoration_4p_bonus_SpellScript);

            bool Load()
            {
                return GetCaster()->GetTypeId() == TYPEID_PLAYER;
            }

            void FilterTargets(std::list<WorldObject*>& targets)
            {
                if (!GetCaster()->ToPlayer()->GetGroup())
                {
                    targets.clear();
                    targets.push_back(GetCaster());
                }
                else
                {
                    targets.remove(GetExplTargetUnit());
                    std::list<Unit*> tempTargets;
                    for (std::list<WorldObject*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                        if ((*itr)->GetTypeId() == TYPEID_PLAYER && GetCaster()->IsInRaidWith((*itr)->ToUnit()))
                            tempTargets.push_back((*itr)->ToUnit());

                    if (tempTargets.empty())
                    {
                        targets.clear();
                        FinishCast(SPELL_FAILED_DONT_REPORT);
                        return;
                    }

                    Unit* target = JadeCore::Containers::SelectRandomContainerElement(tempTargets);
                    targets.clear();
                    targets.push_back(target);
                }
            }

            void Register()
            {
                OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_dru_t10_restoration_4p_bonus_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_DEST_AREA_ALLY);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_dru_t10_restoration_4p_bonus_SpellScript();
        }
};

// 40121 - Swift Flight Form (Passive)
class spell_dru_swift_flight_passive : public SpellScriptLoader
{
    public:
        spell_dru_swift_flight_passive() : SpellScriptLoader("spell_dru_swift_flight_passive") { }

        class spell_dru_swift_flight_passive_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_dru_swift_flight_passive_AuraScript);

            bool Load()
            {
                return GetCaster()->GetTypeId() == TYPEID_PLAYER;
            }

            void CalculateAmount(constAuraEffectPtr /*aurEff*/, int32 & amount, bool & /*canBeRecalculated*/)
            {
                if (Player* caster = GetCaster()->ToPlayer())
                    if (caster->GetSkillValue(SKILL_RIDING) >= 375)
                        amount = 310;
            }

            void Register()
            {
                DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_dru_swift_flight_passive_AuraScript::CalculateAmount, EFFECT_1, SPELL_AURA_MOD_INCREASE_VEHICLE_FLIGHT_SPEED);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_dru_swift_flight_passive_AuraScript();
        }
};

class spell_dru_starfall_dummy : public SpellScriptLoader
{
    public:
        spell_dru_starfall_dummy() : SpellScriptLoader("spell_dru_starfall_dummy") { }

        class spell_dru_starfall_dummy_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_dru_starfall_dummy_SpellScript);

            void FilterTargets(std::list<WorldObject*>& targets)
            {
                JadeCore::Containers::RandomResizeList(targets, 2);
            }

            void HandleDummy(SpellEffIndex /*effIndex*/)
            {
                Unit* caster = GetCaster();
                // Shapeshifting into an animal form or mounting cancels the effect
                if (caster->GetCreatureType() == CREATURE_TYPE_BEAST || caster->IsMounted())
                {
                    if (SpellInfo const* spellInfo = GetTriggeringSpell())
                        caster->RemoveAurasDueToSpell(spellInfo->Id);
                    return;
                }

                // Any effect which causes you to lose control of your character will supress the starfall effect.
                if (caster->HasUnitState(UNIT_STATE_CONTROLLED))
                    return;

                caster->CastSpell(GetHitUnit(), uint32(GetEffectValue()), true);
            }

            void Register()
            {
                OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_dru_starfall_dummy_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_SRC_AREA_ENEMY);
                OnEffectHitTarget += SpellEffectFn(spell_dru_starfall_dummy_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_dru_starfall_dummy_SpellScript();
        }
};

class spell_dru_savage_roar : public SpellScriptLoader
{
    public:
        spell_dru_savage_roar() : SpellScriptLoader("spell_dru_savage_roar") { }

        class spell_dru_savage_roar_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_dru_savage_roar_SpellScript);

            SpellCastResult CheckCast()
            {
                Unit* caster = GetCaster();
                if (caster->GetShapeshiftForm() != FORM_CAT)
                    return SPELL_FAILED_ONLY_SHAPESHIFT;

                return SPELL_CAST_OK;
            }

            void Register()
            {
                OnCheckCast += SpellCheckCastFn(spell_dru_savage_roar_SpellScript::CheckCast);
            }
        };

        class spell_dru_savage_roar_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_dru_savage_roar_AuraScript);

            bool Validate(SpellInfo const* /*spell*/)
            {
                if (!sSpellMgr->GetSpellInfo(DRUID_SAVAGE_ROAR))
                    return false;
                return true;
            }

            void AfterApply(constAuraEffectPtr aurEff, AuraEffectHandleModes /*mode*/)
            {
                Unit* target = GetTarget();
                target->CastSpell(target, DRUID_SAVAGE_ROAR, true, NULL, aurEff, GetCasterGUID());
            }

            void AfterRemove(constAuraEffectPtr /*aurEff*/, AuraEffectHandleModes /*mode*/)
            {
                GetTarget()->RemoveAurasDueToSpell(DRUID_SAVAGE_ROAR);
            }

            void Register()
            {
                AfterEffectApply += AuraEffectApplyFn(spell_dru_savage_roar_AuraScript::AfterApply, EFFECT_1, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
                AfterEffectRemove += AuraEffectRemoveFn(spell_dru_savage_roar_AuraScript::AfterRemove, EFFECT_1, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_dru_savage_roar_SpellScript();
        }

        AuraScript* GetAuraScript() const
        {
            return new spell_dru_savage_roar_AuraScript();
        }
};

// Survival Instincts - 61336
class spell_dru_survival_instincts : public SpellScriptLoader
{
    public:
        spell_dru_survival_instincts() : SpellScriptLoader("spell_dru_survival_instincts") { }

        class spell_dru_survival_instincts_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_dru_survival_instincts_AuraScript);

            void AfterApply(constAuraEffectPtr aurEff, AuraEffectHandleModes /*mode*/)
            {
                GetTarget()->CastSpell(GetTarget(), DRUID_SURVIVAL_INSTINCTS, true);
            }

            void AfterRemove(constAuraEffectPtr /*aurEff*/, AuraEffectHandleModes /*mode*/)
            {
                GetTarget()->RemoveAurasDueToSpell(DRUID_SURVIVAL_INSTINCTS);
            }

            void Register()
            {
                AfterEffectApply += AuraEffectApplyFn(spell_dru_survival_instincts_AuraScript::AfterApply, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_CHANGE_AMOUNT_MASK);
                AfterEffectRemove += AuraEffectRemoveFn(spell_dru_survival_instincts_AuraScript::AfterRemove, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_CHANGE_AMOUNT_MASK);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_dru_survival_instincts_AuraScript();
        }
};

void AddSC_druid_spell_scripts()
{
    new spell_dru_glyph_of_the_treant();
    new spell_dru_incarnation_chosen_of_elune();
    new spell_dru_incarnation_skins();
    new spell_dru_glyph_of_shred();
    new spell_dru_item_pvp_feral_4p();
    new spell_dru_wild_charge_moonkin();
    new spell_dru_thrash_bear();
    new spell_dru_swipe_and_maul();
    new spell_dru_soul_of_the_forest_eclipse();
    new spell_dru_soul_of_the_forest();
    new spell_dru_tigers_fury();
    new spell_dru_play_death();
    new spell_dru_consecration();
    new spell_dru_consecration_area();
    new spell_dru_life_tap();
    new spell_dru_soul_swap();
    new spell_dru_demonic_circle_teleport();
    new spell_dru_shattering_blow();
    new spell_dru_symbiosis_aura();
    new spell_dru_symbiosis();
    new spell_dru_moonfire();
    new spell_dru_natures_vigil();
    new spell_dru_cenarion_ward();
    new spell_dru_ursols_vortex_snare();
    new spell_dru_ursols_vortex();
    new spell_dru_solar_beam();
    new spell_dru_dash();
    new spell_dru_rip_duration();
    new spell_dru_savage_defense();
    new spell_dru_bear_form();
    new spell_dru_ferocious_bite();
    new spell_dru_bear_hug();
    new spell_dru_ravage();
    new spell_dru_lifebloom();
    new spell_dru_killer_instinct();
    new spell_dru_lifebloom_refresh();
    new spell_dru_omen_of_clarity();
    new spell_dru_mark_of_the_wild();
    new spell_dru_natures_cure();
    new spell_dru_glyph_of_regrowth();
    new spell_dru_cat_form();
    new spell_dru_skull_bash();
    new spell_dru_faerie_swarm();
    new spell_dru_wild_mushroom_bloom();
    new spell_dru_wild_mushroom_detonate();
    new spell_dru_wild_mushroom();
    new spell_dru_swiftmend();
    new spell_dru_astral_communion();
    new spell_dru_shooting_stars();
    new spell_dru_celestial_alignment();
    new spell_dru_frenzied_regeneration();
    new spell_dru_stampeding_roar_speed();
    new spell_dru_stampeding_roar();
    new spell_dru_innervate();
    new spell_dru_lacerate();
    new spell_dru_faerie_fire();
    new spell_dru_teleport_moonglade();
    new spell_dru_growl();
    new spell_dru_prowl();
    new spell_dru_eclipse();
    new spell_dru_t10_restoration_4p_bonus();
    new spell_dru_swift_flight_passive();
    new spell_dru_starfall_dummy();
    new spell_dru_savage_roar();
    new spell_dru_survival_instincts();
}
