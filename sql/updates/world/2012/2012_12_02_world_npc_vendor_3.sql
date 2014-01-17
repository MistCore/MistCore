UPDATE creature_template SET npcflag = 129 WHERE entry = 7955;
DELETE FROM npc_vendor WHERE entry = 7955;
INSERT INTO npc_vendor VALUES 
(7955, 0, 13322, 0, 0, 0, 1),
(7955, 1, 8563, 0, 0, 0, 1),
(7955, 2, 13321, 0, 0, 0, 1), 
(7955, 3, 8595, 0, 0, 0, 1),
(7955, 4, 18774, 0, 0, 0, 1),
(7955, 5, 18773, 0, 0, 0, 1),
(7955, 6, 18772, 0, 0, 0, 1);