DELETE FROM spell_bonus_data WHERE entry IN (121414, 120761);
INSERT INTO spell_bonus_data VALUES
(120761, 0, 0, 0.2, 0, 'Hunter - Glaive Toss (right damage)'),
(121414, 0, 0, 0.2, 0, 'Hunter - Glaive Toss (left damage)');
INSERT INTO spell_script_names VALUES
(120761, 'spell_hun_glaive_toss_damage'),
(121414, 'spell_hun_glaive_toss_damage');
INSERT INTO spell_script_names VALUES
(120755, 'spell_hun_glaive_toss_missile'),
(120756, 'spell_hun_glaive_toss_missile');