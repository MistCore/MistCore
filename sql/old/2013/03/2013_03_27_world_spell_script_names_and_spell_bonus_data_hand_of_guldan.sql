INSERT INTO spell_script_names VALUE (86040, 'spell_warl_hand_of_guldan');
INSERT INTO spell_bonus_data VALUE (86040, 0.4826, 0, 0, 0, 'Warlock - Hand of Gul''Dan');
DELETE FROM spell_bonus_data WHERE entry = 47960; -- Shadowflame
INSERT INTO spell_bonus_data VALUE (47960, 0, 0.137, 0, 0, 'Warlock - Shadowflame');