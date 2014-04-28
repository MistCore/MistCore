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
