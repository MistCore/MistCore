-- Insert achievement instance criteria data scripts
DELETE FROM `achievement_criteria_data` WHERE `type`=11 and `criteria_id` IN (7323,7324,7325);
INSERT INTO `achievement_criteria_data` (`criteria_id`, `type`, `value1`, `value2`, `ScriptName`) VALUES
(7323,11,0,0,'achievement_ruby_void'),
(7324,11,0,0,'achievement_emerald_void'),
(7325,11,0,0,'achievement_amber_void');

-- Remove achievements from disables
DELETE FROM `disables` WHERE `sourceType`=4 AND `entry`=7323; -- Ruby Void
DELETE FROM `disables` WHERE `sourceType`=4 AND `entry`=7324; -- Emerald Void
DELETE FROM `disables` WHERE `sourceType`=4 AND `entry`=7325; -- Amber Void