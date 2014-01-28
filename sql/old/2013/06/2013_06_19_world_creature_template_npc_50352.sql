#50352/NPC - Qu Nas

    DELETE FROM creature WHERE id = 50352;
    INSERT INTO `creature` (`id`, `map`, `zoneId`, `areaId`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`, `isActive`) VALUES('50352','870','6134','6026','1','65535','0','0','-884.075','-185.962','34.614','2.37133','300','0','0','17','0','0','0','0','0','0');
    UPDATE `creature_template` SET `exp` = 4, `faction_A` = 14, `faction_H` = 14, `unit_flags2` = 0, `type_flags` = 0, `ScriptName` = 'mob_qu_nas' WHERE `entry` = 50352;
    UPDATE `creature_template` SET
    `mindmg` = 9838,
    `maxdmg` = 14331,
    `attackpower` = ROUND((`mindmg` + `maxdmg`) / 4 * 7),
    `mindmg` = ROUND(`mindmg` - `attackpower` / 7),
    `maxdmg` = ROUND(`maxdmg` - `attackpower` / 7)
    WHERE entry = 50352;
    UPDATE creature SET spawntimesecs = 8940 WHERE id = 50338;