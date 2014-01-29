DELETE FROM spell_script_names WHERE spell_id = 115181;
INSERT INTO spell_script_names VALUE (115181, 'spell_monk_breath_of_fire');

DELETE FROM spell_bonus_data WHERE entry = 123725 OR entry = 115181;
INSERT INTO spell_bonus_data VALUES
(115181, -1, -1, 0.3626, -1, 'Monk - Breath of Fire direct damages'),
(123725, -1, -1, -1, 0.3626, 'Monk - Breath of Fire DoT');