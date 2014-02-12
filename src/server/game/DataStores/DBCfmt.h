/*
 * Copyright (C) 2008-2012 TrinityCore <http://www.trinitycore.org/>
 * Copyright (C) 2005-2009 MaNGOS <http://getmangos.com/>
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

#ifndef TRINITY_DBCSFRM_H
#define TRINITY_DBCSFRM_H

// x - skip<uint32>, X - skip<uint8>, s - char*, f - float, i - uint32, b - uint8, d - index (not included)
// n - index (included), l - bool, p - field present in sql dbc, a - field absent in sql dbc

const char Achievementfmt[]="niixsxiixixxiix";
const std::string CustomAchievementfmt="pppaaaapapaappa";
const std::string CustomAchievementIndex = "ID";
const char AchievementCriteriafmt[]="niiiiiiiisiiiiixxiiiiii";
const char AreaTableEntryfmt[]="iiinixxxxxxxisiiiiifxxxxxxxx";
const char AreaGroupEntryfmt[]="niiiiiii";
const char AreaPOIEntryfmt[]="niiiiiiiiiiiffixixxixxx";
const char AreaTriggerEntryfmt[]="nifffxxxfffffxxx";
const char ArmorLocationfmt[]="nfffff";
const char AuctionHouseEntryfmt[]="niiix";
const char BankBagSlotPricesEntryfmt[]="ni";
const char BarberShopStyleEntryfmt[]="nixxxiii";
const char BattlemasterListEntryfmt[]="niiiiiiiiiiixsiiiixxxx";
const char CharStartOutfitEntryfmt[]="diiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiixxxxxxxxxxxxxxxxxxxxxxxxxxxxx";
const char CharTitlesEntryfmt[]="nxsxix";
const char ChatChannelsEntryfmt[]="nixsx";

const char ChrClassesEntryfmt[]="nixsxxxixiiiixxxxx";
const char ChrRacesEntryfmt[]="nxixiixixxxxixsxxxxxixxxxxxxxxxxxxxx";
const char ChrClassesXPowerTypesfmt[]="nii";
const char ChrSpecializationsfmt[]="nsiixixxxxxssx";

const char CinematicSequencesEntryfmt[]="nxxxxxxxxx";
const char CreatureDisplayInfofmt[]="nixxfxxxxxxxxxxxxxx";
const char CreatureModelDatafmt[]="nxxxxxxxxxxxxxffxxxxxxxxxxxxxxxxx";
const char CreatureFamilyfmt[]="nfifiiiiixsx";
const char CreatureSpellDatafmt[]="niiiixxxx";
const char CreatureTypefmt[]="nxx";
const char CurrencyTypesfmt[]="nixxxxiiiix";

const char DestructibleModelDatafmt[]="ixxixxxixxxixxxixxxxxxxx";
const char DungeonEncounterfmt[]="iiixisxx";
const char DurabilityCostsfmt[]="niiiiiiiiiiiiiiiiiiiiiiiiiiiii";
const char DurabilityQualityfmt[]="nf";
const char EmotesEntryfmt[]="nxxiiixx";
const char EmotesTextEntryfmt[]="nxixxxxxxxxxxxxxxxx";
const char FactionEntryfmt[]="niiiiiiiiiiiiiiiiiiffixsxx";
const char FactionTemplateEntryfmt[]="niiiiiiiiiiiii";
const char GameObjectDisplayInfofmt[]="nsxxxxxxxxxxffffffxxx";

const char GemPropertiesEntryfmt[]="nixxix";
const char GlyphPropertiesfmt[]="niii";
const char GlyphSlotfmt[]="nii";

const char GtBarberShopCostBasefmt[]="xf";
const char GtCombatRatingsfmt[]="xf";
const char GtOCTHpPerStaminafmt[]="df";
const char GtChanceToMeleeCritBasefmt[]="xf";
const char GtChanceToMeleeCritfmt[]="xf";
const char GtChanceToSpellCritBasefmt[]="xf";
const char GtChanceToSpellCritfmt[]="xf";
const char GtOCTClassCombatRatingScalarfmt[]="df";
const char GtOCTRegenHPfmt[]="f";
//const char GtOCTRegenMPfmt[]="f";
const char GtRegenMPPerSptfmt[]="xf";
const char GtSpellScalingfmt[]="df";
const char GtOCTBaseHPByClassfmt[]="df";
const char GtOCTBaseMPByClassfmt[]="df";
const char GuildPerkSpellsfmt[]="dii";
const char Holidaysfmt[]="niiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiixxsiix";
const char ImportPriceArmorfmt[]="nffff";
const char ImportPriceQualityfmt[]="nf";
const char ImportPriceShieldfmt[]="nf";
const char ImportPriceWeaponfmt[]="nf";
const char ItemPriceBasefmt[]="diff";
const char ItemReforgefmt[]="nifif";
const char ItemBagFamilyfmt[]="nx";
const char ItemArmorQualityfmt[]="nfffffffi";
const char ItemArmorShieldfmt[]="nifffffff";
const char ItemArmorTotalfmt[]="niffff";
const char ItemClassfmt[]="difx";
const char ItemDamagefmt[]="nfffffffi";
const char ItemDisenchantLootfmt[]="niiiiii";
//const char ItemDisplayTemplateEntryfmt[]="nxxxxxxxxxxixxxxxxxxxxx";
const char ItemLimitCategoryEntryfmt[]="nxii";
const char ItemRandomPropertiesfmt[]="nxiiixxs";
const char ItemRandomSuffixfmt[]="nsxiiiiiiiiii";
const char ItemSetEntryfmt[]="dsiiiiiiiiiixxxxxxxiiiiiiiiiiiiiiiiii";
const char LFGDungeonEntryfmt[]="nxiiiiiiiiixxixixiiiixx";
const char LiquidTypefmt[]="nxxixixxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx";
const char LockEntryfmt[]="niiiiiiiiiiiiiiiiiiiiiiiixxxxxxxx";
const char PhaseEntryfmt[]="nsi";
const char MailTemplateEntryfmt[]="nxs";
const char MapEntryfmt[]="nxixxsixxixiffxiiii";
const char MapDifficultyEntryfmt[]="diisii";
const char MovieEntryfmt[]="nxxxx";
const char MountCapabilityfmt[]="niiiiiii";
const char MountTypefmt[]="niiiiiiiiiiiiiiiiiiiiiiii";
const char NameGenfmt[] = "dsii";
const char OverrideSpellDatafmt[]="niiiiiiiiiixx";
const char QuestSortEntryfmt[]="nx";
const char QuestXPfmt[]="niiiiiiiiii";
const char QuestFactionRewardfmt[]="niiiiiiiiii";
const char PvPDifficultyfmt[]="diiiii";
const char RandomPropertiesPointsfmt[]="niiiiiiiiiiiiiii";
const char ScalingStatDistributionfmt[]="niiiiiiiiiiiiiiiiiiiixi";
const char ScalingStatValuesfmt[]="iniiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii";
const char SkillLinefmt[]="nisxixix";
const char SkillLineAbilityfmt[]="niiiiiiiiiixx";
const char SoundEntriesfmt[]="nxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx";
const char SpecializationSpellsfmt[]="niiix";
const char SpellCastTimefmt[]="nixx";
const char SpellCategoriesEntryfmt[]="dxxiiiiiix";
const char SpellCategoryEntryfmt[]="nixxxx";
const char SpellDifficultyfmt[]="niiii";
const std::string CustomSpellDifficultyfmt="ppppp";
const std::string CustomSpellDifficultyIndex="id";
const char SpellDurationfmt[]="niii";
const char SpellEffectEntryfmt[]="niifiiiffiiiiiifiifiiixixiiiix";
const char SpellEffectScalingEntryfmt[]="xfffn";
const char SpellEntryfmt[]="nssxxixxxiiiiiiiiiiiiiixi";
const std::string CustomSpellEntryfmt="papppppppppppapapaaaaaaaaaaapaaapapppppppaaaaapaapaaaaaaaaaaaaaaaaaappppppppppppppppppppppppppppppppppppaaaaaapppppppppaaapppppppppaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaappppppppapppaaaaappaaaaaaa";
const std::string CustomSpellEntryIndex = "Id";
const char SpellFocusObjectfmt[]="nx";
const char SpellItemEnchantmentfmt[]="nxiiiiiiiiisiiiiiiixxxxxx";
const char SpellItemEnchantmentConditionfmt[]="nbbbbbxxxxxbbbbbbbbbbiiiiiXXXXX";
const char SpellRadiusfmt[]="nfxxf";
const char SpellRangefmt[]="nffffixx";
const char SpellReagentsEntryfmt[]="diiiiiiiiiiiiiiiixx";
const char SpellScalingEntryfmt[]="diiiifixx";
const char SpellTotemsEntryfmt[]="niiii";
const char SpellTargetRestrictionsEntryfmt[]="nixfxiiii";
const char SpellMiscEntryfmt[]="nixiiiiiiiiiiiiiiifiiiii";
const char SpellPowerEntryfmt[]="nixiixxxxffxx";
const char SpellInterruptsEntryfmt[]="dxxixixi";
const char SpellEquippedItemsEntryfmt[]="dxxiii";
const char SpellAuraOptionsEntryfmt[]="nxxiiii";
const char SpellAuraRestrictionsEntryfmt[]="dxxiiiiiiii";
const char SpellCastingRequirementsEntryfmt[]="dixxixi";
const char SpellClassOptionsEntryfmt[]="dxiiixi";
const char SpellCooldownsEntryfmt[]="dxxiii";
const char SpellLevelsEntryfmt[]="dixiii";
const char SpellRuneCostfmt[]="niiiii";
const char SpellShapeshiftEntryfmt[]="nixixx";
const char SpellShapeshiftFormfmt[]="nxxiixiiixxiiiiiiiixx";
const char StableSlotPricesfmt[] = "ni";
const char SummonPropertiesfmt[] = "niiiii";
const char TalentEntryfmt[]="nxixixxxiis";
const char TaxiNodesEntryfmt[]="nifffsiixxx";
const char TaxiPathEntryfmt[]="niii";
const char TaxiPathNodeEntryfmt[]="diiifffiiii";
const char TeamContributionPointsfmt[]="df";
const char TotemCategoryEntryfmt[]="nxii";
const char VehicleEntryfmt[]="nixffffiiiiiiiifffffffffffffffssssfifiixx";
const char VehicleSeatEntryfmt[]="niiffffffffffiiiiiifffffffiiifffiiiiiiiffiiiiixxxxxxxxxxxxxxxxxxxx";
const char WMOAreaTableEntryfmt[]="niiixxxxxiixxxx";
const char WorldMapAreaEntryfmt[]="xinxffffixxxii";
const char WorldMapOverlayEntryfmt[]="nxiiiixxxxxxxxxx";
const char WorldSafeLocsEntryfmt[]="nifffxx";

#endif
