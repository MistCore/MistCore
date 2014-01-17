-- spell_proc_event
DELETE FROM spell_proc_event
WHERE entry IN (34914, 46953, 56821, 58357, 58616, 56638, 54925);

-- spell_group
DELETE FROM spell_group WHERE spell_id = 52109;

-- creature_template
UPDATE creature_template SET npcflag = npcflag &~ 16777216
WHERE entry IN (42960, 36283, 46041, 44764, 37807, 47216, 43032, 45197, 41776, 43984, 40719, 41101, 48092, 42958, 44578, 48147, 48266, 41570, 36838, 44157, 63363, 42603, 42801,
45715, 65565, 47112, 42608, 48331, 41747, 47481, 46344, 63282, 48913, 44049, 52585, 42857, 50636, 39443, 47747, 41445, 14864, 41327, 42951, 42949, 51157, 48148, 42644, 42871,
38424, 63787, 57287, 42956, 61808, 57378, 46100, 47058, 54635, 49211, 53088, 48343, 42689, 41460, 47820, 49637, 48341, 47098, 57377, 38377, 61817, 52171, 56097, 42646, 42947,
50635, 57107, 66186, 52887, 50638, 58562, 34778, 34777, 34830, 40190, 40240, 40250, 40340, 40604, 40720, 40723, 40869, 40934, 41097, 41099, 41100, 41103, 41104, 42673, 42954,
41109, 41111, 41174, 41196, 41283, 41620, 41744, 41789, 41848, 41989, 42175, 42548, 42571, 42964, 43003, 43044, 43046, 43048, 43115, 43182, 43334, 43499, 43721, 43996, 44057,
44126, 44269, 44369, 44579, 44580, 44731, 44776, 44836, 44928, 45005, 45191, 45344, 45455, 45651, 45682, 45731, 45732, 45910, 46014, 46042, 46085, 46157, 46165, 46301, 46395,
46411, 46496, 46536, 47066, 47201, 47203, 47207, 47213, 47219, 47241, 47274, 47278, 47316, 47403, 47404, 47422, 47446, 47507, 47538, 47732, 47814, 47821, 47822, 47872, 48006,
48116, 48276, 48283, 48293, 48294, 48295, 48296, 48297, 48298, 48299, 48300, 48301, 48302, 48309, 48324, 48342, 48457, 48649, 48671, 48699, 48803, 48804, 49143, 49194, 49208,
49215, 49216, 49244, 49244, 49340, 49457, 49499, 49550, 49560, 49604, 49680, 50643, 51340, 51551, 52884, 52885, 52886, 52888, 52889, 52890, 53089, 53131, 53275, 53887, 54247,
54367, 55549, 55715, 56129, 56130, 56131, 57288, 57289, 57328, 57379, 57443, 57882, 54993, 55083, 57431, 57626, 57710, 61806, 61810, 63253, 63254, 63255, 63355, 63808, 64710,
66129, 66191, 66197);

-- spell_script_names
DELETE FROM spell_script_names WHERE spell_id IN
(-12162,20911,25899,58630,59046,59450,61756,63944,68574,68572,68184,64899,64985,65074,65195,66244,67224,67176,67177,67178,67222,67223,69050,70336,70823,70824,70825,70826,70834,70835,
67244,67245,67246,67248,67249,67250,67602,67603,67604,67630,67681,67957,67958,67959,68154,68155,68156,68646,68647,68753,68754,68755,69049,70836,70850,71219,71222,71224,71474,71475,
71476,71477,71900,71901,71902,71966,71967,71968,72088,72089,72162,72438,72439,72440,72441,72442,72443,72447,72448,72449,72455,72456,72457,72463,72495,72496,72497,72498,72499,72500,
72508,72509,72510,72511,72512,72513,72527,72528,72529,72530,72551,72552,72553,72671,72672,72782,72783,72784,72832,72833,72836,72837,72838,72868,72869,72875,72876,73022,73023,73031,
73032,73033,73034,73058,73708,73709,73710,73779,73780,73781,73782,73783,73784,73785,73786,73787,73797,73798,73799,73912,73913,73914,74296,74297,74325,74341,74342,74343,77844,77845,
77846);
DELETE FROM spell_script_names WHERE ScriptName IN
('spell_dk_death_coil', 'spell_gen_lifeblood', 'spell_rog_prey_on_the_weak', 'spell_dru_starfall_aoe', 'spell_dk_corpse_explosion',
'spell_dru_primal_tenacity', 'spell_dru_predatory_strikes', 'spell_ex_463', 'spell_ex_5581', 'spell_warr_concussion_blow', 'spell_pal_judgement_of_command',
'spell_gen_default_count_pct_from_max_hp', 'spell_pal_blessing_of_sanctuary', 'spell_mark_of_nature', 'spell_item_ashbringer', 'spell_pal_exorcism_and_holy_wrath_damage',
'spell_warl_demonic_empowerment', 'spell_ex_absorb_aura', 'spell_warl_everlasting_affliction', 'spell_pal_divine_storm_dummy', 'spell_dru_glyph_of_starfire',
'spell_sha_earthen_power', 'spell_gen_ds_flush_knockback', 'spell_xt002_heart_overload_periodic', 'spell_pal_guarded_by_the_light', 'spell_pal_divine_sacrifice',
'spell_mistress_kiss_area', 'spell_gen_50pct_count_pct_from_max_hp', 'spell_mistress_kiss', 'spell_dru_moonkin_form_passive');
UPDATE creature_template SET ScriptName = 'npc_air_force_bots' WHERE entry IN
(2614,2615,21974,21993,21996,21997,21999,22001,22002,22003,22063,22065,22066,22068,22069,22070,22071,22078,22079,22080,22086,22087,22088,22090,22124,22125,22126);
INSERT INTO spell_script_names VALUES
(78838, 'spell_item_enohar_explosive_arrows'),
(120715, 'spell_soul_back'),
(68980, 'spell_the_lich_king_moisson_ame'),
(69845, 'spell_sindragosa_collision_filter'),
(70117, 'spell_sindragosa_collision_filter'),
(70127, 'spell_sindragosa_collision_filter'),
(71412, 'spell_putricide_ooze_summon'),
(71415, 'spell_putricide_ooze_summon'),
(69783, 'spell_rotface_ooze_flood_2'),
(71335, 'spell_poix_ardente'),
(69705, 'spell_gunship_behind_zero'),
(70175, 'spell_gunship_incinerating_blast'),
(69400, 'spell_gunship_canon_blast'),
(68555, 'spell_keg_placed');
UPDATE creature_template SET ScriptName = 'npc_air_force_bots' WHERE entry IN
(2614,2615,21974,21993,21996,21997,21999,22001,22002,22003,22063,22065,22066,22068,22069,22070,22071,22078,22079,22080,22086,22087,22088,22090,22124,22125,22126);
UPDATE creature_template SET ScriptName = 'npc_frost_bomb_sindragosa' WHERE entry IN (37186);
UPDATE creature_template SET ScriptName = 'npc_flood_ooze_trigger' WHERE entry IN (37013);
UPDATE creature_template SET ScriptName = 'npc_saurfang_beasts' WHERE entry IN (38508);
UPDATE creature_template SET ScriptName = 'npc_ice_sphere' WHERE entry IN (36633);
UPDATE creature_template SET ScriptName = 'npc_loklira_crone' WHERE entry IN (29975);
UPDATE creature_template SET ScriptName = 'npc_victorious_challenger' WHERE entry IN (30012);
UPDATE creature_template SET ScriptName = 'npc_thorim' WHERE entry IN (29445);
UPDATE creature_template SET ScriptName = 'npc_hira_snowdawn' WHERE entry IN (31238);
UPDATE creature_template SET ScriptName = 'npc_oculus_drake' WHERE entry IN (27657,27658,27659);
UPDATE creature_template SET ScriptName = 'mob_cursed_mogu_sculture' WHERE entry = 61334;
UPDATE creature_template SET ScriptName = 'mob_whirling_dervish' WHERE entry = 61626;
UPDATE creature_template SET ScriptName = 'boss_kuai_the_brute' WHERE entry = 61442;
UPDATE `creature_template` SET `ScriptName`='npc_defile' WHERE `entry` = 38757;
UPDATE creature_template SET AIName = "", scriptname = "npc_gilnean_crow" WHERE entry = 50260;
UPDATE creature_template SET killcredit1=35582, scriptname="npc_bloodfang_stalker_c1" WHERE entry=35229;
UPDATE creature_template SET AIName = "", scriptname = "npc_commandeered_cannon" WHERE entry = 35914;
UPDATE creature_template SET AIName = "", scriptname = "npc_lord_godfrey_p4_8" WHERE entry = 35906;
UPDATE `creature_template` SET `speed_run`=1.28571426868439, `VehicleId`=463, `minlevel`=4, `maxlevel`=4, `faction_h`=2203, `faction_a`=2203, `Unit_Flags`=8, `Modelid1`=238, `Resistance4`=1, `mechanic_immune_mask`=2147483647, `scriptname`='npc_crowley_horse' WHERE `entry`=35231;
UPDATE `creature_template` SET `speed_run`=1.28571426868439, `npcflag`=0, `VehicleId`=494, `minlevel`=4, `maxlevel`=4, `Faction_A`=2203, `Faction_H`=2203,`Unit_Flags`=8, `Modelid1`=236, `Resistance2`=90, `Resistance4`=1, `unit_class`=2, `scriptname`='npc_greymane_horse', `mechanic_immune_mask`=2147483647 WHERE `entry`=35905;
INSERT INTO spell_script_names VALUES
(78838, 'spell_item_enohar_explosive_arrows'),
(120715, 'spell_soul_back'),
(68980, 'spell_the_lich_king_moisson_ame'),
(69845, 'spell_sindragosa_collision_filter'),
(70117, 'spell_sindragosa_collision_filter'),
(70127, 'spell_sindragosa_collision_filter'),
(71412, 'spell_putricide_ooze_summon'),
(71415, 'spell_putricide_ooze_summon'),
(69783, 'spell_rotface_ooze_flood_2'),
(71335, 'spell_poix_ardente'),
(69705, 'spell_gunship_behind_zero'),
(70175, 'spell_gunship_incinerating_blast'),
(69400, 'spell_gunship_canon_blast'),
(68555, 'spell_keg_placed');

UPDATE creature_template SET ScriptName = 'boss_vordraka' WHERE entry = 56009;
UPDATE `creature_template` SET `ScriptName` = 'mob_enormous_stone_quilen' WHERE entry = 64183;
INSERT INTO spell_script_names VALUE (125092, 'spell_mogu_petrification');
INSERT INTO spell_script_names VALUES (121114, 'spell_resin_weaving');
REPLACE INTO instance_template VALUES (1008, 870, "instance_mogu_shan_vault", 0);
UPDATE `creature_template` SET `ScriptName` = 'npc_sap_puddle' WHERE `entry` IN (61613);
UPDATE creature_template SET ScriptName = 'mob_sikthik_amber_weaver' WHERE entry = 61929;
UPDATE creature_template SET ScriptName = 'mob_sikthik_guardian' WHERE entry = 61928;
UPDATE creature_template SET ScriptName = 'mob_resin_flake' WHERE entry = 61910;
UPDATE `creature_template` SET `ScriptName` = 'npc_barrel' WHERE `entry` IN (56731);
UPDATE creature_template SET ScriptName = 'mob_strife' WHERE entry = 59051;
UPDATE creature_template SET ScriptName = 'mob_peril' WHERE entry = 59726;