DELETE FROM spell_bonus_data WHERE entry = 114954;
INSERT INTO spell_bonus_data VALUES
(114923, -1, 0.174, 0, 0, 'Mage - Nether Tempest'),
(114954, 0.087, -1, 0, 0, 'Mage - Nether Tempest (direct damage)');
INSERT INTO spell_script_names VALUE (114923, 'spell_mage_nether_tempest');