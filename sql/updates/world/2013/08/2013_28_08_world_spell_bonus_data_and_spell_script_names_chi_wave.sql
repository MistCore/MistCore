DELETE FROM spell_bonus_data WHERE entry IN (132463, 132467);
INSERT INTO spell_bonus_data VALUES
(132463, 0, 0, 0.64125, 0, 'Monk - Chi Wave (heal)'),
(132467, 0, 0, 0.225, 0, 'Monk - Chi Wave (damage)');
INSERT INTO spell_script_names VALUE (115098, 'spell_monk_chi_wave');
INSERT INTO spell_script_names VALUES
(132463, 'spell_monk_chi_wave_bolt'),
(132467, 'spell_monk_chi_wave_bolt');
INSERT INTO spell_script_names VALUE (132464, 'spell_monk_chi_wave_healing_bolt');