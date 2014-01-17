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
 * Scripts for spells with SPELLFAMILY_WARRIOR and SPELLFAMILY_GENERIC spells used by warrior players.
 * Ordered alphabetically using scriptname.
 * Scriptnames of files in this file should be prefixed with "spell_warr_".
 */

#include "ScriptMgr.h"
#include "SpellScript.h"
#include "SpellAuraEffects.h"
#include "GridNotifiers.h"

enum WarriorSpells
{
    WARRIOR_SPELL_LAST_STAND_TRIGGERED          = 12976,
    WARRIOR_SPELL_VICTORY_RUSH_DAMAGE           = 34428,
    WARRIOR_SPELL_VICTORY_RUSH_HEAL             = 118779,
    WARRIOR_SPELL_VICTORIOUS_STATE              = 32216,
    WARRIOR_SPELL_BLOODTHIRST                   = 23881,
    WARRIOR_SPELL_BLOODTHIRST_HEAL              = 117313,
    WARRIOR_SPELL_DEEP_WOUNDS                   = 115767,
    WARRIOR_SPELL_THUNDER_CLAP                  = 6343,
    WARRIOR_SPELL_WEAKENED_BLOWS                = 115798,
    WARRIOR_SPELL_BLOOD_AND_THUNDER             = 84615,
    WARRIOR_SPELL_SHOCKWAVE_STUN                = 132168,
    WARRIOR_SPELL_HEROIC_LEAP_DAMAGE            = 52174,
    WARRIOR_SPELL_RALLYING_CRY		            = 122507,
    WARRIOR_SPELL_GLYPH_OF_MORTAL_STRIKE        = 58368,
    WARRIOR_SPELL_SWORD_AND_BOARD               = 50227,
    WARRIOR_SPELL_SHIELD_SLAM                   = 23922,
    WARRIOR_SPELL_ALLOW_RAGING_BLOW             = 131116,
    WARRIOR_SPELL_MOCKING_BANNER_TAUNT          = 114198,
    WARRIOR_NPC_MOCKING_BANNER                  = 59390,
    WARRIOR_SPELL_BERZERKER_RAGE_EFFECT         = 23691,
    WARRIOR_SPELL_ENRAGE                        = 12880,
    WARRIOR_SPELL_COLOSSUS_SMASH                = 86346,
    WARRIOR_SPELL_MORTAL_STRIKE_AURA            = 12294,
    WARRIOR_SPELL_TASTE_FOR_BLOOD               = 56638,
    WARRIOR_SPELL_ALLOW_OVERPOWER               = 119962,
    WARRIOR_SPELL_TASTE_FOR_BLOOD_DAMAGE_DONE   = 125831,
    WARRIOR_SPELL_SECOND_WIND_REGEN             = 16491,
    WARRIOR_SPELL_DRAGON_ROAR_KNOCK_BACK        = 118895,
    WARRIOR_SPELL_MEAT_CLEAVER_PROC             = 85739,
    WARRIOR_SPELL_PHYSICAL_VULNERABILITY        = 81326,
    WARRIOR_SPELL_STORM_BOLT_STUN               = 132169,
    WARRIOR_SPELL_SHIELD_BLOCK_TRIGGERED        = 132404,
    WARRIOR_SPELL_GLYPH_OF_HINDERING_STRIKES    = 58366,
    WARRIOR_SPELL_SLUGGISH                      = 129923,
    WARRIOR_SPELL_IMPENDING_VICTORY             = 103840,
    WARRIOR_SPELL_ITEM_PVP_SET_4P_BONUS         = 133277,
    WARRIOR_SPELL_HEROIC_LEAP_SPEED             = 133278,
    WARRIOR_SPELL_DOUBLE_TIME                   = 103827,
};

// Victorious State - 32216
class spell_warr_victorious_state : public SpellScriptLoader
{
    public:
        spell_warr_victorious_state() : SpellScriptLoader("spell_warr_victorious_state") { }

        class spell_warr_victorious_state_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warr_victorious_state_SpellScript);

            void HandleOnHit()
            {
                if (Player* _player = GetCaster()->ToPlayer())
                    if (_player->HasSpellCooldown(WARRIOR_SPELL_IMPENDING_VICTORY))
                        _player->RemoveSpellCooldown(WARRIOR_SPELL_IMPENDING_VICTORY, true);
            }

            void Register()
            {
                OnHit += SpellHitFn(spell_warr_victorious_state_SpellScript::HandleOnHit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warr_victorious_state_SpellScript();
        }
};

// Called by Heroic Strike - 78 and Cleave - 845
// Glyph of Hindering Strikes - 58366
class spell_warr_glyph_of_hindering_strikes : public SpellScriptLoader
{
    public:
        spell_warr_glyph_of_hindering_strikes() : SpellScriptLoader("spell_warr_glyph_of_hindering_strikes") { }

        class spell_warr_glyph_of_hindering_strikes_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warr_glyph_of_hindering_strikes_SpellScript);

            void HandleOnHit()
            {
                if (Player* _player = GetCaster()->ToPlayer())
                    if (Unit* target = GetHitUnit())
                        if (_player->HasAura(WARRIOR_SPELL_GLYPH_OF_HINDERING_STRIKES))
                            _player->CastSpell(target, WARRIOR_SPELL_SLUGGISH, true);
            }

            void Register()
            {
                OnHit += SpellHitFn(spell_warr_glyph_of_hindering_strikes_SpellScript::HandleOnHit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warr_glyph_of_hindering_strikes_SpellScript();
        }
};

// Stampeding Shout - 122294
class spell_warr_stampeding_shout : public SpellScriptLoader
{
    public:
        spell_warr_stampeding_shout() : SpellScriptLoader("spell_warr_stampeding_shout") { }

        class spell_warr_stampeding_shout_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warr_stampeding_shout_SpellScript);

            void HandleOnHit()
            {
                if (Player* _player = GetCaster()->ToPlayer())
                    if (Unit* target = GetHitUnit())
                        target->RemoveMovementImpairingAuras();
            }

            void Register()
            {
                OnHit += SpellHitFn(spell_warr_stampeding_shout_SpellScript::HandleOnHit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warr_stampeding_shout_SpellScript();
        }
};

// Shield Barrier - 112048
class spell_warr_shield_barrier : public SpellScriptLoader
{
    public:
        spell_warr_shield_barrier() : SpellScriptLoader("spell_warr_shield_barrier") { }

        class spell_warr_shield_barrier_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_warr_shield_barrier_AuraScript);

            void CalculateAmount(constAuraEffectPtr /*aurEff*/, int32 & amount, bool & /*canBeRecalculated*/)
            {
                if (GetCaster())
                {
                    int32 rage = int32(GetCaster()->GetPower(POWER_RAGE) / 10);
                    int32 AP = int32(GetCaster()->GetTotalAttackPowerValue(BASE_ATTACK));
                    int32 Strength = int32(GetCaster()->GetStat(STAT_STRENGTH));
                    int32 Stamina = int32(GetCaster()->GetStat(STAT_STAMINA));

                    amount += std::max(int32(2 * (AP - 2 * (Strength - 10))), int32(Stamina * 2.5f)) * (std::min(60, rage) / 20);

                    GetCaster()->SetPower(POWER_RAGE, GetCaster()->GetPower(POWER_RAGE) - std::min(60, rage) * 10);
                }
            }

            void Register()
            {
                DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_warr_shield_barrier_AuraScript::CalculateAmount, EFFECT_0, SPELL_AURA_SCHOOL_ABSORB);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_warr_shield_barrier_AuraScript();
        }
};

// Shield Block - 2565
class spell_warr_shield_block : public SpellScriptLoader
{
    public:
        spell_warr_shield_block() : SpellScriptLoader("spell_warr_shield_block") { }

        class spell_warr_shield_block_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warr_shield_block_SpellScript);

            void HandleOnHit()
            {
                if (Player* _player = GetCaster()->ToPlayer())
                    _player->CastSpell(_player, WARRIOR_SPELL_SHIELD_BLOCK_TRIGGERED, true);
            }

            void Register()
            {
                OnHit += SpellHitFn(spell_warr_shield_block_SpellScript::HandleOnHit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warr_shield_block_SpellScript();
        }
};

// Storm Bolt - 107570
class spell_warr_storm_bolt : public SpellScriptLoader
{
    public:
        spell_warr_storm_bolt() : SpellScriptLoader("spell_warr_storm_bolt") { }

        class spell_warr_storm_bolt_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warr_storm_bolt_SpellScript);

            void HandleOnHit()
            {
                if (Player* _player = GetCaster()->ToPlayer())
                {
                    if (Unit* unitTarget = GetHitUnit())
                    {
                        if (unitTarget->IsImmunedToSpellEffect(sSpellMgr->GetSpellInfo(WARRIOR_SPELL_STORM_BOLT_STUN), 0))
                            SetHitDamage(GetHitDamage() * 4);

                        _player->CastSpell(unitTarget, WARRIOR_SPELL_STORM_BOLT_STUN, true);
                    }
                }
            }

            void Register()
            {
                OnHit += SpellHitFn(spell_warr_storm_bolt_SpellScript::HandleOnHit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warr_storm_bolt_SpellScript();
        }
};

// Colossus Smash - 86346
class spell_warr_colossus_smash : public SpellScriptLoader
{
    public:
        spell_warr_colossus_smash() : SpellScriptLoader("spell_warr_colossus_smash") { }

        class spell_warr_colossus_smash_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warr_colossus_smash_SpellScript);

            void HandleOnHit()
            {
                if (Player* _player = GetCaster()->ToPlayer())
                    if (Unit* target = GetHitUnit())
                        _player->CastSpell(target, WARRIOR_SPELL_PHYSICAL_VULNERABILITY, true);
            }

            void Register()
            {
                OnHit += SpellHitFn(spell_warr_colossus_smash_SpellScript::HandleOnHit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warr_colossus_smash_SpellScript();
        }
};

// Called by Raging Blow - 85288
// Meat Cleaver - 85739
class spell_warr_meat_cleaver : public SpellScriptLoader
{
    public:
        spell_warr_meat_cleaver() : SpellScriptLoader("spell_warr_meat_cleaver") { }

        class spell_warr_meat_cleaver_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warr_meat_cleaver_SpellScript);

            void HandleOnHit()
            {
                if (Player* _player = GetCaster()->ToPlayer())
                    if (_player->HasAura(WARRIOR_SPELL_MEAT_CLEAVER_PROC))
                        _player->RemoveAura(WARRIOR_SPELL_MEAT_CLEAVER_PROC);
            }

            void Register()
            {
                OnHit += SpellHitFn(spell_warr_meat_cleaver_SpellScript::HandleOnHit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warr_meat_cleaver_SpellScript();
        }
};

// Dragon Roar - 118000
class spell_warr_dragon_roar : public SpellScriptLoader
{
    public:
        spell_warr_dragon_roar() : SpellScriptLoader("spell_warr_dragon_roar") { }

        class spell_warr_dragon_roar_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warr_dragon_roar_SpellScript);

            void HandleAfterHit()
            {
                if (Player* _player = GetCaster()->ToPlayer())
                    if (Unit* target = GetHitUnit())
                        _player->CastSpell(target, WARRIOR_SPELL_DRAGON_ROAR_KNOCK_BACK, true);
            }

            void Register()
            {
                AfterHit += SpellHitFn(spell_warr_dragon_roar_SpellScript::HandleAfterHit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warr_dragon_roar_SpellScript();
        }
};

// Staggering Shout - 107566
class spell_warr_staggering_shout : public SpellScriptLoader
{
    public:
        spell_warr_staggering_shout() : SpellScriptLoader("spell_warr_staggering_shout") { }

        class spell_warr_staggering_shout_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warr_staggering_shout_SpellScript);

            void RemoveInvalidTargets(std::list<WorldObject*>& targets)
            {
                targets.remove_if(JadeCore::UnitAuraTypeCheck(false, SPELL_AURA_MOD_DECREASE_SPEED));
            }

            void Register()
            {
                OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_warr_staggering_shout_SpellScript::RemoveInvalidTargets, EFFECT_0, TARGET_UNIT_SRC_AREA_ENEMY);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warr_staggering_shout_SpellScript();
        }
};

// Frenzied Regeneration - 55694
class spell_warr_frenzied_regeneration : public SpellScriptLoader
{
    public:
        spell_warr_frenzied_regeneration() : SpellScriptLoader("spell_warr_frenzied_regeneration") { }

        class spell_warr_frenzied_regeneration_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warr_frenzied_regeneration_SpellScript);

            void HandleOnHit()
            {
                if (Player* _player = GetCaster()->ToPlayer())
                    if (_player->HasAuraState(AURA_STATE_ENRAGE))
                        _player->EnergizeBySpell(_player, GetSpellInfo()->Id, 600, POWER_RAGE);
            }

            void Register()
            {
                OnHit += SpellHitFn(spell_warr_frenzied_regeneration_SpellScript::HandleOnHit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warr_frenzied_regeneration_SpellScript();
        }
};

// Second Wind - 29838
class spell_warr_second_wind : public SpellScriptLoader
{
    public:
        spell_warr_second_wind() : SpellScriptLoader("spell_warr_second_wind") { }

        class spell_warr_second_wind_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warr_second_wind_SpellScript);

            void HandleOnHit()
            {
                if (Player* _player = GetCaster()->ToPlayer())
                    _player->CastSpell(_player, WARRIOR_SPELL_SECOND_WIND_REGEN, true);
            }

            void Register()
            {
                OnHit += SpellHitFn(spell_warr_second_wind_SpellScript::HandleOnHit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warr_second_wind_SpellScript();
        }

        class spell_warr_second_wind_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_warr_second_wind_AuraScript);

            void OnRemove(constAuraEffectPtr aurEff, AuraEffectHandleModes /*mode*/)
            {
                if (Unit* caster = GetCaster())
                    if (caster->HasAura(WARRIOR_SPELL_SECOND_WIND_REGEN))
                        caster->RemoveAura(WARRIOR_SPELL_SECOND_WIND_REGEN);
            }

            void Register()
            {
                OnEffectRemove += AuraEffectRemoveFn(spell_warr_second_wind_AuraScript::OnRemove, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_warr_second_wind_AuraScript();
        }
};

// Called by Heroic Strike - 78 and Cleave - 845
// Taste for Blood (damage done) - 125831
class spell_warr_taste_for_blood_aura : public SpellScriptLoader
{
    public:
        spell_warr_taste_for_blood_aura() : SpellScriptLoader("spell_warr_taste_for_blood_aura") { }

        class spell_warr_taste_for_blood_aura_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warr_taste_for_blood_aura_SpellScript);

            void HandleOnHit()
            {
                if (Player* _player = GetCaster()->ToPlayer())
                {
                    if (Unit* target = GetHitUnit())
                    {
                        // Hotfix (2012-12-11): "Taste for Blood now only stacks 1 time versus other players (was 3 times)."
                        // Patch 5.1.0 (2012-11-27): Will now stack up to 3 times in PvP. It will continue to stack to 5 in other situations.

                        int32 stacks = 0;

                        if (AuraPtr tasteForBlood = _player->GetAura(WARRIOR_SPELL_TASTE_FOR_BLOOD_DAMAGE_DONE))
                            stacks = tasteForBlood->GetStackAmount();

                        stacks++;

                        if (_player->HasAura(WARRIOR_SPELL_TASTE_FOR_BLOOD_DAMAGE_DONE))
                            _player->RemoveAura(WARRIOR_SPELL_TASTE_FOR_BLOOD_DAMAGE_DONE);

                        if (target->GetTypeId() == TYPEID_PLAYER)
                            if (stacks > 2)
                                SetHitDamage(int32(GetHitDamage() / stacks) * 2);
                    }
                }
            }

            void Register()
            {
                OnHit += SpellHitFn(spell_warr_taste_for_blood_aura_SpellScript::HandleOnHit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warr_taste_for_blood_aura_SpellScript();
        }
};

// Called by Overpower - 7384
// Taste for Blood - 56638
class spell_warr_taste_for_blood : public SpellScriptLoader
{
    public:
        spell_warr_taste_for_blood() : SpellScriptLoader("spell_warr_taste_for_blood") { }

        class spell_warr_taste_for_blood_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warr_taste_for_blood_SpellScript);

            bool rolled;

            void HandleOnHit()
            {
                rolled = false;

                if (Player* _player = GetCaster()->ToPlayer())
                {
                    if (Unit* target = GetHitUnit())
                    {
                        if (_player->HasAura(WARRIOR_SPELL_TASTE_FOR_BLOOD))
                        {
                            if (roll_chance_i(30))
                            {
                                rolled = true;
                                // Increase damage of next Heroic Strike or Slam
                                _player->CastSpell(_player, WARRIOR_SPELL_TASTE_FOR_BLOOD_DAMAGE_DONE, true);
                            }
                        }
                    }
                }
            }

            void HandleAfterHit()
            {
                if (Player* _player = GetCaster()->ToPlayer())
                {
                    if (Unit* target = GetHitUnit())
                    {
                        if (_player->HasAura(WARRIOR_SPELL_TASTE_FOR_BLOOD))
                        {
                            if (rolled)
                            {
                                // Second chance to allow overpower !
                                _player->AddComboPoints(target, 1);
                                _player->StartReactiveTimer(REACTIVE_OVERPOWER);
                                _player->CastSpell(_player, WARRIOR_SPELL_ALLOW_OVERPOWER, true);
                            }
                        }
                    }
                }
            }

            void Register()
            {
                OnHit += SpellHitFn(spell_warr_taste_for_blood_SpellScript::HandleOnHit);
                AfterHit += SpellHitFn(spell_warr_taste_for_blood_SpellScript::HandleAfterHit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warr_taste_for_blood_SpellScript();
        }
};

// Sudden Death - 52437
class spell_warr_sudden_death : public SpellScriptLoader
{
    public:
        spell_warr_sudden_death() : SpellScriptLoader("spell_warr_sudden_death") { }

        class spell_warr_sudden_death_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warr_sudden_death_SpellScript);

            void HandleOnHit()
            {
                if (Player* _player = GetCaster()->ToPlayer())
                    if (_player->HasSpellCooldown(WARRIOR_SPELL_COLOSSUS_SMASH))
                        _player->RemoveSpellCooldown(WARRIOR_SPELL_COLOSSUS_SMASH, true);
            }

            void Register()
            {
                OnHit += SpellHitFn(spell_warr_sudden_death_SpellScript::HandleOnHit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warr_sudden_death_SpellScript();
        }
};

// Berzerker Rage - 18499
class spell_warr_berzerker_rage : public SpellScriptLoader
{
    public:
        spell_warr_berzerker_rage() : SpellScriptLoader("spell_warr_berzerker_rage") { }

        class spell_warr_berzerker_rage_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warr_berzerker_rage_SpellScript);

            void HandleOnHit()
            {
                if (Player* _player = GetCaster()->ToPlayer())
                {
                    _player->CastSpell(_player, WARRIOR_SPELL_ENRAGE, true);
                    _player->CastSpell(_player, WARRIOR_SPELL_BERZERKER_RAGE_EFFECT, true);
                }
            }

            void Register()
            {
                OnHit += SpellHitFn(spell_warr_berzerker_rage_SpellScript::HandleOnHit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warr_berzerker_rage_SpellScript();
        }
};

// Mocking Banner - 114192
class spell_warr_mocking_banner : public SpellScriptLoader
{
    public:
        spell_warr_mocking_banner() : SpellScriptLoader("spell_warr_mocking_banner") { }

        class spell_warr_mocking_banner_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_warr_mocking_banner_AuraScript);

            void OnTick(constAuraEffectPtr aurEff)
            {
                if (Player* player = GetTarget()->ToPlayer())
                {
                    std::list<Creature*> bannerList;
                    std::list<Creature*> tempList;

                    GetTarget()->GetCreatureListWithEntryInGrid(tempList, WARRIOR_NPC_MOCKING_BANNER, 30.0f);

                    bannerList = tempList;

                    // Remove other players banners
                    for (auto itr : tempList)
                    {
                        Unit* owner = itr->GetOwner();
                        if (owner && owner == player && itr->isSummon())
                            continue;

                        bannerList.remove(itr);
                    }

                    for (auto itr : bannerList)
                        player->CastSpell(itr, WARRIOR_SPELL_MOCKING_BANNER_TAUNT, true);
                }
            }

            void Register()
            {
                OnEffectPeriodic += AuraEffectPeriodicFn(spell_warr_mocking_banner_AuraScript::OnTick, EFFECT_1, SPELL_AURA_PERIODIC_DUMMY);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_warr_mocking_banner_AuraScript();
        }
};

// Called by the proc of Enrage - 12880
// Raging Blow (allow to use it) - 131116
class spell_warr_raging_blow : public SpellScriptLoader
{
    public:
        spell_warr_raging_blow() : SpellScriptLoader("spell_warr_raging_blow") { }

        class spell_warr_raging_blow_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warr_raging_blow_SpellScript);

            void HandleOnHit()
            {
                if (Player* _player = GetCaster()->ToPlayer())
                    if (_player->GetSpecializationId(_player->GetActiveSpec()) == SPEC_WARRIOR_FURY && _player->getLevel() >= 30)
                        _player->CastSpell(_player, WARRIOR_SPELL_ALLOW_RAGING_BLOW, true);
            }

            void Register()
            {
                OnHit += SpellHitFn(spell_warr_raging_blow_SpellScript::HandleOnHit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warr_raging_blow_SpellScript();
        }
};

// Called by Devastate - 20243
// Sword and Board - 46953
class spell_warr_sword_and_board : public SpellScriptLoader
{
    public:
        spell_warr_sword_and_board() : SpellScriptLoader("spell_warr_sword_and_board") { }

        class spell_warr_sword_and_board_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warr_sword_and_board_SpellScript);

            void HandleOnHit()
            {
                // Fix Sword and Board
                if (Player* _player = GetCaster()->ToPlayer())
                {
                    if (Unit* target = GetHitUnit())
                    {
                        if (roll_chance_i(30))
                        {
                            _player->CastSpell(_player, WARRIOR_SPELL_SWORD_AND_BOARD, true);
                            _player->RemoveSpellCooldown(WARRIOR_SPELL_SHIELD_SLAM, true);
                        }
                    }
                }
            }

            void Register()
            {
                OnHit += SpellHitFn(spell_warr_sword_and_board_SpellScript::HandleOnHit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warr_sword_and_board_SpellScript();
        }
};

// Mortal strike - 12294
class spell_warr_mortal_strike : public SpellScriptLoader
{
    public:
        spell_warr_mortal_strike() : SpellScriptLoader("spell_warr_mortal_strike") { }

        class spell_warr_mortal_strike_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warr_mortal_strike_SpellScript);

            void HandleOnHit()
            {
                // Fix Apply Mortal strike buff on player only if he has the correct glyph
                if (Player* _player = GetCaster()->ToPlayer())
                {
                    if (Unit* target = GetHitUnit())
                    {
                        if (_player->HasAura(WARRIOR_SPELL_MORTAL_STRIKE_AURA))
                            if (!_player->HasAura(WARRIOR_SPELL_GLYPH_OF_MORTAL_STRIKE))
                                _player->RemoveAura(WARRIOR_SPELL_MORTAL_STRIKE_AURA);

                        if (_player->HasAura(WARRIOR_SPELL_TASTE_FOR_BLOOD))
                        {
                            _player->AddComboPoints(target, 1);
                            _player->StartReactiveTimer(REACTIVE_OVERPOWER);
                            _player->CastSpell(_player, WARRIOR_SPELL_ALLOW_OVERPOWER, true);
                        }
                    }
                }
            }

            void Register()
            {
                OnHit += SpellHitFn(spell_warr_mortal_strike_SpellScript::HandleOnHit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warr_mortal_strike_SpellScript();
        }
};

// Rallying cry - 97462
class spell_warr_rallying_cry : public SpellScriptLoader
{
    public:
        spell_warr_rallying_cry() : SpellScriptLoader("spell_warr_rallying_cry") { }

        class spell_warr_rallying_cry_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warr_rallying_cry_SpellScript);

            void HandleDummy(SpellEffIndex /*effIndex*/)
            {
                if (Player* _player = GetCaster()->ToPlayer())
                {
                    _player->CastSpell(_player, WARRIOR_SPELL_RALLYING_CRY, true);

                    std::list<Unit*> memberList;
                    _player->GetPartyMembers(memberList);

                    for (auto itr : memberList)
                        if (itr->IsWithinDistInMap(_player, 30.0f))
                            _player->CastSpell(itr, WARRIOR_SPELL_RALLYING_CRY, true);
                }
            }

            void Register()
            {
                OnEffectHit += SpellEffectFn(spell_warr_rallying_cry_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warr_rallying_cry_SpellScript();
        }
};

// Heroic leap - 6544
class spell_warr_heroic_leap : public SpellScriptLoader
{
    public:
        spell_warr_heroic_leap() : SpellScriptLoader("spell_warr_heroic_leap") { }

        class spell_warr_heroic_leap_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warr_heroic_leap_SpellScript);

            std::list<Unit*> targetList;

            SpellCastResult CheckElevation()
            {
                Unit* caster = GetCaster();

                WorldLocation* dest = const_cast<WorldLocation*>(GetExplTargetDest());
                if (!dest)
                    return SPELL_FAILED_DONT_REPORT;

                if (dest->GetPositionZ() > caster->GetPositionZ() + 5.0f)
                    return SPELL_FAILED_NOPATH;
                else if (caster->HasAuraType(SPELL_AURA_MOD_ROOT))
                    return SPELL_FAILED_ROOTED;

                return SPELL_CAST_OK;
            }

            void HandleAfterCast()
            {
                // Item - Warrior PvP Set 4P Bonus
                if (GetCaster()->HasAura(WARRIOR_SPELL_ITEM_PVP_SET_4P_BONUS))
                    GetCaster()->CastSpell(GetCaster(), WARRIOR_SPELL_HEROIC_LEAP_SPEED, true);
            }

            void Register()
            {
                OnCheckCast += SpellCheckCastFn(spell_warr_heroic_leap_SpellScript::CheckElevation);
                AfterCast += SpellCastFn(spell_warr_heroic_leap_SpellScript::HandleAfterCast);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warr_heroic_leap_SpellScript();
        }

        class spell_warr_heroic_leap_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_warr_heroic_leap_AuraScript);

            void OnRemove(constAuraEffectPtr aurEff, AuraEffectHandleModes /*mode*/)
            {
                if (Unit* caster = GetCaster())
                    caster->CastSpell(caster, WARRIOR_SPELL_HEROIC_LEAP_DAMAGE, true);
            }

            void Register()
            {
                OnEffectRemove += AuraEffectRemoveFn(spell_warr_heroic_leap_AuraScript::OnRemove, EFFECT_2, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_warr_heroic_leap_AuraScript();
        }
};

// Heroic Leap (damage) - 52174
class spell_warr_heroic_leap_damage : public SpellScriptLoader
{
    public:
        spell_warr_heroic_leap_damage() : SpellScriptLoader("spell_warr_heroic_leap_damage") { }

        class spell_warr_heroic_leap_damage_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warr_heroic_leap_damage_SpellScript);

            void HandleOnHit()
            {
                if (Unit* caster = GetCaster())
                    SetHitDamage(int32(caster->GetTotalAttackPowerValue(BASE_ATTACK) * 0.5f));
            }

            void Register()
            {
                OnHit += SpellHitFn(spell_warr_heroic_leap_damage_SpellScript::HandleOnHit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warr_heroic_leap_damage_SpellScript();
        }
};

// Shockwave - 46968
class spell_warr_shockwave : public SpellScriptLoader
{
    public:
        spell_warr_shockwave() : SpellScriptLoader("spell_warr_shockwave") { }

        class spell_warr_shockwave_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warr_shockwave_SpellScript);

            void HandleOnHit()
            {
                if (Player* _player = GetCaster()->ToPlayer())
                    if (Unit* target = GetHitUnit())
                        _player->CastSpell(target, WARRIOR_SPELL_SHOCKWAVE_STUN, true);
            }

            void Register()
            {
                OnHit += SpellHitFn(spell_warr_shockwave_SpellScript::HandleOnHit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warr_shockwave_SpellScript();
        }
};

// Bloodthirst - 23881
class spell_warr_bloodthirst : public SpellScriptLoader
{
    public:
        spell_warr_bloodthirst() : SpellScriptLoader("spell_warr_bloodthirst") { }

        class spell_warr_bloodthirst_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warr_bloodthirst_SpellScript);

            bool Validate(SpellInfo const* /*SpellEntry*/)
            {
                if (!sSpellMgr->GetSpellInfo(WARRIOR_SPELL_BLOODTHIRST))
                    return false;
                return true;
            }
            void HandleOnHit()
            {
                if (Player* _player = GetCaster()->ToPlayer())
                    if (Unit* target = GetHitUnit())
                        if (GetHitDamage())
                            _player->CastSpell(_player, WARRIOR_SPELL_BLOODTHIRST_HEAL, true);
            }

            void Register()
            {
                OnHit += SpellHitFn(spell_warr_bloodthirst_SpellScript::HandleOnHit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warr_bloodthirst_SpellScript();
        }
};

// Victory Rush - 34428
class spell_warr_victory_rush : public SpellScriptLoader
{
    public:
        spell_warr_victory_rush() : SpellScriptLoader("spell_warr_victory_rush") { }

        class spell_warr_victory_rush_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warr_victory_rush_SpellScript);

            bool Validate(SpellInfo const* /*SpellEntry*/)
            {
                if (!sSpellMgr->GetSpellInfo(WARRIOR_SPELL_VICTORY_RUSH_DAMAGE))
                    return false;
                return true;
            }
            void HandleOnHit()
            {
                if (Player* _player = GetCaster()->ToPlayer())
                {
                    if (Unit* target = GetHitUnit())
                    {
                        _player->CastSpell(_player, WARRIOR_SPELL_VICTORY_RUSH_HEAL, true);
                        if (_player->HasAura(WARRIOR_SPELL_VICTORIOUS_STATE))
                            _player->RemoveAura(WARRIOR_SPELL_VICTORIOUS_STATE);
                    }
                }
            }

            void Register()
            {
                OnHit += SpellHitFn(spell_warr_victory_rush_SpellScript::HandleOnHit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warr_victory_rush_SpellScript();
        }
};

class spell_warr_last_stand : public SpellScriptLoader
{
    public:
        spell_warr_last_stand() : SpellScriptLoader("spell_warr_last_stand") { }

        class spell_warr_last_stand_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warr_last_stand_SpellScript);

            bool Validate(SpellInfo const* /*spellEntry*/)
            {
                if (!sSpellMgr->GetSpellInfo(WARRIOR_SPELL_LAST_STAND_TRIGGERED))
                    return false;
                return true;
            }

            void HandleDummy(SpellEffIndex /*effIndex*/)
            {
                if (Unit* caster = GetCaster())
                {
                    int32 healthModSpellBasePoints0 = int32(caster->CountPctFromMaxHealth(30));
                    caster->CastCustomSpell(caster, WARRIOR_SPELL_LAST_STAND_TRIGGERED, &healthModSpellBasePoints0, NULL, NULL, true, NULL);
                }
            }

            void Register()
            {
                // add dummy effect spell handler to Last Stand
                OnEffectHit += SpellEffectFn(spell_warr_last_stand_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warr_last_stand_SpellScript();
        }
};

// Thunder Clap - 6343
class spell_warr_thunder_clap : public SpellScriptLoader
{
    public:
        spell_warr_thunder_clap() : SpellScriptLoader("spell_warr_thunder_clap") { }

        class spell_warr_thunder_clap_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warr_thunder_clap_SpellScript);

            void HandleOnHit()
            {
                if (Player* _player = GetCaster()->ToPlayer())
                    if (Unit* target = GetHitUnit())
                        _player->CastSpell(target, WARRIOR_SPELL_WEAKENED_BLOWS, true);
            }

            void Register()
            {
                OnHit += SpellHitFn(spell_warr_thunder_clap_SpellScript::HandleOnHit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warr_thunder_clap_SpellScript();
        }
};

// Called By Thunder Clap - 6343, Mortal Strike - 12294, Bloodthirst - 23881 and Devastate - 20243
// Deep Wounds - 115767
class spell_warr_deep_wounds : public SpellScriptLoader
{
    public:
        spell_warr_deep_wounds() : SpellScriptLoader("spell_warr_deep_wounds") { }

        class spell_warr_deep_wounds_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warr_deep_wounds_SpellScript);

            void HandleOnHit()
            {
                if (Player* _player = GetCaster()->ToPlayer())
                {
                    if (Unit* target = GetHitUnit())
                    {
                        if (_player->getLevel() >= 32)
                        {
                            if (GetSpellInfo()->Id == WARRIOR_SPELL_THUNDER_CLAP && _player->HasAura(WARRIOR_SPELL_BLOOD_AND_THUNDER))
                                _player->CastSpell(target, WARRIOR_SPELL_DEEP_WOUNDS, true);
                            else
                                _player->CastSpell(target, WARRIOR_SPELL_DEEP_WOUNDS, true);
                        }
                    }
                }
            }

            void Register()
            {
                OnHit += SpellHitFn(spell_warr_deep_wounds_SpellScript::HandleOnHit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warr_deep_wounds_SpellScript();
        }
};

enum Charge
{
    SPELL_CHARGE                            = 100,
    SPELL_CHARGE_STUN                       = 7922,
    SPELL_WARBRINGER                        = 103828,
    SPELL_CHARGE_WARBRINGER_STUN            = 105771
};

// Charge - 100
class spell_warr_charge : public SpellScriptLoader
{
    public:
        spell_warr_charge() : SpellScriptLoader("spell_warr_charge") { }

        class spell_warr_charge_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warr_charge_SpellScript);

            bool Validate(SpellInfo const* /*SpellEntry*/)
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_CHARGE))
                    return false;
                return true;
            }

            void HandleCharge(SpellEffIndex /*effIndex*/)
            {
                if (Player* _player = GetCaster()->ToPlayer())
                {
                    if (Unit* target = GetHitUnit())
                    {
                        if (_player->HasAura(SPELL_WARBRINGER))
                            _player->CastSpell(target, SPELL_CHARGE_WARBRINGER_STUN, true);
                        else
                            _player->CastSpell(target, SPELL_CHARGE_STUN, true);

                        if (!_player->HasSpell(WARRIOR_SPELL_DOUBLE_TIME))
                            _player->EnergizeBySpell(_player, GetSpellInfo()->Id, 100, POWER_RAGE);
                    }
                }
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_warr_charge_SpellScript::HandleCharge, EFFECT_0, SPELL_EFFECT_CHARGE);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warr_charge_SpellScript();
        }
};

void AddSC_warrior_spell_scripts()
{
    new spell_warr_victorious_state();
    new spell_warr_glyph_of_hindering_strikes();
    new spell_warr_stampeding_shout();
    new spell_warr_shield_barrier();
    new spell_warr_shield_block();
    new spell_warr_storm_bolt();
    new spell_warr_colossus_smash();
    new spell_warr_meat_cleaver();
    new spell_warr_dragon_roar();
    new spell_warr_staggering_shout();
    new spell_warr_frenzied_regeneration();
    new spell_warr_second_wind();
    new spell_warr_taste_for_blood_aura();
    new spell_warr_taste_for_blood();
    new spell_warr_sudden_death();
    new spell_warr_berzerker_rage();
    new spell_warr_mocking_banner();
    new spell_warr_raging_blow();
    new spell_warr_sword_and_board();
    new spell_warr_mortal_strike();
    new spell_warr_rallying_cry();
    new spell_warr_heroic_leap_damage();
    new spell_warr_heroic_leap();
    new spell_warr_shockwave();
    new spell_warr_bloodthirst();
    new spell_warr_victory_rush();
    new spell_warr_last_stand();
    new spell_warr_thunder_clap();
    new spell_warr_deep_wounds();
    new spell_warr_charge();
}
