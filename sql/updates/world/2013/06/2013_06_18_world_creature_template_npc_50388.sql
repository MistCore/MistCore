#50388/NPC - Torik-Ethis

    DELETE FROM creature WHERE id = 50388;
    INSERT INTO `creature` (`id`, `map`, `zoneId`, `areaId`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`, `isActive`) VALUES('50388','870','6134','6019','1','1','0','0','-1184.93','2288.25','41.5073','1.24193','300','0','0','17','0','0','0','0','0','0');
    UPDATE `creature_template` SET `exp` = 4, `faction_A` = 14, `faction_H` = 14, `unit_flags2` = 0, `type_flags` = 0, `ScriptName` = 'mob_torik_ethis' WHERE `entry` = 50388;
    UPDATE `creature_template` SET
    `mindmg` = 9838,
    `maxdmg` = 14331,
    `attackpower` = ROUND((`mindmg` + `maxdmg`) / 4 * 7),
    `mindmg` = ROUND(`mindmg` - `attackpower` / 7),
    `maxdmg` = ROUND(`maxdmg` - `attackpower` / 7)
    WHERE entry = 50388;
    UPDATE creature SET spawntimesecs = 8940 WHERE id = 50338;