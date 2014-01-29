INSERT INTO spell_bonus_data VALUE (20271, 0.546, 0, 0, 0, 'Paladin - Judgment');
UPDATE spell_bonus_data SET direct_bonus = 1.12, dot_bonus = 0, ap_bonus = 0, ap_dot_bonus = 0 WHERE entry = 19750; -- Flash of Light
UPDATE spell_script_names SET spell_id = 633 WHERE spell_id = -633; -- Lay on Hands
INSERT INTO spell_script_names VALUE (642, 'spell_pal_divine_shield');
INSERT INTO spell_script_names VALUE (4987, 'spell_pal_cleanse');