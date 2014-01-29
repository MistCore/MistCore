-- Spirit Kings

-- Spells
DELETE FROM spell_script_names WHERE ScriptName = 'spell_crazy_tought';
INSERT INTO spell_script_names VALUE (117833, 'spell_crazy_thought');
INSERT INTO spell_script_names VALUE (117558, 'spell_coalescing_shadow');

-- Stats
UPDATE creature_template SET unit_class = 1, mindmg = 5174, maxdmg = 12574, attackpower = 62114 WHERE entry = 60708; -- Meng
UPDATE creature_template SET minlevel = 92, maxlevel = 92, faction_A = 14, faction_H = 14, speed_walk = 0.8, speed_run = 0.8, speed_fly = 0.8 WHERE entry = 60731; -- Undying Shadows
UPDATE creature_template SET flags_extra = flags_extra | 0x1 WHERE ScriptName = 'boss_spirit_kings';

-- Text
-- Qiang the Merciless
DELETE FROM creature_text WHERE entry = 60709;
INSERT INTO creature_text VALUES
(60709, 0, 0, "I will crush you, in body AND spirit.", 14, 0, 100, 0, 0, 28057, 'QIANG_AGGRO'),
(60709, 1, 0, "I cannot be, defeated.", 14, 0, 100, 0, 0, 28058, 'QIANG_DEFEATED'),
(60709, 2, 0, "My armies are endless, my power, unmatched.", 14, 0, 100, 0, 0, 28059, 'QIANG_INTRO'),
(60709, 3, 0, "My tactics are unbeatable.", 14, 0, 100, 0, 0, 28060, 'QIANG_SLAY_1'),
(60709, 3, 1, "Another victory.", 14, 0, 100, 0, 0, 28061, 'QIANG_SLAY_2'),
(60709, 3, 2, "The emperor reigns more than anything else !", 14, 0, 100, 0, 0, 28062, 'QIANG_SLAY_3'),
(60709, 4, 0, "Soldiers ! Crush their flank !", 14, 0, 100, 0, 0, 28063, 'QIANG_SPELL_1'),
(60709, 4, 1, "Flanking attack ! March into battle !", 14, 0, 100, 0, 0, 28064, 'QIANG_SPELL_2');
-- Subetaï the Swift
DELETE FROM creature_text WHERE entry = 60710;
INSERT INTO creature_text VALUES
(60710, 0, 0, "You'll see your mistake soon enough!", 14, 0, 100, 0, 0, 28109, 'SUBETAI_AGGRO'),
(60710, 1, 0, "I am ... bested.", 14, 0, 100, 0, 0, 28110, 'SUBETAI_DEFEATED'),
(60710, 2, 0, "Bandits and emperors, we both take what we want.", 14, 0, 100, 0, 0, 28111, 'SUBETAI_INTRO'),
(60710, 3, 0, "You were too slow !", 14, 0, 100, 0, 0, 28112, 'SUBETAI_SLAY_1'),
(60710, 3, 1, "I am too quick, too clever.", 14, 0, 100, 0, 0, 28113, 'SUBETAI_SLAY_2'),
(60710, 3, 2, "You stood no chance !", 14, 0, 100, 0, 0, 28114, 'SUBETAI_SLAY_3'),
(60710, 4, 0, "All that is yours ? Mine !", 14, 0, 100, 0, 0, 28115, 'SUBETAI_SPELL_1'),
(60710, 4, 1, "There is nothing I cannot take !", 14, 0, 100, 0, 0, 28116, 'SUBETAI_SPELL_2');
-- Zian of the Endless Shadow
DELETE FROM creature_text WHERE entry = 60701;
INSERT INTO creature_text VALUES
(60701, 0, 0, "Soon you will understand why my subjects fear the shadows !", 14, 0, 100, 0, 0, 27958, 'ZIAN_AGGRO'),
(60701, 1, 0, "The darkness ...surrounds me ...", 14, 0, 100, 0, 0, 27959, 'ZIAN_DEFEATED'),
(60701, 2, 0, "I sense ... courage. Willpower ... light ? That will not do.", 14, 0, 100, 0, 0, 27960, 'ZIAN_INTRO'),
(60701, 3, 0, "Fall into darkness !", 14, 0, 100, 0, 0, 27961, 'ZIAN_SLAY_1'),
(60701, 3, 1, "The shadows will consume you !", 14, 0, 100, 0, 0, 27962, 'ZIAN_SLAY_2'),
(60701, 3, 2, "This is what it means to face an emperor !", 14, 0, 100, 0, 0, 27963, 'ZIAN_SLAY_3'),
(60701, 4, 0, "The darkness comes for you, and with it, death.", 14, 0, 100, 0, 0, 27964, 'ZIAN_SPELL');
-- Meng the Demented
DELETE FROM creature_text WHERE entry = 60708;
INSERT INTO creature_text VALUES
(60708, 0, 0, "You have angered the emperor ! THE SENTENCE IS DEATH !", 14, 0, 100, 0, 0, 28069, 'MENG_AGGRO'),
(60708, 1, 0, "The sentence ... was to be ... yours !", 14, 0, 100, 0, 0, 28070, 'MENG_DEFEATED_CRAZED'),
(60708, 2, 0, "I ... I don't want to die ...", 14, 0, 100, 0, 0, 28071, 'MENG_DEFEATED_COWARDICE'),
(60708, 3, 0, "Who dares summon Emperor Meng, most majestic of mighty monarchs ?", 14, 0, 100, 0, 0, 28072, 'MENG_INTRO'),
(60708, 4, 0, "Like rice stalks before the blade, all fall before me.", 14, 0, 100, 0, 0, 28073, 'MENG_SLAY_1'),
(60708, 4, 1, "None may stand against the Imperial majesty of Meng !", 14, 0, 100, 0, 0, 28074, 'MENG_SLAY_2'),
(60708, 4, 2, "D-d-don't bleed on me ! Filthy, disease !", 14, 0, 100, 0, 0, 28075, 'MENG_SLAY_3'),
(60708, 4, 3, "You ... you made me do it !", 14, 0, 100, 0, 0, 28076, 'MENG_SLAY_4'),
(60708, 5, 0, "Slaughter yourselves for my amusement !", 14, 0, 100, 0, 0, 28077, 'MENG_SPELL_1'),
(60708, 5, 1, "Enemies ... everywhere ! Kill ! Kill them all !", 14, 0, 100, 0, 0, 28078, 'MENG_SPELL_2');