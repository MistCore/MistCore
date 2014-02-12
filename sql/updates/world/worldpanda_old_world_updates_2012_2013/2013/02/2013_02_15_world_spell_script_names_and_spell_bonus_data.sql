UPDATE spell_bonus_data SET ap_dot_bonus = 0.213 WHERE entry = 2818; -- Deadly Poison : DoT
INSERT INTO spell_bonus_data VALUE (113780, 0, 0, 0.109, 0, 'Rogue - Deadly Poison : Instant damage');
INSERT INTO spell_script_names VALUE (2818, 'spell_rog_deadly_poison_instant_damage');