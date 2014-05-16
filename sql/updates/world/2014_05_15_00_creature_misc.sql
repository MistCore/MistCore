UPDATE `creature_template` SET `unit_flags` = 646, `ScriptName` = 'npc_demonic_gateway', `npcflag` = 16777216   WHERE `entry` IN (59262, 59271);

DELETE FROM `creature_template_addon` WHERE `entry` IN (59262, 59271);
INSERT INTO `creature_template_addon` (`entry`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `auras`) VALUES 
(59262, 0, 0, 0, 1, 0, '71994'),
(59271, 0, 0, 0, 1, 0, '71994');