UPDATE creature_template SET npcflag = 129, ScriptName = 'npc_mount_vendor' WHERE entry = 3685;
DELETE FROM npc_vendor WHERE entry = 3685;
INSERT INTO npc_vendor VALUES 
(3685, 0, 46100, 0, 0, 0, 1),
(3685, 1, 15277, 0, 0, 0, 1),
(3685, 2, 15290, 0, 0, 0, 1),
(3685, 3, 18793, 0, 0, 0, 1),
(3685, 4, 18795, 0, 0, 0, 1),
(3685, 5, 18794, 0, 0, 0, 1);