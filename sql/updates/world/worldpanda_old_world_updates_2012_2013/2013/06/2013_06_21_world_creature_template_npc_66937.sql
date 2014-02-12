#66937/NPC - Akkalar

    DELETE FROM creature WHERE id = 66937;
    INSERT INTO `creature` (`id`, `map`, `zoneId`, `areaId`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`, `isActive`) VALUES('66937','870','5785','5943','1','65535','0','0','-790.753','-2744.13','11.7587','2.52879','300','0','0','5','0','0','0','0','0','0');
    UPDATE `creature_template` SET `minlevel` = 90, `maxlevel` = 90, `faction_A` = 14, `faction_H` = 14, `ScriptName` = 'mob_akkalar' WHERE `entry` = 66937;
    UPDATE `creature_template` SET
    `mindmg` = 9838,
    `maxdmg` = 14331,
    `attackpower` = ROUND((`mindmg` + `maxdmg`) / 4 * 7),
    `mindmg` = ROUND(`mindmg` - `attackpower` / 7),
    `maxdmg` = ROUND(`maxdmg` - `attackpower` / 7)
    WHERE entry = 66937;
    UPDATE creature_template SET lootid = 66937 WHERE entry = 66937;
    DELETE FROM creature_looy_template WHERE entry = 66937;
    INSERT INTO creature_loot_template VALUES (66937, 90167, 97.718, 1, 0, 1, 1);
    INSERT INTO creature_loot_template VALUES (66937, 82328, 91.598, 1, 0, 1, 1);
    INSERT INTO creature_loot_template VALUES (66937, 74838, 57.469, 1, 0, 1, 1);
    INSERT INTO creature_loot_template VALUES (66937, 90174, 39.419, 1, 0, 1, 1);
    INSERT INTO creature_loot_template VALUES (66937, 89112, 6.846, 1, 0, 1, 1);
    INSERT INTO creature_loot_template VALUES (66937, 82334, 1.867, 1, 0, 1, 1);
    INSERT INTO creature_loot_template VALUES (66937, 88567, 1.141, 1, 0, 1, 1);
    INSERT INTO creature_loot_template VALUES (66937, 82204, 0.726, 1, 0, 1, 1);
    INSERT INTO creature_loot_template VALUES (66937, 82231, 0.311, 1, 0, 1, 1);
    INSERT INTO creature_loot_template VALUES (66937, 82249, 0.311, 1, 0, 1, 1);
    INSERT INTO creature_loot_template VALUES (66937, 82256, 0.311, 1, 0, 1, 1);
    INSERT INTO creature_loot_template VALUES (66937, 82291, 0.311, 1, 0, 1, 1);
    INSERT INTO creature_loot_template VALUES (66937, 82194, 0.207, 1, 0, 1, 1);
    INSERT INTO creature_loot_template VALUES (66937, 82195, 0.207, 1, 0, 1, 1);
    INSERT INTO creature_loot_template VALUES (66937, 82197, 0.207, 1, 0, 1, 1);
    INSERT INTO creature_loot_template VALUES (66937, 82235, 0.207, 1, 0, 1, 1);
    INSERT INTO creature_loot_template VALUES (66937, 82277, 0.207, 1, 0, 1, 1);
    INSERT INTO creature_loot_template VALUES (66937, 82279, 0.207, 1, 0, 1, 1);
    INSERT INTO creature_loot_template VALUES (66937, 83844, 0.104, 1, 0, 1, 1);
    INSERT INTO creature_loot_template VALUES (66937, 87487, 0.104, 1, 0, 1, 1);
    INSERT INTO creature_loot_template VALUES (66937, 87509, 0.104, 1, 0, 1, 1);
    INSERT INTO creature_loot_template VALUES (66937, 82192, 0.104, 1, 0, 1, 1);
    INSERT INTO creature_loot_template VALUES (66937, 82196, 0.104, 1, 0, 1, 1);
    INSERT INTO creature_loot_template VALUES (66937, 82198, 0.104, 1, 0, 1, 1);
    INSERT INTO creature_loot_template VALUES (66937, 82201, 0.104, 1, 0, 1, 1);
    INSERT INTO creature_loot_template VALUES (66937, 82202, 0.104, 1, 0, 1, 1);
    INSERT INTO creature_loot_template VALUES (66937, 82210, 0.104, 1, 0, 1, 1);
    INSERT INTO creature_loot_template VALUES (66937, 82215, 0.104, 1, 0, 1, 1);
    INSERT INTO creature_loot_template VALUES (66937, 82229, 0.104, 1, 0, 1, 1);
    INSERT INTO creature_loot_template VALUES (66937, 82234, 0.104, 1, 0, 1, 1);
    INSERT INTO creature_loot_template VALUES (66937, 82237, 0.104, 1, 0, 1, 1);
    INSERT INTO creature_loot_template VALUES (66937, 82242, 0.104, 1, 0, 1, 1);
    INSERT INTO creature_loot_template VALUES (66937, 82245, 0.104, 1, 0, 1, 1);
    INSERT INTO creature_loot_template VALUES (66937, 82254, 0.104, 1, 0, 1, 1);
    INSERT INTO creature_loot_template VALUES (66937, 82255, 0.104, 1, 0, 1, 1);
    INSERT INTO creature_loot_template VALUES (66937, 82261, 0.104, 1, 0, 1, 1);
    INSERT INTO creature_loot_template VALUES (66937, 82262, 0.104, 1, 0, 1, 1);
    INSERT INTO creature_loot_template VALUES (66937, 82276, 0.104, 1, 0, 1, 1);
    INSERT INTO creature_loot_template VALUES (66937, 82283, 0.104, 1, 0, 1, 1);
    INSERT INTO creature_loot_template VALUES (66937, 82285, 0.104, 1, 0, 1, 1);
    INSERT INTO creature_loot_template VALUES (66937, 82287, 0.104, 1, 0, 1, 1);
    INSERT INTO creature_loot_template VALUES (66937, 82289, 0.104, 1, 0, 1, 1);
    INSERT INTO creature_loot_template VALUES (66937, 82294, 0.104, 1, 0, 1, 1);
    INSERT INTO creature_loot_template VALUES (66937, 82295, 0.104, 1, 0, 1, 1);