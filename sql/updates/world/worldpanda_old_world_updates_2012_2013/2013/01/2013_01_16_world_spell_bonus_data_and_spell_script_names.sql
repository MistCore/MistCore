INSERT INTO spell_script_names VALUES
(86121, 'spell_warl_soul_swap'),
(86213, 'spell_warl_soul_swap'),
(119678, 'spell_warl_soul_swap_soulburn');
INSERT INTO spell_bonus_data VALUES
(86121, 0.5, -1, -1, -1, 'Warlock - Soul Swap'),
(119678, 0.5, -1, -1, -1, 'Warlock - Soul Swap : Soulburn'),
(86213, 0.5, -1, -1, -1, 'Warlock - Soul Swap : Exhale');
UPDATE spell_bonus_data SET direct_bonus = 1.75 WHERE entry = 48181; -- Haunt