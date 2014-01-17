INSERT INTO spell_script_names VALUE (115313, 'spell_monk_jade_serpent_statue');
-- Set flags UNIT_FLAG_DISABLE_MOVE| UNIT_FLAG_STUNNED| on Serpent Jade Statue and Sturdy ox Statue
UPDATE `creature_template` SET `unit_flags` = 0x4|0x40000 WHERE `entry` = 60849 OR `entry` = 61146;