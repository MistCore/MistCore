DELETE FROM spell_bonus_data WHERE entry = 114163; -- Eternal Flame
DELETE FROM spell_bonus_data WHERE entry = 130551; -- Word of Glory
DELETE FROM spell_script_names WHERE ScriptName = 'spell_pal_eternal_flame';
INSERT INTO spell_bonus_data VALUES
(114163, 0, 0, 0, 0, 'Paladin - Eternal Flame'),
(130551, 0, 0, 0, 0, 'Paladin - Word of Glory');