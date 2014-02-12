INSERT INTO spell_bonus_data VALUE (77758, 0, 0, 0.191, 0.2256, 'Druid - Thrash (bear');
UPDATE spell_bonus_data SET ap_dot_bonus = 0.1764, comments = 'Druid - Thrash (cat)' WHERE entry = 106830; -- Thrash (cat)
INSERT INTO spell_script_names VALUE (77758, 'spell_dru_thrash_bear');