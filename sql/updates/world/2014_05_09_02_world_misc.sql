UPDATE `creature_template` SET `ScriptName` = 'npc_training_dummy_start_zones' WHERE `entry` = 44548;
DELETE FROM `smart_scripts` WHERE `entryorguid` IN (298100, 4462900);
DELETE FROM `creature` WHERE `id` = 0;