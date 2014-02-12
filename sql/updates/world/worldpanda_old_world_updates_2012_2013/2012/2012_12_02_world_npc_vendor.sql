UPDATE creature_template SET npcflag = 129 WHERE entry = 3362;
DELETE FROM npc_vendor WHERE entry = 3362;
INSERT INTO npc_vendor VALUES 
(3362, 0, 1132, 0, 0, 0, 1),
(3362, 1, 5665, 0, 0, 0, 1),
(3362, 2, 5668, 0, 0, 0, 1), 
(3362, 3, 46099, 0, 0, 0, 1),
(3362, 4, 18797, 0, 0, 0, 1),
(3362, 5, 18798, 0, 0, 0, 1),
(3362, 6, 18796, 0, 0, 0, 1);