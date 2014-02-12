#55550/NPC - Lurking Tiger

    DELETE FROM creature WHERE id = 55550;
    INSERT INTO `creature` (`id`, `map`, `zoneId`, `areaId`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`, `isActive`) VALUES('55550','870','5785','5876','1','65535','0','0','761.766','-1633.19','58.359','0.414101','300','0','0','156000','0','0','0','0','0','0');
    INSERT INTO `creature` (`id`, `map`, `zoneId`, `areaId`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`, `isActive`) VALUES('55550','870','5785','5876','1','65535','0','0','812.758','-1676.58','55.8086','5.35897','300','0','0','156000','0','0','0','0','0','0');
    INSERT INTO `creature` (`id`, `map`, `zoneId`, `areaId`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`, `isActive`) VALUES('55550','870','5785','5876','1','65535','0','0','797.644','-1773.41','56.8139','2.70746','300','0','0','156000','0','0','0','0','0','0');
    INSERT INTO `creature` (`id`, `map`, `zoneId`, `areaId`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`, `isActive`) VALUES('55550','870','5785','5876','1','65535','0','0','684.927','-1695.43','40.9345','4.78406','300','0','0','156000','0','0','0','0','0','0');

    UPDATE `creature_template` SET `faction_A` = 14, `faction_H` = 14, `ScriptName` = 'mob_lurking_tiger' WHERE `entry` = 55550;
    UPDATE `creature_template` SET
    `mindmg` = 8000,
    `maxdmg` = 12000,
    `attackpower` = ROUND((`mindmg` + `maxdmg`) / 4 * 7),
    `mindmg` = ROUND(`mindmg` - `attackpower` / 7),
    `maxdmg` = ROUND(`maxdmg` - `attackpower` / 7)
    WHERE entry = 55550;
    DELETE FROM creature_looy_template WHERE entry = 55550;
    INSERT INTO creature_loot_template VALUES (55550, 90167, 97.718, 1, 0, 1, 1);
    INSERT INTO creature_loot_template VALUES (55550, 82328, 91.598, 1, 0, 1, 1);
    INSERT INTO creature_loot_template VALUES (55550, 74838, 57.469, 1, 0, 1, 1);
    INSERT INTO creature_loot_template VALUES (55550, 90174, 39.419, 1, 0, 1, 1);
    INSERT INTO creature_loot_template VALUES (55550, 89112, 6.846, 1, 0, 1, 1);
    INSERT INTO creature_loot_template VALUES (55550, 82334, 1.867, 1, 0, 1, 1);
    INSERT INTO creature_loot_template VALUES (55550, 88567, 1.141, 1, 0, 1, 1);
    INSERT INTO creature_loot_template VALUES (55550, 82204, 0.726, 1, 0, 1, 1);
    INSERT INTO creature_loot_template VALUES (55550, 82231, 0.311, 1, 0, 1, 1);
    INSERT INTO creature_loot_template VALUES (55550, 82249, 0.311, 1, 0, 1, 1);
    INSERT INTO creature_loot_template VALUES (55550, 82256, 0.311, 1, 0, 1, 1);
    INSERT INTO creature_loot_template VALUES (55550, 82291, 0.311, 1, 0, 1, 1);
    INSERT INTO creature_loot_template VALUES (55550, 82194, 0.207, 1, 0, 1, 1);
    INSERT INTO creature_loot_template VALUES (55550, 82195, 0.207, 1, 0, 1, 1);
    INSERT INTO creature_loot_template VALUES (55550, 82197, 0.207, 1, 0, 1, 1);
    INSERT INTO creature_loot_template VALUES (55550, 82235, 0.207, 1, 0, 1, 1);
    INSERT INTO creature_loot_template VALUES (55550, 82277, 0.207, 1, 0, 1, 1);
    INSERT INTO creature_loot_template VALUES (55550, 82279, 0.207, 1, 0, 1, 1);
    INSERT INTO creature_loot_template VALUES (55550, 83844, 0.104, 1, 0, 1, 1);
    INSERT INTO creature_loot_template VALUES (55550, 87487, 0.104, 1, 0, 1, 1);
    INSERT INTO creature_loot_template VALUES (55550, 87509, 0.104, 1, 0, 1, 1);
    INSERT INTO creature_loot_template VALUES (55550, 82192, 0.104, 1, 0, 1, 1);
    INSERT INTO creature_loot_template VALUES (55550, 82196, 0.104, 1, 0, 1, 1);
    INSERT INTO creature_loot_template VALUES (55550, 82198, 0.104, 1, 0, 1, 1);
    INSERT INTO creature_loot_template VALUES (55550, 82201, 0.104, 1, 0, 1, 1);
    INSERT INTO creature_loot_template VALUES (55550, 82202, 0.104, 1, 0, 1, 1);
    INSERT INTO creature_loot_template VALUES (55550, 82210, 0.104, 1, 0, 1, 1);
    INSERT INTO creature_loot_template VALUES (55550, 82215, 0.104, 1, 0, 1, 1);
    INSERT INTO creature_loot_template VALUES (55550, 82229, 0.104, 1, 0, 1, 1);
    INSERT INTO creature_loot_template VALUES (55550, 82234, 0.104, 1, 0, 1, 1);
    INSERT INTO creature_loot_template VALUES (55550, 82237, 0.104, 1, 0, 1, 1);
    INSERT INTO creature_loot_template VALUES (55550, 82242, 0.104, 1, 0, 1, 1);
    INSERT INTO creature_loot_template VALUES (55550, 82245, 0.104, 1, 0, 1, 1);
    INSERT INTO creature_loot_template VALUES (55550, 82254, 0.104, 1, 0, 1, 1);
    INSERT INTO creature_loot_template VALUES (55550, 82255, 0.104, 1, 0, 1, 1);
    INSERT INTO creature_loot_template VALUES (55550, 82261, 0.104, 1, 0, 1, 1);
    INSERT INTO creature_loot_template VALUES (55550, 82262, 0.104, 1, 0, 1, 1);
    INSERT INTO creature_loot_template VALUES (55550, 82276, 0.104, 1, 0, 1, 1);
    INSERT INTO creature_loot_template VALUES (55550, 82283, 0.104, 1, 0, 1, 1);
    INSERT INTO creature_loot_template VALUES (55550, 82285, 0.104, 1, 0, 1, 1);
    INSERT INTO creature_loot_template VALUES (55550, 82287, 0.104, 1, 0, 1, 1);
    INSERT INTO creature_loot_template VALUES (55550, 82289, 0.104, 1, 0, 1, 1);
    INSERT INTO creature_loot_template VALUES (55550, 82294, 0.104, 1, 0, 1, 1);
    INSERT INTO creature_loot_template VALUES (55550, 82295, 0.104, 1, 0, 1, 1);