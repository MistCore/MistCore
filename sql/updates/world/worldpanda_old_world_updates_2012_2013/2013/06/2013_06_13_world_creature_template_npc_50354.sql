#50354/NPC - Havak

    UPDATE `creature_template` SET `exp` = 4, `faction_A` = 14, `faction_H` = 14, `unit_flags2` = 0, `type_flags` = 0, `lootid` = 50354, `ScriptName` = 'mob_havak' WHERE `entry` = 50354;
    UPDATE `creature_template` SET
    `mindmg` = 9838,
    `maxdmg` = 14331,
    `attackpower` = ROUND((`mindmg` + `maxdmg`) / 4 * 7),
    `mindmg` = ROUND(`mindmg` - `attackpower` / 7),
    `maxdmg` = ROUND(`maxdmg` - `attackpower` / 7)
    WHERE entry = 50354;
    UPDATE creature SET spawntimesecs = 8940 WHERE id = 50354;
    DELETE FROM `creature_loot_template` WHERE (`entry`=50354);
    INSERT INTO `creature_loot_template` VALUES 
    (50354, 87217, 21, 1, 0, 1, 1),
    (50354, 86573, 14, 1, 0, 1, 1),
    (50354, 87618, 12, 1, 0, 1, 1),
    (50354, 87620, 11, 1, 0, 1, 1),
    (50354, 87617, 11, 1, 0, 1, 1),
    (50354, 87613, 11, 1, 0, 1, 1),
    (50354, 87614, 11, 1, 0, 1, 1),
    (50354, 87616, 11, 1, 0, 1, 1),
    (50354, 87619, 11, 1, 0, 1, 1),
    (50354, 87621, 11, 1, 0, 1, 1),
    (50354, 87615, 0.11, 1, 0, 1, 1);