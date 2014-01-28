UPDATE creature_template SET npcflag = 129, ScriptName = 'npc_mount_vendor' WHERE entry = 48510;
DELETE FROM npc_vendor WHERE entry = 48510;
INSERT INTO npc_vendor VALUES 
(48510, 0, 62461, 0, 0, 0, 1),
(48510, 1, 62462, 0, 0, 0, 1);