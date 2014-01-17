#50823/NPC - Mister Ferocious

    DELETE FROM creature WHERE id = 50823;
    INSERT INTO `creature` (`id`, `map`, `zoneId`, `areaId`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`, `isActive`) VALUES('50823','870','5785','5836','1','65535','0','0','1807.09','-1501.88','226.622','3.35817','300','0','0','16','0','0','0','0','0','0');
    UPDATE `creature_template` SET `unit_flags` = 0, `unit_flags2` = 0, `type_flags` = 0, `ScriptName` = 'mob_mister_ferocious' WHERE `entry` = 50823;
    UPDATE `creature_template` SET
    `mindmg` = 9838,
    `maxdmg` = 14331,
    `attackpower` = ROUND((`mindmg` + `maxdmg`) / 4 * 7),
    `mindmg` = ROUND(`mindmg` - `attackpower` / 7),
    `maxdmg` = ROUND(`maxdmg` - `attackpower` / 7)
    WHERE entry = 50823;
    UPDATE creature SET spawntimesecs = 8940 WHERE id = 50338;