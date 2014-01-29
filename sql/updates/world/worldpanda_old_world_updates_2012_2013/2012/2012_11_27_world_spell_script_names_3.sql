DELETE FROM spell_script_names WHERE spell_id = 115057;
INSERT INTO spell_script_names VALUE (115057, 'spell_monk_flying_serpent_kick');

DELETE FROM spell_bonus_data WHERE entry = 123586;
INSERT INTO spell_bonus_data VALUE (123586, -1, -1, 0.45, -1, 'Monk - Flying Serpent Kick : Choc on the ground');