-- Fixes moving training dummies in nightelve start zone
UPDATE  `creature_template` SET  `ScriptName` =  'npc_training_dummy_start_zones', `unit_flags`='393216' WHERE `entry` = 44614;
UPDATE `creature` SET `unit_flags`='393216' WHERE `id`= 44614;
