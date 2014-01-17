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

#include "SpellAuraDefines.h"
#include "SpellInfo.h"
#include "SpellMgr.h"
#include "Spell.h"
#include "DBCStores.h"
#include "ConditionMgr.h"

uint32 GetTargetFlagMask(SpellTargetObjectTypes objType)
{
    switch (objType)
    {
        case TARGET_OBJECT_TYPE_DEST:
            return TARGET_FLAG_DEST_LOCATION;
        case TARGET_OBJECT_TYPE_UNIT_AND_DEST:
            return TARGET_FLAG_DEST_LOCATION | TARGET_FLAG_UNIT;
        case TARGET_OBJECT_TYPE_CORPSE_ALLY:
            return TARGET_FLAG_CORPSE_ALLY;
        case TARGET_OBJECT_TYPE_CORPSE_ENEMY:
            return TARGET_FLAG_CORPSE_ENEMY;
        case TARGET_OBJECT_TYPE_CORPSE:
            return TARGET_FLAG_CORPSE_ALLY | TARGET_FLAG_CORPSE_ENEMY;
        case TARGET_OBJECT_TYPE_UNIT:
            return TARGET_FLAG_UNIT;
        case TARGET_OBJECT_TYPE_GOBJ:
            return TARGET_FLAG_GAMEOBJECT;
        case TARGET_OBJECT_TYPE_GOBJ_ITEM:
            return TARGET_FLAG_GAMEOBJECT_ITEM;
        case TARGET_OBJECT_TYPE_ITEM:
            return TARGET_FLAG_ITEM;
        case TARGET_OBJECT_TYPE_SRC:
            return TARGET_FLAG_SOURCE_LOCATION;
        default:
            return TARGET_FLAG_NONE;
    }
}

SpellImplicitTargetInfo::SpellImplicitTargetInfo(uint32 target)
{
    _target = Targets(target);
}

bool SpellImplicitTargetInfo::IsArea() const
{
    return GetSelectionCategory() == TARGET_SELECT_CATEGORY_AREA || GetSelectionCategory() == TARGET_SELECT_CATEGORY_CONE;
}

SpellTargetSelectionCategories SpellImplicitTargetInfo::GetSelectionCategory() const
{
    return _data[_target].SelectionCategory;
}

SpellTargetReferenceTypes SpellImplicitTargetInfo::GetReferenceType() const
{
    return _data[_target].ReferenceType;
}

SpellTargetObjectTypes SpellImplicitTargetInfo::GetObjectType() const
{
    return _data[_target].ObjectType;
}

SpellTargetCheckTypes SpellImplicitTargetInfo::GetCheckType() const
{
    return _data[_target].SelectionCheckType;
}

SpellTargetDirectionTypes SpellImplicitTargetInfo::GetDirectionType() const
{
    return _data[_target].DirectionType;
}

float SpellImplicitTargetInfo::CalcDirectionAngle() const
{
    switch (GetDirectionType())
    {
        case TARGET_DIR_FRONT:
            return 0.0f;
        case TARGET_DIR_BACK:
            return static_cast<float>(M_PI);
        case TARGET_DIR_RIGHT:
            return static_cast<float>(-M_PI/2);
        case TARGET_DIR_LEFT:
            return static_cast<float>(M_PI/2);
        case TARGET_DIR_FRONT_RIGHT:
            return static_cast<float>(-M_PI/4);
        case TARGET_DIR_BACK_RIGHT:
            return static_cast<float>(-3*M_PI/4);
        case TARGET_DIR_BACK_LEFT:
            return static_cast<float>(3*M_PI/4);
        case TARGET_DIR_FRONT_LEFT:
            return static_cast<float>(M_PI/4);
        case TARGET_DIR_RANDOM:
            return float(rand_norm())*static_cast<float>(2*M_PI);
        default:
            return 0.0f;
    }
}

Targets SpellImplicitTargetInfo::GetTarget() const
{
    return _target;
}

uint32 SpellImplicitTargetInfo::GetExplicitTargetMask(bool& srcSet, bool& dstSet) const
{
    uint32 targetMask = 0;
    if (GetTarget() == TARGET_DEST_TRAJ)
    {
        if (!srcSet)
            targetMask = TARGET_FLAG_SOURCE_LOCATION;
        if (!dstSet)
            targetMask |= TARGET_FLAG_DEST_LOCATION;
    }
    else
    {
        switch (GetReferenceType())
        {
            case TARGET_REFERENCE_TYPE_SRC:
                if (srcSet)
                    break;
                targetMask = TARGET_FLAG_SOURCE_LOCATION;
                break;
            case TARGET_REFERENCE_TYPE_DEST:
                if (dstSet)
                    break;
                targetMask = TARGET_FLAG_DEST_LOCATION;
                break;
            case TARGET_REFERENCE_TYPE_TARGET:
                switch (GetObjectType())
                {
                    case TARGET_OBJECT_TYPE_GOBJ:
                        targetMask = TARGET_FLAG_GAMEOBJECT;
                        break;
                    case TARGET_OBJECT_TYPE_GOBJ_ITEM:
                        targetMask = TARGET_FLAG_GAMEOBJECT_ITEM;
                        break;
                    case TARGET_OBJECT_TYPE_UNIT_AND_DEST:
                    case TARGET_OBJECT_TYPE_UNIT:
                    case TARGET_OBJECT_TYPE_DEST:
                        switch (GetCheckType())
                        {
                            case TARGET_CHECK_ENEMY:
                                targetMask = TARGET_FLAG_UNIT_ENEMY;
                                break;
                            case TARGET_CHECK_ALLY:
                                targetMask = TARGET_FLAG_UNIT_ALLY;
                                break;
                            case TARGET_CHECK_PARTY:
                                targetMask = TARGET_FLAG_UNIT_PARTY;
                                break;
                            case TARGET_CHECK_RAID:
                                targetMask = TARGET_FLAG_UNIT_RAID;
                                break;
                            case TARGET_CHECK_PASSENGER:
                                targetMask = TARGET_FLAG_UNIT_PASSENGER;
                                break;
                            case TARGET_CHECK_RAID_CLASS:
                                // nobreak;
                            default:
                                targetMask = TARGET_FLAG_UNIT;
                                break;
                        }
                        break;
                    default:
                        break;
                }
                break;
            default:
                break;
        }
    }

    switch (GetObjectType())
    {
        case TARGET_OBJECT_TYPE_SRC:
            srcSet = true;
            break;
        case TARGET_OBJECT_TYPE_DEST:
        case TARGET_OBJECT_TYPE_UNIT_AND_DEST:
            dstSet = true;
            break;
        default:
            break;
    }
    return targetMask;
}

SpellImplicitTargetInfo::StaticData  SpellImplicitTargetInfo::_data[TOTAL_SPELL_TARGETS] =
{
    {TARGET_OBJECT_TYPE_NONE, TARGET_REFERENCE_TYPE_NONE,   TARGET_SELECT_CATEGORY_NYI,     TARGET_CHECK_DEFAULT,  TARGET_DIR_NONE},        // 0
    {TARGET_OBJECT_TYPE_UNIT, TARGET_REFERENCE_TYPE_CASTER, TARGET_SELECT_CATEGORY_DEFAULT, TARGET_CHECK_DEFAULT,  TARGET_DIR_NONE},        // 1 TARGET_UNIT_CASTER
    {TARGET_OBJECT_TYPE_UNIT, TARGET_REFERENCE_TYPE_CASTER, TARGET_SELECT_CATEGORY_NEARBY,  TARGET_CHECK_ENEMY,    TARGET_DIR_NONE},        // 2 TARGET_UNIT_NEARBY_ENEMY
    {TARGET_OBJECT_TYPE_UNIT, TARGET_REFERENCE_TYPE_CASTER, TARGET_SELECT_CATEGORY_NEARBY,  TARGET_CHECK_PARTY,    TARGET_DIR_NONE},        // 3 TARGET_UNIT_NEARBY_PARTY
    {TARGET_OBJECT_TYPE_UNIT, TARGET_REFERENCE_TYPE_CASTER, TARGET_SELECT_CATEGORY_NEARBY,  TARGET_CHECK_ALLY,     TARGET_DIR_NONE},        // 4 TARGET_UNIT_NEARBY_ALLY
    {TARGET_OBJECT_TYPE_UNIT, TARGET_REFERENCE_TYPE_CASTER, TARGET_SELECT_CATEGORY_DEFAULT, TARGET_CHECK_DEFAULT,  TARGET_DIR_NONE},        // 5 TARGET_UNIT_PET
    {TARGET_OBJECT_TYPE_UNIT, TARGET_REFERENCE_TYPE_TARGET, TARGET_SELECT_CATEGORY_DEFAULT, TARGET_CHECK_ENEMY,    TARGET_DIR_NONE},        // 6 TARGET_UNIT_TARGET_ENEMY
    {TARGET_OBJECT_TYPE_UNIT, TARGET_REFERENCE_TYPE_SRC,    TARGET_SELECT_CATEGORY_AREA,    TARGET_CHECK_ENTRY,    TARGET_DIR_NONE},        // 7 TARGET_UNIT_SRC_AREA_ENTRY
    {TARGET_OBJECT_TYPE_UNIT, TARGET_REFERENCE_TYPE_DEST,   TARGET_SELECT_CATEGORY_AREA,    TARGET_CHECK_ENTRY,    TARGET_DIR_NONE},        // 8 TARGET_UNIT_DEST_AREA_ENTRY
    {TARGET_OBJECT_TYPE_DEST, TARGET_REFERENCE_TYPE_CASTER, TARGET_SELECT_CATEGORY_DEFAULT, TARGET_CHECK_DEFAULT,  TARGET_DIR_NONE},        // 9 TARGET_DEST_HOME
    {TARGET_OBJECT_TYPE_NONE, TARGET_REFERENCE_TYPE_NONE,   TARGET_SELECT_CATEGORY_NYI,     TARGET_CHECK_DEFAULT,  TARGET_DIR_NONE},        // 10
    {TARGET_OBJECT_TYPE_UNIT, TARGET_REFERENCE_TYPE_SRC,    TARGET_SELECT_CATEGORY_NYI,     TARGET_CHECK_DEFAULT,  TARGET_DIR_NONE},        // 11 TARGET_UNIT_SRC_AREA_UNK_11
    {TARGET_OBJECT_TYPE_NONE, TARGET_REFERENCE_TYPE_NONE,   TARGET_SELECT_CATEGORY_NYI,     TARGET_CHECK_DEFAULT,  TARGET_DIR_NONE},        // 12
    {TARGET_OBJECT_TYPE_NONE, TARGET_REFERENCE_TYPE_NONE,   TARGET_SELECT_CATEGORY_NYI,     TARGET_CHECK_DEFAULT,  TARGET_DIR_NONE},        // 13
    {TARGET_OBJECT_TYPE_NONE, TARGET_REFERENCE_TYPE_NONE,   TARGET_SELECT_CATEGORY_NYI,     TARGET_CHECK_DEFAULT,  TARGET_DIR_NONE},        // 14
    {TARGET_OBJECT_TYPE_UNIT, TARGET_REFERENCE_TYPE_SRC,    TARGET_SELECT_CATEGORY_AREA,    TARGET_CHECK_ENEMY,    TARGET_DIR_NONE},        // 15 TARGET_UNIT_SRC_AREA_ENEMY
    {TARGET_OBJECT_TYPE_UNIT, TARGET_REFERENCE_TYPE_DEST,   TARGET_SELECT_CATEGORY_AREA,    TARGET_CHECK_ENEMY,    TARGET_DIR_NONE},        // 16 TARGET_UNIT_DEST_AREA_ENEMY
    {TARGET_OBJECT_TYPE_DEST, TARGET_REFERENCE_TYPE_CASTER, TARGET_SELECT_CATEGORY_DEFAULT, TARGET_CHECK_DEFAULT,  TARGET_DIR_NONE},        // 17 TARGET_DEST_DB
    {TARGET_OBJECT_TYPE_DEST, TARGET_REFERENCE_TYPE_CASTER, TARGET_SELECT_CATEGORY_DEFAULT, TARGET_CHECK_DEFAULT,  TARGET_DIR_NONE},        // 18 TARGET_DEST_CASTER
    {TARGET_OBJECT_TYPE_NONE, TARGET_REFERENCE_TYPE_NONE,   TARGET_SELECT_CATEGORY_NYI,     TARGET_CHECK_DEFAULT,  TARGET_DIR_NONE},        // 19
    {TARGET_OBJECT_TYPE_UNIT, TARGET_REFERENCE_TYPE_CASTER, TARGET_SELECT_CATEGORY_AREA,    TARGET_CHECK_PARTY,    TARGET_DIR_NONE},        // 20 TARGET_UNIT_CASTER_AREA_PARTY
    {TARGET_OBJECT_TYPE_UNIT, TARGET_REFERENCE_TYPE_TARGET, TARGET_SELECT_CATEGORY_DEFAULT, TARGET_CHECK_ALLY,     TARGET_DIR_NONE},        // 21 TARGET_UNIT_TARGET_ALLY
    {TARGET_OBJECT_TYPE_SRC,  TARGET_REFERENCE_TYPE_CASTER, TARGET_SELECT_CATEGORY_DEFAULT, TARGET_CHECK_DEFAULT,  TARGET_DIR_NONE},        // 22 TARGET_SRC_CASTER
    {TARGET_OBJECT_TYPE_GOBJ, TARGET_REFERENCE_TYPE_TARGET, TARGET_SELECT_CATEGORY_DEFAULT, TARGET_CHECK_DEFAULT,  TARGET_DIR_NONE},        // 23 TARGET_GAMEOBJECT_TARGET
    {TARGET_OBJECT_TYPE_UNIT, TARGET_REFERENCE_TYPE_CASTER, TARGET_SELECT_CATEGORY_CONE,    TARGET_CHECK_ENEMY,    TARGET_DIR_FRONT},       // 24 TARGET_UNIT_CONE_ENEMY_24
    {TARGET_OBJECT_TYPE_UNIT, TARGET_REFERENCE_TYPE_TARGET, TARGET_SELECT_CATEGORY_DEFAULT, TARGET_CHECK_DEFAULT,  TARGET_DIR_NONE},        // 25 TARGET_UNIT_TARGET_ANY
    {TARGET_OBJECT_TYPE_GOBJ_ITEM, TARGET_REFERENCE_TYPE_TARGET, TARGET_SELECT_CATEGORY_DEFAULT, TARGET_CHECK_DEFAULT, TARGET_DIR_NONE},    // 26 TARGET_GAMEOBJECT_ITEM_TARGET
    {TARGET_OBJECT_TYPE_UNIT, TARGET_REFERENCE_TYPE_CASTER, TARGET_SELECT_CATEGORY_DEFAULT, TARGET_CHECK_DEFAULT,  TARGET_DIR_NONE},        // 27 TARGET_UNIT_MASTER
    {TARGET_OBJECT_TYPE_DEST, TARGET_REFERENCE_TYPE_DEST,   TARGET_SELECT_CATEGORY_DEFAULT, TARGET_CHECK_ENEMY,    TARGET_DIR_NONE},        // 28 TARGET_DEST_DYNOBJ_ENEMY
    {TARGET_OBJECT_TYPE_DEST, TARGET_REFERENCE_TYPE_DEST,   TARGET_SELECT_CATEGORY_DEFAULT, TARGET_CHECK_ALLY,     TARGET_DIR_NONE},        // 29 TARGET_DEST_DYNOBJ_ALLY
    {TARGET_OBJECT_TYPE_UNIT, TARGET_REFERENCE_TYPE_SRC,    TARGET_SELECT_CATEGORY_AREA,    TARGET_CHECK_ALLY,     TARGET_DIR_NONE},        // 30 TARGET_UNIT_SRC_AREA_ALLY
    {TARGET_OBJECT_TYPE_UNIT, TARGET_REFERENCE_TYPE_DEST,   TARGET_SELECT_CATEGORY_AREA,    TARGET_CHECK_ALLY,     TARGET_DIR_NONE},        // 31 TARGET_UNIT_DEST_AREA_ALLY
    {TARGET_OBJECT_TYPE_DEST, TARGET_REFERENCE_TYPE_CASTER, TARGET_SELECT_CATEGORY_DEFAULT, TARGET_CHECK_DEFAULT,  TARGET_DIR_FRONT_LEFT},  // 32 TARGET_DEST_CASTER_SUMMON
    {TARGET_OBJECT_TYPE_UNIT, TARGET_REFERENCE_TYPE_SRC,    TARGET_SELECT_CATEGORY_AREA,    TARGET_CHECK_PARTY,    TARGET_DIR_NONE},        // 33 TARGET_UNIT_SRC_AREA_PARTY
    {TARGET_OBJECT_TYPE_UNIT, TARGET_REFERENCE_TYPE_DEST,   TARGET_SELECT_CATEGORY_AREA,    TARGET_CHECK_PARTY,    TARGET_DIR_NONE},        // 34 TARGET_UNIT_DEST_AREA_PARTY
    {TARGET_OBJECT_TYPE_UNIT, TARGET_REFERENCE_TYPE_TARGET, TARGET_SELECT_CATEGORY_DEFAULT, TARGET_CHECK_PARTY,    TARGET_DIR_NONE},        // 35 TARGET_UNIT_TARGET_PARTY
    {TARGET_OBJECT_TYPE_DEST, TARGET_REFERENCE_TYPE_CASTER, TARGET_SELECT_CATEGORY_NYI,     TARGET_CHECK_DEFAULT,  TARGET_DIR_NONE},        // 36 TARGET_DEST_CASTER_UNK_36
    {TARGET_OBJECT_TYPE_UNIT, TARGET_REFERENCE_TYPE_LAST,   TARGET_SELECT_CATEGORY_AREA,    TARGET_CHECK_PARTY,    TARGET_DIR_NONE},        // 37 TARGET_UNIT_LASTTARGET_AREA_PARTY
    {TARGET_OBJECT_TYPE_UNIT, TARGET_REFERENCE_TYPE_CASTER, TARGET_SELECT_CATEGORY_NEARBY,  TARGET_CHECK_ENTRY,    TARGET_DIR_NONE},        // 38 TARGET_UNIT_NEARBY_ENTRY
    {TARGET_OBJECT_TYPE_DEST, TARGET_REFERENCE_TYPE_CASTER, TARGET_SELECT_CATEGORY_DEFAULT, TARGET_CHECK_DEFAULT,  TARGET_DIR_NONE},        // 39 TARGET_DEST_CASTER_FISHING
    {TARGET_OBJECT_TYPE_GOBJ, TARGET_REFERENCE_TYPE_CASTER, TARGET_SELECT_CATEGORY_NEARBY,  TARGET_CHECK_ENTRY,    TARGET_DIR_NONE},        // 40 TARGET_GAMEOBJECT_NEARBY_ENTRY
    {TARGET_OBJECT_TYPE_DEST, TARGET_REFERENCE_TYPE_CASTER, TARGET_SELECT_CATEGORY_DEFAULT, TARGET_CHECK_DEFAULT,  TARGET_DIR_FRONT_RIGHT}, // 41 TARGET_DEST_CASTER_FRONT_RIGHT
    {TARGET_OBJECT_TYPE_DEST, TARGET_REFERENCE_TYPE_CASTER, TARGET_SELECT_CATEGORY_DEFAULT, TARGET_CHECK_DEFAULT,  TARGET_DIR_BACK_RIGHT},  // 42 TARGET_DEST_CASTER_BACK_RIGHT
    {TARGET_OBJECT_TYPE_DEST, TARGET_REFERENCE_TYPE_CASTER, TARGET_SELECT_CATEGORY_DEFAULT, TARGET_CHECK_DEFAULT,  TARGET_DIR_BACK_LEFT},   // 43 TARGET_DEST_CASTER_BACK_LEFT
    {TARGET_OBJECT_TYPE_DEST, TARGET_REFERENCE_TYPE_CASTER, TARGET_SELECT_CATEGORY_DEFAULT, TARGET_CHECK_DEFAULT,  TARGET_DIR_FRONT_LEFT},  // 44 TARGET_DEST_CASTER_FRONT_LEFT
    {TARGET_OBJECT_TYPE_UNIT, TARGET_REFERENCE_TYPE_TARGET, TARGET_SELECT_CATEGORY_DEFAULT, TARGET_CHECK_ALLY,     TARGET_DIR_NONE},        // 45 TARGET_UNIT_TARGET_CHAINHEAL_ALLY
    {TARGET_OBJECT_TYPE_DEST, TARGET_REFERENCE_TYPE_CASTER, TARGET_SELECT_CATEGORY_NEARBY,  TARGET_CHECK_ENTRY,    TARGET_DIR_NONE},        // 46 TARGET_DEST_NEARBY_ENTRY
    {TARGET_OBJECT_TYPE_DEST, TARGET_REFERENCE_TYPE_CASTER, TARGET_SELECT_CATEGORY_DEFAULT, TARGET_CHECK_DEFAULT,  TARGET_DIR_FRONT},       // 47 TARGET_DEST_CASTER_FRONT
    {TARGET_OBJECT_TYPE_DEST, TARGET_REFERENCE_TYPE_CASTER, TARGET_SELECT_CATEGORY_DEFAULT, TARGET_CHECK_DEFAULT,  TARGET_DIR_BACK},        // 48 TARGET_DEST_CASTER_BACK
    {TARGET_OBJECT_TYPE_DEST, TARGET_REFERENCE_TYPE_CASTER, TARGET_SELECT_CATEGORY_DEFAULT, TARGET_CHECK_DEFAULT,  TARGET_DIR_RIGHT},       // 49 TARGET_DEST_CASTER_RIGHT
    {TARGET_OBJECT_TYPE_DEST, TARGET_REFERENCE_TYPE_CASTER, TARGET_SELECT_CATEGORY_DEFAULT, TARGET_CHECK_DEFAULT,  TARGET_DIR_LEFT},        // 50 TARGET_DEST_CASTER_LEFT
    {TARGET_OBJECT_TYPE_GOBJ, TARGET_REFERENCE_TYPE_SRC,    TARGET_SELECT_CATEGORY_AREA,    TARGET_CHECK_DEFAULT,  TARGET_DIR_NONE},        // 51 TARGET_GAMEOBJECT_SRC_AREA
    {TARGET_OBJECT_TYPE_GOBJ, TARGET_REFERENCE_TYPE_DEST,   TARGET_SELECT_CATEGORY_AREA,    TARGET_CHECK_DEFAULT,  TARGET_DIR_NONE},        // 52 TARGET_GAMEOBJECT_DEST_AREA
    {TARGET_OBJECT_TYPE_DEST, TARGET_REFERENCE_TYPE_TARGET, TARGET_SELECT_CATEGORY_DEFAULT, TARGET_CHECK_ENEMY,    TARGET_DIR_NONE},        // 53 TARGET_DEST_TARGET_ENEMY
    {TARGET_OBJECT_TYPE_UNIT, TARGET_REFERENCE_TYPE_CASTER, TARGET_SELECT_CATEGORY_CONE,    TARGET_CHECK_ENEMY,    TARGET_DIR_FRONT},       // 54 TARGET_UNIT_CONE_ENEMY_54
    {TARGET_OBJECT_TYPE_DEST, TARGET_REFERENCE_TYPE_CASTER, TARGET_SELECT_CATEGORY_DEFAULT, TARGET_CHECK_DEFAULT,  TARGET_DIR_NONE},        // 55 TARGET_DEST_CASTER_FRONT_LEAP
    {TARGET_OBJECT_TYPE_UNIT, TARGET_REFERENCE_TYPE_CASTER, TARGET_SELECT_CATEGORY_AREA,    TARGET_CHECK_RAID,     TARGET_DIR_NONE},        // 56 TARGET_UNIT_CASTER_AREA_RAID
    {TARGET_OBJECT_TYPE_UNIT, TARGET_REFERENCE_TYPE_TARGET, TARGET_SELECT_CATEGORY_DEFAULT, TARGET_CHECK_RAID,     TARGET_DIR_NONE},        // 57 TARGET_UNIT_TARGET_RAID
    {TARGET_OBJECT_TYPE_UNIT, TARGET_REFERENCE_TYPE_CASTER, TARGET_SELECT_CATEGORY_NEARBY,  TARGET_CHECK_RAID,     TARGET_DIR_NONE},        // 58 TARGET_UNIT_NEARBY_RAID
    {TARGET_OBJECT_TYPE_UNIT, TARGET_REFERENCE_TYPE_CASTER, TARGET_SELECT_CATEGORY_CONE,    TARGET_CHECK_ALLY,     TARGET_DIR_FRONT},       // 59 TARGET_UNIT_CONE_ALLY
    {TARGET_OBJECT_TYPE_UNIT, TARGET_REFERENCE_TYPE_CASTER, TARGET_SELECT_CATEGORY_CONE,    TARGET_CHECK_ENTRY,    TARGET_DIR_FRONT},       // 60 TARGET_UNIT_CONE_ENTRY
    {TARGET_OBJECT_TYPE_UNIT, TARGET_REFERENCE_TYPE_TARGET, TARGET_SELECT_CATEGORY_AREA,    TARGET_CHECK_RAID_CLASS,TARGET_DIR_NONE},       // 61 TARGET_UNIT_TARGET_AREA_RAID_CLASS
    {TARGET_OBJECT_TYPE_NONE, TARGET_REFERENCE_TYPE_NONE,   TARGET_SELECT_CATEGORY_NYI,     TARGET_CHECK_DEFAULT,  TARGET_DIR_NONE},        // 62 TARGET_UNK_62
    {TARGET_OBJECT_TYPE_DEST, TARGET_REFERENCE_TYPE_TARGET, TARGET_SELECT_CATEGORY_DEFAULT, TARGET_CHECK_DEFAULT,  TARGET_DIR_NONE},        // 63 TARGET_DEST_TARGET_ANY
    {TARGET_OBJECT_TYPE_DEST, TARGET_REFERENCE_TYPE_TARGET, TARGET_SELECT_CATEGORY_DEFAULT, TARGET_CHECK_DEFAULT,  TARGET_DIR_FRONT},       // 64 TARGET_DEST_TARGET_FRONT
    {TARGET_OBJECT_TYPE_DEST, TARGET_REFERENCE_TYPE_TARGET, TARGET_SELECT_CATEGORY_DEFAULT, TARGET_CHECK_DEFAULT,  TARGET_DIR_BACK},        // 65 TARGET_DEST_TARGET_BACK
    {TARGET_OBJECT_TYPE_DEST, TARGET_REFERENCE_TYPE_TARGET, TARGET_SELECT_CATEGORY_DEFAULT, TARGET_CHECK_DEFAULT,  TARGET_DIR_RIGHT},       // 66 TARGET_DEST_TARGET_RIGHT
    {TARGET_OBJECT_TYPE_DEST, TARGET_REFERENCE_TYPE_TARGET, TARGET_SELECT_CATEGORY_DEFAULT, TARGET_CHECK_DEFAULT,  TARGET_DIR_LEFT},        // 67 TARGET_DEST_TARGET_LEFT
    {TARGET_OBJECT_TYPE_DEST, TARGET_REFERENCE_TYPE_TARGET, TARGET_SELECT_CATEGORY_DEFAULT, TARGET_CHECK_DEFAULT,  TARGET_DIR_FRONT_RIGHT}, // 68 TARGET_DEST_TARGET_FRONT_RIGHT
    {TARGET_OBJECT_TYPE_DEST, TARGET_REFERENCE_TYPE_TARGET, TARGET_SELECT_CATEGORY_DEFAULT, TARGET_CHECK_DEFAULT,  TARGET_DIR_BACK_RIGHT},  // 69 TARGET_DEST_TARGET_BACK_RIGHT
    {TARGET_OBJECT_TYPE_DEST, TARGET_REFERENCE_TYPE_TARGET, TARGET_SELECT_CATEGORY_DEFAULT, TARGET_CHECK_DEFAULT,  TARGET_DIR_BACK_LEFT},   // 70 TARGET_DEST_TARGET_BACK_LEFT
    {TARGET_OBJECT_TYPE_DEST, TARGET_REFERENCE_TYPE_TARGET, TARGET_SELECT_CATEGORY_DEFAULT, TARGET_CHECK_DEFAULT,  TARGET_DIR_FRONT_LEFT},  // 71 TARGET_DEST_TARGET_FRONT_LEFT
    {TARGET_OBJECT_TYPE_DEST, TARGET_REFERENCE_TYPE_CASTER, TARGET_SELECT_CATEGORY_DEFAULT, TARGET_CHECK_DEFAULT,  TARGET_DIR_RANDOM},      // 72 TARGET_DEST_CASTER_RANDOM
    {TARGET_OBJECT_TYPE_DEST, TARGET_REFERENCE_TYPE_CASTER, TARGET_SELECT_CATEGORY_DEFAULT, TARGET_CHECK_DEFAULT,  TARGET_DIR_RANDOM},      // 73 TARGET_DEST_CASTER_RADIUS
    {TARGET_OBJECT_TYPE_DEST, TARGET_REFERENCE_TYPE_TARGET, TARGET_SELECT_CATEGORY_DEFAULT, TARGET_CHECK_DEFAULT,  TARGET_DIR_RANDOM},      // 74 TARGET_DEST_TARGET_RANDOM
    {TARGET_OBJECT_TYPE_DEST, TARGET_REFERENCE_TYPE_TARGET, TARGET_SELECT_CATEGORY_DEFAULT, TARGET_CHECK_DEFAULT,  TARGET_DIR_RANDOM},      // 75 TARGET_DEST_TARGET_RADIUS
    {TARGET_OBJECT_TYPE_DEST, TARGET_REFERENCE_TYPE_CASTER, TARGET_SELECT_CATEGORY_CHANNEL, TARGET_CHECK_DEFAULT,  TARGET_DIR_NONE},        // 76 TARGET_DEST_CHANNEL_TARGET
    {TARGET_OBJECT_TYPE_UNIT, TARGET_REFERENCE_TYPE_CASTER, TARGET_SELECT_CATEGORY_CHANNEL, TARGET_CHECK_DEFAULT,  TARGET_DIR_NONE},        // 77 TARGET_UNIT_CHANNEL_TARGET
    {TARGET_OBJECT_TYPE_DEST, TARGET_REFERENCE_TYPE_DEST,   TARGET_SELECT_CATEGORY_DEFAULT, TARGET_CHECK_DEFAULT,  TARGET_DIR_FRONT},       // 78 TARGET_DEST_DEST_FRONT
    {TARGET_OBJECT_TYPE_DEST, TARGET_REFERENCE_TYPE_DEST,   TARGET_SELECT_CATEGORY_DEFAULT, TARGET_CHECK_DEFAULT,  TARGET_DIR_BACK},        // 79 TARGET_DEST_DEST_BACK
    {TARGET_OBJECT_TYPE_DEST, TARGET_REFERENCE_TYPE_DEST,   TARGET_SELECT_CATEGORY_DEFAULT, TARGET_CHECK_DEFAULT,  TARGET_DIR_RIGHT},       // 80 TARGET_DEST_DEST_RIGHT
    {TARGET_OBJECT_TYPE_DEST, TARGET_REFERENCE_TYPE_DEST,   TARGET_SELECT_CATEGORY_DEFAULT, TARGET_CHECK_DEFAULT,  TARGET_DIR_LEFT},        // 81 TARGET_DEST_DEST_LEFT
    {TARGET_OBJECT_TYPE_DEST, TARGET_REFERENCE_TYPE_DEST,   TARGET_SELECT_CATEGORY_DEFAULT, TARGET_CHECK_DEFAULT,  TARGET_DIR_FRONT_RIGHT}, // 82 TARGET_DEST_DEST_FRONT_RIGHT
    {TARGET_OBJECT_TYPE_DEST, TARGET_REFERENCE_TYPE_DEST,   TARGET_SELECT_CATEGORY_DEFAULT, TARGET_CHECK_DEFAULT,  TARGET_DIR_BACK_RIGHT},  // 83 TARGET_DEST_DEST_BACK_RIGHT
    {TARGET_OBJECT_TYPE_DEST, TARGET_REFERENCE_TYPE_DEST,   TARGET_SELECT_CATEGORY_DEFAULT, TARGET_CHECK_DEFAULT,  TARGET_DIR_BACK_LEFT},   // 84 TARGET_DEST_DEST_BACK_LEFT
    {TARGET_OBJECT_TYPE_DEST, TARGET_REFERENCE_TYPE_DEST,   TARGET_SELECT_CATEGORY_DEFAULT, TARGET_CHECK_DEFAULT,  TARGET_DIR_FRONT_LEFT},  // 85 TARGET_DEST_DEST_FRONT_LEFT
    {TARGET_OBJECT_TYPE_DEST, TARGET_REFERENCE_TYPE_DEST,   TARGET_SELECT_CATEGORY_DEFAULT, TARGET_CHECK_DEFAULT,  TARGET_DIR_RANDOM},      // 86 TARGET_DEST_DEST_RANDOM
    {TARGET_OBJECT_TYPE_DEST, TARGET_REFERENCE_TYPE_DEST,   TARGET_SELECT_CATEGORY_DEFAULT, TARGET_CHECK_DEFAULT,  TARGET_DIR_NONE},        // 87 TARGET_DEST_DEST
    {TARGET_OBJECT_TYPE_DEST, TARGET_REFERENCE_TYPE_DEST,   TARGET_SELECT_CATEGORY_DEFAULT, TARGET_CHECK_DEFAULT,  TARGET_DIR_NONE},        // 88 TARGET_DEST_DYNOBJ_NONE
    {TARGET_OBJECT_TYPE_DEST, TARGET_REFERENCE_TYPE_DEST,   TARGET_SELECT_CATEGORY_DEFAULT, TARGET_CHECK_DEFAULT,  TARGET_DIR_NONE},        // 89 TARGET_DEST_TRAJ
    {TARGET_OBJECT_TYPE_UNIT, TARGET_REFERENCE_TYPE_TARGET, TARGET_SELECT_CATEGORY_DEFAULT, TARGET_CHECK_DEFAULT,  TARGET_DIR_NONE},        // 90 TARGET_UNIT_TARGET_MINIPET
    {TARGET_OBJECT_TYPE_DEST, TARGET_REFERENCE_TYPE_DEST,   TARGET_SELECT_CATEGORY_DEFAULT, TARGET_CHECK_DEFAULT,  TARGET_DIR_RANDOM},      // 91 TARGET_DEST_DEST_RADIUS
    {TARGET_OBJECT_TYPE_UNIT, TARGET_REFERENCE_TYPE_CASTER, TARGET_SELECT_CATEGORY_DEFAULT, TARGET_CHECK_DEFAULT,  TARGET_DIR_NONE},        // 92 TARGET_UNIT_SUMMONER
    {TARGET_OBJECT_TYPE_CORPSE, TARGET_REFERENCE_TYPE_SRC,   TARGET_SELECT_CATEGORY_NYI,     TARGET_CHECK_ENEMY,    TARGET_DIR_NONE},       // 93 TARGET_CORPSE_SRC_AREA_ENEMY
    {TARGET_OBJECT_TYPE_UNIT, TARGET_REFERENCE_TYPE_CASTER, TARGET_SELECT_CATEGORY_DEFAULT, TARGET_CHECK_DEFAULT,  TARGET_DIR_NONE},        // 94 TARGET_UNIT_VEHICLE
    {TARGET_OBJECT_TYPE_UNIT, TARGET_REFERENCE_TYPE_TARGET, TARGET_SELECT_CATEGORY_DEFAULT, TARGET_CHECK_PASSENGER, TARGET_DIR_NONE},       // 95 TARGET_UNIT_TARGET_PASSENGER
    {TARGET_OBJECT_TYPE_UNIT, TARGET_REFERENCE_TYPE_CASTER, TARGET_SELECT_CATEGORY_DEFAULT, TARGET_CHECK_DEFAULT,  TARGET_DIR_NONE},        // 96 TARGET_UNIT_PASSENGER_0
    {TARGET_OBJECT_TYPE_UNIT, TARGET_REFERENCE_TYPE_CASTER, TARGET_SELECT_CATEGORY_DEFAULT, TARGET_CHECK_DEFAULT,  TARGET_DIR_NONE},        // 97 TARGET_UNIT_PASSENGER_1
    {TARGET_OBJECT_TYPE_UNIT, TARGET_REFERENCE_TYPE_CASTER, TARGET_SELECT_CATEGORY_DEFAULT, TARGET_CHECK_DEFAULT,  TARGET_DIR_NONE},        // 98 TARGET_UNIT_PASSENGER_2
    {TARGET_OBJECT_TYPE_UNIT, TARGET_REFERENCE_TYPE_CASTER, TARGET_SELECT_CATEGORY_DEFAULT, TARGET_CHECK_DEFAULT,  TARGET_DIR_NONE},        // 99 TARGET_UNIT_PASSENGER_3
    {TARGET_OBJECT_TYPE_UNIT, TARGET_REFERENCE_TYPE_CASTER, TARGET_SELECT_CATEGORY_DEFAULT, TARGET_CHECK_DEFAULT,  TARGET_DIR_NONE},        // 100 TARGET_UNIT_PASSENGER_4
    {TARGET_OBJECT_TYPE_UNIT, TARGET_REFERENCE_TYPE_CASTER, TARGET_SELECT_CATEGORY_DEFAULT, TARGET_CHECK_DEFAULT,  TARGET_DIR_NONE},        // 101 TARGET_UNIT_PASSENGER_5
    {TARGET_OBJECT_TYPE_UNIT, TARGET_REFERENCE_TYPE_CASTER, TARGET_SELECT_CATEGORY_DEFAULT, TARGET_CHECK_DEFAULT,  TARGET_DIR_NONE},        // 102 TARGET_UNIT_PASSENGER_6
    {TARGET_OBJECT_TYPE_UNIT, TARGET_REFERENCE_TYPE_CASTER, TARGET_SELECT_CATEGORY_DEFAULT, TARGET_CHECK_DEFAULT,  TARGET_DIR_NONE},        // 103 TARGET_UNIT_PASSENGER_7
    {TARGET_OBJECT_TYPE_UNIT, TARGET_REFERENCE_TYPE_CASTER, TARGET_SELECT_CATEGORY_CONE,    TARGET_CHECK_ENEMY,    TARGET_DIR_FRONT},       // 104 TARGET_UNIT_CONE_ENEMY_104
    {TARGET_OBJECT_TYPE_UNIT, TARGET_REFERENCE_TYPE_NONE,   TARGET_SELECT_CATEGORY_NYI,     TARGET_CHECK_DEFAULT,  TARGET_DIR_NONE},        // 105 TARGET_UNIT_UNK_105
    {TARGET_OBJECT_TYPE_DEST, TARGET_REFERENCE_TYPE_CASTER, TARGET_SELECT_CATEGORY_CHANNEL, TARGET_CHECK_DEFAULT,  TARGET_DIR_NONE},        // 106 TARGET_DEST_CHANNEL_CASTER
    {TARGET_OBJECT_TYPE_NONE, TARGET_REFERENCE_TYPE_DEST,   TARGET_SELECT_CATEGORY_NYI,     TARGET_CHECK_DEFAULT,  TARGET_DIR_NONE},        // 107 TARGET_UNK_DEST_AREA_UNK_107
    {TARGET_OBJECT_TYPE_GOBJ, TARGET_REFERENCE_TYPE_CASTER, TARGET_SELECT_CATEGORY_CONE,    TARGET_CHECK_DEFAULT,  TARGET_DIR_FRONT},       // 108 TARGET_GAMEOBJECT_CONE
    {TARGET_OBJECT_TYPE_NONE, TARGET_REFERENCE_TYPE_NONE,   TARGET_SELECT_CATEGORY_NYI,     TARGET_CHECK_DEFAULT,  TARGET_DIR_NONE},        // 109
    {TARGET_OBJECT_TYPE_UNIT, TARGET_REFERENCE_TYPE_CASTER, TARGET_SELECT_CATEGORY_CONE,    TARGET_CHECK_ENEMY,    TARGET_DIR_FRONT},       // 110 TARGET_UNIT_CONE_ENEMY_110
    {TARGET_OBJECT_TYPE_NONE, TARGET_REFERENCE_TYPE_NONE,   TARGET_SELECT_CATEGORY_NYI,     TARGET_CHECK_DEFAULT,  TARGET_DIR_NONE},        // 111
    {TARGET_OBJECT_TYPE_NONE, TARGET_REFERENCE_TYPE_NONE,   TARGET_SELECT_CATEGORY_NYI,     TARGET_CHECK_DEFAULT,  TARGET_DIR_NONE},        // 112
    {TARGET_OBJECT_TYPE_NONE, TARGET_REFERENCE_TYPE_NONE,   TARGET_SELECT_CATEGORY_NYI,     TARGET_CHECK_DEFAULT,  TARGET_DIR_NONE},        // 113
    {TARGET_OBJECT_TYPE_NONE, TARGET_REFERENCE_TYPE_NONE,   TARGET_SELECT_CATEGORY_NYI,     TARGET_CHECK_DEFAULT,  TARGET_DIR_NONE},        // 114
    {TARGET_OBJECT_TYPE_NONE, TARGET_REFERENCE_TYPE_NONE,   TARGET_SELECT_CATEGORY_NYI,     TARGET_CHECK_DEFAULT,  TARGET_DIR_NONE},        // 115
    {TARGET_OBJECT_TYPE_NONE, TARGET_REFERENCE_TYPE_NONE,   TARGET_SELECT_CATEGORY_NYI,     TARGET_CHECK_DEFAULT,  TARGET_DIR_NONE},        // 116
    {TARGET_OBJECT_TYPE_NONE, TARGET_REFERENCE_TYPE_NONE,   TARGET_SELECT_CATEGORY_NYI,     TARGET_CHECK_DEFAULT,  TARGET_DIR_NONE},        // 117
    {TARGET_OBJECT_TYPE_NONE, TARGET_REFERENCE_TYPE_NONE,   TARGET_SELECT_CATEGORY_NYI,     TARGET_CHECK_DEFAULT,  TARGET_DIR_NONE},        // 118
    {TARGET_OBJECT_TYPE_NONE, TARGET_REFERENCE_TYPE_CASTER, TARGET_SELECT_CATEGORY_AREA,    TARGET_CHECK_RAID,     TARGET_DIR_NONE},        // 119 TARGET_UNK_119
    {TARGET_OBJECT_TYPE_NONE, TARGET_REFERENCE_TYPE_NONE,   TARGET_SELECT_CATEGORY_NYI,     TARGET_CHECK_DEFAULT,  TARGET_DIR_NONE},        // 120
    {TARGET_OBJECT_TYPE_NONE, TARGET_REFERENCE_TYPE_NONE,   TARGET_SELECT_CATEGORY_NYI,     TARGET_CHECK_DEFAULT,  TARGET_DIR_NONE},        // 121
    {TARGET_OBJECT_TYPE_NONE, TARGET_REFERENCE_TYPE_NONE,   TARGET_SELECT_CATEGORY_NYI,     TARGET_CHECK_DEFAULT,  TARGET_DIR_NONE},        // 122
    {TARGET_OBJECT_TYPE_NONE, TARGET_REFERENCE_TYPE_NONE,   TARGET_SELECT_CATEGORY_NYI,     TARGET_CHECK_DEFAULT,  TARGET_DIR_NONE},        // 123
    {TARGET_OBJECT_TYPE_NONE, TARGET_REFERENCE_TYPE_NONE,   TARGET_SELECT_CATEGORY_NYI,     TARGET_CHECK_DEFAULT,  TARGET_DIR_NONE},        // 124
    {TARGET_OBJECT_TYPE_NONE, TARGET_REFERENCE_TYPE_NONE,   TARGET_SELECT_CATEGORY_NYI,     TARGET_CHECK_DEFAULT,  TARGET_DIR_NONE},        // 125
    {TARGET_OBJECT_TYPE_NONE, TARGET_REFERENCE_TYPE_NONE,   TARGET_SELECT_CATEGORY_NYI,     TARGET_CHECK_DEFAULT,  TARGET_DIR_NONE},        // 126
    {TARGET_OBJECT_TYPE_NONE, TARGET_REFERENCE_TYPE_NONE,   TARGET_SELECT_CATEGORY_NYI,     TARGET_CHECK_DEFAULT,  TARGET_DIR_NONE},        // 127
    {TARGET_OBJECT_TYPE_NONE, TARGET_REFERENCE_TYPE_NONE,   TARGET_SELECT_CATEGORY_NYI,     TARGET_CHECK_DEFAULT,  TARGET_DIR_NONE},        // 128
    {TARGET_OBJECT_TYPE_UNIT, TARGET_REFERENCE_TYPE_CASTER, TARGET_SELECT_CATEGORY_CONE,    TARGET_CHECK_ENEMY,    TARGET_DIR_FRONT},       // 129 TARGET_UNIT_CONE_ENEMY_129
};

SpellEffectInfo::SpellEffectInfo(SpellEntry const* spellEntry, SpellInfo const* spellInfo, uint8 effIndex, uint32 difficulty)
{
    SpellEffectEntry const* _effect = spellEntry->GetSpellEffect(effIndex, difficulty);
    SpellEffectScalingEntry const* _effectScaling = GetSpellEffectScalingEntry(_effect ? _effect->Id : 0);
    SpellScalingEntry const* scaling = spellInfo->GetSpellScaling();


    _spellInfo = spellInfo;
    _effIndex = effIndex;
    Effect = _effect ? _effect->Effect : 0;
    ApplyAuraName = _effect ? _effect->EffectApplyAuraName : 0;
    Amplitude = _effect ? _effect->EffectAmplitude : 0;
    DieSides = _effect ? _effect->EffectDieSides : 0;
    RealPointsPerLevel = _effect ? _effect->EffectRealPointsPerLevel : 0.0f;
    BasePoints = _effect ? _effect->EffectBasePoints : 0;
    PointsPerComboPoint = _effect ? _effect->EffectPointsPerComboPoint : 0.0f;
    ValueMultiplier = _effect ? _effect->EffectValueMultiplier : 0.0f;
    DamageMultiplier = _effect ? _effect->EffectDamageMultiplier : 0.0f;
    BonusMultiplier = _effect ? _effect->EffectBonusMultiplier : 0.0f;
    MiscValue = _effect ? _effect->EffectMiscValue : 0;
    MiscValueB = _effect ? _effect->EffectMiscValueB : 0;
    Mechanic = Mechanics(_effect ? _effect->EffectMechanic : 0);
    TargetA = SpellImplicitTargetInfo(_effect ? _effect->EffectImplicitTargetA : 0);
    TargetB = SpellImplicitTargetInfo(_effect ? _effect->EffectImplicitTargetB : 0);
    RadiusEntry = _effect && _effect->EffectRadiusIndex ? sSpellRadiusStore.LookupEntry(_effect->EffectRadiusIndex) : NULL;
    if (!RadiusEntry)
         RadiusEntry = _effect && _effect->EffectRadiusMaxIndex ? sSpellRadiusStore.LookupEntry(_effect->EffectRadiusMaxIndex) : NULL;
    ChainTarget = _effect ? _effect->EffectChainTarget : 0;
    ItemType = _effect ? _effect->EffectItemType : 0;
    TriggerSpell = _effect ? _effect->EffectTriggerSpell : 0;
    SpellClassMask = _effect ? _effect->EffectSpellClassMask : flag96(0);
    ImplicitTargetConditions = NULL;
    ScalingMultiplier = _effectScaling ? _effectScaling->Multiplier : 0.0f;
    DeltaScalingMultiplier = _effectScaling ? _effectScaling->RandomMultiplier : 0.0f;
    ComboScalingMultiplier = _effectScaling ? _effectScaling->OtherMultiplier: 0.0f;
}

bool SpellEffectInfo::IsEffect() const
{
    return Effect != 0;
}

bool SpellEffectInfo::IsEffect(SpellEffects effectName) const
{
    return Effect == uint32(effectName);
}

bool SpellEffectInfo::IsAura() const
{
    return (IsUnitOwnedAuraEffect() || Effect == SPELL_EFFECT_PERSISTENT_AREA_AURA) && ApplyAuraName != 0;
}

bool SpellEffectInfo::IsPersistenAura() const
{
    return Effect == SPELL_EFFECT_PERSISTENT_AREA_AURA && ApplyAuraName != 0;
}

bool SpellEffectInfo::IsAura(AuraType aura) const
{
    return IsAura() && AuraType(ApplyAuraName) == uint32(aura);
}

bool SpellEffectInfo::IsTargetingArea() const
{
    return TargetA.IsArea() || TargetB.IsArea();
}

bool SpellEffectInfo::IsAreaAuraEffect() const
{
    if (Effect == SPELL_EFFECT_APPLY_AREA_AURA_PARTY    ||
        Effect == SPELL_EFFECT_APPLY_AREA_AURA_RAID     ||
        Effect == SPELL_EFFECT_APPLY_AREA_AURA_FRIEND   ||
        Effect == SPELL_EFFECT_APPLY_AREA_AURA_ENEMY    ||
        Effect == SPELL_EFFECT_APPLY_AREA_AURA_PET      ||
        Effect == SPELL_EFFECT_APPLY_AREA_AURA_OWNER)
        return true;
    return false;
}

bool SpellEffectInfo::IsFarUnitTargetEffect() const
{
    return (Effect == SPELL_EFFECT_SUMMON_PLAYER)
        || (Effect == SPELL_EFFECT_SUMMON_RAF_FRIEND)
        || (Effect == SPELL_EFFECT_RESURRECT)
        || (Effect == SPELL_EFFECT_RESURRECT_NEW)
        || (Effect == SPELL_EFFECT_SKIN_PLAYER_CORPSE);
}

bool SpellEffectInfo::IsFarDestTargetEffect() const
{
    return Effect == SPELL_EFFECT_TELEPORT_UNITS;
}

bool SpellEffectInfo::IsUnitOwnedAuraEffect() const
{
    return IsAreaAuraEffect() || Effect == SPELL_EFFECT_APPLY_AURA;
}

int32 SpellEffectInfo::CalcValue(Unit const* caster, int32 const* bp, Unit const* target) const
{
    float basePointsPerLevel = RealPointsPerLevel;
    int32 basePoints = bp ? *bp : BasePoints;
    float comboDamage = PointsPerComboPoint;

    // base amount modification based on spell lvl vs caster lvl
    if (ScalingMultiplier != 0.0f)
    {
        if (caster && !_spellInfo->IsCustomCalculated())
        {
            int32 level = caster->getLevel();
            if (target && _spellInfo->IsPositiveEffect(_effIndex) && (Effect == SPELL_EFFECT_APPLY_AURA) && _spellInfo->Id != 774) // Hack Fix Rejuvenation, doesn't use the target level for basepoints
                level = target->getLevel();

            if (GtSpellScalingEntry const* gtScaling = sGtSpellScalingStore.LookupEntry((_spellInfo->ScalingClass != -1 ? _spellInfo->ScalingClass - 1 : MAX_CLASSES - 1) * 100 + level - 1))
            {
                float multiplier = gtScaling->value;
                if (_spellInfo->CastTimeMax > 0 && _spellInfo->CastTimeMaxLevel > level)
                    multiplier *= float(_spellInfo->CastTimeMin + (level - 1) * (_spellInfo->CastTimeMax - _spellInfo->CastTimeMin) / (_spellInfo->CastTimeMaxLevel - 1)) / float(_spellInfo->CastTimeMax);
                if (_spellInfo->CoefLevelBase > level)
                    multiplier *= (1.0f - _spellInfo->CoefBase) * (float)(level - 1) / (float)(_spellInfo->CoefLevelBase - 1) + _spellInfo->CoefBase;

                float preciseBasePoints = ScalingMultiplier * multiplier;
                if (DeltaScalingMultiplier)
                {
                    float delta = DeltaScalingMultiplier * ScalingMultiplier * multiplier * 0.5f;
                    preciseBasePoints += frand(-delta, delta);
                }

                basePoints = int32(preciseBasePoints);

                if (ComboScalingMultiplier)
                    comboDamage = ComboScalingMultiplier * multiplier;
            }
        }
    }
    else
    {
        if (caster)
        {
            int32 level = int32(caster->getLevel());
            if (level > int32(_spellInfo->MaxLevel) && _spellInfo->MaxLevel > 0)
                level = int32(_spellInfo->MaxLevel);
            else if (level < int32(_spellInfo->BaseLevel))
                level = int32(_spellInfo->BaseLevel);
            level -= int32(_spellInfo->SpellLevel);
            basePoints += int32(level * basePointsPerLevel);

            if (basePointsPerLevel && basePoints >= 100 && (Effect == SPELL_EFFECT_DAMAGE_FROM_MAX_HEALTH_PCT || ApplyAuraName == SPELL_AURA_PERIODIC_DAMAGE_PERCENT))  // Temporary
                basePoints /= 10;
        }

        // roll in a range <1;EffectDieSides> as of patch 3.3.3
        int32 randomPoints = int32(DieSides);
        switch (randomPoints)
        {
            case 0: break;
            case 1: basePoints += 1; break;                     // range 1..1
            default:
            {
                // range can have positive (1..rand) and negative (rand..1) values, so order its for irand
                int32 randvalue = (randomPoints >= 1)
                    ? irand(1, randomPoints)
                    : irand(randomPoints, 1);

                basePoints += randvalue;
                break;
            }
        }
    }

    float value = float(basePoints);

    // random damage
    if (caster)
    {
        // bonus amount from combo points
        if (caster->m_movedPlayer && comboDamage)
            if (uint8 comboPoints = caster->m_movedPlayer->GetComboPoints())
                value += comboDamage * comboPoints;

        value = caster->ApplyEffectModifiers(_spellInfo, _effIndex, value);

        // amount multiplication based on caster's level
        if (!_spellInfo->GetSpellScaling() && !basePointsPerLevel && (_spellInfo->Attributes & SPELL_ATTR0_LEVEL_DAMAGE_CALCULATION && _spellInfo->SpellLevel) &&
                Effect != SPELL_EFFECT_WEAPON_PERCENT_DAMAGE &&
                Effect != SPELL_EFFECT_KNOCK_BACK &&
                Effect != SPELL_EFFECT_ADD_EXTRA_ATTACKS &&
                Effect != SPELL_EFFECT_GAMEOBJECT_DAMAGE &&
                ApplyAuraName != SPELL_AURA_MOD_SPEED_ALWAYS &&
                ApplyAuraName != SPELL_AURA_MOD_SPEED_NOT_STACK &&
                ApplyAuraName != SPELL_AURA_MOD_INCREASE_SPEED &&
                ApplyAuraName != SPELL_AURA_MOD_DECREASE_SPEED)
                //there are many more: slow speed, -healing pct
            value *= 0.25f * exp(caster->getLevel() * (70 - _spellInfo->SpellLevel) / 1000.0f);
            //value = int32(value * (int32)getLevel() / (int32)(_spellInfo->spellLevel ? _spellInfo->spellLevel : 1));

        // Hack Fix Arcane Barrage triggered
        if (_spellInfo->Id == 50273)
            value = float(basePoints);
    }

    return int32(value);
}

int32 SpellEffectInfo::CalcBaseValue(int32 value) const
{
    if (DieSides == 0)
        return value;
    else
        return value - 1;
}

float SpellEffectInfo::CalcValueMultiplier(Unit* caster, Spell* spell) const
{
    float multiplier = ValueMultiplier;
    if (Player* modOwner = (caster ? caster->GetSpellModOwner() : NULL))
        modOwner->ApplySpellMod(_spellInfo->Id, SPELLMOD_VALUE_MULTIPLIER, multiplier, spell);
    return multiplier;
}

float SpellEffectInfo::CalcDamageMultiplier(Unit* caster, Spell* spell) const
{
    float multiplier = DamageMultiplier;
    if (Player* modOwner = (caster ? caster->GetSpellModOwner() : NULL))
        modOwner->ApplySpellMod(_spellInfo->Id, SPELLMOD_DAMAGE_MULTIPLIER, multiplier, spell);
    return multiplier;
}

bool SpellEffectInfo::HasRadius() const
{
    return RadiusEntry != NULL;
}

float SpellEffectInfo::CalcRadius(Unit* caster, Spell* spell) const
{
    if (!HasRadius())
        return 0.0f;

    float radius = _spellInfo->IsPositive() ? RadiusEntry->radiusFriend : RadiusEntry->radiusHostile;
    if (Player* modOwner = (caster ? caster->GetSpellModOwner() : NULL))
        modOwner->ApplySpellMod(_spellInfo->Id, SPELLMOD_RADIUS, radius, spell);

    return radius;
}

uint32 SpellEffectInfo::GetProvidedTargetMask() const
{
    return GetTargetFlagMask(TargetA.GetObjectType()) | GetTargetFlagMask(TargetB.GetObjectType());
}

uint32 SpellEffectInfo::GetMissingTargetMask(bool srcSet /*= false*/, bool dstSet /*= false*/, uint32 mask /*=0*/) const
{
    uint32 effImplicitTargetMask = GetTargetFlagMask(GetUsedTargetObjectType());
    uint32 providedTargetMask = GetTargetFlagMask(TargetA.GetObjectType()) | GetTargetFlagMask(TargetB.GetObjectType()) | mask;

    // remove all flags covered by effect target mask
    if (providedTargetMask & TARGET_FLAG_UNIT_MASK)
        effImplicitTargetMask &= ~(TARGET_FLAG_UNIT_MASK);
    if (providedTargetMask & TARGET_FLAG_CORPSE_MASK)
        effImplicitTargetMask &= ~(TARGET_FLAG_UNIT_MASK | TARGET_FLAG_CORPSE_MASK);
    if (providedTargetMask & TARGET_FLAG_GAMEOBJECT_ITEM)
        effImplicitTargetMask &= ~(TARGET_FLAG_GAMEOBJECT_ITEM | TARGET_FLAG_GAMEOBJECT | TARGET_FLAG_ITEM);
    if (providedTargetMask & TARGET_FLAG_GAMEOBJECT)
        effImplicitTargetMask &= ~(TARGET_FLAG_GAMEOBJECT | TARGET_FLAG_GAMEOBJECT_ITEM);
    if (providedTargetMask & TARGET_FLAG_ITEM)
        effImplicitTargetMask &= ~(TARGET_FLAG_ITEM | TARGET_FLAG_GAMEOBJECT_ITEM);
    if (dstSet || providedTargetMask & TARGET_FLAG_DEST_LOCATION)
        effImplicitTargetMask &= ~(TARGET_FLAG_DEST_LOCATION);
    if (srcSet || providedTargetMask & TARGET_FLAG_SOURCE_LOCATION)
        effImplicitTargetMask &= ~(TARGET_FLAG_SOURCE_LOCATION);

    return effImplicitTargetMask;
}

SpellEffectImplicitTargetTypes SpellEffectInfo::GetImplicitTargetType() const
{
    return _data[Effect].ImplicitTargetType;
}

SpellTargetObjectTypes SpellEffectInfo::GetUsedTargetObjectType() const
{
    return _data[Effect].UsedTargetObjectType;
}

SpellEffectInfo::StaticData  SpellEffectInfo::_data[TOTAL_SPELL_EFFECTS] =
{
    // implicit target type           used target object type
    {EFFECT_IMPLICIT_TARGET_NONE,     TARGET_OBJECT_TYPE_NONE}, // 0
    {EFFECT_IMPLICIT_TARGET_EXPLICIT, TARGET_OBJECT_TYPE_UNIT}, // 1 SPELL_EFFECT_INSTAKILL
    {EFFECT_IMPLICIT_TARGET_EXPLICIT, TARGET_OBJECT_TYPE_UNIT}, // 2 SPELL_EFFECT_SCHOOL_DAMAGE
    {EFFECT_IMPLICIT_TARGET_NONE,     TARGET_OBJECT_TYPE_NONE}, // 3 SPELL_EFFECT_DUMMY
    {EFFECT_IMPLICIT_TARGET_NONE,     TARGET_OBJECT_TYPE_NONE}, // 4 SPELL_EFFECT_PORTAL_TELEPORT
    {EFFECT_IMPLICIT_TARGET_EXPLICIT, TARGET_OBJECT_TYPE_UNIT_AND_DEST}, // 5 SPELL_EFFECT_TELEPORT_UNITS
    {EFFECT_IMPLICIT_TARGET_EXPLICIT, TARGET_OBJECT_TYPE_UNIT}, // 6 SPELL_EFFECT_APPLY_AURA
    {EFFECT_IMPLICIT_TARGET_EXPLICIT, TARGET_OBJECT_TYPE_UNIT}, // 7 SPELL_EFFECT_ENVIRONMENTAL_DAMAGE
    {EFFECT_IMPLICIT_TARGET_EXPLICIT, TARGET_OBJECT_TYPE_UNIT}, // 8 SPELL_EFFECT_POWER_DRAIN
    {EFFECT_IMPLICIT_TARGET_EXPLICIT, TARGET_OBJECT_TYPE_UNIT}, // 9 SPELL_EFFECT_HEALTH_LEECH
    {EFFECT_IMPLICIT_TARGET_EXPLICIT, TARGET_OBJECT_TYPE_UNIT}, // 10 SPELL_EFFECT_HEAL
    {EFFECT_IMPLICIT_TARGET_EXPLICIT, TARGET_OBJECT_TYPE_UNIT}, // 11 SPELL_EFFECT_BIND
    {EFFECT_IMPLICIT_TARGET_NONE,     TARGET_OBJECT_TYPE_NONE}, // 12 SPELL_EFFECT_PORTAL
    {EFFECT_IMPLICIT_TARGET_NONE,     TARGET_OBJECT_TYPE_NONE}, // 13 SPELL_EFFECT_RITUAL_BASE
    {EFFECT_IMPLICIT_TARGET_NONE,     TARGET_OBJECT_TYPE_NONE}, // 14 SPELL_EFFECT_RITUAL_SPECIALIZE
    {EFFECT_IMPLICIT_TARGET_NONE,     TARGET_OBJECT_TYPE_NONE}, // 15 SPELL_EFFECT_RITUAL_ACTIVATE_PORTAL
    {EFFECT_IMPLICIT_TARGET_EXPLICIT, TARGET_OBJECT_TYPE_UNIT}, // 16 SPELL_EFFECT_QUEST_COMPLETE
    {EFFECT_IMPLICIT_TARGET_EXPLICIT, TARGET_OBJECT_TYPE_UNIT}, // 17 SPELL_EFFECT_WEAPON_DAMAGE_NOSCHOOL
    {EFFECT_IMPLICIT_TARGET_EXPLICIT, TARGET_OBJECT_TYPE_CORPSE_ALLY}, // 18 SPELL_EFFECT_RESURRECT
    {EFFECT_IMPLICIT_TARGET_EXPLICIT, TARGET_OBJECT_TYPE_UNIT}, // 19 SPELL_EFFECT_ADD_EXTRA_ATTACKS
    {EFFECT_IMPLICIT_TARGET_NONE,     TARGET_OBJECT_TYPE_UNIT}, // 20 SPELL_EFFECT_DODGE
    {EFFECT_IMPLICIT_TARGET_NONE,     TARGET_OBJECT_TYPE_UNIT}, // 21 SPELL_EFFECT_EVADE
    {EFFECT_IMPLICIT_TARGET_NONE,     TARGET_OBJECT_TYPE_UNIT}, // 22 SPELL_EFFECT_PARRY
    {EFFECT_IMPLICIT_TARGET_NONE,     TARGET_OBJECT_TYPE_UNIT}, // 23 SPELL_EFFECT_BLOCK
    {EFFECT_IMPLICIT_TARGET_EXPLICIT, TARGET_OBJECT_TYPE_UNIT}, // 24 SPELL_EFFECT_CREATE_ITEM
    {EFFECT_IMPLICIT_TARGET_NONE,     TARGET_OBJECT_TYPE_UNIT}, // 25 SPELL_EFFECT_WEAPON
    {EFFECT_IMPLICIT_TARGET_NONE,     TARGET_OBJECT_TYPE_UNIT}, // 26 SPELL_EFFECT_DEFENSE
    {EFFECT_IMPLICIT_TARGET_EXPLICIT, TARGET_OBJECT_TYPE_DEST}, // 27 SPELL_EFFECT_PERSISTENT_AREA_AURA
    {EFFECT_IMPLICIT_TARGET_EXPLICIT, TARGET_OBJECT_TYPE_DEST}, // 28 SPELL_EFFECT_SUMMON
    {EFFECT_IMPLICIT_TARGET_EXPLICIT, TARGET_OBJECT_TYPE_UNIT_AND_DEST}, // 29 SPELL_EFFECT_LEAP
    {EFFECT_IMPLICIT_TARGET_NONE,     TARGET_OBJECT_TYPE_UNIT}, // 30 SPELL_EFFECT_ENERGIZE
    {EFFECT_IMPLICIT_TARGET_EXPLICIT, TARGET_OBJECT_TYPE_UNIT}, // 31 SPELL_EFFECT_WEAPON_PERCENT_DAMAGE
    {EFFECT_IMPLICIT_TARGET_NONE,     TARGET_OBJECT_TYPE_NONE}, // 32 SPELL_EFFECT_TRIGGER_MISSILE
    {EFFECT_IMPLICIT_TARGET_EXPLICIT, TARGET_OBJECT_TYPE_GOBJ_ITEM}, // 33 SPELL_EFFECT_OPEN_LOCK
    {EFFECT_IMPLICIT_TARGET_NONE,     TARGET_OBJECT_TYPE_UNIT}, // 34 SPELL_EFFECT_SUMMON_CHANGE_ITEM
    {EFFECT_IMPLICIT_TARGET_EXPLICIT, TARGET_OBJECT_TYPE_UNIT}, // 35 SPELL_EFFECT_APPLY_AREA_AURA_PARTY
    {EFFECT_IMPLICIT_TARGET_EXPLICIT, TARGET_OBJECT_TYPE_UNIT}, // 36 SPELL_EFFECT_LEARN_SPELL
    {EFFECT_IMPLICIT_TARGET_NONE,     TARGET_OBJECT_TYPE_UNIT}, // 37 SPELL_EFFECT_SPELL_DEFENSE
    {EFFECT_IMPLICIT_TARGET_EXPLICIT, TARGET_OBJECT_TYPE_UNIT}, // 38 SPELL_EFFECT_DISPEL
    {EFFECT_IMPLICIT_TARGET_NONE,     TARGET_OBJECT_TYPE_UNIT}, // 39 SPELL_EFFECT_LANGUAGE
    {EFFECT_IMPLICIT_TARGET_EXPLICIT, TARGET_OBJECT_TYPE_UNIT}, // 40 SPELL_EFFECT_DUAL_WIELD
    {EFFECT_IMPLICIT_TARGET_EXPLICIT, TARGET_OBJECT_TYPE_UNIT}, // 41 SPELL_EFFECT_JUMP
    {EFFECT_IMPLICIT_TARGET_NONE,     TARGET_OBJECT_TYPE_DEST}, // 42 SPELL_EFFECT_JUMP_DEST
    {EFFECT_IMPLICIT_TARGET_EXPLICIT, TARGET_OBJECT_TYPE_UNIT_AND_DEST}, // 43 SPELL_EFFECT_TELEPORT_UNITS_FACE_CASTER
    {EFFECT_IMPLICIT_TARGET_EXPLICIT, TARGET_OBJECT_TYPE_UNIT}, // 44 SPELL_EFFECT_SKILL_STEP
    {EFFECT_IMPLICIT_TARGET_EXPLICIT, TARGET_OBJECT_TYPE_UNIT}, // 45 SPELL_EFFECT_PLAY_MOVIE
    {EFFECT_IMPLICIT_TARGET_NONE,     TARGET_OBJECT_TYPE_UNIT}, // 46 SPELL_EFFECT_SPAWN
    {EFFECT_IMPLICIT_TARGET_NONE,     TARGET_OBJECT_TYPE_UNIT}, // 47 SPELL_EFFECT_TRADE_SKILL
    {EFFECT_IMPLICIT_TARGET_NONE,     TARGET_OBJECT_TYPE_UNIT}, // 48 SPELL_EFFECT_STEALTH
    {EFFECT_IMPLICIT_TARGET_NONE,     TARGET_OBJECT_TYPE_UNIT}, // 49 SPELL_EFFECT_DETECT
    {EFFECT_IMPLICIT_TARGET_EXPLICIT, TARGET_OBJECT_TYPE_DEST}, // 50 SPELL_EFFECT_TRANS_DOOR
    {EFFECT_IMPLICIT_TARGET_NONE,     TARGET_OBJECT_TYPE_UNIT}, // 51 SPELL_EFFECT_FORCE_CRITICAL_HIT
    {EFFECT_IMPLICIT_TARGET_NONE,     TARGET_OBJECT_TYPE_UNIT}, // 52 SPELL_EFFECT_GUARANTEE_HIT
    {EFFECT_IMPLICIT_TARGET_EXPLICIT, TARGET_OBJECT_TYPE_ITEM}, // 53 SPELL_EFFECT_ENCHANT_ITEM
    {EFFECT_IMPLICIT_TARGET_EXPLICIT, TARGET_OBJECT_TYPE_ITEM}, // 54 SPELL_EFFECT_ENCHANT_ITEM_TEMPORARY
    {EFFECT_IMPLICIT_TARGET_EXPLICIT, TARGET_OBJECT_TYPE_UNIT}, // 55 SPELL_EFFECT_TAMECREATURE
    {EFFECT_IMPLICIT_TARGET_EXPLICIT, TARGET_OBJECT_TYPE_DEST}, // 56 SPELL_EFFECT_SUMMON_PET
    {EFFECT_IMPLICIT_TARGET_EXPLICIT, TARGET_OBJECT_TYPE_UNIT}, // 57 SPELL_EFFECT_LEARN_PET_SPELL
    {EFFECT_IMPLICIT_TARGET_EXPLICIT, TARGET_OBJECT_TYPE_UNIT}, // 58 SPELL_EFFECT_WEAPON_DAMAGE
    {EFFECT_IMPLICIT_TARGET_EXPLICIT, TARGET_OBJECT_TYPE_UNIT}, // 59 SPELL_EFFECT_CREATE_RANDOM_ITEM
    {EFFECT_IMPLICIT_TARGET_NONE,     TARGET_OBJECT_TYPE_UNIT}, // 60 SPELL_EFFECT_PROFICIENCY
    {EFFECT_IMPLICIT_TARGET_NONE,     TARGET_OBJECT_TYPE_NONE}, // 61 SPELL_EFFECT_SEND_EVENT
    {EFFECT_IMPLICIT_TARGET_EXPLICIT, TARGET_OBJECT_TYPE_UNIT}, // 62 SPELL_EFFECT_POWER_BURN
    {EFFECT_IMPLICIT_TARGET_EXPLICIT, TARGET_OBJECT_TYPE_UNIT}, // 63 SPELL_EFFECT_THREAT
    {EFFECT_IMPLICIT_TARGET_NONE,     TARGET_OBJECT_TYPE_NONE}, // 64 SPELL_EFFECT_TRIGGER_SPELL
    {EFFECT_IMPLICIT_TARGET_EXPLICIT, TARGET_OBJECT_TYPE_UNIT}, // 65 SPELL_EFFECT_APPLY_AREA_AURA_RAID
    {EFFECT_IMPLICIT_TARGET_EXPLICIT, TARGET_OBJECT_TYPE_UNIT}, // 66 SPELL_EFFECT_CREATE_MANA_GEM
    {EFFECT_IMPLICIT_TARGET_EXPLICIT, TARGET_OBJECT_TYPE_UNIT}, // 67 SPELL_EFFECT_HEAL_MAX_HEALTH
    {EFFECT_IMPLICIT_TARGET_EXPLICIT, TARGET_OBJECT_TYPE_UNIT}, // 68 SPELL_EFFECT_INTERRUPT_CAST
    {EFFECT_IMPLICIT_TARGET_EXPLICIT, TARGET_OBJECT_TYPE_UNIT_AND_DEST}, // 69 SPELL_EFFECT_DISTRACT
    {EFFECT_IMPLICIT_TARGET_EXPLICIT, TARGET_OBJECT_TYPE_UNIT}, // 70 SPELL_EFFECT_PULL
    {EFFECT_IMPLICIT_TARGET_EXPLICIT, TARGET_OBJECT_TYPE_UNIT}, // 71 SPELL_EFFECT_PICKPOCKET
    {EFFECT_IMPLICIT_TARGET_EXPLICIT, TARGET_OBJECT_TYPE_DEST}, // 72 SPELL_EFFECT_ADD_FARSIGHT
    {EFFECT_IMPLICIT_TARGET_EXPLICIT, TARGET_OBJECT_TYPE_UNIT}, // 73 SPELL_EFFECT_UNTRAIN_TALENTS
    {EFFECT_IMPLICIT_TARGET_NONE,     TARGET_OBJECT_TYPE_UNIT}, // 74 SPELL_EFFECT_APPLY_GLYPH
    {EFFECT_IMPLICIT_TARGET_EXPLICIT, TARGET_OBJECT_TYPE_UNIT}, // 75 SPELL_EFFECT_HEAL_MECHANICAL
    {EFFECT_IMPLICIT_TARGET_EXPLICIT, TARGET_OBJECT_TYPE_DEST}, // 76 SPELL_EFFECT_SUMMON_OBJECT_WILD
    {EFFECT_IMPLICIT_TARGET_NONE,     TARGET_OBJECT_TYPE_NONE}, // 77 SPELL_EFFECT_SCRIPT_EFFECT
    {EFFECT_IMPLICIT_TARGET_NONE,     TARGET_OBJECT_TYPE_UNIT}, // 78 SPELL_EFFECT_ATTACK
    {EFFECT_IMPLICIT_TARGET_NONE,     TARGET_OBJECT_TYPE_UNIT}, // 79 SPELL_EFFECT_SANCTUARY
    {EFFECT_IMPLICIT_TARGET_EXPLICIT, TARGET_OBJECT_TYPE_UNIT}, // 80 SPELL_EFFECT_ADD_COMBO_POINTS
    {EFFECT_IMPLICIT_TARGET_EXPLICIT, TARGET_OBJECT_TYPE_DEST}, // 81 SPELL_EFFECT_CREATE_HOUSE
    {EFFECT_IMPLICIT_TARGET_EXPLICIT, TARGET_OBJECT_TYPE_UNIT}, // 82 SPELL_EFFECT_BIND_SIGHT
    {EFFECT_IMPLICIT_TARGET_EXPLICIT, TARGET_OBJECT_TYPE_UNIT_AND_DEST}, // 83 SPELL_EFFECT_DUEL
    {EFFECT_IMPLICIT_TARGET_NONE,     TARGET_OBJECT_TYPE_UNIT}, // 84 SPELL_EFFECT_STUCK
    {EFFECT_IMPLICIT_TARGET_NONE,     TARGET_OBJECT_TYPE_NONE}, // 85 SPELL_EFFECT_SUMMON_PLAYER
    {EFFECT_IMPLICIT_TARGET_EXPLICIT, TARGET_OBJECT_TYPE_GOBJ}, // 86 SPELL_EFFECT_ACTIVATE_OBJECT
    {EFFECT_IMPLICIT_TARGET_EXPLICIT, TARGET_OBJECT_TYPE_GOBJ}, // 87 SPELL_EFFECT_GAMEOBJECT_DAMAGE
    {EFFECT_IMPLICIT_TARGET_EXPLICIT, TARGET_OBJECT_TYPE_GOBJ}, // 88 SPELL_EFFECT_GAMEOBJECT_REPAIR
    {EFFECT_IMPLICIT_TARGET_EXPLICIT, TARGET_OBJECT_TYPE_GOBJ}, // 89 SPELL_EFFECT_GAMEOBJECT_SET_DESTRUCTION_STATE
    {EFFECT_IMPLICIT_TARGET_EXPLICIT, TARGET_OBJECT_TYPE_UNIT}, // 90 SPELL_EFFECT_KILL_CREDIT
    {EFFECT_IMPLICIT_TARGET_EXPLICIT, TARGET_OBJECT_TYPE_UNIT}, // 91 SPELL_EFFECT_THREAT_ALL
    {EFFECT_IMPLICIT_TARGET_EXPLICIT, TARGET_OBJECT_TYPE_UNIT}, // 92 SPELL_EFFECT_ENCHANT_HELD_ITEM
    {EFFECT_IMPLICIT_TARGET_NONE,     TARGET_OBJECT_TYPE_UNIT}, // 93 SPELL_EFFECT_FORCE_DESELECT
    {EFFECT_IMPLICIT_TARGET_NONE,     TARGET_OBJECT_TYPE_UNIT}, // 94 SPELL_EFFECT_SELF_RESURRECT
    {EFFECT_IMPLICIT_TARGET_EXPLICIT, TARGET_OBJECT_TYPE_UNIT}, // 95 SPELL_EFFECT_SKINNING
    {EFFECT_IMPLICIT_TARGET_EXPLICIT, TARGET_OBJECT_TYPE_UNIT}, // 96 SPELL_EFFECT_CHARGE
    {EFFECT_IMPLICIT_TARGET_NONE,     TARGET_OBJECT_TYPE_UNIT}, // 97 SPELL_EFFECT_CAST_BUTTON
    {EFFECT_IMPLICIT_TARGET_EXPLICIT, TARGET_OBJECT_TYPE_UNIT}, // 98 SPELL_EFFECT_KNOCK_BACK
    {EFFECT_IMPLICIT_TARGET_EXPLICIT, TARGET_OBJECT_TYPE_ITEM}, // 99 SPELL_EFFECT_DISENCHANT
    {EFFECT_IMPLICIT_TARGET_EXPLICIT, TARGET_OBJECT_TYPE_UNIT}, // 100 SPELL_EFFECT_INEBRIATE
    {EFFECT_IMPLICIT_TARGET_EXPLICIT, TARGET_OBJECT_TYPE_ITEM}, // 101 SPELL_EFFECT_FEED_PET
    {EFFECT_IMPLICIT_TARGET_EXPLICIT, TARGET_OBJECT_TYPE_UNIT}, // 102 SPELL_EFFECT_DISMISS_PET
    {EFFECT_IMPLICIT_TARGET_EXPLICIT, TARGET_OBJECT_TYPE_UNIT}, // 103 SPELL_EFFECT_REPUTATION
    {EFFECT_IMPLICIT_TARGET_EXPLICIT, TARGET_OBJECT_TYPE_DEST}, // 104 SPELL_EFFECT_SUMMON_OBJECT_SLOT1
    {EFFECT_IMPLICIT_TARGET_EXPLICIT, TARGET_OBJECT_TYPE_DEST}, // 105 SPELL_EFFECT_SUMMON_OBJECT_SLOT2
    {EFFECT_IMPLICIT_TARGET_EXPLICIT, TARGET_OBJECT_TYPE_DEST}, // 106 SPELL_EFFECT_SUMMON_OBJECT_SLOT3
    {EFFECT_IMPLICIT_TARGET_EXPLICIT, TARGET_OBJECT_TYPE_DEST}, // 107 SPELL_EFFECT_SUMMON_OBJECT_SLOT4
    {EFFECT_IMPLICIT_TARGET_EXPLICIT, TARGET_OBJECT_TYPE_UNIT}, // 108 SPELL_EFFECT_DISPEL_MECHANIC
    {EFFECT_IMPLICIT_TARGET_EXPLICIT, TARGET_OBJECT_TYPE_DEST}, // 109 SPELL_EFFECT_SUMMON_DEAD_PET
    {EFFECT_IMPLICIT_TARGET_NONE,     TARGET_OBJECT_TYPE_UNIT}, // 110 SPELL_EFFECT_DESTROY_ALL_TOTEMS
    {EFFECT_IMPLICIT_TARGET_EXPLICIT, TARGET_OBJECT_TYPE_UNIT}, // 111 SPELL_EFFECT_DURABILITY_DAMAGE
    {EFFECT_IMPLICIT_TARGET_EXPLICIT, TARGET_OBJECT_TYPE_UNIT}, // 112 SPELL_EFFECT_112
    {EFFECT_IMPLICIT_TARGET_EXPLICIT, TARGET_OBJECT_TYPE_CORPSE_ALLY}, // 113 SPELL_EFFECT_RESURRECT_NEW
    {EFFECT_IMPLICIT_TARGET_EXPLICIT, TARGET_OBJECT_TYPE_UNIT}, // 114 SPELL_EFFECT_ATTACK_ME
    {EFFECT_IMPLICIT_TARGET_EXPLICIT, TARGET_OBJECT_TYPE_UNIT}, // 115 SPELL_EFFECT_DURABILITY_DAMAGE_PCT
    {EFFECT_IMPLICIT_TARGET_EXPLICIT, TARGET_OBJECT_TYPE_CORPSE_ENEMY}, // 116 SPELL_EFFECT_SKIN_PLAYER_CORPSE
    {EFFECT_IMPLICIT_TARGET_EXPLICIT, TARGET_OBJECT_TYPE_UNIT}, // 117 SPELL_EFFECT_SPIRIT_HEAL
    {EFFECT_IMPLICIT_TARGET_NONE,     TARGET_OBJECT_TYPE_UNIT}, // 118 SPELL_EFFECT_SKILL
    {EFFECT_IMPLICIT_TARGET_EXPLICIT, TARGET_OBJECT_TYPE_UNIT}, // 119 SPELL_EFFECT_APPLY_AREA_AURA_PET
    {EFFECT_IMPLICIT_TARGET_EXPLICIT, TARGET_OBJECT_TYPE_UNIT}, // 120 SPELL_EFFECT_TELEPORT_GRAVEYARD
    {EFFECT_IMPLICIT_TARGET_EXPLICIT, TARGET_OBJECT_TYPE_UNIT}, // 121 SPELL_EFFECT_NORMALIZED_WEAPON_DMG
    {EFFECT_IMPLICIT_TARGET_NONE,     TARGET_OBJECT_TYPE_NONE}, // 122 SPELL_EFFECT_122
    {EFFECT_IMPLICIT_TARGET_EXPLICIT, TARGET_OBJECT_TYPE_UNIT}, // 123 SPELL_EFFECT_SEND_TAXI
    {EFFECT_IMPLICIT_TARGET_EXPLICIT, TARGET_OBJECT_TYPE_UNIT}, // 124 SPELL_EFFECT_PULL_TOWARDS
    {EFFECT_IMPLICIT_TARGET_EXPLICIT, TARGET_OBJECT_TYPE_UNIT}, // 125 SPELL_EFFECT_MODIFY_THREAT_PERCENT
    {EFFECT_IMPLICIT_TARGET_EXPLICIT, TARGET_OBJECT_TYPE_UNIT}, // 126 SPELL_EFFECT_STEAL_BENEFICIAL_BUFF
    {EFFECT_IMPLICIT_TARGET_EXPLICIT, TARGET_OBJECT_TYPE_ITEM}, // 127 SPELL_EFFECT_PROSPECTING
    {EFFECT_IMPLICIT_TARGET_EXPLICIT, TARGET_OBJECT_TYPE_UNIT}, // 128 SPELL_EFFECT_APPLY_AREA_AURA_FRIEND
    {EFFECT_IMPLICIT_TARGET_EXPLICIT, TARGET_OBJECT_TYPE_UNIT}, // 129 SPELL_EFFECT_APPLY_AREA_AURA_ENEMY
    {EFFECT_IMPLICIT_TARGET_EXPLICIT, TARGET_OBJECT_TYPE_UNIT}, // 130 SPELL_EFFECT_REDIRECT_THREAT
    {EFFECT_IMPLICIT_TARGET_NONE,     TARGET_OBJECT_TYPE_UNIT}, // 131 SPELL_EFFECT_PLAY_SOUND
    {EFFECT_IMPLICIT_TARGET_EXPLICIT, TARGET_OBJECT_TYPE_UNIT}, // 132 SPELL_EFFECT_PLAY_MUSIC
    {EFFECT_IMPLICIT_TARGET_EXPLICIT, TARGET_OBJECT_TYPE_UNIT}, // 133 SPELL_EFFECT_UNLEARN_SPECIALIZATION
    {EFFECT_IMPLICIT_TARGET_NONE,     TARGET_OBJECT_TYPE_UNIT}, // 134 SPELL_EFFECT_KILL_CREDIT2
    {EFFECT_IMPLICIT_TARGET_EXPLICIT, TARGET_OBJECT_TYPE_DEST}, // 135 SPELL_EFFECT_CALL_PET
    {EFFECT_IMPLICIT_TARGET_EXPLICIT, TARGET_OBJECT_TYPE_UNIT}, // 136 SPELL_EFFECT_HEAL_PCT
    {EFFECT_IMPLICIT_TARGET_EXPLICIT, TARGET_OBJECT_TYPE_UNIT}, // 137 SPELL_EFFECT_ENERGIZE_PCT
    {EFFECT_IMPLICIT_TARGET_EXPLICIT, TARGET_OBJECT_TYPE_UNIT}, // 138 SPELL_EFFECT_LEAP_BACK
    {EFFECT_IMPLICIT_TARGET_EXPLICIT, TARGET_OBJECT_TYPE_UNIT}, // 139 SPELL_EFFECT_CLEAR_QUEST
    {EFFECT_IMPLICIT_TARGET_EXPLICIT, TARGET_OBJECT_TYPE_UNIT}, // 140 SPELL_EFFECT_FORCE_CAST
    {EFFECT_IMPLICIT_TARGET_EXPLICIT, TARGET_OBJECT_TYPE_UNIT}, // 141 SPELL_EFFECT_FORCE_CAST_WITH_VALUE
    {EFFECT_IMPLICIT_TARGET_EXPLICIT, TARGET_OBJECT_TYPE_UNIT}, // 142 SPELL_EFFECT_TRIGGER_SPELL_WITH_VALUE
    {EFFECT_IMPLICIT_TARGET_EXPLICIT, TARGET_OBJECT_TYPE_UNIT}, // 143 SPELL_EFFECT_APPLY_AREA_AURA_OWNER
    {EFFECT_IMPLICIT_TARGET_EXPLICIT, TARGET_OBJECT_TYPE_UNIT_AND_DEST}, // 144 SPELL_EFFECT_KNOCK_BACK_DEST
    {EFFECT_IMPLICIT_TARGET_EXPLICIT, TARGET_OBJECT_TYPE_UNIT_AND_DEST}, // 145 SPELL_EFFECT_PULL_TOWARDS_DEST
    {EFFECT_IMPLICIT_TARGET_EXPLICIT, TARGET_OBJECT_TYPE_UNIT}, // 146 SPELL_EFFECT_ACTIVATE_RUNE
    {EFFECT_IMPLICIT_TARGET_EXPLICIT, TARGET_OBJECT_TYPE_UNIT}, // 147 SPELL_EFFECT_QUEST_FAIL
    {EFFECT_IMPLICIT_TARGET_NONE,     TARGET_OBJECT_TYPE_NONE}, // 148 SPELL_EFFECT_TRIGGER_MISSILE_SPELL_WITH_VALUE
    {EFFECT_IMPLICIT_TARGET_EXPLICIT, TARGET_OBJECT_TYPE_DEST}, // 149 SPELL_EFFECT_CHARGE_DEST
    {EFFECT_IMPLICIT_TARGET_EXPLICIT, TARGET_OBJECT_TYPE_UNIT}, // 150 SPELL_EFFECT_QUEST_START
    {EFFECT_IMPLICIT_TARGET_NONE,     TARGET_OBJECT_TYPE_NONE}, // 151 SPELL_EFFECT_TRIGGER_SPELL_2
    {EFFECT_IMPLICIT_TARGET_NONE,     TARGET_OBJECT_TYPE_NONE}, // 152 SPELL_EFFECT_SUMMON_RAF_FRIEND
    {EFFECT_IMPLICIT_TARGET_EXPLICIT, TARGET_OBJECT_TYPE_UNIT}, // 153 SPELL_EFFECT_CREATE_TAMED_PET
    {EFFECT_IMPLICIT_TARGET_EXPLICIT, TARGET_OBJECT_TYPE_UNIT}, // 154 SPELL_EFFECT_DISCOVER_TAXI
    {EFFECT_IMPLICIT_TARGET_NONE,     TARGET_OBJECT_TYPE_UNIT}, // 155 SPELL_EFFECT_TITAN_GRIP
    {EFFECT_IMPLICIT_TARGET_EXPLICIT, TARGET_OBJECT_TYPE_ITEM}, // 156 SPELL_EFFECT_ENCHANT_ITEM_PRISMATIC
    {EFFECT_IMPLICIT_TARGET_EXPLICIT, TARGET_OBJECT_TYPE_UNIT}, // 157 SPELL_EFFECT_CREATE_ITEM_2
    {EFFECT_IMPLICIT_TARGET_EXPLICIT, TARGET_OBJECT_TYPE_ITEM}, // 158 SPELL_EFFECT_MILLING
    {EFFECT_IMPLICIT_TARGET_EXPLICIT, TARGET_OBJECT_TYPE_UNIT}, // 159 SPELL_EFFECT_ALLOW_RENAME_PET
    {EFFECT_IMPLICIT_TARGET_EXPLICIT, TARGET_OBJECT_TYPE_UNIT}, // 160 SPELL_EFFECT_160
    {EFFECT_IMPLICIT_TARGET_EXPLICIT, TARGET_OBJECT_TYPE_UNIT}, // 161 SPELL_EFFECT_TALENT_SPEC_COUNT
    {EFFECT_IMPLICIT_TARGET_EXPLICIT, TARGET_OBJECT_TYPE_UNIT}, // 162 SPELL_EFFECT_TALENT_SPEC_SELECT
    {EFFECT_IMPLICIT_TARGET_EXPLICIT, TARGET_OBJECT_TYPE_UNIT}, // 163 SPELL_EFFECT_163
    {EFFECT_IMPLICIT_TARGET_EXPLICIT, TARGET_OBJECT_TYPE_UNIT}, // 164 SPELL_EFFECT_REMOVE_AURA
};

SpellInfo::SpellInfo(SpellEntry const* spellEntry, uint32 difficulty)
{
    Id = spellEntry->Id;
    AttributesCu = 0;

    SpellName = spellEntry->SpellName;
    Rank = spellEntry->Rank;
    RuneCostID = spellEntry->runeCostID;
    SpellDifficultyId = 0;
    SpellScalingId = spellEntry->SpellScalingId;
    SpellAuraOptionsId = spellEntry->SpellAuraOptionsId;
    SpellAuraRestrictionsId = spellEntry->SpellAuraRestrictionsId;
    SpellCastingRequirementsId = spellEntry->SpellCastingRequirementsId;
    SpellCategoriesId = spellEntry->SpellCategoriesId;
    SpellClassOptionsId = spellEntry->SpellClassOptionsId;
    SpellCooldownsId = spellEntry->SpellCooldownsId;
    SpellEquippedItemsId = spellEntry->SpellEquippedItemsId;
    SpellInterruptsId = spellEntry->SpellInterruptsId;
    SpellLevelsId = spellEntry->SpellLevelsId;
   // SpellPowerId = spellEntry->SpellPowerId;
    SpellReagentsId = spellEntry->SpellReagentsId;
    SpellShapeshiftId = spellEntry->SpellShapeshiftId;
    SpellTargetRestrictionsId = spellEntry->SpellTargetRestrictionsId;
    SpellTotemsId = spellEntry->SpellTotemsId;
    SpellMiscId = spellEntry->SpellMiscId;

    // SpellDifficultyEntry
    for (uint8 i = 0; i < MAX_SPELL_EFFECTS; ++i)
        Effects[i] = SpellEffectInfo(spellEntry, this, i, difficulty);

    // SpellScalingEntry
    SpellScalingEntry const* _scaling = GetSpellScaling();
    CastTimeMin = _scaling ? _scaling->CastTimeMin : 0;
    CastTimeMax = _scaling ?_scaling->CastTimeMax : 0;
    CastTimeMaxLevel = _scaling ? _scaling->CastTimeMaxLevel : 0;
    ScalingClass = _scaling ? _scaling->ScalingClass : 0;
    CoefBase = _scaling ? _scaling->CoefBase : 0;
    CoefLevelBase = _scaling ? _scaling->CoefLevelBase : 0;

    // SpellAuraOptionsEntry
    SpellAuraOptionsEntry const* _options = GetSpellAuraOptions();
    ProcFlags = _options ? _options->procFlags : 0;
    ProcChance = _options ? _options->procChance : 0;
    ProcCharges = _options ? _options->procCharges : 0;
    StackAmount = _options ? _options->StackAmount : 0;

    // SpellAuraRestrictionsEntry
    SpellAuraRestrictionsEntry const* _aura = GetSpellAuraRestrictions();
    CasterAuraState = _aura ? _aura->CasterAuraState : 0;
    TargetAuraState = _aura ? _aura->TargetAuraState : 0;
    CasterAuraStateNot = _aura ? _aura->CasterAuraStateNot : 0;
    TargetAuraStateNot = _aura ? _aura->TargetAuraStateNot : 0;
    CasterAuraSpell = _aura ? _aura->casterAuraSpell : 0;
    TargetAuraSpell = _aura ? _aura->targetAuraSpell : 0;
    ExcludeCasterAuraSpell = _aura ? _aura->excludeCasterAuraSpell : 0;
    ExcludeTargetAuraSpell = _aura ? _aura->excludeTargetAuraSpell : 0;

    // SpellCastingRequirementsEntry
    SpellCastingRequirementsEntry const* _castreq = GetSpellCastingRequirements();
    RequiresSpellFocus = _castreq ? _castreq->RequiresSpellFocus : 0;
    FacingCasterFlags = _castreq ? _castreq->FacingCasterFlags : 0;
    AreaGroupId = _castreq ? _castreq->AreaGroupId : -1;

    // SpellCategoriesEntry
    SpellCategoriesEntry const* _categorie = GetSpellCategories();
    Category = _categorie ? _categorie->Category : 0;
    Dispel = _categorie ? _categorie->Dispel : 0;
    Mechanic = _categorie ? _categorie->Mechanic : 0;
    StartRecoveryCategory = _categorie ? _categorie->StartRecoveryCategory : 0;
    DmgClass = _categorie ? _categorie->DmgClass : 0;
    PreventionType = _categorie ? _categorie->PreventionType : 0;

    if (SpellCategoryEntry const* categoryInfo = sSpellCategoryStores.LookupEntry(Category))
    	CategoryFlags = categoryInfo->Flags;
    else
    	CategoryFlags = 0;

    // SpellClassOptionsEntry
    SpellClassOptionsEntry const* _class = GetSpellClassOptions();
    SpellFamilyName = _class ? _class->SpellFamilyName : 0;
    SpellFamilyFlags = _class ? _class->SpellFamilyFlags : flag96(0);

    // SpellCooldownsEntry
    SpellCooldownsEntry const* _cooldowns = GetSpellCooldowns();
    RecoveryTime = _cooldowns ? _cooldowns->RecoveryTime : 0;
    CategoryRecoveryTime = _cooldowns ? _cooldowns->CategoryRecoveryTime : 0;
    StartRecoveryTime = _cooldowns ? _cooldowns->StartRecoveryTime : 0;

    // SpellEquippedItemsEntry
    SpellEquippedItemsEntry const* _equipped = GetSpellEquippedItems();
    EquippedItemClass = _equipped ? _equipped->EquippedItemClass : -1;
    EquippedItemSubClassMask = _equipped ?_equipped->EquippedItemSubClassMask : -1;
    EquippedItemInventoryTypeMask = _equipped ? _equipped->EquippedItemInventoryTypeMask : -1;

    // SpellInterruptsEntry
    SpellInterruptsEntry const* _interrupt = GetSpellInterrupts();
    InterruptFlags = _interrupt ? _interrupt->InterruptFlags : 0;
    AuraInterruptFlags = _interrupt ? _interrupt->AuraInterruptFlags : 0;
    ChannelInterruptFlags = _interrupt ? _interrupt->ChannelInterruptFlags : 0;

    // SpellLevelsEntry
    SpellLevelsEntry const* _levels = GetSpellLevels();
    MaxLevel = _levels ? _levels->maxLevel : 0;
    BaseLevel = _levels ? _levels->baseLevel : 0;
    SpellLevel = _levels ? _levels->spellLevel : 0;

    // SpellPowerEntry
    ManaCost =  0;
    ManaCostPercentage = 0;
    ManaPerSecond = 0;
    PowerType = POWER_MANA;

    spellPower = new SpellPowerEntry();
    spellPower->manaCost = 0;
    spellPower->ManaCostPercentage = 0;
    spellPower->manaPerSecond = 0;
    spellPower->SpellId = Id;
    spellPower->powerType = POWER_MANA;

    // SpellMiscEntry
    SpellMiscEntry const* _misc = GetSpellMisc();
    Attributes = _misc ? _misc->Attributes : 0;
    AttributesEx = _misc ? _misc->AttributesEx : 0;
    AttributesEx2 = _misc ? _misc->AttributesEx2 : 0;
    AttributesEx3 = _misc ? _misc->AttributesEx3 : 0;
    AttributesEx4 = _misc ? _misc->AttributesEx4 : 0;
    AttributesEx5 = _misc ? _misc->AttributesEx5 : 0;
    AttributesEx6 = _misc ? _misc->AttributesEx6 : 0;
    AttributesEx7 = _misc ? _misc->AttributesEx7 : 0;
    AttributesEx8 = _misc ? _misc->AttributesEx8 : 0;
    AttributesEx9 = _misc ? _misc->AttributesEx9 : 0;
    AttributesEx10 = _misc ? _misc->AttributesEx10 : 0;
    AttributesEx11 = _misc ? _misc->AttributesEx11 : 0;

    uint32 castingTimeIndex = _misc ? _misc->CastingTimeIndex : 0;
    uint32 durationIndex = _misc ? _misc->DurationIndex : 0;
    uint32 rangeIndex = _misc ? _misc->rangeIndex : 0;

    CastTimeEntry = sSpellCastTimesStore.LookupEntry(castingTimeIndex);
    DurationEntry = sSpellDurationStore.LookupEntry(durationIndex);
    //PowerType = spellEntry->powerType; WTF
    RangeEntry = sSpellRangeStore.LookupEntry(rangeIndex);
    Speed = _misc ? _misc->speed : 1.00f;
    for (uint8 i = 0; i < 2; ++i)
        SpellVisual[i] = _misc ? _misc->SpellVisual[i] : 0;
    SpellIconID = _misc ? _misc->SpellIconID : 0;
    ActiveIconID = _misc ? _misc->activeIconID : 0;
    SchoolMask = _misc ? _misc->SchoolMask : 0;


    // SpellReagentsEntry
    SpellReagentsEntry const* _reagents = GetSpellReagents();
    for (uint8 i = 0; i < MAX_SPELL_REAGENTS; ++i)
        Reagent[i] = _reagents ? _reagents->Reagent[i] : 0;
    for (uint8 i = 0; i < MAX_SPELL_REAGENTS; ++i)
        ReagentCount[i] = _reagents ? _reagents->ReagentCount[i] : 0;

    // SpellShapeshiftEntry
    SpellShapeshiftEntry const* _shapeshift = GetSpellShapeshift();
    Stances = _shapeshift ? _shapeshift->Stances : 0;
    StancesNot = _shapeshift ? _shapeshift->StancesNot : 0;

    // SpellTargetRestrictionsEntry
    SpellTargetRestrictionsEntry const* _target = GetSpellTargetRestrictions();
    Targets = _target ? _target->Targets : 0;
    TargetCreatureType = _target ? _target->TargetCreatureType : 0;
    MaxAffectedTargets = _target ? _target->MaxAffectedTargets : 0;

    // SpellTotemsEntry
    SpellTotemsEntry const* _totem = GetSpellTotems();
    for (uint8 i = 0; i < 2; ++i)
        TotemCategory[i] = _totem ? _totem->TotemCategory[i] : 0;
    for (uint8 i = 0; i < 2; ++i)
        Totem[i] = _totem ? _totem->Totem[i] : 0;

    // SpecializationSpellsEntry
    SpecializationSpellEntry const* specializationInfo = NULL;
    for (uint32 i = 0; i < sSpecializationSpellStore.GetNumRows(); i++)
    {
        specializationInfo = sSpecializationSpellStore.LookupEntry(i);
        if(!specializationInfo)
            continue;

        if (specializationInfo->LearnSpell == Id)
            SpecializationIdList.push_back(specializationInfo->SpecializationEntry);

        if(specializationInfo->OverrideSpell == Id)
            OverrideSpellList.push_back(specializationInfo->LearnSpell);
    }

    talentId = 0;

    ExplicitTargetMask = _GetExplicitTargetMask();
    ChainEntry = NULL;
}

SpellInfo::~SpellInfo()
{
    _UnloadImplicitTargetConditionLists();
}

bool SpellInfo::HasEffect(SpellEffects effect) const
{
    for (uint8 i = 0; i < MAX_SPELL_EFFECTS; ++i)
        if (Effects[i].IsEffect(effect))
            return true;
    return false;
}

bool SpellInfo::HasAura(AuraType aura) const
{
    for (uint8 i = 0; i < MAX_SPELL_EFFECTS; ++i)
        if (Effects[i].IsAura(aura))
            return true;
    return false;
}

bool SpellInfo::HasAreaAuraEffect() const
{
    for (uint8 i = 0; i < MAX_SPELL_EFFECTS; ++i)
        if (Effects[i].IsAreaAuraEffect())
            return true;
    return false;
}

bool SpellInfo::HasPersistenAura() const
{
    for (uint8 i = 0; i < MAX_SPELL_EFFECTS; ++i)
        if (Effects[i].IsPersistenAura())
            return true;
    return false;
}

bool SpellInfo::IsExplicitDiscovery() const
{
    return ((Effects[0].Effect == SPELL_EFFECT_CREATE_RANDOM_ITEM
        || Effects[0].Effect == SPELL_EFFECT_CREATE_ITEM_2)
        && Effects[1].Effect == SPELL_EFFECT_SCRIPT_EFFECT)
        || Id == 64323 || Id == 112996;
}

bool SpellInfo::IsLootCrafting() const
{
    return (Effects[0].Effect == SPELL_EFFECT_CREATE_RANDOM_ITEM ||
        // different random cards from Inscription (121==Virtuoso Inking Set category) r without explicit item
        (Effects[0].Effect == SPELL_EFFECT_CREATE_ITEM_2 &&
        (TotemCategory[0] != 0 || Effects[0].ItemType == 0)));
}

bool SpellInfo::IsQuestTame() const
{
    return Effects[0].Effect == SPELL_EFFECT_THREAT && Effects[1].Effect == SPELL_EFFECT_APPLY_AURA && Effects[1].ApplyAuraName == SPELL_AURA_DUMMY;
}

bool SpellInfo::IsProfessionOrRiding() const
{
    for (uint8 i = 0; i < MAX_SPELL_EFFECTS; ++i)
    {
        if (Effects[i].Effect == SPELL_EFFECT_SKILL)
        {
            uint32 skill = Effects[i].MiscValue;

            if (IsProfessionOrRidingSkill(skill))
                return true;
        }
    }
    return false;
}

bool SpellInfo::IsProfession() const
{
    for (uint8 i = 0; i < MAX_SPELL_EFFECTS; ++i)
    {
        if (Effects[i].Effect == SPELL_EFFECT_SKILL)
        {
            uint32 skill = Effects[i].MiscValue;

            if (IsProfessionSkill(skill))
                return true;
        }
    }
    return false;
}

bool SpellInfo::IsPrimaryProfession() const
{
    for (uint8 i = 0; i < MAX_SPELL_EFFECTS; ++i)
    {
        if (Effects[i].Effect == SPELL_EFFECT_SKILL)
        {
            uint32 skill = Effects[i].MiscValue;

            if (IsPrimaryProfessionSkill(skill))
                return true;
        }
    }
    return false;
}

bool SpellInfo::IsPrimaryProfessionFirstRank() const
{
    return IsPrimaryProfession() && GetRank() == 1;
}

bool SpellInfo::IsAbilityLearnedWithProfession() const
{
    SkillLineAbilityMapBounds bounds = sSpellMgr->GetSkillLineAbilityMapBounds(Id);

    for (SkillLineAbilityMap::const_iterator _spell_idx = bounds.first; _spell_idx != bounds.second; ++_spell_idx)
    {
        SkillLineAbilityEntry const* pAbility = _spell_idx->second;
        if (!pAbility || pAbility->learnOnGetSkill != ABILITY_LEARNED_ON_GET_PROFESSION_SKILL)
            continue;

        if (pAbility->req_skill_value > 0)
            return true;
    }

    return false;
}

bool SpellInfo::IsAbilityOfSkillType(uint32 skillType) const
{
    SkillLineAbilityMapBounds bounds = sSpellMgr->GetSkillLineAbilityMapBounds(Id);

    for (SkillLineAbilityMap::const_iterator _spell_idx = bounds.first; _spell_idx != bounds.second; ++_spell_idx)
        if (_spell_idx->second->skillId == uint32(skillType))
            return true;

    return false;
}

bool SpellInfo::IsAffectingArea() const
{
    for (uint8 i = 0; i < MAX_SPELL_EFFECTS; ++i)
        if (Effects[i].IsEffect() && (Effects[i].IsTargetingArea() || Effects[i].IsEffect(SPELL_EFFECT_PERSISTENT_AREA_AURA) || Effects[i].IsAreaAuraEffect()))
            return true;
    return false;
}

// checks if spell targets are selected from area, doesn't include spell effects in check (like area wide auras for example)
bool SpellInfo::IsTargetingArea() const
{
    for (uint8 i = 0; i < MAX_SPELL_EFFECTS; ++i)
        if (Effects[i].IsEffect() && Effects[i].IsTargetingArea())
            return true;
    return false;
}

bool SpellInfo::NeedsExplicitUnitTarget() const
{
    return GetExplicitTargetMask() & TARGET_FLAG_UNIT_MASK;
}

bool SpellInfo::NeedsToBeTriggeredByCaster() const
{
    if (NeedsExplicitUnitTarget())
        return true;
    for (uint8 i = 0; i < MAX_SPELL_EFFECTS; ++i)
    {
        if (Effects[i].IsEffect())
        {
            if (Effects[i].TargetA.GetSelectionCategory() == TARGET_SELECT_CATEGORY_CHANNEL
                || Effects[i].TargetB.GetSelectionCategory() == TARGET_SELECT_CATEGORY_CHANNEL)
                return true;
        }
    }
    return false;
}

bool SpellInfo::IsPassive() const
{
    return Attributes & SPELL_ATTR0_PASSIVE;
}

bool SpellInfo::IsAutocastable() const
{
    if (Attributes & SPELL_ATTR0_PASSIVE)
        return false;
    if (AttributesEx & SPELL_ATTR1_UNAUTOCASTABLE_BY_PET)
        return false;
    return true;
}

bool SpellInfo::IsStackableWithRanks() const
{
    if (IsPassive())
        return false;
    if (PowerType != POWER_MANA && PowerType != POWER_HEALTH)
        return false;
    if (IsProfessionOrRiding())
        return false;

    if (IsAbilityLearnedWithProfession())
        return false;

    // All stance spells. if any better way, change it.
    for (uint8 i = 0; i < MAX_SPELL_EFFECTS; ++i)
    {
        switch (SpellFamilyName)
        {
            case SPELLFAMILY_PALADIN:
                // Paladin aura Spell
                if (Effects[i].Effect == SPELL_EFFECT_APPLY_AREA_AURA_RAID)
                    return false;
                break;
            case SPELLFAMILY_DRUID:
                // Druid form Spell
                if (Effects[i].Effect == SPELL_EFFECT_APPLY_AURA &&
                    Effects[i].ApplyAuraName == SPELL_AURA_MOD_SHAPESHIFT)
                    return false;
                break;
        }
    }
    return true;
}

bool SpellInfo::IsPassiveStackableWithRanks() const
{
    return IsPassive() && !HasEffect(SPELL_EFFECT_APPLY_AURA);
}

bool SpellInfo::IsMultiSlotAura() const
{
    return (IsPassive() || Id == 44413) && Id != 76856; // hack fix for Unshackled Fury stacking with itself
}

bool SpellInfo::IsDeathPersistent() const
{
    return AttributesEx3 & SPELL_ATTR3_DEATH_PERSISTENT;
}

bool SpellInfo::IsRequiringDeadTarget() const
{
    return AttributesEx3 & SPELL_ATTR3_ONLY_TARGET_GHOSTS;
}

bool SpellInfo::IsAllowingDeadTarget() const
{
    return AttributesEx2 & SPELL_ATTR2_CAN_TARGET_DEAD || Targets & (TARGET_FLAG_CORPSE_ALLY | TARGET_FLAG_CORPSE_ENEMY | TARGET_FLAG_UNIT_DEAD);
}

bool SpellInfo::CanBeUsedInCombat() const
{
    return !(Attributes & SPELL_ATTR0_CANT_USED_IN_COMBAT);
}

bool SpellInfo::IsPositive() const
{
    return !(AttributesCu & SPELL_ATTR0_CU_NEGATIVE);
}

bool SpellInfo::IsPositiveEffect(uint8 effIndex) const
{
    switch (effIndex)
    {
        default:
        case 0:
            return !(AttributesCu & SPELL_ATTR0_CU_NEGATIVE_EFF0);
        case 1:
            return !(AttributesCu & SPELL_ATTR0_CU_NEGATIVE_EFF1);
        case 2:
            return !(AttributesCu & SPELL_ATTR0_CU_NEGATIVE_EFF2);
    }
}

bool SpellInfo::IsChanneled() const
{
    return (AttributesEx & (SPELL_ATTR1_CHANNELED_1 | SPELL_ATTR1_CHANNELED_2));
}

bool SpellInfo::NeedsComboPoints() const
{
    return (AttributesEx & (SPELL_ATTR1_REQ_COMBO_POINTS1 | SPELL_ATTR1_REQ_COMBO_POINTS2));
}

bool SpellInfo::IsBreakingStealth() const
{
    return !(AttributesEx & SPELL_ATTR1_NOT_BREAK_STEALTH);
}

bool SpellInfo::IsRangedWeaponSpell() const
{
    return (SpellFamilyName == SPELLFAMILY_HUNTER && !(SpellFamilyFlags[1] & 0x10000000)) // for 53352, cannot find better way
        || (EquippedItemSubClassMask & ITEM_SUBCLASS_MASK_WEAPON_RANGED);
}

bool SpellInfo::IsAutoRepeatRangedSpell() const
{
    return AttributesEx2 & SPELL_ATTR2_AUTOREPEAT_FLAG;
}

bool SpellInfo::IsAffectedBySpellMods() const
{
    return !(AttributesEx3 & SPELL_ATTR3_NO_DONE_BONUS);
}

bool SpellInfo::IsAffectedBySpellMod(SpellModifier* mod) const
{
    if (!IsAffectedBySpellMods())
        return false;

    SpellInfo const* affectSpell = sSpellMgr->GetSpellInfo(mod->spellId);
    // False if affect_spell == NULL or spellFamily not equal
    if (!affectSpell || affectSpell->SpellFamilyName != SpellFamilyName)
        return false;

    // true
    if (mod->mask & SpellFamilyFlags)
        return true;

    // Elemental Blast is affected by Ancestral Swiftness and Maelstrom Weapon
    if (Id == 117014 && (affectSpell->Id == 16188 || affectSpell->Id == 53817))
        return true;

    return false;
}

bool SpellInfo::CanPierceImmuneAura(SpellInfo const* aura) const
{
    // these spells pierce all avalible spells (Resurrection Sickness for example)
    if (Attributes & SPELL_ATTR0_UNAFFECTED_BY_INVULNERABILITY)
        return true;

    if (aura && aura->Id == 33786)
    {
        // Re-cyclone & Fiery Fire
        if (Id == aura->Id || SpellIconID == 109)
            return false;
    }

    // these spells (Cyclone for example) can pierce all...
    if ((AttributesEx & SPELL_ATTR1_UNAFFECTED_BY_SCHOOL_IMMUNE)
        // ...but not these (Divine shield for example)
        && !(aura && (aura->Mechanic == MECHANIC_IMMUNE_SHIELD || aura->Mechanic == MECHANIC_INVULNERABILITY || aura->Id == 48707)))
        return true;

    return false;
}

bool SpellInfo::CanDispelAura(SpellInfo const* aura) const
{
    // These spells (like Mass Dispel) can dispell all auras
    if (Attributes & SPELL_ATTR0_UNAFFECTED_BY_INVULNERABILITY)
        return true;

    // These auras (like Divine Shield) can't be dispelled
    if (aura->Attributes & SPELL_ATTR0_UNAFFECTED_BY_INVULNERABILITY)
        return false;

    // These auras (Cyclone for example) are not dispelable
    if (aura->AttributesEx & SPELL_ATTR1_UNAFFECTED_BY_SCHOOL_IMMUNE)
        return false;

    return true;
}

bool SpellInfo::IsSingleTarget() const
{
    // all other single target spells have if it has AttributesEx5
    if (AttributesEx5 & SPELL_ATTR5_SINGLE_TARGET_SPELL)
        return true;

    switch (GetSpellSpecific())
    {
        case SPELL_SPECIFIC_JUDGEMENT:
            return true;
        default:
            break;
    }

    return false;
}

bool SpellInfo::IsSingleTargetWith(SpellInfo const* spellInfo) const
{
    // TODO - need better check
    // Equal icon and spellfamily
    if (SpellFamilyName == spellInfo->SpellFamilyName &&
        SpellIconID == spellInfo->SpellIconID)
        return true;

    SpellSpecificType spec = GetSpellSpecific();
    // spell with single target specific types
    switch (spec)
    {
        case SPELL_SPECIFIC_JUDGEMENT:
        case SPELL_SPECIFIC_MAGE_POLYMORPH:
            if (spellInfo->GetSpellSpecific() == spec)
                return true;
            break;
        default:
            break;
    }

    return false;
}

bool SpellInfo::IsAuraExclusiveBySpecificWith(SpellInfo const* spellInfo) const
{
    SpellSpecificType spellSpec1 = GetSpellSpecific();
    SpellSpecificType spellSpec2 = spellInfo->GetSpellSpecific();
    switch (spellSpec1)
    {
        case SPELL_SPECIFIC_TRACKER:
        case SPELL_SPECIFIC_WARLOCK_ARMOR:
        case SPELL_SPECIFIC_MAGE_ARMOR:
        case SPELL_SPECIFIC_ELEMENTAL_SHIELD:
        case SPELL_SPECIFIC_MAGE_POLYMORPH:
        case SPELL_SPECIFIC_PRESENCE:
        case SPELL_SPECIFIC_CHARM:
        case SPELL_SPECIFIC_SCROLL:
        case SPELL_SPECIFIC_WARRIOR_ENRAGE:
        case SPELL_SPECIFIC_MAGE_ARCANE_BRILLANCE:
        case SPELL_SPECIFIC_PRIEST_DIVINE_SPIRIT:
            return spellSpec1 == spellSpec2;
        case SPELL_SPECIFIC_FOOD:
            return spellSpec2 == SPELL_SPECIFIC_FOOD
                || spellSpec2 == SPELL_SPECIFIC_FOOD_AND_DRINK;
        case SPELL_SPECIFIC_DRINK:
            return spellSpec2 == SPELL_SPECIFIC_DRINK
                || spellSpec2 == SPELL_SPECIFIC_FOOD_AND_DRINK;
        case SPELL_SPECIFIC_FOOD_AND_DRINK:
            return spellSpec2 == SPELL_SPECIFIC_FOOD
                || spellSpec2 == SPELL_SPECIFIC_DRINK
                || spellSpec2 == SPELL_SPECIFIC_FOOD_AND_DRINK;
        default:
            return false;
    }
}

bool SpellInfo::IsAuraExclusiveBySpecificPerCasterWith(SpellInfo const* spellInfo) const
{
    SpellSpecificType spellSpec = GetSpellSpecific();
    switch (spellSpec)
    {
        case SPELL_SPECIFIC_SEAL:
        case SPELL_SPECIFIC_HAND:
        case SPELL_SPECIFIC_AURA:
        case SPELL_SPECIFIC_STING:
        case SPELL_SPECIFIC_CURSE:
        case SPELL_SPECIFIC_BANE:
        case SPELL_SPECIFIC_ASPECT:
        case SPELL_SPECIFIC_JUDGEMENT:
        case SPELL_SPECIFIC_WARLOCK_CORRUPTION:
        case SPELL_SPECIFIC_CHAKRA:
            return spellSpec == spellInfo->GetSpellSpecific();
        default:
            return false;
    }
}

SpellCastResult SpellInfo::CheckShapeshift(uint32 form) const
{
    // talents that learn spells can have stance requirements that need ignore
    // (this requirement only for client-side stance show in talent description)
    if (/*GetTalentSpellCost(Id) > 0 &&*/
        (Effects[0].Effect == SPELL_EFFECT_LEARN_SPELL || Effects[1].Effect == SPELL_EFFECT_LEARN_SPELL || Effects[2].Effect == SPELL_EFFECT_LEARN_SPELL))
        return SPELL_CAST_OK;

    uint32 stanceMask = (form ? 1 << (form - 1) : 0);

    if (stanceMask & StancesNot)                 // can explicitly not be casted in this stance
        return SPELL_FAILED_NOT_SHAPESHIFT;

    if (stanceMask & Stances)                    // can explicitly be casted in this stance
        return SPELL_CAST_OK;

    bool actAsShifted = false;
    SpellShapeshiftFormEntry const* shapeInfo = NULL;
    if (form > 0)
    {
        shapeInfo = sSpellShapeshiftFormStore.LookupEntry(form);
        if (!shapeInfo)
        {
            sLog->outError(LOG_FILTER_SPELLS_AURAS, "GetErrorAtShapeshiftedCast: unknown shapeshift %u", form);
            return SPELL_CAST_OK;
        }
        actAsShifted = !(shapeInfo->flags1 & 1);            // shapeshift acts as normal form for spells
    }

    if (actAsShifted)
    {
        if (Attributes & SPELL_ATTR0_NOT_SHAPESHIFT) // not while shapeshifted
            return SPELL_FAILED_NOT_SHAPESHIFT;
        else if (Stances != 0)                   // needs other shapeshift
            return SPELL_FAILED_ONLY_SHAPESHIFT;
    }
    else
    {
        // needs shapeshift
        if (!(AttributesEx2 & SPELL_ATTR2_NOT_NEED_SHAPESHIFT) && Stances != 0)
            return SPELL_FAILED_ONLY_SHAPESHIFT;
    }

    // Check if stance disables cast of not-stance spells
    // Example: cannot cast any other spells in zombie or ghoul form
    // TODO: Find a way to disable use of these spells clientside
    if (shapeInfo && shapeInfo->flags1 & 0x400)
    {
        if (!(stanceMask & Stances))
            return SPELL_FAILED_ONLY_SHAPESHIFT;
    }

    return SPELL_CAST_OK;
}

SpellCastResult SpellInfo::CheckLocation(uint32 map_id, uint32 zone_id, uint32 area_id, Player const* player) const
{
    // normal case
    if (AreaGroupId > 0)
    {
        bool found = false;
        AreaGroupEntry const* groupEntry = sAreaGroupStore.LookupEntry(AreaGroupId);
        while (groupEntry)
        {
            for (uint8 i = 0; i < MAX_GROUP_AREA_IDS; ++i)
                if (groupEntry->AreaId[i] == zone_id || groupEntry->AreaId[i] == area_id)
                    found = true;
            if (found || !groupEntry->nextGroup)
                break;
            // Try search in next group
            groupEntry = sAreaGroupStore.LookupEntry(groupEntry->nextGroup);
        }

        if (!found)
            return SPELL_FAILED_INCORRECT_AREA;
    }

    // continent limitation (virtual continent)
    if (AttributesEx4 & SPELL_ATTR4_CAST_ONLY_IN_OUTLAND)
    {
        uint32 v_map = GetVirtualMapForMapAndZone(map_id, zone_id);
        MapEntry const* mapEntry = sMapStore.LookupEntry(v_map);
        if (!mapEntry || mapEntry->addon < 1 || !mapEntry->IsContinent())
            return SPELL_FAILED_INCORRECT_AREA;
    }

    // raid instance limitation
    if (AttributesEx6 & SPELL_ATTR6_NOT_IN_RAID_INSTANCE)
    {
        MapEntry const* mapEntry = sMapStore.LookupEntry(map_id);
        if (!mapEntry || mapEntry->IsRaid())
            return SPELL_FAILED_NOT_IN_RAID_INSTANCE;
    }

    // DB base check (if non empty then must fit at least single for allow)
    SpellAreaMapBounds saBounds = sSpellMgr->GetSpellAreaMapBounds(Id);
    if (saBounds.first != saBounds.second)
    {
        for (SpellAreaMap::const_iterator itr = saBounds.first; itr != saBounds.second; ++itr)
        {
            if (itr->second.IsFitToRequirements(player, zone_id, area_id))
                return SPELL_CAST_OK;
        }
        return SPELL_FAILED_INCORRECT_AREA;
    }

    // bg spell checks
    switch (Id)
    {
        case 29534:                                         // Traces of Silithyst
            return zone_id == 1377 ? SPELL_CAST_OK : SPELL_FAILED_REQUIRES_AREA;
        case 23333:                                         // Warsong Flag
        case 23335:                                         // Silverwing Flag
            return (map_id == 489 || map_id == 726) && player && player->InBattleground() ? SPELL_CAST_OK : SPELL_FAILED_REQUIRES_AREA;
        case 34976:                                         // Netherstorm Flag
            return map_id == 566 && player && player->InBattleground() ? SPELL_CAST_OK : SPELL_FAILED_REQUIRES_AREA;
        case 2584:                                          // Waiting to Resurrect
        case 22011:                                         // Spirit Heal Channel
        case 22012:                                         // Spirit Heal
        case 24171:                                         // Resurrection Impact Visual
        case 42792:                                         // Recently Dropped Flag
        case 43681:                                         // Inactive
        case 44535:                                         // Spirit Heal (mana)
        {
            MapEntry const* mapEntry = sMapStore.LookupEntry(map_id);
            if (!mapEntry)
                return SPELL_FAILED_INCORRECT_AREA;

            return zone_id == 4197 || (mapEntry->IsBattleground() && player && player->InBattleground()) ? SPELL_CAST_OK : SPELL_FAILED_REQUIRES_AREA;
        }
        case 44521:                                         // Preparation
        {
            if (!player)
                return SPELL_FAILED_REQUIRES_AREA;

            MapEntry const* mapEntry = sMapStore.LookupEntry(map_id);
            if (!mapEntry)
                return SPELL_FAILED_INCORRECT_AREA;

            if (!mapEntry->IsBattleground())
                return SPELL_FAILED_REQUIRES_AREA;

            Battleground* bg = player->GetBattleground();
            return bg && bg->GetStatus() == STATUS_WAIT_JOIN ? SPELL_CAST_OK : SPELL_FAILED_REQUIRES_AREA;
        }
        case 32724:                                         // Gold Team (Alliance)
        case 32725:                                         // Green Team (Alliance)
        case 35774:                                         // Gold Team (Horde)
        case 35775:                                         // Green Team (Horde)
        {
            MapEntry const* mapEntry = sMapStore.LookupEntry(map_id);
            if (!mapEntry)
                return SPELL_FAILED_INCORRECT_AREA;

            return mapEntry->IsBattleArena() && player && player->InBattleground() ? SPELL_CAST_OK : SPELL_FAILED_REQUIRES_AREA;
        }
        case 32727:                                         // Arena Preparation
        {
            if (!player)
                return SPELL_FAILED_REQUIRES_AREA;

            MapEntry const* mapEntry = sMapStore.LookupEntry(map_id);
            if (!mapEntry)
                return SPELL_FAILED_INCORRECT_AREA;

            if (!mapEntry->IsBattleArena())
                return SPELL_FAILED_REQUIRES_AREA;

            Battleground* bg = player->GetBattleground();
            return bg && bg->GetStatus() == STATUS_WAIT_JOIN ? SPELL_CAST_OK : SPELL_FAILED_REQUIRES_AREA;
        }
    }

    // aura limitations
    if (player)
    {
        for (uint8 i = 0; i < MAX_SPELL_EFFECTS; ++i)
        {
            if (!Effects[i].IsAura())
                continue;

            switch (Effects[i].ApplyAuraName)
            {
                case SPELL_AURA_FLY:
                {
                    if (!player->IsKnowHowFlyIn(map_id, zone_id))
                        return SPELL_FAILED_INCORRECT_AREA;
                    break;
                }
                case SPELL_AURA_MOUNTED:
                {
                    if (Effects[i].MiscValueB && !player->GetMountCapability(Effects[i].MiscValueB))
                        return SPELL_FAILED_NOT_HERE;
                    break;
                }
            }
        }
    }

    return SPELL_CAST_OK;
}

SpellCastResult SpellInfo::CheckTarget(Unit const* caster, WorldObject const* target, bool implicit) const
{
    if (AttributesEx & SPELL_ATTR1_CANT_TARGET_SELF && caster == target)
        return SPELL_FAILED_BAD_TARGETS;

    // check visibility - ignore stealth for implicit (area) targets
    if (!(AttributesEx6 & SPELL_ATTR6_CAN_TARGET_INVISIBLE) && !caster->canSeeOrDetect(target, implicit))
        return SPELL_FAILED_BAD_TARGETS;

    Unit const* unitTarget = target->ToUnit();

    // creature/player specific target checks
    if (unitTarget)
    {
        if (AttributesEx & SPELL_ATTR1_CANT_TARGET_IN_COMBAT && unitTarget->isInCombat())
            return SPELL_FAILED_TARGET_AFFECTING_COMBAT;

        // only spells with SPELL_ATTR3_ONLY_TARGET_GHOSTS can target ghosts
        if (((AttributesEx3 & SPELL_ATTR3_ONLY_TARGET_GHOSTS) != 0) != unitTarget->HasAuraType(SPELL_AURA_GHOST))
        {
            if (AttributesEx3 & SPELL_ATTR3_ONLY_TARGET_GHOSTS)
                return SPELL_FAILED_TARGET_NOT_GHOST;
            else
                return SPELL_FAILED_BAD_TARGETS;
        }

        if (caster != unitTarget)
        {
            if (caster->GetTypeId() == TYPEID_PLAYER)
            {
                // Do not allow these spells to target creatures not tapped by us (Banish, Polymorph, many quest spells)
                if (AttributesEx2 & SPELL_ATTR2_CANT_TARGET_TAPPED)
                    if (Creature const* targetCreature = unitTarget->ToCreature())
                        if (targetCreature->hasLootRecipient() && !targetCreature->isTappedBy(caster->ToPlayer()))
                            return SPELL_FAILED_CANT_CAST_ON_TAPPED;

                if (AttributesCu & SPELL_ATTR0_CU_PICKPOCKET)
                {
                     if (unitTarget->GetTypeId() == TYPEID_PLAYER)
                         return SPELL_FAILED_BAD_TARGETS;
                     else if ((unitTarget->GetCreatureTypeMask() & CREATURE_TYPEMASK_HUMANOID_OR_UNDEAD) == 0)
                         return SPELL_FAILED_TARGET_NO_POCKETS;
                }

                // Not allow disarm unarmed player
                if (Mechanic == MECHANIC_DISARM)
                {
                    if (unitTarget->GetTypeId() == TYPEID_PLAYER)
                    {
                        Player const* player = unitTarget->ToPlayer();
                        if (!player->GetWeaponForAttack(BASE_ATTACK) || !player->IsUseEquipedWeapon(true))
                            return SPELL_FAILED_TARGET_NO_WEAPONS;
                    }
                    else if (!unitTarget->GetUInt32Value(UNIT_VIRTUAL_ITEM_SLOT_ID) && Id != 64058) // Custom MoP Script - Hack Fix Psychic Horror
                        return SPELL_FAILED_TARGET_NO_WEAPONS;
                }
            }
        }
    }
    // corpse specific target checks
    else if (Corpse const* corpseTarget = target->ToCorpse())
    {
        // cannot target bare bones
        if (corpseTarget->GetType() == CORPSE_BONES)
            return SPELL_FAILED_BAD_TARGETS;
        // we have to use owner for some checks (aura preventing resurrection for example)
        if (Player* owner = ObjectAccessor::FindPlayer(corpseTarget->GetOwnerGUID()))
            unitTarget = owner;
        // we're not interested in corpses without owner
        else
            return SPELL_FAILED_BAD_TARGETS;
    }
    // other types of objects - always valid
    else return SPELL_CAST_OK;

    // corpseOwner and unit specific target checks
    if (AttributesEx3 & SPELL_ATTR3_ONLY_TARGET_PLAYERS && !unitTarget->ToPlayer())
       return SPELL_FAILED_TARGET_NOT_PLAYER;

    if (!IsAllowingDeadTarget() && !unitTarget->isAlive())
       return SPELL_FAILED_TARGETS_DEAD;

    // check this flag only for implicit targets (chain and area), allow to explicitly target units for spells like Shield of Righteousness
    if (implicit && AttributesEx6 & SPELL_ATTR6_CANT_TARGET_CROWD_CONTROLLED && !unitTarget->CanFreeMove())
       return SPELL_FAILED_BAD_TARGETS;

    // checked in Unit::IsValidAttack/AssistTarget, shouldn't be checked for ENTRY targets
    //if (!(AttributesEx6 & SPELL_ATTR6_CAN_TARGET_UNTARGETABLE) && target->HasFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE))
    //    return SPELL_FAILED_BAD_TARGETS;

    //if (!(AttributesEx6 & SPELL_ATTR6_CAN_TARGET_POSSESSED_FRIENDS)

    if (!CheckTargetCreatureType(unitTarget))
    {
        if (target->GetTypeId() == TYPEID_PLAYER)
            return SPELL_FAILED_TARGET_IS_PLAYER;
        else
            return SPELL_FAILED_BAD_TARGETS;
    }

    // check GM mode and GM invisibility - only for player casts (npc casts are controlled by AI) and negative spells
    if (unitTarget != caster && (caster->IsControlledByPlayer() || !IsPositive()) && unitTarget->GetTypeId() == TYPEID_PLAYER)
    {
        if (!unitTarget->ToPlayer()->IsVisible())
            return SPELL_FAILED_BM_OR_INVISGOD;

        if (unitTarget->ToPlayer()->isGameMaster())
            return SPELL_FAILED_BM_OR_INVISGOD;
    }

    // not allow casting on flying player
    if (unitTarget->HasUnitState(UNIT_STATE_IN_FLIGHT))
        return SPELL_FAILED_BAD_TARGETS;

    // TARGET_UNIT_MASTER gets blocked here for passengers, because the whole idea of this check is to 
    // not allow passengers to be implicitly hit by spells, however this target type should be an exception,
    // if this is left it kills spells that award kill credit from vehicle to master and some or all* spells,
    // the use of these 2 covers passenger target check
    if (!(Targets & TARGET_UNIT_MASTER) && !caster->IsVehicle())
    {
        if (TargetAuraState && !unitTarget->HasAuraState(AuraStateType(TargetAuraState), this, caster))
            return SPELL_FAILED_TARGET_AURASTATE;

        if (TargetAuraStateNot && unitTarget->HasAuraState(AuraStateType(TargetAuraStateNot), this, caster))
            return SPELL_FAILED_TARGET_AURASTATE;
    }

    if (TargetAuraSpell && !unitTarget->HasAura(sSpellMgr->GetSpellIdForDifficulty(TargetAuraSpell, caster)))
        return SPELL_FAILED_TARGET_AURASTATE;

    if (ExcludeTargetAuraSpell && unitTarget->HasAura(sSpellMgr->GetSpellIdForDifficulty(ExcludeTargetAuraSpell, caster)))
        return SPELL_FAILED_TARGET_AURASTATE;

    if (unitTarget->HasAuraType(SPELL_AURA_PREVENT_RESURRECTION))
        if (HasEffect(SPELL_EFFECT_SELF_RESURRECT) || HasEffect(SPELL_EFFECT_RESURRECT) || HasEffect(SPELL_EFFECT_RESURRECT_NEW))
            return SPELL_FAILED_TARGET_CANNOT_BE_RESURRECTED;

    return SPELL_CAST_OK;
}

SpellCastResult SpellInfo::CheckExplicitTarget(Unit const* caster, WorldObject const* target, Item const* itemTarget) const
{
    uint32 neededTargets = GetExplicitTargetMask();
    if (!target)
    {
        if (neededTargets & (TARGET_FLAG_UNIT_MASK | TARGET_FLAG_GAMEOBJECT_MASK | TARGET_FLAG_CORPSE_MASK) && Id != 115073 && Id != 6544)
            if (!(neededTargets & TARGET_FLAG_GAMEOBJECT_ITEM) || !itemTarget)
                return SPELL_FAILED_BAD_TARGETS;
        return SPELL_CAST_OK;
    }

    if (Unit const* unitTarget = target->ToUnit())
    {
        if (neededTargets & (TARGET_FLAG_UNIT_ENEMY | TARGET_FLAG_UNIT_ALLY | TARGET_FLAG_UNIT_RAID | TARGET_FLAG_UNIT_PARTY | TARGET_FLAG_UNIT_MINIPET | TARGET_FLAG_UNIT_PASSENGER))
        {
            if (neededTargets & TARGET_FLAG_UNIT_ENEMY)
                if (caster->_IsValidAttackTarget(unitTarget, this))
                    return SPELL_CAST_OK;
            if (neededTargets & TARGET_FLAG_UNIT_ALLY
                || (neededTargets & TARGET_FLAG_UNIT_PARTY && caster->IsInPartyWith(unitTarget))
                || (neededTargets & TARGET_FLAG_UNIT_RAID && caster->IsInRaidWith(unitTarget)))
                    if (caster->_IsValidAssistTarget(unitTarget, this))
                        return SPELL_CAST_OK;
            if (neededTargets & TARGET_FLAG_UNIT_MINIPET)
                if (unitTarget->GetGUID() == caster->GetCritterGUID())
                    return SPELL_CAST_OK;
            if (neededTargets & TARGET_FLAG_UNIT_PASSENGER)
                if (unitTarget->IsOnVehicle(caster))
                    return SPELL_CAST_OK;
            return SPELL_FAILED_BAD_TARGETS;
        }
    }
    return SPELL_CAST_OK;
}

bool SpellInfo::CheckTargetCreatureType(Unit const* target) const
{
    // Curse of Doom & Exorcism: not find another way to fix spell target check :/
    if (SpellFamilyName == SPELLFAMILY_WARLOCK && Category == 1179)
    {
        // not allow cast at player
        if (target->GetTypeId() == TYPEID_PLAYER)
            return false;
        else
            return true;
    }
    uint32 creatureType = target->GetCreatureTypeMask();
    return !TargetCreatureType || !creatureType || (creatureType & TargetCreatureType);
}

SpellSchoolMask SpellInfo::GetSchoolMask() const
{
    return SpellSchoolMask(SchoolMask);
}

uint32 SpellInfo::GetAllEffectsMechanicMask() const
{
    uint32 mask = 0;
    if (Mechanic)
        mask |= 1 << Mechanic;
    for (int i = 0; i < MAX_SPELL_EFFECTS; ++i)
        if (Effects[i].IsEffect() && Effects[i].Mechanic)
            mask |= 1 << Effects[i].Mechanic;
    return mask;
}

uint32 SpellInfo::GetEffectMechanicMask(uint8 effIndex) const
{
    uint32 mask = 0;
    if (Mechanic)
        mask |= 1<< Mechanic;
    if (Effects[effIndex].IsEffect() && Effects[effIndex].Mechanic)
        mask |= 1<< Effects[effIndex].Mechanic;
    return mask;
}

uint32 SpellInfo::GetSpellMechanicMaskByEffectMask(uint32 effectMask) const
{
    uint32 mask = 0;
    if (Mechanic)
        mask |= 1<< Mechanic;
    for (int i = 0; i < MAX_SPELL_EFFECTS; ++i)
        if ((effectMask & (1 << i)) && Effects[i].Mechanic)
            mask |= 1<< Effects[i].Mechanic;
    return mask;
}

Mechanics SpellInfo::GetEffectMechanic(uint8 effIndex) const
{
    if (Effects[effIndex].IsEffect() && Effects[effIndex].Mechanic)
        return Mechanics(Effects[effIndex].Mechanic);
    if (Mechanic)
        return Mechanics(Mechanic);
    return MECHANIC_NONE;
}

bool SpellInfo::HasAnyEffectMechanic() const
{
    for (uint8 i = 0; i < MAX_SPELL_EFFECTS; ++i)
        if (Effects[i].Mechanic)
            return true;
    return false;
}

uint32 SpellInfo::GetDispelMask() const
{
    return GetDispelMask(DispelType(Dispel));
}

uint32 SpellInfo::GetDispelMask(DispelType type)
{
    // If dispel all
    if (type == DISPEL_ALL)
        return DISPEL_ALL_MASK;
    else
        return uint32(1 << type);
}

uint32 SpellInfo::GetExplicitTargetMask() const
{
    return ExplicitTargetMask;
}

AuraStateType SpellInfo::GetAuraState() const
{
    // Seals
    if (GetSpellSpecific() == SPELL_SPECIFIC_SEAL)
        return AURA_STATE_JUDGEMENT;

    // Conflagrate aura state on Immolate and Shadowflame
    if (SpellFamilyName == SPELLFAMILY_WARLOCK &&
        // Immolate
        ((SpellFamilyFlags[0] & 4) ||
        // Shadowflame
        (SpellFamilyFlags[2] & 2)))
        return AURA_STATE_CONFLAGRATE;

    // Faerie Fire (druid versions)
    if (Id == 770 || Id == 102355)
        return AURA_STATE_FAERIE_FIRE;

    // Sting (hunter's pet ability)
    if (Category == 1133)
        return AURA_STATE_FAERIE_FIRE;

    // Victorious
    if (SpellFamilyName == SPELLFAMILY_WARRIOR &&  SpellFamilyFlags[1] & 0x00040000)
        return AURA_STATE_WARRIOR_VICTORY_RUSH;

    // Swiftmend state on Regrowth & Rejuvenation
    if (SpellFamilyName == SPELLFAMILY_DRUID && SpellFamilyFlags[0] & 0x50)
        return AURA_STATE_SWIFTMEND;

    // Deadly poison aura state
    if (SpellFamilyName == SPELLFAMILY_ROGUE && SpellFamilyFlags[0] & 0x10000)
        return AURA_STATE_DEADLY_POISON;

    // Enrage aura state
    if (Dispel == DISPEL_ENRAGE)
        return AURA_STATE_ENRAGE;

    // Bleeding aura state
    if (GetAllEffectsMechanicMask() & 1<<MECHANIC_BLEED)
        return AURA_STATE_BLEEDING;

    if (GetSchoolMask() & SPELL_SCHOOL_MASK_FROST)
        for (uint8 i = 0; i < MAX_SPELL_EFFECTS; ++i)
            if (Effects[i].IsAura() && (Effects[i].ApplyAuraName == SPELL_AURA_MOD_STUN
                || Effects[i].ApplyAuraName == SPELL_AURA_MOD_ROOT))
                return AURA_STATE_FROZEN;

    switch (Id)
    {
        case 71465: // Divine Surge
        case 50241: // Evasive Charges
            return AURA_STATE_UNKNOWN22;
        default:
            break;
    }

    return AURA_STATE_NONE;
}

SpellSpecificType SpellInfo::GetSpellSpecific() const
{
    switch (SpellFamilyName)
    {
        case SPELLFAMILY_GENERIC:
        {
            // Food / Drinks (mostly)
            if (AuraInterruptFlags & AURA_INTERRUPT_FLAG_NOT_SEATED)
            {
                bool food = false;
                bool drink = false;
                for (uint8 i = 0; i < MAX_SPELL_EFFECTS; ++i)
                {
                    if (!Effects[i].IsAura())
                        continue;
                    switch (Effects[i].ApplyAuraName)
                    {
                        // Food
                        case SPELL_AURA_MOD_REGEN:
                        case SPELL_AURA_OBS_MOD_HEALTH:
                            food = true;
                            break;
                        // Drink
                        case SPELL_AURA_MOD_POWER_REGEN:
                        case SPELL_AURA_OBS_MOD_POWER:
                            drink = true;
                            break;
                        default:
                            break;
                    }
                }

                if (food && drink)
                    return SPELL_SPECIFIC_FOOD_AND_DRINK;
                else if (food)
                    return SPELL_SPECIFIC_FOOD;
                else if (drink)
                    return SPELL_SPECIFIC_DRINK;
            }
            // scrolls effects
            else
            {
                SpellInfo const* firstRankSpellInfo = GetFirstRankSpell();
                switch (firstRankSpellInfo->Id)
                {
                    case 8118: // Strength
                    case 8099: // Stamina
                    case 8112: // Spirit
                    case 8096: // Intellect
                    case 8115: // Agility
                    case 8091: // Armor
                        return SPELL_SPECIFIC_SCROLL;
                    case 12880: // Enrage (Enrage)
                    case 57518: // Enrage (Wrecking Crew)
                        return SPELL_SPECIFIC_WARRIOR_ENRAGE;
                }
            }
            break;
        }
        case SPELLFAMILY_MAGE:
        {
            // family flags 18(Molten), 25(Frost/Ice), 28(Mage)
            if (SpellFamilyFlags[0] & 0x12040000)
                return SPELL_SPECIFIC_MAGE_ARMOR;

            // Arcane brillance and Arcane intelect (normal check fails because of flags difference)
            if (SpellFamilyFlags[0] & 0x400)
                return SPELL_SPECIFIC_MAGE_ARCANE_BRILLANCE;

            if ((SpellFamilyFlags[0] & 0x1000000) && Effects[0].ApplyAuraName == SPELL_AURA_MOD_CONFUSE)
                return SPELL_SPECIFIC_MAGE_POLYMORPH;

            break;
        }
        case SPELLFAMILY_WARRIOR:
        {
            if (Id == 12292) // Death Wish
                return SPELL_SPECIFIC_WARRIOR_ENRAGE;

            break;
        }
        case SPELLFAMILY_WARLOCK:
        {
            // Agony, Doom (Metamorphosis) and Havoc are no longer curses
            if (Id == 980 || Id == 603 || Id == 80240)
                return SPELL_SPECIFIC_BANE;

            // only warlock curses have this
            if (Dispel == DISPEL_CURSE)
                return SPELL_SPECIFIC_CURSE;
            break;
        }
        case SPELLFAMILY_PRIEST:
        {
            // Divine Spirit and Prayer of Spirit
            if (SpellFamilyFlags[0] & 0x20)
                return SPELL_SPECIFIC_PRIEST_DIVINE_SPIRIT;

            // Chakra : Serenity, Chakra : Chastise and Chakra : Sanctuary
            if (Id == 81208 || Id == 81209 || Id == 81206)
                return SPELL_SPECIFIC_CHAKRA;

            break;
        }
        case SPELLFAMILY_HUNTER:
        {
            // only hunter stings have this
            if (Dispel == DISPEL_POISON)
                return SPELL_SPECIFIC_STING;

            // only hunter aspects have this (but not all aspects in hunter family) and Hack fix for Deterrence - Is not an aspect !
            if (SpellFamilyFlags.HasFlag(0x00380000, 0x00440000, 0x00001010) && Id != 67801)
                return SPELL_SPECIFIC_ASPECT;

            break;
        }
        case SPELLFAMILY_PALADIN:
        {
            // Collection of all the seal family flags. No other paladin spell has any of those.
            // Collection of all the seal Id.
            if (Id == 20164         // Seal of Justice
                || Id == 20154      // Seal of Righteoussness
                || Id == 31801      // Seal of Truth
                || Id == 20165      // Seal of Insight
                || Id == 105361)    // Seal of Command
                return SPELL_SPECIFIC_SEAL;

            if (SpellFamilyFlags[0] & 0x00002190)
                return SPELL_SPECIFIC_HAND;

            // Judgement of Wisdom, Judgement of Light, Judgement of Justice
            if (Id == 20271)
                return SPELL_SPECIFIC_JUDGEMENT;

            // only paladin auras have this (for palaldin class family)
            if (SpellFamilyFlags[2] & 0x00000020)
                return SPELL_SPECIFIC_AURA;

            break;
        }
        case SPELLFAMILY_SHAMAN:
        {
            // family flags 10 (Lightning), 42 (Earth), 37 (Water), proc shield from T2 8 pieces bonus
            if (SpellFamilyFlags[1] & 0x420
                || SpellFamilyFlags[0] & 0x00000400
                || Id == 23552)
                return SPELL_SPECIFIC_ELEMENTAL_SHIELD;

            break;
        }
        case SPELLFAMILY_DEATHKNIGHT:
            if (Id == 48266 || Id == 48263 || Id == 48265)
                return SPELL_SPECIFIC_PRESENCE;
            break;
    }

    for (uint8 i = 0; i < MAX_SPELL_EFFECTS; ++i)
    {
        if (Effects[i].Effect == SPELL_EFFECT_APPLY_AURA)
        {
            switch (Effects[i].ApplyAuraName)
            {
                case SPELL_AURA_MOD_CHARM:
                case SPELL_AURA_MOD_POSSESS_PET:
                case SPELL_AURA_MOD_POSSESS:
                case SPELL_AURA_AOE_CHARM:
                    return SPELL_SPECIFIC_CHARM;
                case SPELL_AURA_TRACK_CREATURES:
                case SPELL_AURA_TRACK_RESOURCES:
                case SPELL_AURA_TRACK_STEALTHED:
                    return SPELL_SPECIFIC_TRACKER;
            }
        }
    }

    return SPELL_SPECIFIC_NORMAL;
}

float SpellInfo::GetMinRange(bool positive) const
{
    if (!RangeEntry)
        return 0.0f;
    if (positive)
        return RangeEntry->minRangeFriend;
    return RangeEntry->minRangeHostile;
}

float SpellInfo::GetMaxRange(bool positive, Unit* caster, Spell* spell) const
{
    if (!RangeEntry)
        return 0.0f;
    float range;
    if (positive)
        range = RangeEntry->maxRangeFriend;
    else
        range = RangeEntry->maxRangeHostile;
    if (caster)
        if (Player* modOwner = caster->GetSpellModOwner())
            modOwner->ApplySpellMod(Id, SPELLMOD_RANGE, range, spell);
    return range;
}

int32 SpellInfo::GetDuration() const
{
    if (!DurationEntry)
        return 0;
    return (DurationEntry->Duration[0] == -1) ? -1 : abs(DurationEntry->Duration[0]);
}

int32 SpellInfo::GetMaxDuration() const
{
    if (!DurationEntry)
        return 0;
    return (DurationEntry->Duration[2] == -1) ? -1 : abs(DurationEntry->Duration[2]);
}

uint32 SpellInfo::CalcCastTime(Unit* caster, Spell* spell) const
{
    int32 castTime = 0;

    // not all spells have cast time index and this is all is pasiive abilities
    if (caster && CastTimeMax > 0)
    {
        castTime = CastTimeMax;
        if (CastTimeMaxLevel > int32(caster->getLevel()))
            castTime = CastTimeMin + int32(caster->getLevel() - 1) * (CastTimeMax - CastTimeMin) / (CastTimeMaxLevel - 1);
    }
    else if (CastTimeEntry)
        castTime = CastTimeEntry->CastTime;

    if (!castTime)
        return 0;

    if (caster)
        caster->ModSpellCastTime(this, castTime, spell);

    // Kil'Jaeden's Cunning
    if (caster && caster->HasAuraType(SPELL_AURA_KIL_JAEDENS_CUNNING) && caster->isMoving() && !caster->HasAura(119048))
        castTime += CalculatePct(castTime, 50);

    // Fix Cultivation - with Herb Gathering
    if (Id == 2366 && caster && caster->HasAura(20552))
        castTime = 500;

    // Glyph of Capacitor Totem
    if (caster && Id == 118905)
        if (Unit* owner = caster->GetOwner())
            if (owner->HasAura(55442))
                castTime -= 2000;

    // Glyph of the Righteous Retreat
    if (caster && Id == 8690)
        if (caster->HasAura(115933) && (caster->HasAura(642) || caster->HasAura(110700)))
            castTime /= 2;

    // Elegon - Overloaded
    if (caster && caster->HasAura(117204))
        if (AuraPtr overloaded = caster->GetAura(117204))
            castTime -= CalculatePct(castTime, (20 * overloaded->GetStackAmount()));

    // Glyph of Denounce
    if (Id == 2812 && caster && caster->HasAura(115654))
        castTime -= 1000;

    return (castTime > 0) ? uint32(castTime) : 0;
}

uint32 SpellInfo::GetMaxTicks() const
{
    int32 DotDuration = GetDuration();
    if (DotDuration == 0)
        return 1;

    // 200% limit
    if (DotDuration > 30000)
        DotDuration = 30000;

    for (uint8 x = 0; x < MAX_SPELL_EFFECTS; x++)
    {
        if (Effects[x].Effect == SPELL_EFFECT_APPLY_AURA)
            switch (Effects[x].ApplyAuraName)
            {
                case SPELL_AURA_PERIODIC_DAMAGE:
                case SPELL_AURA_PERIODIC_HEAL:
                case SPELL_AURA_PERIODIC_LEECH:
                    if (Effects[x].Amplitude != 0)
                        return DotDuration / Effects[x].Amplitude;
                    break;
            }
    }

    return 6;
}

uint32 SpellInfo::GetRecoveryTime() const
{
    return RecoveryTime > CategoryRecoveryTime ? RecoveryTime : CategoryRecoveryTime;
}

uint32 SpellInfo::CalcPowerCost(Unit const* caster, SpellSchoolMask schoolMask, SpellPowerEntry const* spellPower) const
{
    // Spell drain all exist power on cast (Only paladin lay of Hands)
    if (AttributesEx & SPELL_ATTR1_DRAIN_ALL_POWER)
    {
        // If power type - health drain all
        if (spellPower->powerType == POWER_HEALTH)
            return caster->GetHealth();
        // Else drain all power
        if (spellPower->powerType < MAX_POWERS)
            return caster->GetPower(Powers(spellPower->powerType));
        sLog->outError(LOG_FILTER_SPELLS_AURAS, "SpellInfo::CalcPowerCost: Unknown power type '%d' in spell %d", spellPower->powerType, Id);
        return 0;
    }

    // Base powerCost
    int32 powerCost = spellPower->manaCost;
    // PCT cost from total amount
    if (spellPower->ManaCostPercentage)
    {
        switch (spellPower->powerType)
        {
            // health as power used
            case POWER_HEALTH:
                powerCost += int32(CalculatePct(caster->GetCreateHealth(), spellPower->ManaCostPercentage));
                break;
            case POWER_MANA:
                powerCost += int32(CalculatePct(caster->GetCreateMana(), spellPower->ManaCostPercentage));
                break;
            case POWER_RAGE:
            case POWER_FOCUS:
            case POWER_ENERGY:
                powerCost += int32(CalculatePct(caster->GetMaxPower(Powers(spellPower->powerType)), spellPower->ManaCostPercentage));
                break;
            case POWER_RUNES:
            case POWER_RUNIC_POWER:
                sLog->outDebug(LOG_FILTER_SPELLS_AURAS, "CalculateManaCost: Not implemented yet!");
                break;
            default:
                sLog->outError(LOG_FILTER_SPELLS_AURAS, "CalculateManaCost: Unknown power type '%d' in spell %d", spellPower->powerType, Id);
                return 0;
        }
    }
    SpellSchools school = GetFirstSchoolInMask(schoolMask);
    // Flat mod from caster auras by spell school
    powerCost += caster->GetInt32Value(UNIT_FIELD_POWER_COST_MODIFIER + school);
    // Apply cost mod by spell
    if (Player* modOwner = caster->GetSpellModOwner())
        modOwner->ApplySpellMod(Id, SPELLMOD_COST, powerCost);

    if (Attributes & SPELL_ATTR0_LEVEL_DAMAGE_CALCULATION)
        powerCost = int32(powerCost / (1.117f * SpellLevel / caster->getLevel() -0.1327f));

    // PCT mod from user auras by school
    powerCost = int32(powerCost * (1.0f + caster->GetFloatValue(UNIT_FIELD_POWER_COST_MULTIPLIER + school)));
    if (powerCost < 0)
        powerCost = 0;
    return powerCost;
}

bool SpellInfo::IsRanked() const
{
    return ChainEntry != NULL;
}

uint8 SpellInfo::GetRank() const
{
    if (!ChainEntry)
        return 1;
    return ChainEntry->rank;
}

SpellInfo const* SpellInfo::GetFirstRankSpell() const
{
    if (!ChainEntry)
        return this;
    return ChainEntry->first;
}
SpellInfo const* SpellInfo::GetLastRankSpell() const
{
    if (!ChainEntry)
        return NULL;
    return ChainEntry->last;
}
SpellInfo const* SpellInfo::GetNextRankSpell() const
{
    if (!ChainEntry)
        return NULL;
    return ChainEntry->next;
}
SpellInfo const* SpellInfo::GetPrevRankSpell() const
{
    if (!ChainEntry)
        return NULL;
    return ChainEntry->prev;
}

SpellInfo const* SpellInfo::GetAuraRankForLevel(uint8 level) const
{
    // ignore passive spells
    if (IsPassive())
        return this;

    bool needRankSelection = false;
    for (uint8 i = 0; i < MAX_SPELL_EFFECTS; ++i)
    {
        if (IsPositiveEffect(i) &&
            (Effects[i].Effect == SPELL_EFFECT_APPLY_AURA ||
            Effects[i].Effect == SPELL_EFFECT_APPLY_AREA_AURA_PARTY ||
            Effects[i].Effect == SPELL_EFFECT_APPLY_AREA_AURA_RAID) &&
            !Effects[i].ScalingMultiplier)
        {
            needRankSelection = true;
            break;
        }
    }

    // not required
    if (!needRankSelection)
        return this;

    for (SpellInfo const* nextSpellInfo = this; nextSpellInfo != NULL; nextSpellInfo = nextSpellInfo->GetPrevRankSpell())
    {
        // if found appropriate level
        if (uint32(level + 10) >= nextSpellInfo->SpellLevel)
            return nextSpellInfo;

        // one rank less then
    }

    // not found
    return NULL;
}

bool SpellInfo::IsRankOf(SpellInfo const* spellInfo) const
{
    return spellInfo && GetFirstRankSpell() == spellInfo->GetFirstRankSpell();
}

bool SpellInfo::IsDifferentRankOf(SpellInfo const* spellInfo) const
{
    if (Id == spellInfo->Id)
        return false;
    return IsRankOf(spellInfo);
}

bool SpellInfo::IsHighRankOf(SpellInfo const* spellInfo) const
{
    if (ChainEntry && spellInfo->ChainEntry)
    {
        if (ChainEntry->first == spellInfo->ChainEntry->first)
            if (ChainEntry->rank > spellInfo->ChainEntry->rank)
                return true;
    }
    return false;
}

uint32 SpellInfo::_GetExplicitTargetMask() const
{
    bool srcSet = false;
    bool dstSet = false;
    uint32 targetMask = Targets;
    // prepare target mask using effect target entries
    for (uint8 i = 0; i < MAX_SPELL_EFFECTS; ++i)
    {
        if (!Effects[i].IsEffect())
            continue;
        targetMask |= Effects[i].TargetA.GetExplicitTargetMask(srcSet, dstSet);
        targetMask |= Effects[i].TargetB.GetExplicitTargetMask(srcSet, dstSet);

        // add explicit target flags based on spell effects which have EFFECT_IMPLICIT_TARGET_EXPLICIT and no valid target provided
        if (Effects[i].GetImplicitTargetType() != EFFECT_IMPLICIT_TARGET_EXPLICIT)
            continue;

        // extend explicit target mask only if valid targets for effect could not be provided by target types
        uint32 effectTargetMask = Effects[i].GetMissingTargetMask(srcSet, dstSet, targetMask);

        // don't add explicit object/dest flags when spell has no max range
        if (GetMaxRange(true) == 0.0f && GetMaxRange(false) == 0.0f)
            effectTargetMask &= ~(TARGET_FLAG_UNIT_MASK | TARGET_FLAG_GAMEOBJECT | TARGET_FLAG_CORPSE_MASK | TARGET_FLAG_DEST_LOCATION);
        targetMask |= effectTargetMask;
    }
    return targetMask;
}

bool SpellInfo::IsAllwaysStackModifers() const
{
    if (IsPassive())
        return true;

    if (SpellFamilyName == SPELLFAMILY_POTION)
        return true;

    switch (Id)
    {
        // warsong flags
        case 23333:
        case 23335:

        case 16191: // mana tide buff 
            return true;
       default:
            break;
    }
    return false;
}

bool SpellInfo::_IsPositiveEffect(uint8 effIndex, bool deep) const
{
    // not found a single positive spell with this attribute
    if (Attributes & SPELL_ATTR0_DEBUFF)
        return false;

    switch (SpellFamilyName)
    {
        case SPELLFAMILY_GENERIC:
            switch (Id)
            {
                case 29214: // Wrath of the Plaguebringer
                case 34700: // Allergic Reaction
                case 54836: // Wrath of the Plaguebringer
                    return false;
                case 30877: // Tag Murloc
                case 61716: // Rabbit Costume
                case 61734: // Noblegarden Bunny
                case 62344: // Fists of Stone
                    return true;
                default:
                    break;
            }
            break;
        case SPELLFAMILY_MAGE:
            // Amplify Magic, Dampen Magic
            if (SpellFamilyFlags[0] == 0x00002000)
                return true;
            // Ignite
            if (SpellIconID == 45)
                return true;
            break;
        case SPELLFAMILY_PRIEST:
            switch (Id)
            {
                case 64844: // Divine Hymn
                case 64904: // Hymn of Hope
                case 47585: // Dispersion
                    return true;
                default:
                    break;
            }
            break;
        case SPELLFAMILY_HUNTER:
            // Aspect of the Viper
            if (Id == 34074)
                return true;
            break;
        case SPELLFAMILY_SHAMAN:
            if (Id == 30708)
                return false;
            break;
        case SPELLFAMILY_ROGUE:
            switch (Id)
            {
                // Envenom must be considered as a positive effect even though it deals damage
                case 32645:
                    return true;
                default:
                    break;
            }
            break;
        default:
            break;
    }

    switch (Mechanic)
    {
        case MECHANIC_IMMUNE_SHIELD:
            return true;
        default:
            break;
    }

    // Special case: effects which determine positivity of whole spell
    for (uint8 i = 0; i < MAX_SPELL_EFFECTS; ++i)
    {
        if (Effects[i].IsAura() && Effects[i].ApplyAuraName == SPELL_AURA_MOD_STEALTH)
            return true;
    }

    switch (Effects[effIndex].Effect)
    {
        case SPELL_EFFECT_DUMMY:
            // some explicitly required dummy effect sets
            switch (Id)
            {
                case 28441:
                    return false; // AB Effect 000
                default:
                    break;
            }
            break;
        // always positive effects (check before target checks that provided non-positive result in some case for positive effects)
        case SPELL_EFFECT_HEAL:
        case SPELL_EFFECT_LEARN_SPELL:
        case SPELL_EFFECT_SKILL_STEP:
        case SPELL_EFFECT_HEAL_PCT:
        case SPELL_EFFECT_ENERGIZE_PCT:
            return true;
        case SPELL_EFFECT_APPLY_AREA_AURA_ENEMY:
            return false;

            // non-positive aura use
        case SPELL_EFFECT_APPLY_AURA:
        case SPELL_EFFECT_APPLY_AREA_AURA_FRIEND:
        {
            switch (Effects[effIndex].ApplyAuraName)
            {
                case SPELL_AURA_MOD_DAMAGE_DONE:            // dependent from bas point sign (negative -> negative)
                case SPELL_AURA_MOD_STAT:
                case SPELL_AURA_MOD_SKILL:
                case SPELL_AURA_MOD_DODGE_PERCENT:
                case SPELL_AURA_MOD_HEALING_PCT:
                case SPELL_AURA_MOD_HEALING_DONE:
                case SPELL_AURA_MOD_DAMAGE_PERCENT_DONE:
                    if (Effects[effIndex].CalcValue() < 0)
                        return false;
                    break;
                case SPELL_AURA_MOD_DAMAGE_TAKEN:           // dependent from bas point sign (positive -> negative)
                    if (Effects[effIndex].CalcValue() > 0)
                        return false;
                    break;
                case SPELL_AURA_MOD_CRIT_PCT:
                case SPELL_AURA_MOD_SPELL_CRIT_CHANCE:
                    if (Effects[effIndex].CalcValue() > 0)
                        return true;                        // some expected positive spells have SPELL_ATTR1_NEGATIVE
                    break;
                case SPELL_AURA_ADD_TARGET_TRIGGER:
                    return true;
                case SPELL_AURA_PERIODIC_TRIGGER_SPELL_WITH_VALUE:
                case SPELL_AURA_PERIODIC_TRIGGER_SPELL:
                    if (!deep)
                    {
                        if (SpellInfo const* spellTriggeredProto = sSpellMgr->GetSpellInfo(Effects[effIndex].TriggerSpell))
                        {
                            // negative targets of main spell return early
                            for (uint8 i = 0; i < MAX_SPELL_EFFECTS; ++i)
                            {
                                if (!spellTriggeredProto->Effects[i].Effect)
                                    continue;
                                // if non-positive trigger cast targeted to positive target this main cast is non-positive
                                // this will place this spell auras as debuffs
                                if (_IsPositiveTarget(spellTriggeredProto->Effects[i].TargetA.GetTarget(), spellTriggeredProto->Effects[effIndex].TargetB.GetTarget()) && !spellTriggeredProto->_IsPositiveEffect(i, true))
                                    return false;
                            }
                        }
                    }
                case SPELL_AURA_PROC_TRIGGER_SPELL:
                    // many positive auras have negative triggered spells at damage for example and this not make it negative (it can be canceled for example)
                    break;
                case SPELL_AURA_MOD_STUN:                   //have positive and negative spells, we can't sort its correctly at this moment.
                    if (effIndex == 0 && Effects[1].Effect == 0 && Effects[2].Effect == 0)
                        return false;                       // but all single stun aura spells is negative
                    break;
                case SPELL_AURA_MOD_PACIFY_SILENCE:
                    if (Id == 24740)             // Wisp Costume
                        return true;
                    return false;
                case SPELL_AURA_MOD_ROOT:
                case SPELL_AURA_MOD_SILENCE:
                case SPELL_AURA_GHOST:
                case SPELL_AURA_PERIODIC_LEECH:
                case SPELL_AURA_MOD_STALKED:
                case SPELL_AURA_PERIODIC_DAMAGE_PERCENT:
                case SPELL_AURA_PREVENT_RESURRECTION:
                    return false;
                case SPELL_AURA_PERIODIC_DAMAGE:            // used in positive spells also.
                    // part of negative spell if casted at self (prevent cancel)
                    if (Effects[effIndex].TargetA.GetTarget() == TARGET_UNIT_CASTER)
                        return false;
                    break;
                case SPELL_AURA_MOD_DECREASE_SPEED:         // used in positive spells also
                    // part of positive spell if casted at self
                    if (Effects[effIndex].TargetA.GetTarget() != TARGET_UNIT_CASTER)
                        return false;
                    // but not this if this first effect (didn't find better check)
                    if (Attributes & SPELL_ATTR0_DEBUFF && effIndex == 0)
                        return false;
                    break;
                case SPELL_AURA_MECHANIC_IMMUNITY:
                {
                    // non-positive immunities
                    switch (Effects[effIndex].MiscValue)
                    {
                        case MECHANIC_BANDAGE:
                        case MECHANIC_SHIELD:
                        case MECHANIC_MOUNT:
                        case MECHANIC_INVULNERABILITY:
                            return false;
                        default:
                            break;
                    }
                    break;
                }
                case SPELL_AURA_ADD_FLAT_MODIFIER:          // mods
                case SPELL_AURA_ADD_PCT_MODIFIER:
                {
                    // non-positive mods
                    switch (Effects[effIndex].MiscValue)
                    {
                        case SPELLMOD_COST:                 // dependent from bas point sign (negative -> positive)
                            if (Effects[effIndex].CalcValue() > 0)
                            {
                                if (!deep)
                                {
                                    bool negative = true;
                                    for (uint8 i = 0; i < MAX_SPELL_EFFECTS; ++i)
                                    {
                                        if (i != effIndex)
                                            if (_IsPositiveEffect(i, true))
                                            {
                                                negative = false;
                                                break;
                                            }
                                    }
                                    if (negative)
                                        return false;
                                }
                            }
                            break;
                        default:
                            break;
                    }
                    break;
                }
                default:
                    break;
            }
            break;
        }
        default:
            break;
    }

    // non-positive targets
    if (!_IsPositiveTarget(Effects[effIndex].TargetA.GetTarget(), Effects[effIndex].TargetB.GetTarget()))
        return false;

    // negative spell if triggered spell is negative
    if (!deep && !Effects[effIndex].ApplyAuraName && Effects[effIndex].TriggerSpell)
    {
        if (SpellInfo const* spellTriggeredProto = sSpellMgr->GetSpellInfo(Effects[effIndex].TriggerSpell))
            if (!spellTriggeredProto->_IsPositiveSpell())
                return false;
    }

    // ok, positive
    return true;
}

bool SpellInfo::_IsPositiveSpell() const
{
    // spells with at least one negative effect are considered negative
    // some self-applied spells have negative effects but in self casting case negative check ignored.
    for (uint8 i = 0; i < MAX_SPELL_EFFECTS; ++i)
        if (!_IsPositiveEffect(i, true))
            return false;
    return true;
}

bool SpellInfo::_IsPositiveTarget(uint32 targetA, uint32 targetB)
{
    // non-positive targets
    switch (targetA)
    {
        case TARGET_UNIT_NEARBY_ENEMY:
        case TARGET_UNIT_TARGET_ENEMY:
        case TARGET_UNIT_SRC_AREA_ENEMY:
        case TARGET_UNIT_DEST_AREA_ENEMY:
        case TARGET_UNIT_CONE_ENEMY_24:
        case TARGET_UNIT_CONE_ENEMY_104:
        case TARGET_UNIT_CONE_ENEMY_110:
        case TARGET_UNIT_CONE_ENEMY_129:
        case TARGET_DEST_DYNOBJ_ENEMY:
        case TARGET_DEST_TARGET_ENEMY:
            return false;
        default:
            break;
    }
    if (targetB)
        return _IsPositiveTarget(targetB, 0);
    return true;
}

SpellTargetRestrictionsEntry const* SpellInfo::GetSpellTargetRestrictions() const
{
    return SpellTargetRestrictionsId ? sSpellTargetRestrictionsStore.LookupEntry(SpellTargetRestrictionsId) : NULL;
}

SpellEquippedItemsEntry const* SpellInfo::GetSpellEquippedItems() const
{
    return SpellEquippedItemsId ? sSpellEquippedItemsStore.LookupEntry(SpellEquippedItemsId) : NULL;
}

SpellInterruptsEntry const* SpellInfo::GetSpellInterrupts() const
{
    return SpellInterruptsId ? sSpellInterruptsStore.LookupEntry(SpellInterruptsId) : NULL;
}

SpellLevelsEntry const* SpellInfo::GetSpellLevels() const
{
    return SpellLevelsId ? sSpellLevelsStore.LookupEntry(SpellLevelsId) : NULL;
}

SpellPowerEntry const* SpellInfo::GetSpellPower() const
{
    return sSpellPowerStore.LookupEntry(Id);
}

SpellMiscEntry const* SpellInfo::GetSpellMisc() const
{
    return SpellMiscId ? sSpellMiscStore.LookupEntry(SpellMiscId) : NULL;
}

SpellReagentsEntry const* SpellInfo::GetSpellReagents() const
{
    return SpellReagentsId ? sSpellReagentsStore.LookupEntry(SpellReagentsId) : NULL;
}

SpellScalingEntry const* SpellInfo::GetSpellScaling() const
{
    return SpellScalingId ? sSpellScalingStore.LookupEntry(SpellScalingId) : NULL;
}

SpellShapeshiftEntry const* SpellInfo::GetSpellShapeshift() const
{
    return SpellShapeshiftId ? sSpellShapeshiftStore.LookupEntry(SpellShapeshiftId) : NULL;
}

SpellTotemsEntry const* SpellInfo::GetSpellTotems() const
{
    return SpellTotemsId ? sSpellTotemsStore.LookupEntry(SpellTotemsId) : NULL;
}

SpellAuraOptionsEntry const* SpellInfo::GetSpellAuraOptions() const
{
    return SpellAuraOptionsId ? sSpellAuraOptionsStore.LookupEntry(SpellAuraOptionsId) : NULL;
}

SpellAuraRestrictionsEntry const* SpellInfo::GetSpellAuraRestrictions() const
{
    return SpellAuraRestrictionsId ? sSpellAuraRestrictionsStore.LookupEntry(SpellAuraRestrictionsId) : NULL;
}

SpellCastingRequirementsEntry const* SpellInfo::GetSpellCastingRequirements() const
{
    return SpellCastingRequirementsId ? sSpellCastingRequirementsStore.LookupEntry(SpellCastingRequirementsId) : NULL;
}

SpellCategoriesEntry const* SpellInfo::GetSpellCategories() const
{
    return SpellCategoriesId ? sSpellCategoriesStore.LookupEntry(SpellCategoriesId) : NULL;
}

SpellClassOptionsEntry const* SpellInfo::GetSpellClassOptions() const
{
    return SpellClassOptionsId ? sSpellClassOptionsStore.LookupEntry(SpellClassOptionsId) : NULL;
}

SpellCooldownsEntry const* SpellInfo::GetSpellCooldowns() const
{
    return SpellCooldownsId ? sSpellCooldownsStore.LookupEntry(SpellCooldownsId) : NULL;
}

SpellEffectEntry const* SpellEntry::GetSpellEffect(uint32 eff, uint32 difficulty) const
{
    return GetSpellEffectEntry(Id, eff, difficulty);
}

void SpellInfo::_UnloadImplicitTargetConditionLists()
{
    // find the same instances of ConditionList and delete them.
    for (uint8 i = 0; i < MAX_SPELL_EFFECTS; ++i)
    {
        ConditionList* cur = Effects[i].ImplicitTargetConditions;
        if (!cur)
            continue;
        for (uint8 j = i; j < MAX_SPELL_EFFECTS; ++j)
        {
            if (Effects[j].ImplicitTargetConditions == cur)
                Effects[j].ImplicitTargetConditions = NULL;
        }
        delete cur;
    }
}

bool SpellInfo::_IsCrowdControl(uint8 effMask, bool nodamage) const
{
    for (uint8 effIndex = 0; effIndex < MAX_SPELL_EFFECTS; ++effIndex)
    {
        if (effMask && !(effMask & (1 << effIndex)))
            continue;

        if (nodamage)
        {
            switch (Effects[effIndex].Effect)
            {
                case SPELL_EFFECT_HEALTH_LEECH:
                case SPELL_EFFECT_SCHOOL_DAMAGE:
                    return false;
            }
        }

        switch (Effects[effIndex].ApplyAuraName)
        {
            case SPELL_AURA_MOD_STUN:
                switch (SpellIconID)
                {
                    case 15:
                    case 457:
                        return false;
                        break;
                    default:
                        break;
                }
            case SPELL_AURA_MOD_CONFUSE:
            case SPELL_AURA_MOD_FEAR:
            case SPELL_AURA_MOD_ROOT:
            case SPELL_AURA_TRANSFORM:
                if (!IsPositive())
                    return true;
                break;
            default: break;
        }
    }
    return false;
}

bool SpellInfo::_IsNeedDelay() const
{
    switch (Id)
    {
        case 379:   // Earth Shield (Shaman)
        case 14157: // Ruthlessness (Rogue)
        case 33110: // Prayer of Mending (Priest)
        case 48503: // Living Seed (Druid)
        case 52752: // Ancestral Awakening (Shaman)
        case 62836: // Slag Imbued (Ignis, Ulduar)
        case 63536: // Slag Imbued (Ignis, Ulduar)
        case 70802: // Mayhem (Rogue)
        case 70157: // Ice Tomb (Sindragosa, ICC)
        case 79128: // Improved Expose Armor
        case 36032: // Arcane Blast
        case 109950: // Fury of Destroyer
        case 114157: // Execution Sentence
            return true;
    }

    // Flurry (Shaman)
    if (SpellFamilyName == SPELLFAMILY_SHAMAN && SpellIconID == 108)
        return true;

    return false;
}

bool SpellInfo::IsBreakingCamouflageAfterHit() const
{
    // Traps
    if (SpellFamilyFlags[1] & 0x8002000 ||
        SpellFamilyFlags[2] & 0x20000)
        return true;

    // Damage casts
    switch (Id)
    {
        case 19434: // Aimed Shot
        case 82928: // Aimed Shot
        case 77767: // Cobra Shot
        case 56641: // Steady Shot
            return true;
    }

    return false;
}

bool SpellInfo::IsBreakingCamouflage() const
{
    // This is bad but I dont't see another way
    // I cannot check spells using any mask
    // Use it only for hunter camouflage
    switch (GetSpellSpecific())
    {
        case SPELL_SPECIFIC_FOOD:
        case SPELL_SPECIFIC_FOOD_AND_DRINK:
        case SPELL_SPECIFIC_WELL_FED:
        case SPELL_SPECIFIC_ASPECT:
            return false;
    }

    switch (Id)
    {
        case 136:   // Mend Pet
        case 982:   // Revive Pet
        case 1130:  // Hunter's Mark
        case 1462:  // Beast Lore
        case 1499:  // Frost Trap
        case 1543:  // Flare
        case 3045:  // Rapid Fire
        case 5384:  // Feign Death
        case 6197:  // Eagle Eye
        case 6991:  // Feed Pet
        case 13795: // Immolation Trap
        case 13809: // Ice Trap
        case 13813: // Explosive Trap
        case 19263: // Deterence
        case 19434: // Aimed Shot
        case 23989: // Readiness
        case 26297: // Berserking (Troll Racial)
        case 34477: // Misdirection
        case 34600: // Snake Trap
        case 42292: // PvP Trinket
        case 53271: // Master's Call
        case 56641: // Steady Shot
        case 60192: // Frost Trap launcher
        case 77767: // Cobra Shot
        case 77769: // Trap Launcher
        case 82935: // Immplation Trap launcher
        case 82939: // Explosive Trap launcher
        case 82941: // Ice Trap launcher
        case 82945: // Immolation Trap Launcher
        case 82948: // Snake Trap launcher
        case 93435: // Roar of Courage (Special Ability)
        case 109259:// Powershot
            return false;
    }

    return true;
}

bool SpellInfo::IsIgnoringCombat() const
{
    if (HasAttribute(SPELL_ATTR4_DAMAGE_DOESNT_BREAK_AURAS))
        return true;

    switch (Id)
    {
        // Slice and Dice
        case 5171:
        case 6434:
        case 6774:
        // Honor Among Thieves
        case 51698:
        case 51699:
        case 51700:
        case 51701:
        case 52916:
        // Divine Hymn
        case 64843:
        case 64844:
        case 70619:
        // Shadowmeld
        case 58984:
        // Blackjack
        case 79124:
        case 79126:
        // Redirect
        case 73981:
        // Venomous Wounds
        case 79136:
        // Master Poisoner
        case 93068:
        // Blind
        case 2094:
        // Ignite
        case 12654:
        // Resistance is Futile
        case 83676:
        // Vendeta
        case 79140:
        // Earth Shield
        case 379:
        // Earthliving Weapon proc
        case 51730:
        // Ancestral Vigor
        case 105284:
        // Ancestral Fortitude
        case 16177:
        case 16236:
            return true;
        default: break;
    }
    
    // Dark Intent
    if (SpellFamilyName == SPELLFAMILY_WARLOCK && (SpellFamilyFlags[2] & 0x00800000))
        return true;
    
    return false;
}

bool SpellInfo::IsAfflictionPeriodicDamage() const
{
    switch (Id)
    {
        case 172:   // Corruption
        case 980:   // Agony
        case 30108: // Unstable Affliction
        case 131736:// Unstable Affliction (triggered)
        case 131737:// Agony (triggered)
        case 131740:// Corruption (triggered)
            return true;
        default:
            return false;
    }
}

float SpellInfo::GetGiftOfTheSerpentScaling(Unit* caster) const
{
    float scale = 1.0f;

    switch (Id)
    {
        case 117640:// Spinning Crane Kick (Heal)
            scale = 0.1f;
            break;
        case 115151:// Renewing Mist
        case 115310:// Revival
        case 119611:// Renewing Mist (HoT)
        case 124040:// Chi Torpedo
        case 124101:// Zen Sphere : Detonate
        case 130654:// Chi Burst (Heal)
            scale = 0.15f;
            break;
        case 117895:// Eminence
        case 132120:// Enveloping Mist
            scale = 0.2f;
            break;
        case 116670:// Uplift
        case 124081:// Zen Sphere (HoT)
        case 132463:// Chi Wave (Heal)
            scale = 0.25f;
            break;
        case 115175:// Soothing Mist
            scale = 0.3f;
            break;
        default:
            break;
    }

    // Serpent Statue has different scaling
    if (caster->GetTypeId() == TYPEID_UNIT && caster->ToUnit()->GetEntry() == 60849)
    {
        switch (Id)
        {
            case 117895:// Eminence
                scale = 0.1f;
                break;
            case 115175:// Soothing Mist
                scale = 0.15f;
                break;
            default:
                break;
        }
    }

    return scale;
}

bool SpellInfo::IsReducingCastTime() const
{
    switch (Id)
    {
        case 5760:  // Mind-Numbing
        case 50274: // Spore Cloud
        case 58604: // Lava Breath
        case 73975: // Necrotic Strike
        case 90315: // Tailspin
        case 109466:// Curse of Enfeeblement
        case 109468:// Curse of Enfeeblement (Soulburn)
        case 116198:// Enfeeblement Aura (Metamorphosis)
            return true;
    }

    return false;
}

bool SpellInfo::CanTriggerBladeFlurry() const
{
    switch (Id)
    {
        case 1752:  // Sinister Strike
        case 2098:  // Eviscerate
        case 5374:  // Mutilate
        case 5938:  // Shiv
        case 8676:  // Ambush
        case 26679: // Deadly Throw
        case 27576: // Mutilate Off-Hand
        case 51723: // Fan of Knives
        case 57841: // Killing Spree
        case 57842: // Killing Spree Off-Hand
        case 84617: // Revealing Strike
        case 86392: // Main Gauche
        case 114014:// Shuriken Toss
        case 121411:// Crimson Tempest
        case 121473:// Shadow Blade
        case 121474:// Shadow Blade Off-Hand
            return true;
    }

    return false;
}

bool SpellInfo::IsCustomCharged(SpellInfo const* procSpell) const
{
    // Stealth aura and some custom rules ...
    if (HasAura(SPELL_AURA_MOD_STEALTH))
    {
        if (procSpell)
        {
            if (procSpell->Id == 93435 ||   // Roar of Courage
                procSpell->Id == 32182 ||   // Heroism
                procSpell->Id == 2825 ||    // Bloodlust
                procSpell->Id == 1725 ||    // Distract
                procSpell->Id == 114198 ||  // Mocking Banner taunt
                procSpell->Id == 130733)    // and Shadow Word: Insanity allowing Cast
                return true;
        }
    }

    switch (Id)
    {
        case 16246: // Clearcasting (Shaman)
            if (procSpell && procSpell->Id == 8004)
                return true;
            break;
        case 20066: // Repentence
            if (procSpell && procSpell->Id == 31803)
                return true;
            break;
        case 324:   // Lightning Shield
        case 36032: // Arcane Charge
        case 79683: // Arcane Missiles !
        case 93400: // Shooting Stars
        case 114637:// Bastion of Glory
        case 119962:// Overpower !
        case 121153:// Blindside
        case 131116:// Raging Blow !
            return true;
    }

    return false;
}

bool SpellInfo::IsCustomCastCanceled(Unit* caster) const
{
    switch (Id)
    {
        case 22778: // Hamstring Rage Reduction
            if (caster->HasAura(Id))
                return true;
            break;
        case 32973: // Gloves S12 - Shaman
            if (caster->HasAura(Id))
                return true;
            break;
        case 33830: // Gloves S12 - Druid
            if (caster->HasAura(Id))
                return true;
            break;
        case 44297: // Gloves S12 - Priest
            if (caster->HasAura(Id))
                return true;
            break;
        case 131562:// Item Monk - 2P S12 Windwalker
            if (caster->HasAura(Id))
                return true;
            break;
        case 132365:// Vengeance (old)
            return true;
    }

    return false;
}

bool SpellInfo::IsWrongPrecastSpell(SpellInfo const* m_preCastSpell) const
{
    switch (Id)
    {
        case 51723: // Fan of Knives
            if (m_preCastSpell->Id == 51690)
                return true;
            break;
        case 108507:// Kil'Jaeden's Cunning
            if (m_preCastSpell->Id == 119048)
                return true;
            break;
        case 115072:// Expel Harm
            if (m_preCastSpell->Id == 101545)
                return true;
            break;
        case 118858:// Incanter's Ward
            if (m_preCastSpell->Id == 118859)
                return true;
            break;
        case 119050:// Kil'Jaeden's Cunning (Decrease speed)
            if (m_preCastSpell->Id == 119049)
                return true;
            break;
        default:
            break;
    }

    return false;
}

bool SpellInfo::IsPoisonOrBleedSpell() const
{
    switch (Id)
    {
        case 703:   // Garrote
        case 1943:  // Rupture
        case 2818:  // Deadly Poison (DoT)
        case 3409:  // Crippling Poison
        case 5760:  // Mind-Numbling Poison
        case 8680:  // Wound Poison
        case 79136: // Venomous Wound (damage)
        case 89775: // Hemorrhage (DoT)
        case 112961:// Leeching Poison
        case 113780:// Deadly Poison (direct damage)
        case 113952:// Paralytic Poison
        case 122233:// Crimson Tempest (DoT)
            return true;
        default:
            break;
    }

    return false;
}

bool SpellInfo::IsCanBeStolen() const
{
    // some of the rules for those spells that can be stolen by Dark Simulacrum
    // spells should use mana
    if (PowerType != POWER_MANA)
        return false;

    // and should have mana cost
    if (!ManaCost && !ManaCostPercentage)
        return false;

    // special rules
    switch (Id)
    {
        case 633:   // Lay on Hands
        case 22812: // Barkskin
        case 24275: // Hammer of Wrath
        case 31935: // Avenger's Shield
        case 53563: // Beaconf of the Light
            return false;
        default:
            break;
    }

    for (uint8 x = 0; x < MAX_SPELL_EFFECTS; ++x)
    {
        switch (Effects[x].Effect)
        {
            case SPELL_EFFECT_SUMMON:
            case SPELL_EFFECT_SUMMON_PET:
            case SPELL_EFFECT_CAST_BUTTON:
            case SPELL_EFFECT_TAMECREATURE:
            case SPELL_EFFECT_WEAPON_PERCENT_DAMAGE:
            case SPELL_EFFECT_KNOCK_BACK:
                return false;
            case SPELL_EFFECT_SCHOOL_DAMAGE:
                if (DmgClass == SPELL_DAMAGE_CLASS_MELEE)
                    return false;
                break;
            default:
                break;
        }
        switch (Effects[x].ApplyAuraName)
        {
            case SPELL_AURA_MOD_SHAPESHIFT:
                return false;
            default:
                break;
        }
    }

    return true;
}

bool SpellInfo::IsNeedToCheckSchoolImmune() const
{
    // there are a problem with some of spells that does holypower or break cc kinda pvp trinket
    // so we need hack-handle for em

    switch (Id)
    {
        case 879:   // Exorcism
        case 24275: // Hammer of Wrath
        case 25912: // Holy Shock damage
        case 25914: // Holy Shock heal
        case 35395: // Crusader Strike
        case 42292: // Pvp Trinket
        case 59752: // Every Man for Himself (racical)
        case 82327: // Holy Radiance
            return false;
        default:
            break;
    }

    return true;
}

bool SpellInfo::IsRemoveLossControlEffects() const
{
    switch (Id)
    {
        case 42292: // Pvp Trinket
        case 59752: // Every Man for Himself (racical)
        case 108201:// Desecrated Ground
            return true;
        default:
            break;
    }

    return false;
}

int32 SpellInfo::GetCustomCoefficientForStormlash() const
{
    switch (Id)
    {
        case 403:   // Lightning Bolt
        case 1120:  // Drain Soul
        case 45284: // Lightning Bolt (Mastery)
        case 51505: // Lava Burst
        case 77451: // Lava Burst (Mastery)
            return 200;
        case 1752:  // Sinister Strike
            return 50;
        default:
            break;
    }

    return 0;
}

bool SpellInfo::DoesIgnoreGlobalCooldown(Unit* caster) const
{
    switch (Id)
    {
        case 85673: // Word of Glory
        case 114163:// Eternal Flame
        case 136494:// Word of Glory (other)
            if (caster->HasAura(53592)) // Guarded by the Light
                return true;
            break;
        default:
            break;
    }

    return false;
}

bool SpellInfo::IsAffectedByResilience() const
{
    switch (Id)
    {
        case 49016: // Unholy Frenzy
        case 87023: // Cauterize
        case 110914:// Dark Bargain (DoT)
        case 124280:// Touch of Karma (DoT)
            return false;
        default:
            break;
    }

    return true;
}

bool SpellInfo::IsLethalPoison() const
{
    switch (Id)
    {
        case 5760:  // Mind-Numbling Poison
        case 112961:// Leeching Poison
        case 113952:// Paralytic Poison
            return true;
        default:
            break;
    }

    return false;
}

bool SpellInfo::CanTriggerHotStreak() const
{
    switch (Id)
    {
        case 133:   // Fireball
        case 2136:  // Fire Blast
        case 2948:  // Scorch
        case 11129: // Combustion
        case 11366: // Pyroblast
        case 30455: // Ice Lance
        case 44614: // Frostfire Bolt
        case 108853:// Inferno Blast
            return true;
        default:
            break;
    }

    return false;
}

bool SpellInfo::IsCustomCalculated() const
{
    switch (Id)
    {
        case 113344:// Bloodbath
        case 124464:// Mastery: Shadowy Recall - Shadow Word: Pain
        case 124465:// Mastery: Shadowy Recall - Vampiric Touch
        case 124467:// Mastery: Shadowy Recall - Devouring Plague
        case 124468:// Mastery: Shadowy Recall - Mind Flay
            return true;
        default:
            break;
    }

    return false;
}
