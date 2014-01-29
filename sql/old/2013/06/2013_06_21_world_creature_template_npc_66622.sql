#66622/NPC - Rakira

    DELETE FROM creature WHERE id = 66622;
    INSERT INTO `creature` (`id`, `map`, `zoneId`, `areaId`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`, `isActive`) VALUES('66622','870','5785','5891','1','65535','0','0','213.685','-2435.45','72.3088','0.0755944','300','0','0','4','0','0','0','0','0','0');

    UPDATE `creature_template` SET `minlevel` = 85, `maxlevel` = 85, `faction_A` = 14, `faction_H` = 14, `type_flags` = 0, `ScriptName` = 'mob_rakira' WHERE `entry` = 66622;
    UPDATE `creature_template` SET
    `mindmg` = 8000,
    `maxdmg` = 12000,
    `attackpower` = ROUND((`mindmg` + `maxdmg`) / 4 * 7),
    `mindmg` = ROUND(`mindmg` - `attackpower` / 7),
    `maxdmg` = ROUND(`maxdmg` - `attackpower` / 7)
    WHERE entry = 66622;
    DELETE FROM creature_looy_template WHERE entry = 66622;
    INSERT INTO creature_loot_template VALUES (66622, 90167, 97.718, 1, 0, 1, 1);
    INSERT INTO creature_loot_template VALUES (66622, 82328, 91.598, 1, 0, 1, 1);
    INSERT INTO creature_loot_template VALUES (66622, 74838, 57.469, 1, 0, 1, 1);
    INSERT INTO creature_loot_template VALUES (66622, 90174, 39.419, 1, 0, 1, 1);
    INSERT INTO creature_loot_template VALUES (66622, 89112, 6.846, 1, 0, 1, 1);
    INSERT INTO creature_loot_template VALUES (66622, 82334, 1.867, 1, 0, 1, 1);
    INSERT INTO creature_loot_template VALUES (66622, 88567, 1.141, 1, 0, 1, 1);
    INSERT INTO creature_loot_template VALUES (66622, 82204, 0.726, 1, 0, 1, 1);
    INSERT INTO creature_loot_template VALUES (66622, 82231, 0.311, 1, 0, 1, 1);
    INSERT INTO creature_loot_template VALUES (66622, 82249, 0.311, 1, 0, 1, 1);
    INSERT INTO creature_loot_template VALUES (66622, 82256, 0.311, 1, 0, 1, 1);
    INSERT INTO creature_loot_template VALUES (66622, 82291, 0.311, 1, 0, 1, 1);
    INSERT INTO creature_loot_template VALUES (66622, 82194, 0.207, 1, 0, 1, 1);
    INSERT INTO creature_loot_template VALUES (66622, 82195, 0.207, 1, 0, 1, 1);
    INSERT INTO creature_loot_template VALUES (66622, 82197, 0.207, 1, 0, 1, 1);
    INSERT INTO creature_loot_template VALUES (66622, 82235, 0.207, 1, 0, 1, 1);
    INSERT INTO creature_loot_template VALUES (66622, 82277, 0.207, 1, 0, 1, 1);
    INSERT INTO creature_loot_template VALUES (66622, 82279, 0.207, 1, 0, 1, 1);
    INSERT INTO creature_loot_template VALUES (66622, 83844, 0.104, 1, 0, 1, 1);
    INSERT INTO creature_loot_template VALUES (66622, 87487, 0.104, 1, 0, 1, 1);
    INSERT INTO creature_loot_template VALUES (66622, 87509, 0.104, 1, 0, 1, 1);
    INSERT INTO creature_loot_template VALUES (66622, 82192, 0.104, 1, 0, 1, 1);
    INSERT INTO creature_loot_template VALUES (66622, 82196, 0.104, 1, 0, 1, 1);
    INSERT INTO creature_loot_template VALUES (66622, 82198, 0.104, 1, 0, 1, 1);
    INSERT INTO creature_loot_template VALUES (66622, 82201, 0.104, 1, 0, 1, 1);
    INSERT INTO creature_loot_template VALUES (66622, 82202, 0.104, 1, 0, 1, 1);
    INSERT INTO creature_loot_template VALUES (66622, 82210, 0.104, 1, 0, 1, 1);
    INSERT INTO creature_loot_template VALUES (66622, 82215, 0.104, 1, 0, 1, 1);
    INSERT INTO creature_loot_template VALUES (66622, 82229, 0.104, 1, 0, 1, 1);
    INSERT INTO creature_loot_template VALUES (66622, 82234, 0.104, 1, 0, 1, 1);
    INSERT INTO creature_loot_template VALUES (66622, 82237, 0.104, 1, 0, 1, 1);
    INSERT INTO creature_loot_template VALUES (66622, 82242, 0.104, 1, 0, 1, 1);
    INSERT INTO creature_loot_template VALUES (66622, 82245, 0.104, 1, 0, 1, 1);
    INSERT INTO creature_loot_template VALUES (66622, 82254, 0.104, 1, 0, 1, 1);
    INSERT INTO creature_loot_template VALUES (66622, 82255, 0.104, 1, 0, 1, 1);
    INSERT INTO creature_loot_template VALUES (66622, 82261, 0.104, 1, 0, 1, 1);
    INSERT INTO creature_loot_template VALUES (66622, 82262, 0.104, 1, 0, 1, 1);
    INSERT INTO creature_loot_template VALUES (66622, 82276, 0.104, 1, 0, 1, 1);
    INSERT INTO creature_loot_template VALUES (66622, 82283, 0.104, 1, 0, 1, 1);
    INSERT INTO creature_loot_template VALUES (66622, 82285, 0.104, 1, 0, 1, 1);
    INSERT INTO creature_loot_template VALUES (66622, 82287, 0.104, 1, 0, 1, 1);
    INSERT INTO creature_loot_template VALUES (66622, 82289, 0.104, 1, 0, 1, 1);
    INSERT INTO creature_loot_template VALUES (66622, 82294, 0.104, 1, 0, 1, 1);
    INSERT INTO creature_loot_template VALUES (66622, 82295, 0.104, 1, 0, 1, 1);