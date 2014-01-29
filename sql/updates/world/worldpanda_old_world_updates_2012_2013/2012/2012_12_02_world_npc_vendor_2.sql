UPDATE creature_template SET npcflag = 129 WHERE entry = 7952;
DELETE FROM npc_vendor WHERE entry = 7952;
INSERT INTO npc_vendor VALUES 
(7952, 0, 8592, 0, 0, 0, 1),
(7952, 1, 8591, 0, 0, 0, 1),
(7952, 2, 8588, 0, 0, 0, 1), 
(7952, 3, 18790, 0, 0, 0, 1),
(7952, 4, 18789, 0, 0, 0, 1),
(7952, 5, 18788, 0, 0, 0, 1);