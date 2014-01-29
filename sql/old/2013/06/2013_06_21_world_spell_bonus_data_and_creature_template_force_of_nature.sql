UPDATE creature_template SET spell1 = 113830 WHERE entry = 54985; -- Taunt for Guardian Treant
UPDATE creature_template SET spell1 = 113801 WHERE entry = 54984; -- Bash for Feral Treant
UPDATE creature_template SET spell1 = 113769, spell2 = 113770 WHERE entry = 1964; -- Wrath and Entangling Roots for Balance Treant
UPDATE creature_template SET spell1 = 113828, spell2 = 0 WHERE entry = 54983; -- Healing Touch for Resto Treant

INSERT INTO spell_bonus_data VALUES
(113769, 0.3, 0, 0, 0, 'Force of Nature - Wrath'),
(113828, 0.323, 0, 0, 0, 'Force of Nature - Healing Touch');