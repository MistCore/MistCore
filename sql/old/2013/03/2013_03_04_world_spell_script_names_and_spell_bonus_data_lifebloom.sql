UPDATE spell_bonus_data SET direct_bonus = 0.752 WHERE entry = 33763; -- Lifebloom : Final heal
INSERT INTO spell_script_names VALUE (33763, 'spell_dru_lifebloom');
INSERT INTO spell_script_names VALUES
(5185, 'spell_dru_lifebloom_refresh'),
(8936, 'spell_dru_lifebloom_refresh'),
(50464, 'spell_dru_lifebloom_refresh');