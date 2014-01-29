UPDATE spell_bonus_data SET direct_bonus = 0.4 WHERE entry = 31707; -- Waterbolt
INSERT INTO spell_bonus_data VALUE (33395, 0.023, 0, 0, 0, 'Mage - Water Elemental Freeze');
UPDATE pet_levelstats SET hp = 1, mana = 1 WHERE creature_entry = 510;