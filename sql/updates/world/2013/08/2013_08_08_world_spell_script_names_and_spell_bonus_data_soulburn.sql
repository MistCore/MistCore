INSERT INTO spell_script_names VALUE (74434, 'spell_warl_soulburn_override');
INSERT INTO spell_script_names VALUES
(109468, 'spell_warl_soulburn_remove'),
(104225, 'spell_warl_soulburn_remove'),
(104223, 'spell_warl_soulburn_remove');
INSERT INTO spell_script_names VALUE (114794, 'spell_warl_demonic_circle_teleport');
INSERT INTO spell_script_names VALUE (114790, 'spell_warl_soulburn_seed_of_corruption');
INSERT INTO spell_script_names VALUE (87385, 'spell_warl_soulburn_seed_of_corruption_damage');
INSERT INTO spell_script_names VALUE (104220, 'spell_warl_soulburn_health_funnel');
INSERT INTO spell_bonus_data VALUE (114790, 0, 0.25, 0, 0, 'Warlock - Soulburn: Seed of Corruption');
DELETE FROM spell_bonus_data WHERE entry IN (27285,87385);
INSERT INTO spell_bonus_data VALUES
(27285, 0.91, 0, 0, 0, 'Warlock - Seed of Corruption (AoE)'),
(87385, 0.91, 0, 0, 0, 'Warlock - Soulburn: Seed of Corruption (AoE)');