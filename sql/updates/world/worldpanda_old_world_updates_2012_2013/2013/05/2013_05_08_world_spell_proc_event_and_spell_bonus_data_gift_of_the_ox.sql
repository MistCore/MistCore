DELETE FROM spell_proc_event WHERE entry = 124502;
INSERT INTO spell_proc_event (entry, procFlags) VALUE (124502, (0x10|0x400000|0x800000));
DELETE FROM spell_bonus_data WHERE entry = 124507;
INSERT INTO spell_bonus_data VALUE (124507, 0, 0, 0.5025, 0, 'Monk - Gift of the Ox healing');