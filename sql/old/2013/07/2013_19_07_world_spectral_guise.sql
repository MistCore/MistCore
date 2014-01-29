UPDATE creature_template SET ScriptName = 'npc_spectral_guise', flags_extra = 0, type_flags = 0, modelid1 = 11686, modelid2 = 0 WHERE entry = 59607;
INSERT INTO spell_script_names VALUE (119030, 'spell_pri_spectral_guise_charges');
INSERT INTO spell_proc_event (`entry`, `procFlags`) VALUE (119030, (0x8|0x20|0x80|0x200|0x2000|0x20000|0x80000|0x100000));