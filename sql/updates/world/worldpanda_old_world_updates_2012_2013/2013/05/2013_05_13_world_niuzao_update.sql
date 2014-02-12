UPDATE creature
SET unit_flags = 0
WHERE Id = 61928 OR Id = 61929 OR id = 61910;

INSERT INTO spell_script_names VALUES (121114, 'spell_resin_weaving');

UPDATE creature_template SET ScriptName = 'mob_sikthik_amber_weaver' WHERE entry = 61929;
UPDATE creature_template SET ScriptName = 'mob_sikthik_guardian' WHERE entry = 61928;

UPDATE creature_template SET modelid1 = 38497, modelid2 = 0 WHERE entry = 62208;

