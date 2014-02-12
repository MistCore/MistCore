INSERT INTO spell_script_names VALUE (114164, 'spell_pri_psyfiend_hit_me_driver');
UPDATE creature_template SET ScriptName = 'npc_psyfiend' WHERE entry = 59190;
INSERT INTO spell_proc_event (`entry`, `procFlags`) VALUE (114164, (0x8|0x20|0x80|0x200|0x2000|0x20000|0x80000|0x100000));