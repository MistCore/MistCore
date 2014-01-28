UPDATE creature_template SET npcflag = 129, ScriptName = 'npc_mount_vendor' WHERE entry = 17584;
DELETE FROM npc_vendor WHERE entry = 17584;
INSERT INTO npc_vendor VALUES 
(17584, 0, 29743, 0, 0, 0, 1),
(17584, 1, 29744, 0, 0, 0, 1),
(17584, 2, 28481, 0, 0, 0, 1),
(17584, 3, 29747, 0, 0, 0, 1),
(17584, 4, 29746, 0, 0, 0, 1),
(17584, 5, 29745, 0, 0, 0, 1);