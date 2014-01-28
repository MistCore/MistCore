#66617/NPC - Ro shen

    DELETE FROM creature WHERE id = 66617;
    INSERT INTO `creature` (`id`, `map`, `zoneId`, `areaId`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`, `isActive`) VALUES('66617','870','5785','5954','1','65535','0','0','-35.8617','-3151.29','86.1623','2.25113','300','0','0','3','0','0','0','0','0','0');

    UPDATE `creature_template` SET `minlevel` = 85, `maxlevel` = 85, `faction_A` = 14, `faction_H` = 14, `type_flags` = 0, `ScriptName` = 'mob_ro_shen' WHERE `entry` = 66617;
        UPDATE `creature_template` SET
    `mindmg` = 8000,
    `maxdmg` = 12000,
    `attackpower` = ROUND((`mindmg` + `maxdmg`) / 4 * 7),
    `mindmg` = ROUND(`mindmg` - `attackpower` / 7),
    `maxdmg` = ROUND(`maxdmg` - `attackpower` / 7)
    WHERE entry = 66617;
    
UPDATE creature_template SET lootid = 66617 WHERE entry = 66617;
DELETE FROM creature_loot_template WHERE entry = 66617; 
INSERT INTO creature_loot_template VALUES (66617, 81194, 95.854, 1, 0, 1, 1);
INSERT INTO creature_loot_template VALUES (66617, 74833, 36.299, 1, 0, 1, 1);
INSERT INTO creature_loot_template VALUES (66617, 81212, 4.044, 1, 0, 1, 1);
INSERT INTO creature_loot_template VALUES (66617, 89112, 2.629, 1, 0, 1, 1);
INSERT INTO creature_loot_template VALUES (66617, 81968, 0.202, 1, 0, 1, 1);
INSERT INTO creature_loot_template VALUES (66617, 81970, 0.202, 1, 0, 1, 1);
INSERT INTO creature_loot_template VALUES (66617, 81974, 0.202, 1, 0, 1, 1);
INSERT INTO creature_loot_template VALUES (66617, 81980, 0.202, 1, 0, 1, 1);
INSERT INTO creature_loot_template VALUES (66617, 82031, 0.202, 1, 0, 1, 1);
INSERT INTO creature_loot_template VALUES (66617, 82066, 0.202, 1, 0, 1, 1);
INSERT INTO creature_loot_template VALUES (66617, 87903, 0.202, 1, 0, 1, 1);
INSERT INTO creature_loot_template VALUES (66617, 83848, 0.101, 1, 0, 1, 1);
INSERT INTO creature_loot_template VALUES (66617, 81967, 0.101, 1, 0, 1, 1);
INSERT INTO creature_loot_template VALUES (66617, 81972, 0.101, 1, 0, 1, 1);
INSERT INTO creature_loot_template VALUES (66617, 81986, 0.101, 1, 0, 1, 1);
INSERT INTO creature_loot_template VALUES (66617, 81997, 0.101, 1, 0, 1, 1);
INSERT INTO creature_loot_template VALUES (66617, 81998, 0.101, 1, 0, 1, 1);
INSERT INTO creature_loot_template VALUES (66617, 82007, 0.101, 1, 0, 1, 1);
INSERT INTO creature_loot_template VALUES (66617, 82015, 0.101, 1, 0, 1, 1);
INSERT INTO creature_loot_template VALUES (66617, 82017, 0.101, 1, 0, 1, 1);
INSERT INTO creature_loot_template VALUES (66617, 82032, 0.101, 1, 0, 1, 1);
INSERT INTO creature_loot_template VALUES (66617, 82036, 0.101, 1, 0, 1, 1);
INSERT INTO creature_loot_template VALUES (66617, 82037, 0.101, 1, 0, 1, 1);
INSERT INTO creature_loot_template VALUES (66617, 82044, 0.101, 1, 0, 1, 1);
INSERT INTO creature_loot_template VALUES (66617, 82063, 0.101, 1, 0, 1, 1);
INSERT INTO creature_loot_template VALUES (66617, 82068, 0.101, 1, 0, 1, 1);