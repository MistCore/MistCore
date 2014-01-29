INSERT INTO spell_script_names VALUE (89420, 'spell_warl_soulburn_drain_life');
DELETE FROM spell_bonus_data WHERE entry = 89420;
INSERT INTO spell_bonus_data VALUE (89420, 0, 0.334, 0, 0, 'Warlock - Soulburn : Drain Life');