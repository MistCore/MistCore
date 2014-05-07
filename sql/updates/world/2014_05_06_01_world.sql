-- fix http://wowhead.com/quest=29422
UPDATE creature SET phaseMask=2048 WHERE guid=1340326;
-- Fix error db
DELETE FROM spell_script_names WHERE spell_id in (19750, 20711, 27827, 585, 2060, 8050, 54785, 119996, 115315);
INSERT INTO spell_script_names VALUES
(19750, 'spell_pal_selfless_healer'),
(20711, 'spell_pri_spirit_of_redemption'),
(27827, 'spell_pri_spirit_of_redemption_form'),
(585, 'spell_pri_train_of_thought'),
(2060, 'spell_pri_train_of_thought'),
(8050, 'spell_sha_lava_surge'),
(54785, 'spell_warl_demonic_leap_jump'),
(119996, 'spell_monk_transcendence_transfer'),
(115315, 'spell_monk_black_ox_statue');
