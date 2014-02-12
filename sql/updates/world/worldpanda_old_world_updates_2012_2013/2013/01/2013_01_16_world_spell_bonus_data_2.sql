INSERT INTO spell_bonus_data VALUES
(7814, 0.907, -1, -1, -1, 'Succubus - Lash of Pain'),
(54049, 0.38, -1, -1, -1, 'Felhunter - Shadow Bite'),
(103103, -1, 0.2, -1, -1, 'Warlock - Malefic Grasp');
UPDATE spell_bonus_data SET dot_bonus = 0.26 WHERE entry = 980; -- Curse of Agony