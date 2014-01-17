#50828/NPC - Bonobos

    DELETE FROM creature WHERE id = 50828;
    INSERT INTO `creature` (`id`, `map`, `zoneId`, `areaId`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`, `isActive`) VALUES('50828','870','5805','5967','1','65535','0','0','41.6965','2067.66','140.691','5.40846','300','0','0','17','0','0','0','0','0','0');

    UPDATE `creature_template` SET `exp` = 4, `faction_A` = 14, `faction_H` = 14, `type_flags` = 0, `ScriptName` = 'mob_bonobos' WHERE `entry` = 50828;
    UPDATE `creature_template` SET
    `mindmg` = 9838,
    `maxdmg` = 14331,
    `attackpower` = ROUND((`mindmg` + `maxdmg`) / 4 * 7),
    `mindmg` = ROUND(`mindmg` - `attackpower` / 7),
    `maxdmg` = ROUND(`maxdmg` - `attackpower` / 7)
    WHERE entry = 50828;
    UPDATE creature SET spawntimesecs = 8940 WHERE id = 50828;
    UPDATE `creature_template` SET `lootid` = 50828 WHERE `entry` = 50828;
    DELETE FROM `creature_loot_template` WHERE (`entry`=50828);
    INSERT INTO `creature_loot_template` VALUES 
    (50828, 87217, 20, 1, 0, 1, 1),
    (50828, 87595, 11, 1, 0, 1, 1),
    (50828, 87597, 11, 1, 0, 1, 1),
    (50828, 87602, 11, 1, 0, 1, 1),
    (50828, 87599, 11, 1, 0, 1, 1),
    (50828, 87600, 11, 1, 0, 1, 1),
    (50828, 87598, 11, 1, 0, 1, 1),
    (50828, 87596, 11, 1, 0, 1, 1),
    (50828, 87601, 11, 1, 0, 1, 1),
    (50828, 87591, 10, 1, 0, 1, 1),
    (50828, 87603, 10, 1, 0, 1, 1);