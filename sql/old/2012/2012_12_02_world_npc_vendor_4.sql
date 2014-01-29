UPDATE creature_template SET npcflag = 129 WHERE entry = 1261;
DELETE FROM npc_vendor WHERE entry = 1261;
INSERT INTO npc_vendor VALUES 
(1261, 0, 5873, 0, 0, 0, 1),
(1261, 1, 5864, 0, 0, 0, 1),
(1261, 2, 5872, 0, 0, 0, 1), 
(1261, 3, 18785, 0, 0, 0, 1),
(1261, 4, 18787, 0, 0, 0, 1),
(1261, 5, 18786, 0, 0, 0, 1);