UPDATE spell_bonus_data SET direct_bonus = 0.614 WHERE entry = 50464; -- Nourish
UPDATE spell_bonus_data SET direct_bonus = 1.811 WHERE entry = 2912; -- Starfire
UPDATE spell_bonus_data SET dot_bonus = 0.092 WHERE entry = 48438; -- Wild Growth
UPDATE spell_bonus_data SET direct_bonus = 1.504, dot_bonus = 0.057 WHERE entry = 33763; -- Lifebloom
UPDATE spell_bonus_data SET direct_bonus = 0.958, dot_bonus = 0.219 WHERE entry = 8936; -- Regrowth
DELETE FROM spell_bonus_data WHERE entry = 18562;
INSERT INTO spell_bonus_data VALUE
(93402, 0.24, 0.24, -1, -1, 'Druid - Sunfire'),
(78674, 2.197, -1, -1, -1, 'Druid - Starsurge'),
(50286, 0.33, -1, -1, -1, 'Druid - Starfall (triggered)'),
(88751, 0.349, -1, -1, -1, 'Druid - Wild Mushroom : Detonate'),
(106830, -1, -1, 0.239, 0.882, 'Druid - Thrash'),
(18562, 1.29, -1, -1, -1, 'Druid - Swiftmend'),
(81269, 0.155, -1, -1, -1, 'Druid - Swiftmend (triggered)');