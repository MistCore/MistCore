#50734/NPC - Lith ik the Stalker

    DELETE FROM creature WHERE id = 50734;
    INSERT INTO `creature` (`id`, `map`, `zoneId`, `areaId`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`, `isActive`) VALUES('50734','870','5842','5842','1','65535','0','0','1149.02','4484.93','185.385','2.68093','300','0','0','3051574','0','0','0','0','0','0');
    UPDATE `creature_template` SET `unit_flags` = 0, `unit_flags2` = 0, `type_flags` = 0, `ScriptName` = 'mob_lith_ik' WHERE `entry` = 50734;
    UPDATE `creature_template` SET
    `mindmg` = 9838,
    `maxdmg` = 14331,
    `attackpower` = ROUND((`mindmg` + `maxdmg`) / 4 * 7),
    `mindmg` = ROUND(`mindmg` - `attackpower` / 7),
    `maxdmg` = ROUND(`maxdmg` - `attackpower` / 7)
    WHERE entry = 50734;
    UPDATE creature SET spawntimesecs = 8940 WHERE id = 50338;