UPDATE creature_template SET npcflag = 129 WHERE entry = 4885;
DELETE FROM npc_vendor WHERE entry = 4885;
INSERT INTO npc_vendor VALUES 
(4885, 0, 2414, 0, 0, 0, 1),
(4885, 1, 5655, 0, 0, 0, 1),
(4885, 2, 5656, 0, 0, 0, 1), 
(4885, 3, 18778, 0, 0, 0, 1),
(4885, 4, 18776, 0, 0, 0, 1),
(4885, 5, 18777, 0, 0, 0, 1);
UPDATE creature_template SET npcflag = 129 WHERE entry = 384;
DELETE FROM npc_vendor WHERE entry = 384;
INSERT INTO npc_vendor VALUES 
(384, 0, 2414, 0, 0, 0, 1),
(384, 1, 5655, 0, 0, 0, 1),
(384, 2, 5656, 0, 0, 0, 1), 
(384, 3, 18778, 0, 0, 0, 1),
(384, 4, 18776, 0, 0, 0, 1),
(384, 5, 18777, 0, 0, 0, 1);
UPDATE creature_template SET npcflag = 129 WHERE entry = 43694;
DELETE FROM npc_vendor WHERE entry = 43694;
INSERT INTO npc_vendor VALUES 
(43694, 0, 2414, 0, 0, 0, 1),
(43694, 1, 5655, 0, 0, 0, 1),
(43694, 2, 5656, 0, 0, 0, 1), 
(43694, 3, 2411, 0, 0, 0, 1),
(43694, 4, 18778, 0, 0, 0, 1),
(43694, 5, 18776, 0, 0, 0, 1),
(43694, 6, 18777, 0, 0, 0, 1);