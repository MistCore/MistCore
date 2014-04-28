-- Doors in Temple of Jade Serpent should not be clickable
UPDATE  `gameobject_template` SET  `flags` =  '4' WHERE `entry` = 213545;
UPDATE  `gameobject_template` SET  `flags` =  '4' WHERE `entry` = 213547;
-- readd a stormwind guard who was deleted by me instead of a worgen racial trainer
INSERT INTO `creature` (`guid`, `id`, `map`, `zoneId`, `areaId`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`, `isActive`) VALUES (168293, 42218, 0, 6170, 9, 1, 1, 0, 0, -8909.29, -132.802, 80.6389, 2.11185, 120, 0, 0, 1, 0, 0, 0, 0, 0, 0); 
-- delete worgen racial trainer 
DELETE FROM `creature` WHERE `guid` = 1343710; -- nordshire abbey spawn
DELETE FROM `creature` WHERE `guid` = 1322355; -- stormwind spawn
DELETE FROM `creature_template` WHERE `entry` = 69070; -- template, id will be used in throne of thunder
-- remove double spawned npcs in shrine of seven stars
DELETE FROM `creature` WHERE `guid` = 1343231; -- Raishen the Needle <Tailoring Supplies> 
DELETE FROM `creature` WHERE `guid` = 1330733; -- Veronica Faraday <Inscription Supplies>
DELETE FROM `creature` WHERE `guid` = 1343226; -- Tanner Pang <Leatherworking & Skinning Supplies>
DELETE FROM `creature` WHERE `guid` = 1330729; -- Tommy Tinkerspade <Herbalism Supplies>
-- add more game_tele positions for The Jade Forest
INSERT INTO `game_tele` (`id`, `position_x`, `position_y`, `position_z`, `orientation`, `map`, `name`) VALUES  
('1569', '961.321472', '-2462.934814', '180.579086', '4.408737', '870', 'TempleOfTheJadeSerpent'),
('1570', '1507.572632', '-1816.659790', '246.184235', '5.934554', '870', 'DawnsBlossom'),
('1571', '523.207520', '-1673.087891', '198.900345', '1.686340', '870', 'SerpentsOverlook'),
('1572', '-301.668915', '-1755.793213', '61.588871', '5.372994', '870', 'PawdonVillage'),
('1573', '-184.395279', '-2635.250977', '0.353680', '4.838919', '870', 'PearlfinVillage'),
('1574', '1601.301758', '-2531.587158', '152.212265', '3.715334', '870', 'TheAboretum'),
('1575', '2549.373779', '-2418.198730', '24.083061', '5.173822', '870', 'SriLaVillage'),
('1576', '2398.645264', '-2101.295654', '228.802246', '5.164394', '870', 'EmperorsOmen'),
('1577', '2507.808594', '-1590.638794', '400.869446', '3.360335', '870', 'TianMonastery');
