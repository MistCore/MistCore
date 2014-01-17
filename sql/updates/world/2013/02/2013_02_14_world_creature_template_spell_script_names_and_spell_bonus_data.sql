UPDATE creature_template SET mindmg = 4530, maxdmg = 6713, attackpower = 24, ScriptName = 'npc_guardian_of_ancient_kings' WHERE entry = 46506; -- Retribution spec
UPDATE creature_template SET ScriptName = 'npc_guardian_of_ancient_kings' WHERE entry IN (46490, 46499); -- Holy and Protection spec
INSERT INTO spell_script_names VALUE (86698, 'spell_pal_guardian_of_ancient_kings_retribution');
INSERT INTO spell_script_names VALUE (86704, 'spell_pal_ancient_fury');
INSERT INTO spell_bonus_data VALUE (86704, 0.107, 0, 0, 0, 'Paladin - Ancient Fury');