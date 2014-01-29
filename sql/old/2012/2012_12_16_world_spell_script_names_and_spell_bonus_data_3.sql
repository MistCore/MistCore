INSERT INTO spell_script_names VALUES
(6343, 'spell_warr_deep_wounds'),
(12294, 'spell_warr_deep_wounds'),
(20243, 'spell_warr_deep_wounds'),
(23881, 'spell_warr_deep_wounds');
INSERT INTO spell_script_names VALUE (6343, 'spell_warr_thunder_clap');
DELETE FROM spell_bonus_data WHERE entry = 12162;
INSERT INTO spell_bonus_data VALUE (115767, -1, -1, -1, 0.24, 'Warrior - Deep Wounds');
UPDATE spell_bonus_data SET ap_bonus = 0.45 WHERE entry = 6343;