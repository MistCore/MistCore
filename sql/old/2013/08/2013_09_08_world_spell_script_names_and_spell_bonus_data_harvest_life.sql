DELETE FROM spell_script_names WHERE ScriptName = 'spell_warl_harvest_life';
DELETE FROM spell_script_names WHERE ScriptName = 'spell_warl_soulburn_harvest_life';
INSERT INTO spell_script_names VALUE (115707, 'spell_warl_soulburn_harvest_life');
INSERT INTO spell_script_names VALUE (108371, 'spell_warl_harvest_life');
DELETE FROM spell_bonus_data WHERE entry IN (108371, 115707);
INSERT INTO spell_bonus_data VALUES
(108371, 0, 0.45, 0, 0, 'Warlock - Harvest Life'),
(115707, 0, 0.45, 0, 0, 'Warlock - Soulburn: Harvest Life');