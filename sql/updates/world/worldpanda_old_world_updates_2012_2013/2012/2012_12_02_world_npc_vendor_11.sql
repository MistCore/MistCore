UPDATE creature_template SET npcflag = 129, ScriptName = 'npc_mount_vendor' WHERE entry = 4731;
DELETE FROM npc_vendor WHERE entry = 4731;
INSERT INTO npc_vendor VALUES 
(4731, 0, 13331, 0, 0, 0, 1),
(4731, 1, 13333, 0, 0, 0, 1),
(4731, 2, 13332, 0, 0, 0, 1),
(4731, 3, 46308, 0, 0, 0, 1),
(4731, 4, 18791, 0, 0, 0, 1),
(4731, 5, 47101, 0, 0, 0, 1),
(4731, 6, 13334, 0, 0, 0, 1);