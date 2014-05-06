-- fix http://wowhead.com/quest=29422
UPDATE creature SET phaseMask=2048 WHERE guid=1340326;
-- Fix error db
INSERT INTO spell_script_names VALUES (19750, 'spell_pal_selfless_healer');
INSERT INTO spell_script_names VALUES (20711, 'spell_pri_spirit_of_redemption');
INSERT INTO spell_script_names VALUES (27827, 'spell_pri_spirit_of_redemption_form');
INSERT INTO spell_script_names VALUES (585, 'spell_pri_train_of_thought');
INSERT INTO spell_script_names VALUES (2060, 'spell_pri_train_of_thought');
INSERT INTO spell_script_names VALUES (8050, 'spell_sha_lava_surge');
INSERT INTO spell_script_names VALUES (54785, 'spell_warl_demonic_leap_jump');
INSERT INTO spell_script_names VALUES (119996, 'spell_monk_transcendence_transfer');
INSERT INTO spell_script_names VALUES (115315, 'spell_monk_black_ox_statue');
