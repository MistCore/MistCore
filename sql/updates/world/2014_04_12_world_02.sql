-- Human mages now have frostfire bolt in the bar at creation
UPDATE playercreateinfo_action SET  `action` =  '44614' WHERE race =  '1' AND class =  '8' AND button =  '0';
-- Stormwind Royal Guard shouldn't have the spell Stormwind Flag Carrier always on, fixed a visual bug
DELETE FROM `smart_scripts` WHERE `entryorguid` = 42218 AND `source_type` = 0 AND `id` = 8 AND `link` = 0;
-- There shouldn't be Worgen Racial Trainer in the human start zone
DELETE FROM `creature` WHERE `guid` = 168293;
-- remove unneeded table copies
DROP TABLE `creature_addon_copy`, `creature_addon_qsdsqd`, `creature_formations_copy`, `creature_transport_copy`, `quest_template_copy`;
