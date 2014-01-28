DELETE FROM spell_target_position WHERE id IN (130702, 132627, 130696, 132621); -- Alliance / Horde
INSERT INTO spell_target_position VALUES
(130702, 870, -289.437866, -1681.793091, 53.107918, 6.241153), -- Portal
(132627, 870, -289.437866, -1681.793091, 53.107918, 6.241153), -- Teleport
(130696, 870, 3030.504150, -547.760681, 248.230789, 1.495704), -- Portal
(132621, 870, 3030.504150, -547.760681, 248.230789, 1.495704); -- Teleport

DELETE FROM gameobject_template WHERE entry IN (216057, 216058); -- Horde / Alliance
INSERT INTO gameobject_template VALUES
(216057, 22, 12658, 'Portal to Vale of Eternal Blossoms', '', '', '', 1735, 0, 1, 0, 0, 0, 0, 0, 0, 130698, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', '', 15595),
(216058, 22, 12658, 'Portal to Vale of Eternal Blossoms', '', '', '', 1735, 0, 1, 0, 0, 0, 0, 0, 0, 130703, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', '', 15595);