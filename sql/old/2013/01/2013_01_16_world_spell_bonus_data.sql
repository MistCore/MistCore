UPDATE spell_bonus_data SET direct_bonus = 1.2 WHERE entry = 686; -- Shadow Bolt
UPDATE spell_bonus_data SET dot_bonus = 0.24 WHERE entry = 30108; -- Unstable Affliction
UPDATE spell_bonus_data SET dot_bonus = 0.375 WHERE entry = 1120; -- Drain Soul
INSERT INTO spell_bonus_data VALUES
(3110, 0.907, -1, -1, -1, 'Imp - Firebolt'),
(3716, 0.3, -1, -1, -1, 'Voidwalker - Torment');