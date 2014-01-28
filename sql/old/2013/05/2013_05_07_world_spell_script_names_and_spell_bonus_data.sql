INSERT INTO spell_script_names VALUE (53600, 'spell_pal_shield_of_the_righteous');
UPDATE spell_bonus_data SET ap_bonus = 0.617 WHERE entry = 53600; -- Shield of the Righteous
UPDATE spell_bonus_data SET direct_bonus = 0.315, ap_bonus = 0.8175 WHERE entry = 31935; -- Avenger's Shield