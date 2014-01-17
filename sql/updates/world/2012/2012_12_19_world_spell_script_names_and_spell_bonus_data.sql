INSERT INTO spell_script_names VALUES
(17962, 'spell_warl_burning_embers'), -- Conflagrate
(108685, 'spell_warl_burning_embers'), -- Conflagrate (Fire and Brimstone)
(29722, 'spell_warl_burning_embers'), -- Incinerate
(114654, 'spell_warl_burning_embers'); -- Incinerate (Fire and Brimstone)

INSERT INTO spell_bonus_data VALUE (108685, 0.744, -1, -1, -1, 'Warlock - Conflagrate (Fire and Brimstone)'); -- Conflagrate (Fire and Brimstone)
UPDATE spell_bonus_data SET direct_bonus = 1.5, dot_bonus = -1, ap_bonus = -1, ap_dot_bonus = -1 WHERE entry = 17962; -- Conflagrate
UPDATE spell_bonus_data SET direct_bonus = 1.4 WHERE entry = 29722; -- Incinerate
INSERT INTO spell_bonus_data VALUE (114654, 0.707, -1, -1, -1, 'Warlock - Incinerate (Fire and Brimstone)'); -- Incinerate (Fire and Brimstone)