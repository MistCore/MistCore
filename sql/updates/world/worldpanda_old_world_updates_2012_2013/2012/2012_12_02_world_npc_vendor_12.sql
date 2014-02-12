UPDATE creature_template SET npcflag = 129, ScriptName = 'npc_mount_vendor' WHERE entry = 4730;
DELETE FROM npc_vendor WHERE entry = 4730;
INSERT INTO npc_vendor VALUES 
(4730, 0, 8629, 0, 0, 0, 1),
(4730, 1, 8631, 0, 0, 0, 1),
(4730, 2, 47100, 0, 0, 0, 1),
(4730, 3, 8632, 0, 0, 0, 1),
(4730, 4, 18902, 0, 0, 0, 1),
(4730, 5, 18767, 0, 0, 0, 1),
(4730, 6, 18766, 0, 0, 0, 1);