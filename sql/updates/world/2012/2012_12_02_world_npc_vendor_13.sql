UPDATE creature_template SET npcflag = 129, ScriptName = 'npc_mount_vendor' WHERE entry = 16264;
DELETE FROM npc_vendor WHERE entry = 16264;
INSERT INTO npc_vendor VALUES 
(16264, 0, 28927, 0, 0, 0, 1),
(16264, 1, 29222, 0, 0, 0, 1),
(16264, 2, 29220, 0, 0, 0, 1),
(16264, 3, 29221, 0, 0, 0, 1),
(16264, 4, 29224, 0, 0, 0, 1),
(16264, 5, 28936, 0, 0, 0, 1),
(16264, 6, 29223, 0, 0, 0, 1);