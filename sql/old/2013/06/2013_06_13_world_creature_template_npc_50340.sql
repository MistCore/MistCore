#50340/NPC - Gaarn the Toxic

    UPDATE `creature_template` SET `exp` = 4, `faction_A` = 14, `faction_H` = 14, `unit_flags2` = 0, `type_flags` = 0, `ScriptName` = 'mob_gaarn_the_toxic' WHERE `entry` = 50340;
    UPDATE `creature_template` SET
    `mindmg` = 9838,
    `maxdmg` = 14331,
    `attackpower` = ROUND((`mindmg` + `maxdmg`) / 4 * 7),
    `mindmg` = ROUND(`mindmg` - `attackpower` / 7),
    `maxdmg` = ROUND(`maxdmg` - `attackpower` / 7)
    WHERE entry = 50340;
    UPDATE creature SET spawntimesecs = 8940 WHERE id = 50340;
    UPDATE `creature_template` SET `lootid` = 50340 WHERE `entry` = 50340;
    DELETE FROM `creature_loot_template` WHERE (`entry`=50340);
    INSERT INTO `creature_loot_template` VALUES 
    (50340, 87217, 20, 1, 0, 1, 1),
    (50340, 90725, 15, 1, 0, 1, 1),
    (50340, 87609, 12, 1, 0, 1, 1),
    (50340, 87612, 11, 1, 0, 1, 1),
    (50340, 87604, 11, 1, 0, 1, 1),
    (50340, 87605, 11, 1, 0, 1, 1),
    (50340, 87610, 11, 1, 0, 1, 1),
    (50340, 87611, 11, 1, 0, 1, 1),
    (50340, 87606, 11, 1, 0, 1, 1),
    (50340, 87607, 11, 1, 0, 1, 1),
    (50340, 87608, 10, 1, 0, 1, 1);