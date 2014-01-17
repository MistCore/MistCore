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

#include "UpdateFieldFlags.h"

uint32 ItemUpdateFieldFlags[CONTAINER_END] =
{
    UF_FLAG_PUBLIC,                                         // OBJECT_FIELD_GUID
    UF_FLAG_PUBLIC,                                         // OBJECT_FIELD_GUID+1
    UF_FLAG_PUBLIC,                                         // OBJECT_FIELD_DATA
    UF_FLAG_PUBLIC,                                         // OBJECT_FIELD_DATA+1
    UF_FLAG_PUBLIC,                                         // OBJECT_FIELD_TYPE
    UF_FLAG_PUBLIC,                                         // OBJECT_FIELD_ENTRY
    UF_FLAG_PUBLIC,                                         // OBJECT_FIELD_SCALE_X
    UF_FLAG_PUBLIC,                                         // ITEM_FIELD_OWNER
    UF_FLAG_PUBLIC,                                         // ITEM_FIELD_OWNER+1
    UF_FLAG_PUBLIC,                                         // ITEM_FIELD_CONTAINED
    UF_FLAG_PUBLIC,                                         // ITEM_FIELD_CONTAINED+1
    UF_FLAG_PUBLIC,                                         // ITEM_FIELD_CREATOR
    UF_FLAG_PUBLIC,                                         // ITEM_FIELD_CREATOR+1
    UF_FLAG_PUBLIC,                                         // ITEM_FIELD_GIFTCREATOR
    UF_FLAG_PUBLIC,                                         // ITEM_FIELD_GIFTCREATOR+1
    UF_FLAG_OWNER | UF_FLAG_ITEM_OWNER,                     // ITEM_FIELD_STACK_COUNT
    UF_FLAG_OWNER | UF_FLAG_ITEM_OWNER,                     // ITEM_FIELD_DURATION
    UF_FLAG_OWNER | UF_FLAG_ITEM_OWNER,                     // ITEM_FIELD_SPELL_CHARGES
    UF_FLAG_OWNER | UF_FLAG_ITEM_OWNER,                     // ITEM_FIELD_SPELL_CHARGES+1
    UF_FLAG_OWNER | UF_FLAG_ITEM_OWNER,                     // ITEM_FIELD_SPELL_CHARGES+2
    UF_FLAG_OWNER | UF_FLAG_ITEM_OWNER,                     // ITEM_FIELD_SPELL_CHARGES+3
    UF_FLAG_OWNER | UF_FLAG_ITEM_OWNER,                     // ITEM_FIELD_SPELL_CHARGES+4
    UF_FLAG_PUBLIC,                                         // ITEM_FIELD_FLAGS
    UF_FLAG_PUBLIC,                                         // ITEM_FIELD_ENCHANTMENT_1_1
    UF_FLAG_PUBLIC,                                         // ITEM_FIELD_ENCHANTMENT_1_1+1
    UF_FLAG_PUBLIC,                                         // ITEM_FIELD_ENCHANTMENT_1_3
    UF_FLAG_PUBLIC,                                         // ITEM_FIELD_ENCHANTMENT_2_1
    UF_FLAG_PUBLIC,                                         // ITEM_FIELD_ENCHANTMENT_2_1+1
    UF_FLAG_PUBLIC,                                         // ITEM_FIELD_ENCHANTMENT_2_3
    UF_FLAG_PUBLIC,                                         // ITEM_FIELD_ENCHANTMENT_3_1
    UF_FLAG_PUBLIC,                                         // ITEM_FIELD_ENCHANTMENT_3_1+1
    UF_FLAG_PUBLIC,                                         // ITEM_FIELD_ENCHANTMENT_3_3
    UF_FLAG_PUBLIC,                                         // ITEM_FIELD_ENCHANTMENT_4_1
    UF_FLAG_PUBLIC,                                         // ITEM_FIELD_ENCHANTMENT_4_1+1
    UF_FLAG_PUBLIC,                                         // ITEM_FIELD_ENCHANTMENT_4_3
    UF_FLAG_PUBLIC,                                         // ITEM_FIELD_ENCHANTMENT_5_1
    UF_FLAG_PUBLIC,                                         // ITEM_FIELD_ENCHANTMENT_5_1+1
    UF_FLAG_PUBLIC,                                         // ITEM_FIELD_ENCHANTMENT_5_3
    UF_FLAG_PUBLIC,                                         // ITEM_FIELD_ENCHANTMENT_6_1
    UF_FLAG_PUBLIC,                                         // ITEM_FIELD_ENCHANTMENT_6_1+1
    UF_FLAG_PUBLIC,                                         // ITEM_FIELD_ENCHANTMENT_6_3
    UF_FLAG_PUBLIC,                                         // ITEM_FIELD_ENCHANTMENT_7_1
    UF_FLAG_PUBLIC,                                         // ITEM_FIELD_ENCHANTMENT_7_1+1
    UF_FLAG_PUBLIC,                                         // ITEM_FIELD_ENCHANTMENT_7_3
    UF_FLAG_PUBLIC,                                         // ITEM_FIELD_ENCHANTMENT_8_1
    UF_FLAG_PUBLIC,                                         // ITEM_FIELD_ENCHANTMENT_8_1+1
    UF_FLAG_PUBLIC,                                         // ITEM_FIELD_ENCHANTMENT_8_3
    UF_FLAG_PUBLIC,                                         // ITEM_FIELD_ENCHANTMENT_9_1
    UF_FLAG_PUBLIC,                                         // ITEM_FIELD_ENCHANTMENT_9_1+1
    UF_FLAG_PUBLIC,                                         // ITEM_FIELD_ENCHANTMENT_9_3
    UF_FLAG_PUBLIC,                                         // ITEM_FIELD_ENCHANTMENT_10_1
    UF_FLAG_PUBLIC,                                         // ITEM_FIELD_ENCHANTMENT_10_1+1
    UF_FLAG_PUBLIC,                                         // ITEM_FIELD_ENCHANTMENT_10_3
    UF_FLAG_PUBLIC,                                         // ITEM_FIELD_ENCHANTMENT_11_1
    UF_FLAG_PUBLIC,                                         // ITEM_FIELD_ENCHANTMENT_11_1+1
    UF_FLAG_PUBLIC,                                         // ITEM_FIELD_ENCHANTMENT_11_3
    UF_FLAG_PUBLIC,                                         // ITEM_FIELD_ENCHANTMENT_12_1
    UF_FLAG_PUBLIC,                                         // ITEM_FIELD_ENCHANTMENT_12_1+1
    UF_FLAG_PUBLIC,                                         // ITEM_FIELD_ENCHANTMENT_12_3
    UF_FLAG_PUBLIC,                                         // ITEM_FIELD_ENCHANTMENT_13_1
    UF_FLAG_PUBLIC,                                         // ITEM_FIELD_ENCHANTMENT_13_1+1
    UF_FLAG_PUBLIC,                                         // ITEM_FIELD_ENCHANTMENT_13_3
    UF_FLAG_PUBLIC,                                         // ITEM_FIELD_PROPERTY_SEED
    UF_FLAG_PUBLIC,                                         // ITEM_FIELD_RANDOM_PROPERTIES_ID
    UF_FLAG_OWNER | UF_FLAG_ITEM_OWNER,                     // ITEM_FIELD_DURABILITY
    UF_FLAG_OWNER | UF_FLAG_ITEM_OWNER,                     // ITEM_FIELD_MAXDURABILITY
    UF_FLAG_PUBLIC,                                         // ITEM_FIELD_CREATE_PLAYED_TIME
    UF_FLAG_PUBLIC,                                         // ITEM_FIELD_MODIFIERS_MASK
    UF_FLAG_PUBLIC,                                         // CONTAINER_FIELD_SLOT_1
    UF_FLAG_PUBLIC,                                         // CONTAINER_FIELD_SLOT_1+1
    UF_FLAG_PUBLIC,                                         // CONTAINER_FIELD_SLOT_1+2
    UF_FLAG_PUBLIC,                                         // CONTAINER_FIELD_SLOT_1+3
    UF_FLAG_PUBLIC,                                         // CONTAINER_FIELD_SLOT_1+4
    UF_FLAG_PUBLIC,                                         // CONTAINER_FIELD_SLOT_1+5
    UF_FLAG_PUBLIC,                                         // CONTAINER_FIELD_SLOT_1+6
    UF_FLAG_PUBLIC,                                         // CONTAINER_FIELD_SLOT_1+7
    UF_FLAG_PUBLIC,                                         // CONTAINER_FIELD_SLOT_1+8
    UF_FLAG_PUBLIC,                                         // CONTAINER_FIELD_SLOT_1+9
    UF_FLAG_PUBLIC,                                         // CONTAINER_FIELD_SLOT_1+10
    UF_FLAG_PUBLIC,                                         // CONTAINER_FIELD_SLOT_1+11
    UF_FLAG_PUBLIC,                                         // CONTAINER_FIELD_SLOT_1+12
    UF_FLAG_PUBLIC,                                         // CONTAINER_FIELD_SLOT_1+13
    UF_FLAG_PUBLIC,                                         // CONTAINER_FIELD_SLOT_1+14
    UF_FLAG_PUBLIC,                                         // CONTAINER_FIELD_SLOT_1+15
    UF_FLAG_PUBLIC,                                         // CONTAINER_FIELD_SLOT_1+16
    UF_FLAG_PUBLIC,                                         // CONTAINER_FIELD_SLOT_1+17
    UF_FLAG_PUBLIC,                                         // CONTAINER_FIELD_SLOT_1+18
    UF_FLAG_PUBLIC,                                         // CONTAINER_FIELD_SLOT_1+19
    UF_FLAG_PUBLIC,                                         // CONTAINER_FIELD_SLOT_1+20
    UF_FLAG_PUBLIC,                                         // CONTAINER_FIELD_SLOT_1+21
    UF_FLAG_PUBLIC,                                         // CONTAINER_FIELD_SLOT_1+22
    UF_FLAG_PUBLIC,                                         // CONTAINER_FIELD_SLOT_1+23
    UF_FLAG_PUBLIC,                                         // CONTAINER_FIELD_SLOT_1+24
    UF_FLAG_PUBLIC,                                         // CONTAINER_FIELD_SLOT_1+25
    UF_FLAG_PUBLIC,                                         // CONTAINER_FIELD_SLOT_1+26
    UF_FLAG_PUBLIC,                                         // CONTAINER_FIELD_SLOT_1+27
    UF_FLAG_PUBLIC,                                         // CONTAINER_FIELD_SLOT_1+28
    UF_FLAG_PUBLIC,                                         // CONTAINER_FIELD_SLOT_1+29
    UF_FLAG_PUBLIC,                                         // CONTAINER_FIELD_SLOT_1+30
    UF_FLAG_PUBLIC,                                         // CONTAINER_FIELD_SLOT_1+31
    UF_FLAG_PUBLIC,                                         // CONTAINER_FIELD_SLOT_1+32
    UF_FLAG_PUBLIC,                                         // CONTAINER_FIELD_SLOT_1+33
    UF_FLAG_PUBLIC,                                         // CONTAINER_FIELD_SLOT_1+34
    UF_FLAG_PUBLIC,                                         // CONTAINER_FIELD_SLOT_1+35
    UF_FLAG_PUBLIC,                                         // CONTAINER_FIELD_SLOT_1+36
    UF_FLAG_PUBLIC,                                         // CONTAINER_FIELD_SLOT_1+37
    UF_FLAG_PUBLIC,                                         // CONTAINER_FIELD_SLOT_1+38
    UF_FLAG_PUBLIC,                                         // CONTAINER_FIELD_SLOT_1+39
    UF_FLAG_PUBLIC,                                         // CONTAINER_FIELD_SLOT_1+40
    UF_FLAG_PUBLIC,                                         // CONTAINER_FIELD_SLOT_1+41
    UF_FLAG_PUBLIC,                                         // CONTAINER_FIELD_SLOT_1+42
    UF_FLAG_PUBLIC,                                         // CONTAINER_FIELD_SLOT_1+43
    UF_FLAG_PUBLIC,                                         // CONTAINER_FIELD_SLOT_1+44
    UF_FLAG_PUBLIC,                                         // CONTAINER_FIELD_SLOT_1+45
    UF_FLAG_PUBLIC,                                         // CONTAINER_FIELD_SLOT_1+46
    UF_FLAG_PUBLIC,                                         // CONTAINER_FIELD_SLOT_1+47
    UF_FLAG_PUBLIC,                                         // CONTAINER_FIELD_SLOT_1+48
    UF_FLAG_PUBLIC,                                         // CONTAINER_FIELD_SLOT_1+49
    UF_FLAG_PUBLIC,                                         // CONTAINER_FIELD_SLOT_1+50
    UF_FLAG_PUBLIC,                                         // CONTAINER_FIELD_SLOT_1+51
    UF_FLAG_PUBLIC,                                         // CONTAINER_FIELD_SLOT_1+52
    UF_FLAG_PUBLIC,                                         // CONTAINER_FIELD_SLOT_1+53
    UF_FLAG_PUBLIC,                                         // CONTAINER_FIELD_SLOT_1+54
    UF_FLAG_PUBLIC,                                         // CONTAINER_FIELD_SLOT_1+55
    UF_FLAG_PUBLIC,                                         // CONTAINER_FIELD_SLOT_1+56
    UF_FLAG_PUBLIC,                                         // CONTAINER_FIELD_SLOT_1+57
    UF_FLAG_PUBLIC,                                         // CONTAINER_FIELD_SLOT_1+58
    UF_FLAG_PUBLIC,                                         // CONTAINER_FIELD_SLOT_1+59
    UF_FLAG_PUBLIC,                                         // CONTAINER_FIELD_SLOT_1+60
    UF_FLAG_PUBLIC,                                         // CONTAINER_FIELD_SLOT_1+61
    UF_FLAG_PUBLIC,                                         // CONTAINER_FIELD_SLOT_1+62
    UF_FLAG_PUBLIC,                                         // CONTAINER_FIELD_SLOT_1+63
    UF_FLAG_PUBLIC,                                         // CONTAINER_FIELD_SLOT_1+64
    UF_FLAG_PUBLIC,                                         // CONTAINER_FIELD_SLOT_1+65
    UF_FLAG_PUBLIC,                                         // CONTAINER_FIELD_SLOT_1+66
    UF_FLAG_PUBLIC,                                         // CONTAINER_FIELD_SLOT_1+67
    UF_FLAG_PUBLIC,                                         // CONTAINER_FIELD_SLOT_1+68
    UF_FLAG_PUBLIC,                                         // CONTAINER_FIELD_SLOT_1+69
    UF_FLAG_PUBLIC,                                         // CONTAINER_FIELD_SLOT_1+70
    UF_FLAG_PUBLIC,                                         // CONTAINER_FIELD_SLOT_1+71
    UF_FLAG_PUBLIC,                                         // CONTAINER_FIELD_NUM_SLOTS
};

uint32 UnitUpdateFieldFlags[PLAYER_END] =
{
    UF_FLAG_PUBLIC,                                         // OBJECT_FIELD_GUID
    UF_FLAG_PUBLIC,                                         // OBJECT_FIELD_GUID+1
    UF_FLAG_PUBLIC,                                         // OBJECT_FIELD_DATA
    UF_FLAG_PUBLIC,                                         // OBJECT_FIELD_DATA+1
    UF_FLAG_PUBLIC,                                         // OBJECT_FIELD_TYPE
    UF_FLAG_PUBLIC,                                         // OBJECT_FIELD_ENTRY
    UF_FLAG_PUBLIC,                                         // OBJECT_FIELD_SCALE_X
    UF_FLAG_PUBLIC,                                         // UNIT_FIELD_CHARM
    UF_FLAG_PUBLIC,                                         // UNIT_FIELD_CHARM+1
    UF_FLAG_PUBLIC,                                         // UNIT_FIELD_SUMMON
    UF_FLAG_PUBLIC,                                         // UNIT_FIELD_SUMMON+1
    UF_FLAG_PRIVATE,                                        // UNIT_FIELD_CRITTER
    UF_FLAG_PRIVATE,                                        // UNIT_FIELD_CRITTER+1
    UF_FLAG_PUBLIC,                                         // UNIT_FIELD_CHARMEDBY
    UF_FLAG_PUBLIC,                                         // UNIT_FIELD_CHARMEDBY+1
    UF_FLAG_PUBLIC,                                         // UNIT_FIELD_SUMMONEDBY
    UF_FLAG_PUBLIC,                                         // UNIT_FIELD_SUMMONEDBY+1
    UF_FLAG_PUBLIC,                                         // UNIT_FIELD_CREATEDBY
    UF_FLAG_PUBLIC,                                         // UNIT_FIELD_CREATEDBY+1
    UF_FLAG_PUBLIC,                                         // UNIT_FIELD_TARGET
    UF_FLAG_PUBLIC,                                         // UNIT_FIELD_TARGET+1
    UF_FLAG_PUBLIC,                                         // UNIT_FIELD_CHANNEL_OBJECT
    UF_FLAG_PUBLIC,                                         // UNIT_FIELD_CHANNEL_OBJECT+1
	UF_FLAG_PUBLIC,                                         // UNIT_SUMMONED_BY_HOME_REALM
    UF_FLAG_PUBLIC,                                         // UNIT_CHANNEL_SPELL
    UF_FLAG_PUBLIC,                                         // UNIT_FIELD_BYTES_0
	UF_FLAG_PUBLIC,                                         // UNIT_FIELD_OVERRIDE_BYTES_0
    UF_FLAG_PUBLIC,                                         // UNIT_FIELD_HEALTH
    UF_FLAG_PUBLIC,                                         // UNIT_FIELD_POWER1
    UF_FLAG_PUBLIC,                                         // UNIT_FIELD_POWER2
    UF_FLAG_PUBLIC,                                         // UNIT_FIELD_POWER3
    UF_FLAG_PUBLIC,                                         // UNIT_FIELD_POWER4
    UF_FLAG_PUBLIC,                                         // UNIT_FIELD_POWER5
    UF_FLAG_PUBLIC,                                         // UNIT_FIELD_MAXHEALTH
    UF_FLAG_PUBLIC,                                         // UNIT_FIELD_MAXPOWER1
    UF_FLAG_PUBLIC,                                         // UNIT_FIELD_MAXPOWER2
    UF_FLAG_PUBLIC,                                         // UNIT_FIELD_MAXPOWER3
    UF_FLAG_PUBLIC,                                         // UNIT_FIELD_MAXPOWER4
    UF_FLAG_PUBLIC,                                         // UNIT_FIELD_MAXPOWER5
    UF_FLAG_PRIVATE | UF_FLAG_OWNER | UF_FLAG_UNUSED2,      // UNIT_FIELD_POWER_REGEN_FLAT_MODIFIER
    UF_FLAG_PRIVATE | UF_FLAG_OWNER | UF_FLAG_UNUSED2,      // UNIT_FIELD_POWER_REGEN_FLAT_MODIFIER+1
    UF_FLAG_PRIVATE | UF_FLAG_OWNER | UF_FLAG_UNUSED2,      // UNIT_FIELD_POWER_REGEN_FLAT_MODIFIER+2
    UF_FLAG_PRIVATE | UF_FLAG_OWNER | UF_FLAG_UNUSED2,      // UNIT_FIELD_POWER_REGEN_FLAT_MODIFIER+3
    UF_FLAG_PRIVATE | UF_FLAG_OWNER | UF_FLAG_UNUSED2,      // UNIT_FIELD_POWER_REGEN_FLAT_MODIFIER+4
    UF_FLAG_PRIVATE | UF_FLAG_OWNER | UF_FLAG_UNUSED2,      // UNIT_FIELD_POWER_REGEN_INTERRUPTED_FLAT_MODIFIER
    UF_FLAG_PRIVATE | UF_FLAG_OWNER | UF_FLAG_UNUSED2,      // UNIT_FIELD_POWER_REGEN_INTERRUPTED_FLAT_MODIFIER+1
    UF_FLAG_PRIVATE | UF_FLAG_OWNER | UF_FLAG_UNUSED2,      // UNIT_FIELD_POWER_REGEN_INTERRUPTED_FLAT_MODIFIER+2
    UF_FLAG_PRIVATE | UF_FLAG_OWNER | UF_FLAG_UNUSED2,      // UNIT_FIELD_POWER_REGEN_INTERRUPTED_FLAT_MODIFIER+3
    UF_FLAG_PRIVATE | UF_FLAG_OWNER | UF_FLAG_UNUSED2,      // UNIT_FIELD_POWER_REGEN_INTERRUPTED_FLAT_MODIFIER+4
    UF_FLAG_PUBLIC,                                         // UNIT_FIELD_LEVEL
    UF_FLAG_PUBLIC,                                         // UNIT_FIELD_FACTIONTEMPLATE
    UF_FLAG_PUBLIC,                                         // UNIT_VIRTUAL_ITEM_SLOT_ID
    UF_FLAG_PUBLIC,                                         // UNIT_VIRTUAL_ITEM_SLOT_ID+1
    UF_FLAG_PUBLIC,                                         // UNIT_VIRTUAL_ITEM_SLOT_ID+2
    UF_FLAG_PUBLIC,                                         // UNIT_FIELD_FLAGS
    UF_FLAG_PUBLIC,                                         // UNIT_FIELD_FLAGS_2
    UF_FLAG_PUBLIC,                                         // UNIT_FIELD_AURASTATE
    UF_FLAG_PUBLIC,                                         // UNIT_FIELD_BASEATTACKTIME
    UF_FLAG_PUBLIC,                                         // UNIT_FIELD_BASEATTACKTIME+1
    UF_FLAG_PRIVATE,                                        // UNIT_FIELD_RANGEDATTACKTIME
    UF_FLAG_PUBLIC,                                         // UNIT_FIELD_BOUNDINGRADIUS
    UF_FLAG_PUBLIC,                                         // UNIT_FIELD_COMBATREACH
    UF_FLAG_DYNAMIC,                                        // UNIT_FIELD_DISPLAYID
    UF_FLAG_PUBLIC,                                         // UNIT_FIELD_NATIVEDISPLAYID
    UF_FLAG_PUBLIC,                                         // UNIT_FIELD_MOUNTDISPLAYID
    UF_FLAG_PRIVATE | UF_FLAG_OWNER | UF_FLAG_SPECIAL_INFO, // UNIT_FIELD_MINDAMAGE
    UF_FLAG_PRIVATE | UF_FLAG_OWNER | UF_FLAG_SPECIAL_INFO, // UNIT_FIELD_MAXDAMAGE
    UF_FLAG_PRIVATE | UF_FLAG_OWNER | UF_FLAG_SPECIAL_INFO, // UNIT_FIELD_MINOFFHANDDAMAGE
    UF_FLAG_PRIVATE | UF_FLAG_OWNER | UF_FLAG_SPECIAL_INFO, // UNIT_FIELD_MAXOFFHANDDAMAGE
    UF_FLAG_PUBLIC,                                         // UNIT_FIELD_BYTES_1
    UF_FLAG_PUBLIC,                                         // UNIT_FIELD_PETNUMBER
    UF_FLAG_PUBLIC,                                         // UNIT_FIELD_PET_NAME_TIMESTAMP
    UF_FLAG_OWNER,                                          // UNIT_FIELD_PETEXPERIENCE
    UF_FLAG_OWNER,                                          // UNIT_FIELD_PETNEXTLEVELEXP
    UF_FLAG_DYNAMIC,                                        // UNIT_DYNAMIC_FLAGS
    UF_FLAG_PUBLIC,                                         // UNIT_MOD_CAST_SPEED
    UF_FLAG_PUBLIC,                                         // UNIT_MOD_CAST_HASTE
    UF_FLAG_PUBLIC,                                         // UNIT_MOD_HASTE
    UF_FLAG_PUBLIC,                                         // UNIT_MOD_HASTE_REGEN
    UF_FLAG_PUBLIC,                                         // UNIT_CREATED_BY_SPELL
    UF_FLAG_DYNAMIC,                                        // UNIT_NPC_FLAGS
    UF_FLAG_PUBLIC,                                         // UNIT_NPC_EMOTESTATE
    UF_FLAG_PUBLIC,                                         // UNIT_FIELD_STAT0
    UF_FLAG_PRIVATE | UF_FLAG_OWNER,                        // UNIT_FIELD_STAT1
    UF_FLAG_PRIVATE | UF_FLAG_OWNER,                        // UNIT_FIELD_STAT2
    UF_FLAG_PRIVATE | UF_FLAG_OWNER,                        // UNIT_FIELD_STAT3
    UF_FLAG_PRIVATE | UF_FLAG_OWNER,                        // UNIT_FIELD_STAT4
    UF_FLAG_PRIVATE | UF_FLAG_OWNER,                        // UNIT_FIELD_POSSTAT0
    UF_FLAG_PRIVATE | UF_FLAG_OWNER,                        // UNIT_FIELD_POSSTAT1
    UF_FLAG_PRIVATE | UF_FLAG_OWNER,                        // UNIT_FIELD_POSSTAT2
    UF_FLAG_PRIVATE | UF_FLAG_OWNER,                        // UNIT_FIELD_POSSTAT3
    UF_FLAG_PRIVATE | UF_FLAG_OWNER,                        // UNIT_FIELD_POSSTAT4
    UF_FLAG_PRIVATE | UF_FLAG_OWNER,                        // UNIT_FIELD_NEGSTAT0
    UF_FLAG_PRIVATE | UF_FLAG_OWNER,                        // UNIT_FIELD_NEGSTAT1
    UF_FLAG_PRIVATE | UF_FLAG_OWNER,                        // UNIT_FIELD_NEGSTAT2
    UF_FLAG_PRIVATE | UF_FLAG_OWNER,                        // UNIT_FIELD_NEGSTAT3
    UF_FLAG_PRIVATE | UF_FLAG_OWNER,                        // UNIT_FIELD_NEGSTAT4
    UF_FLAG_PRIVATE | UF_FLAG_OWNER | UF_FLAG_SPECIAL_INFO, // UNIT_FIELD_RESISTANCES
    UF_FLAG_PRIVATE | UF_FLAG_OWNER | UF_FLAG_SPECIAL_INFO, // UNIT_FIELD_RESISTANCES+1
    UF_FLAG_PRIVATE | UF_FLAG_OWNER | UF_FLAG_SPECIAL_INFO, // UNIT_FIELD_RESISTANCES+2
    UF_FLAG_PRIVATE | UF_FLAG_OWNER | UF_FLAG_SPECIAL_INFO, // UNIT_FIELD_RESISTANCES+3
    UF_FLAG_PRIVATE | UF_FLAG_OWNER | UF_FLAG_SPECIAL_INFO, // UNIT_FIELD_RESISTANCES+4
    UF_FLAG_PRIVATE | UF_FLAG_OWNER | UF_FLAG_SPECIAL_INFO, // UNIT_FIELD_RESISTANCES+5
    UF_FLAG_PRIVATE | UF_FLAG_OWNER | UF_FLAG_SPECIAL_INFO, // UNIT_FIELD_RESISTANCES+6
    UF_FLAG_PRIVATE | UF_FLAG_OWNER,                        // UNIT_FIELD_RESISTANCEBUFFMODSPOSITIVE
    UF_FLAG_PRIVATE | UF_FLAG_OWNER,                        // UNIT_FIELD_RESISTANCEBUFFMODSPOSITIVE+1
    UF_FLAG_PRIVATE | UF_FLAG_OWNER,                        // UNIT_FIELD_RESISTANCEBUFFMODSPOSITIVE+2
    UF_FLAG_PRIVATE | UF_FLAG_OWNER,                        // UNIT_FIELD_RESISTANCEBUFFMODSPOSITIVE+3
    UF_FLAG_PRIVATE | UF_FLAG_OWNER,                        // UNIT_FIELD_RESISTANCEBUFFMODSPOSITIVE+4
    UF_FLAG_PRIVATE | UF_FLAG_OWNER,                        // UNIT_FIELD_RESISTANCEBUFFMODSPOSITIVE+5
    UF_FLAG_PRIVATE | UF_FLAG_OWNER,                        // UNIT_FIELD_RESISTANCEBUFFMODSPOSITIVE+6
    UF_FLAG_PRIVATE | UF_FLAG_OWNER,                        // UNIT_FIELD_RESISTANCEBUFFMODSNEGATIVE
    UF_FLAG_PRIVATE | UF_FLAG_OWNER,                        // UNIT_FIELD_RESISTANCEBUFFMODSNEGATIVE+1
    UF_FLAG_PRIVATE | UF_FLAG_OWNER,                        // UNIT_FIELD_RESISTANCEBUFFMODSNEGATIVE+2
    UF_FLAG_PRIVATE | UF_FLAG_OWNER,                        // UNIT_FIELD_RESISTANCEBUFFMODSNEGATIVE+3
    UF_FLAG_PRIVATE | UF_FLAG_OWNER,                        // UNIT_FIELD_RESISTANCEBUFFMODSNEGATIVE+4
    UF_FLAG_PRIVATE | UF_FLAG_OWNER,                        // UNIT_FIELD_RESISTANCEBUFFMODSNEGATIVE+5
    UF_FLAG_PRIVATE | UF_FLAG_OWNER,                        // UNIT_FIELD_RESISTANCEBUFFMODSNEGATIVE+6
    UF_FLAG_PUBLIC,                                         // UNIT_FIELD_BASE_MANA
    UF_FLAG_PRIVATE | UF_FLAG_OWNER,                        // UNIT_FIELD_BASE_HEALTH
    UF_FLAG_PUBLIC,                                         // UNIT_FIELD_BYTES_2
    UF_FLAG_PUBLIC,                                         // UNIT_FIELD_ATTACK_POWER
    UF_FLAG_PRIVATE | UF_FLAG_OWNER,                        // UNIT_FIELD_ATTACK_POWER_MOD_POS
    UF_FLAG_PRIVATE | UF_FLAG_OWNER,                        // UNIT_FIELD_ATTACK_POWER_MOD_NEG
    UF_FLAG_PRIVATE | UF_FLAG_OWNER,                        // UNIT_FIELD_ATTACK_POWER_MULTIPLIER
    UF_FLAG_PRIVATE | UF_FLAG_OWNER,                        // UNIT_FIELD_RANGED_ATTACK_POWER
    UF_FLAG_PRIVATE | UF_FLAG_OWNER,                        // UNIT_FIELD_RANGED_ATTACK_POWER_MOD_POS
    UF_FLAG_PRIVATE | UF_FLAG_OWNER,                        // UNIT_FIELD_RANGED_ATTACK_POWER_MOD_NEG
    UF_FLAG_PRIVATE | UF_FLAG_OWNER,                        // UNIT_FIELD_RANGED_ATTACK_POWER_MULTIPLIER
    UF_FLAG_PRIVATE | UF_FLAG_OWNER,                        // UNIT_FIELD_MINRANGEDDAMAGE
    UF_FLAG_PRIVATE | UF_FLAG_OWNER,                        // UNIT_FIELD_MAXRANGEDDAMAGE
    UF_FLAG_PRIVATE | UF_FLAG_OWNER,                        // UNIT_FIELD_POWER_COST_MODIFIER
    UF_FLAG_PRIVATE | UF_FLAG_OWNER,                        // UNIT_FIELD_POWER_COST_MODIFIER+1
    UF_FLAG_PRIVATE | UF_FLAG_OWNER,                        // UNIT_FIELD_POWER_COST_MODIFIER+2
    UF_FLAG_PRIVATE | UF_FLAG_OWNER,                        // UNIT_FIELD_POWER_COST_MODIFIER+3
    UF_FLAG_PRIVATE | UF_FLAG_OWNER,                        // UNIT_FIELD_POWER_COST_MODIFIER+4
    UF_FLAG_PRIVATE | UF_FLAG_OWNER,                        // UNIT_FIELD_POWER_COST_MODIFIER+5
    UF_FLAG_PRIVATE | UF_FLAG_OWNER,                        // UNIT_FIELD_POWER_COST_MODIFIER+6
    UF_FLAG_PRIVATE | UF_FLAG_OWNER,                        // UNIT_FIELD_POWER_COST_MULTIPLIER
    UF_FLAG_PRIVATE | UF_FLAG_OWNER,                        // UNIT_FIELD_POWER_COST_MULTIPLIER+1
    UF_FLAG_PRIVATE | UF_FLAG_OWNER,                        // UNIT_FIELD_POWER_COST_MULTIPLIER+2
    UF_FLAG_PRIVATE | UF_FLAG_OWNER,                        // UNIT_FIELD_POWER_COST_MULTIPLIER+3
    UF_FLAG_PRIVATE | UF_FLAG_OWNER,                        // UNIT_FIELD_POWER_COST_MULTIPLIER+4
    UF_FLAG_PRIVATE | UF_FLAG_OWNER,                        // UNIT_FIELD_POWER_COST_MULTIPLIER+5
    UF_FLAG_PRIVATE | UF_FLAG_OWNER,                        // UNIT_FIELD_POWER_COST_MULTIPLIER+6
    UF_FLAG_PRIVATE | UF_FLAG_OWNER,                        // UNIT_FIELD_MAXHEALTHMODIFIER
    UF_FLAG_PUBLIC,                                         // UNIT_FIELD_HOVERHEIGHT
	UF_FLAG_PUBLIC,                                         // UNIT_FIELD_MINITEMLEVEL
    UF_FLAG_PUBLIC,                                         // UNIT_FIELD_MAXITEMLEVEL
    UF_FLAG_PUBLIC,                                         // UNIT_FIELD_WILD_BATTLE_PET_LEVEL
    UF_FLAG_PUBLIC,                                         // UNIT_FIELD_BATTLE_PET_COMPANION_ID
    UF_FLAG_PUBLIC,                                         // UNIT_FIELD_BATTLE_PET_COMPANION_NAME_TIMESTAMP
    UF_FLAG_NONE,                                           // UNIT_FIELD_PADDING
    UF_FLAG_PUBLIC,                                         // PLAYER_DUEL_ARBITER
    UF_FLAG_PUBLIC,                                         // PLAYER_DUEL_ARBITER+1
    UF_FLAG_PUBLIC,                                         // PLAYER_FLAGS
    UF_FLAG_PUBLIC,                                         // PLAYER_GUILDRANK
    UF_FLAG_PUBLIC,                                         // PLAYER_GUILDDELETE_DATE
    UF_FLAG_PUBLIC,                                         // PLAYER_GUILDLEVEL
    UF_FLAG_PUBLIC,                                         // PLAYER_BYTES
    UF_FLAG_PUBLIC,                                         // PLAYER_BYTES_2
    UF_FLAG_PUBLIC,                                         // PLAYER_BYTES_3
    UF_FLAG_PUBLIC,                                         // PLAYER_DUEL_TEAM
    UF_FLAG_PUBLIC,                                         // PLAYER_GUILD_TIMESTAMP
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_1_1
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_1_2
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_1_3
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_1_3+1
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_1_4
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_2_1
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_2_2
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_2_3
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_2_3+1
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_2_5
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_3_1
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_3_2
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_3_3
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_3_3+1
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_3_5
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_4_1
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_4_2
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_4_3
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_4_3+1
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_4_5
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_5_1
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_5_2
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_5_3
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_5_3+1
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_5_5
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_6_1
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_6_2
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_6_3
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_6_3+1
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_6_5
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_7_1
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_7_2
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_7_3
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_7_3+1
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_7_5
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_8_1
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_8_2
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_8_3
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_8_3+1
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_8_5
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_9_1
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_9_2
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_9_3
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_9_3+1
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_9_5
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_10_1
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_10_2
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_10_3
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_10_3+1
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_10_5
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_11_1
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_11_2
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_11_3
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_11_3+1
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_11_5
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_12_1
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_12_2
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_12_3
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_12_3+1
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_12_5
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_13_1
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_13_2
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_13_3
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_13_3+1
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_13_5
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_14_1
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_14_2
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_14_3
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_14_3+1
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_14_5
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_15_1
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_15_2
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_15_3
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_15_3+1
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_15_5
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_16_1
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_16_2
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_16_3
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_16_3+1
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_16_5
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_17_1
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_17_2
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_17_3
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_17_3+1
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_17_5
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_18_1
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_18_2
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_18_3
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_18_3+1
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_18_5
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_19_1
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_19_2
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_19_3
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_19_3+1
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_19_5
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_20_1
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_20_2
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_20_3
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_20_3+1
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_20_5
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_21_1
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_21_2
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_21_3
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_21_3+1
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_21_5
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_22_1
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_22_2
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_22_3
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_22_3+1
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_22_5
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_23_1
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_23_2
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_23_3
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_23_3+1
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_23_5
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_24_1
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_24_2
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_24_3
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_24_3+1
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_24_5
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_25_1
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_25_2
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_25_3
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_25_3+1
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_25_5
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_26_1
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_26_2
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_26_3
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_26_3+1
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_26_5
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_27_1
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_27_2
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_27_3
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_27_3+1
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_27_5
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_28_1
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_28_2
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_28_3
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_28_3+1
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_28_5
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_29_1
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_29_2
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_29_3
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_29_3+1
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_29_5
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_30_1
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_30_2
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_30_3
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_30_3+1
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_30_5
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_31_1
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_31_2
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_31_3
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_31_3+1
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_31_5
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_32_1
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_32_2
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_32_3
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_32_3+1
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_32_5
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_33_1
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_33_2
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_33_3
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_33_3+1
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_33_5
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_34_1
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_34_2
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_34_3
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_34_3+1
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_34_5
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_35_1
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_35_2
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_35_3
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_35_3+1
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_35_5
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_36_1
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_36_2
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_36_3
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_36_3+1
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_36_5
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_37_1
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_37_2
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_37_3
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_37_3+1
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_37_5
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_38_1
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_38_2
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_38_3
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_38_3+1
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_38_5
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_39_1
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_39_2
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_39_3
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_39_3+1
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_39_5
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_40_1
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_40_2
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_40_3
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_40_3+1
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_40_5
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_41_1
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_41_2
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_41_3
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_41_3+1
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_41_5
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_42_1
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_42_2
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_42_3
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_42_3+1
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_42_5
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_43_1
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_43_2
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_43_3
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_43_3+1
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_43_5
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_44_1
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_44_2
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_44_3
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_44_3+1
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_44_5
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_45_1
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_45_2
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_45_3
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_45_3+1
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_45_5
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_46_1
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_46_2
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_46_3
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_46_3+1
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_46_5
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_47_1
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_47_2
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_47_3
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_47_3+1
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_47_5
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_48_1
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_48_2
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_48_3
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_48_3+1
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_48_5
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_49_1
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_49_2
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_49_3
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_49_3+1
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_49_5
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_50_1
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_50_2
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_50_3
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_50_3+1
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_50_5
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_51_1
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_51_2
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_51_3
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_51_4
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_51_5
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_52_1
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_52_2
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_52_3
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_52_4
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_52_5
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_53_1
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_53_2
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_53_3
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_53_4
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_53_5
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_54_1
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_54_2
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_54_3
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_54_4
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_54_5
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_55_1
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_55_2
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_55_3
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_55_4
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_55_5
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_56_1
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_56_2
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_56_3
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_56_4
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_56_5
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_57_1
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_57_2
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_57_3
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_57_4
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_57_5
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_58_1
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_58_2
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_58_3
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_58_4
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_58_5
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_59_1
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_59_2
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_59_3
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_59_4
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_59_5
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_60_1
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_60_2
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_60_3
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_60_4
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_60_5
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_61_1
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_61_2
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_61_3
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_61_4
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_61_5
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_62_1
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_62_2
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_62_3
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_62_4
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_62_5
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_63_1
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_63_2
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_63_3
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_63_4
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_63_5
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_64_1
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_64_2
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_64_3
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_64_4
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_64_5
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_65_1
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_65_2
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_65_3
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_65_4
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_65_5
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_66_1
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_66_2
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_66_3
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_66_4
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_66_5
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_67_1
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_67_2
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_67_3
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_67_4
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_67_5
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_68_1
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_68_2
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_68_3
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_68_4
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_68_5
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_69_1
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_69_2
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_69_3
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_69_4
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_69_5
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_70_1
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_70_2
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_70_3
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_70_4
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_70_5
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_71_1
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_71_2
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_71_3
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_71_4
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_71_5
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_72_1
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_72_2
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_72_3
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_72_4
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_72_5
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_73_1
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_73_2
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_73_3
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_73_4
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_73_5
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_74_1
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_74_2
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_74_3
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_74_4
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_74_5
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_75_1
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_75_2
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_75_3
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_75_4
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_75_5
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_76_1
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_76_2
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_76_3
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_76_4
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_76_5
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_77_1
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_77_2
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_77_3
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_77_4
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_77_5
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_78_1
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_78_2
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_78_3
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_78_4
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_78_5
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_79_1
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_79_2
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_79_3
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_79_4
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_79_5
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_80_1
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_80_2
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_80_3
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_80_4
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_80_5
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_81_1
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_81_2
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_81_3
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_81_4
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_81_5
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_82_1
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_82_2
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_82_3
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_82_4
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_82_5
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_83_1
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_83_2
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_83_3
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_83_4
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_83_5
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_84_1
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_84_2
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_84_3
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_84_4
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_84_5
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_85_1
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_85_2
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_85_3
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_85_4
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_85_5
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_86_1
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_86_2
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_86_3
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_86_4
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_86_5
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_87_1
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_87_2
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_87_3
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_87_4
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_87_5
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_88_1
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_88_2
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_88_3
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_88_4
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_88_5
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_89_1
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_89_2
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_89_3
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_89_4
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_89_5
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_90_1
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_90_2
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_90_3
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_90_4
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_90_5
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_91_1
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_91_2
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_91_3
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_91_4
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_91_5
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_92_1
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_92_2
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_92_3
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_92_4
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_92_5
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_93_1
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_93_2
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_93_3
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_93_4
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_93_5
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_94_1
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_94_2
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_94_3
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_94_4
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_94_5
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_95_1
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_95_2
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_95_3
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_95_4
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_95_5
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_96_1
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_96_2
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_96_3
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_96_4
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_96_5
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_97_1
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_97_2
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_97_3
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_97_4
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_97_5
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_98_1
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_98_2
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_98_3
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_98_4
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_98_5
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_99_1
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_99_2
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_99_3
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_99_4
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_99_5
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_100_1
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_100_2
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_100_3
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_100_4
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_100_5
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_101_1
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_101_2
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_101_3
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_101_4
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_101_5
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_102_1
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_102_2
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_102_3
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_102_4
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_102_5
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_103_1
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_103_2
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_103_3
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_103_4
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_103_5
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_104_1
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_104_2
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_104_3
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_104_4
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_104_5
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_105_1
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_105_2
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_105_3
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_105_4
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_105_5
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_106_1
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_106_2
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_106_3
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_106_4
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_106_5
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_107_1
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_107_2
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_107_3
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_107_4
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_107_5
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_108_1
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_108_2
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_108_3
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_108_4
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_108_5
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_109_1
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_109_2
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_109_3
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_109_4
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_109_5
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_110_1
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_110_2
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_110_3
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_110_4
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_110_5
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_111_1
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_111_2
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_111_3
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_111_4
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_111_5
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_112_1
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_112_2
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_112_3
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_112_4
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_112_5
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_113_1
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_113_2
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_113_3
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_113_4
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_113_5
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_114_1
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_114_2
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_114_3
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_114_4
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_114_5
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_115_1
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_115_2
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_115_3
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_115_4
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_115_5
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_116_1
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_116_2
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_116_3
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_116_4
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_116_5
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_117_1
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_117_2
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_117_3
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_117_4
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_117_5
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_118_1
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_118_2
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_118_3
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_118_4
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_118_5
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_119_1
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_119_2
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_119_3
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_119_4
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_119_5
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_120_1
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_120_2
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_120_3
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_120_4
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_120_5
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_121_1
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_121_2
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_121_3
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_121_4
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_121_5
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_122_1
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_122_2
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_122_3
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_122_4
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_122_5
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_123_1
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_123_2
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_123_3
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_123_4
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_123_5
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_124_1
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_124_2
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_124_3
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_124_4
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_124_5
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_125_1
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_125_2
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_125_3
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_125_4
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_125_5
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_126_1
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_126_2
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_126_3
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_126_4
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_126_5
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_127_1
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_127_2
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_127_3
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_127_4
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_127_5
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_128_1
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_128_2
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_128_3
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_128_4
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_128_5
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_129_1
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_129_2
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_129_3
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_129_4
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_129_5
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_130_1
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_130_2
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_130_3
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_130_4
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_130_5
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_131_1
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_131_2
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_131_3
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_131_4
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_131_5
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_132_1
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_132_2
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_132_3
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_132_4
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_132_5
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_133_1
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_133_2
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_133_3
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_133_4
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_133_5
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_134_1
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_134_2
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_134_3
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_134_4
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_134_5
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_135_1
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_135_2
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_135_3
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_135_4
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_135_5
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_136_1
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_136_2
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_136_3
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_136_4
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_136_5
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_137_1
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_137_2
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_137_3
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_137_4
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_137_5
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_138_1
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_138_2
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_138_3
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_138_4
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_138_5
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_139_1
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_139_2
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_139_3
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_139_4
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_139_5
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_140_1
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_140_2
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_140_3
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_140_4
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_140_5
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_141_1
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_141_2
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_141_3
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_141_4
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_141_5
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_142_1
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_142_2
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_142_3
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_142_4
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_142_5
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_143_1
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_143_2
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_143_3
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_143_4
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_143_5
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_144_1
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_144_2
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_144_3
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_144_4
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_144_5
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_145_1
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_145_2
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_145_3
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_145_4
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_145_5
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_146_1
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_146_2
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_146_3
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_146_4
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_146_5
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_147_1
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_147_2
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_147_3
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_147_4
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_147_5
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_148_1
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_148_2
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_148_3
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_148_4
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_148_5
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_149_1
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_149_2
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_149_3
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_149_4
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_149_5
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_150_1
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_150_2
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_150_3
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_150_4
    UF_FLAG_PARTY_MEMBER,                                   // PLAYER_QUEST_LOG_150_5	
    UF_FLAG_PUBLIC,                                         // PLAYER_VISIBLE_ITEM_1_ENTRYID
    UF_FLAG_PUBLIC,                                         // PLAYER_VISIBLE_ITEM_1_ENCHANTMENT
    UF_FLAG_PUBLIC,                                         // PLAYER_VISIBLE_ITEM_2_ENTRYID
    UF_FLAG_PUBLIC,                                         // PLAYER_VISIBLE_ITEM_2_ENCHANTMENT
    UF_FLAG_PUBLIC,                                         // PLAYER_VISIBLE_ITEM_3_ENTRYID
    UF_FLAG_PUBLIC,                                         // PLAYER_VISIBLE_ITEM_3_ENCHANTMENT
    UF_FLAG_PUBLIC,                                         // PLAYER_VISIBLE_ITEM_4_ENTRYID
    UF_FLAG_PUBLIC,                                         // PLAYER_VISIBLE_ITEM_4_ENCHANTMENT
    UF_FLAG_PUBLIC,                                         // PLAYER_VISIBLE_ITEM_5_ENTRYID
    UF_FLAG_PUBLIC,                                         // PLAYER_VISIBLE_ITEM_5_ENCHANTMENT
    UF_FLAG_PUBLIC,                                         // PLAYER_VISIBLE_ITEM_6_ENTRYID
    UF_FLAG_PUBLIC,                                         // PLAYER_VISIBLE_ITEM_6_ENCHANTMENT
    UF_FLAG_PUBLIC,                                         // PLAYER_VISIBLE_ITEM_7_ENTRYID
    UF_FLAG_PUBLIC,                                         // PLAYER_VISIBLE_ITEM_7_ENCHANTMENT
    UF_FLAG_PUBLIC,                                         // PLAYER_VISIBLE_ITEM_8_ENTRYID
    UF_FLAG_PUBLIC,                                         // PLAYER_VISIBLE_ITEM_8_ENCHANTMENT
    UF_FLAG_PUBLIC,                                         // PLAYER_VISIBLE_ITEM_9_ENTRYID
    UF_FLAG_PUBLIC,                                         // PLAYER_VISIBLE_ITEM_9_ENCHANTMENT
    UF_FLAG_PUBLIC,                                         // PLAYER_VISIBLE_ITEM_10_ENTRYID
    UF_FLAG_PUBLIC,                                         // PLAYER_VISIBLE_ITEM_10_ENCHANTMENT
    UF_FLAG_PUBLIC,                                         // PLAYER_VISIBLE_ITEM_11_ENTRYID
    UF_FLAG_PUBLIC,                                         // PLAYER_VISIBLE_ITEM_11_ENCHANTMENT
    UF_FLAG_PUBLIC,                                         // PLAYER_VISIBLE_ITEM_12_ENTRYID
    UF_FLAG_PUBLIC,                                         // PLAYER_VISIBLE_ITEM_12_ENCHANTMENT
    UF_FLAG_PUBLIC,                                         // PLAYER_VISIBLE_ITEM_13_ENTRYID
    UF_FLAG_PUBLIC,                                         // PLAYER_VISIBLE_ITEM_13_ENCHANTMENT
    UF_FLAG_PUBLIC,                                         // PLAYER_VISIBLE_ITEM_14_ENTRYID
    UF_FLAG_PUBLIC,                                         // PLAYER_VISIBLE_ITEM_14_ENCHANTMENT
    UF_FLAG_PUBLIC,                                         // PLAYER_VISIBLE_ITEM_15_ENTRYID
    UF_FLAG_PUBLIC,                                         // PLAYER_VISIBLE_ITEM_15_ENCHANTMENT
    UF_FLAG_PUBLIC,                                         // PLAYER_VISIBLE_ITEM_16_ENTRYID
    UF_FLAG_PUBLIC,                                         // PLAYER_VISIBLE_ITEM_16_ENCHANTMENT
    UF_FLAG_PUBLIC,                                         // PLAYER_VISIBLE_ITEM_17_ENTRYID
    UF_FLAG_PUBLIC,                                         // PLAYER_VISIBLE_ITEM_17_ENCHANTMENT
    UF_FLAG_PUBLIC,                                         // PLAYER_VISIBLE_ITEM_18_ENTRYID
    UF_FLAG_PUBLIC,                                         // PLAYER_VISIBLE_ITEM_18_ENCHANTMENT
    UF_FLAG_PUBLIC,                                         // PLAYER_VISIBLE_ITEM_19_ENTRYID
    UF_FLAG_PUBLIC,                                         // PLAYER_VISIBLE_ITEM_19_ENCHANTMENT
    UF_FLAG_PUBLIC,                                         // PLAYER_CHOSEN_TITLE
    UF_FLAG_PUBLIC,                                         // PLAYER_FAKE_INEBRIATION	
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
    UF_FLAG_PRIVATE,                                   // Autogen POWERRR !! ... OSEF
};

uint32 GameObjectUpdateFieldFlags[GAMEOBJECT_END] =
{
    UF_FLAG_PUBLIC,                                         // OBJECT_FIELD_GUID
    UF_FLAG_PUBLIC,                                         // OBJECT_FIELD_GUID+1
    UF_FLAG_PUBLIC,                                         // OBJECT_FIELD_DATA
    UF_FLAG_PUBLIC,                                         // OBJECT_FIELD_DATA+1
    UF_FLAG_PUBLIC,                                         // OBJECT_FIELD_TYPE
    UF_FLAG_PUBLIC,                                         // OBJECT_FIELD_ENTRY
    UF_FLAG_PUBLIC,                                         // OBJECT_FIELD_SCALE_X
    UF_FLAG_PUBLIC,                                         // OBJECT_FIELD_CREATED_BY
    UF_FLAG_PUBLIC,                                         // OBJECT_FIELD_CREATED_BY+1
    UF_FLAG_PUBLIC,                                         // GAMEOBJECT_DISPLAYID
    UF_FLAG_PUBLIC,                                         // GAMEOBJECT_FLAGS
    UF_FLAG_PUBLIC,                                         // GAMEOBJECT_PARENTROTATION
    UF_FLAG_PUBLIC,                                         // GAMEOBJECT_PARENTROTATION+1
    UF_FLAG_PUBLIC,                                         // GAMEOBJECT_PARENTROTATION+2
    UF_FLAG_PUBLIC,                                         // GAMEOBJECT_PARENTROTATION+3
    UF_FLAG_DYNAMIC,                                        // GAMEOBJECT_DYNAMIC
    UF_FLAG_PUBLIC,                                         // GAMEOBJECT_FACTION
    UF_FLAG_PUBLIC,                                         // GAMEOBJECT_LEVEL
    UF_FLAG_PUBLIC,                                         // GAMEOBJECT_BYTES_1
};



uint32 DynamicObjectUpdateFieldFlags[DYNAMICOBJECT_END] =
{
    UF_FLAG_PUBLIC,                                         // OBJECT_FIELD_GUID
    UF_FLAG_PUBLIC,                                         // OBJECT_FIELD_GUID+1
    UF_FLAG_PUBLIC,                                         // OBJECT_FIELD_DATA
    UF_FLAG_PUBLIC,                                         // OBJECT_FIELD_DATA+1
    UF_FLAG_PUBLIC,                                         // OBJECT_FIELD_TYPE
    UF_FLAG_PUBLIC,                                         // OBJECT_FIELD_ENTRY
    UF_FLAG_PUBLIC,                                         // OBJECT_FIELD_SCALE_X
    UF_FLAG_PUBLIC,                                         // DYNAMICOBJECT_CASTER
    UF_FLAG_PUBLIC,                                         // DYNAMICOBJECT_CASTER+1
    UF_FLAG_DYNAMIC,                                        // DYNAMICOBJECT_BYTES
    UF_FLAG_PUBLIC,                                         // DYNAMICOBJECT_SPELLID
    UF_FLAG_PUBLIC,                                         // DYNAMICOBJECT_RADIUS
    UF_FLAG_PUBLIC,                                         // DYNAMICOBJECT_CASTTIME
};

uint32 CorpseUpdateFieldFlags[CORPSE_END] =
{
    UF_FLAG_PUBLIC,                                         // OBJECT_FIELD_GUID
    UF_FLAG_PUBLIC,                                         // OBJECT_FIELD_GUID+1
    UF_FLAG_PUBLIC,                                         // OBJECT_FIELD_DATA
    UF_FLAG_PUBLIC,                                         // OBJECT_FIELD_DATA+1
    UF_FLAG_PUBLIC,                                         // OBJECT_FIELD_TYPE
    UF_FLAG_PUBLIC,                                         // OBJECT_FIELD_ENTRY
    UF_FLAG_PUBLIC,                                         // OBJECT_FIELD_SCALE_X
    UF_FLAG_PUBLIC,                                         // CORPSE_FIELD_OWNER
    UF_FLAG_PUBLIC,                                         // CORPSE_FIELD_OWNER+1
    UF_FLAG_PUBLIC,                                         // CORPSE_FIELD_PARTY
    UF_FLAG_PUBLIC,                                         // CORPSE_FIELD_PARTY+1
    UF_FLAG_PUBLIC,                                         // CORPSE_FIELD_DISPLAY_ID
    UF_FLAG_PUBLIC,                                         // CORPSE_FIELD_ITEM
    UF_FLAG_PUBLIC,                                         // CORPSE_FIELD_ITEM+1
    UF_FLAG_PUBLIC,                                         // CORPSE_FIELD_ITEM+2
    UF_FLAG_PUBLIC,                                         // CORPSE_FIELD_ITEM+3
    UF_FLAG_PUBLIC,                                         // CORPSE_FIELD_ITEM+4
    UF_FLAG_PUBLIC,                                         // CORPSE_FIELD_ITEM+5
    UF_FLAG_PUBLIC,                                         // CORPSE_FIELD_ITEM+6
    UF_FLAG_PUBLIC,                                         // CORPSE_FIELD_ITEM+7
    UF_FLAG_PUBLIC,                                         // CORPSE_FIELD_ITEM+8
    UF_FLAG_PUBLIC,                                         // CORPSE_FIELD_ITEM+9
    UF_FLAG_PUBLIC,                                         // CORPSE_FIELD_ITEM+10
    UF_FLAG_PUBLIC,                                         // CORPSE_FIELD_ITEM+11
    UF_FLAG_PUBLIC,                                         // CORPSE_FIELD_ITEM+12
    UF_FLAG_PUBLIC,                                         // CORPSE_FIELD_ITEM+13
    UF_FLAG_PUBLIC,                                         // CORPSE_FIELD_ITEM+14
    UF_FLAG_PUBLIC,                                         // CORPSE_FIELD_ITEM+15
    UF_FLAG_PUBLIC,                                         // CORPSE_FIELD_ITEM+16
    UF_FLAG_PUBLIC,                                         // CORPSE_FIELD_ITEM+17
    UF_FLAG_PUBLIC,                                         // CORPSE_FIELD_ITEM+18
    UF_FLAG_PUBLIC,                                         // CORPSE_FIELD_BYTES_1
    UF_FLAG_PUBLIC,                                         // CORPSE_FIELD_BYTES_2
    UF_FLAG_PUBLIC,                                         // CORPSE_FIELD_FLAGS
    UF_FLAG_DYNAMIC,                                        // CORPSE_FIELD_DYNAMIC_FLAGS
};

uint32 AreaTriggerUpdateFieldFlags[AREATRIGGER_END] =
{
    UF_FLAG_PUBLIC,                                         // OBJECT_FIELD_GUID
    UF_FLAG_PUBLIC,                                         // OBJECT_FIELD_GUID+1
    UF_FLAG_PUBLIC,                                         // OBJECT_FIELD_DATA
    UF_FLAG_PUBLIC,                                         // OBJECT_FIELD_DATA+1
    UF_FLAG_PUBLIC,                                         // OBJECT_FIELD_TYPE
    UF_FLAG_PUBLIC,                                         // OBJECT_FIELD_ENTRY
    UF_FLAG_PUBLIC,                                         // OBJECT_FIELD_SCALE_X
    UF_FLAG_PUBLIC,                                         // AREATRIGGER_CASTER
    UF_FLAG_PUBLIC,                                         // AREATRIGGER_CASTER+1
    UF_FLAG_PUBLIC,                                         // AREATRIGGER_DURATION
    UF_FLAG_PUBLIC,                                         // AREATRIGGER_SPELLID
    UF_FLAG_PUBLIC,                                         // AREATRIGGER_SPELLVISUALID
};
