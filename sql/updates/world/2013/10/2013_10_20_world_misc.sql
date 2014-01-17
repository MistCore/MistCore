UPDATE `creature_template` SET `difficulty_entry_1`=0, `difficulty_entry_2`=0, `difficulty_entry_3`=0, `exp`=3 WHERE `entry` IN 
(12050,
 13326,
 13331,
 13422,
 13358,
 11949,
 11948,
 12053,
 13328,
 13332,
 13421,
 13359,
 11947,
 11946,
 14763,
 14762,
 14764,
 14765,
 14773,
 14776,
 14772,
 14777,
 10987,
 11600,
 11602,
 11657,
13396,
13080,
13098,
13078,
13397,
13099,
13081,
13079,
 11603,
 11604,
 11605,
 11677,
 10982,
13317,
13096,
13087,
13086,
13316,
13097,
13089,
13088,
14848,
 2225, 
 3343, 
 3625, 
 4255, 
 4257, 
 5134, 
 5135, 
 5139, 
 10364, 
 10367, 
 10981,  
 10986, 
 10990,  
 11675, 
 11678, 
 11839, 
 11947, 
 11948, 
 11949, 
 11997, 
 12051, 
 12096, 
 12097, 
 12127, 
 13176, 
 13179,  
 13216, 
 13218, 
 13236, 
 13257,  
 13284, 
 13438,  
 13442, 
 13443, 
 13447,  
 13577, 
 13617, 
 13797, 
 13798, 
 13816,  
 14185, 
 14186, 
 14187, 
 14188, 
 14282, 
 14283, 
 14284, 
 11946, 
 11948, 
 11947, 
 11949);

DELETE FROM `disables` WHERE `sourceType`=3 AND `entry`=9;

DELETE FROM `gameobject` WHERE `map`=628;

UPDATE `creature_template_addon` SET `emote`=0 WHERE `entry` IN (31681, 29941);
UPDATE `creature_template` SET `modelid2`=0 WHERE `entry`=17591;
UPDATE `creature_template` SET `modelid2`=0 WHERE `entry`=17641;

UPDATE `gameobject_template` SET `flags`=0 WHERE `entry`=191305;
UPDATE `gameobject_template` SET `flags`=0 WHERE `entry`=191306;
UPDATE `gameobject_template` SET `flags`=0 WHERE `entry`=191307;
UPDATE `gameobject_template` SET `flags`=0 WHERE `entry`=191308;
UPDATE `gameobject_template` SET `flags`=0 WHERE `entry`=191309;
UPDATE `gameobject_template` SET `faction`=1801, `flags`=0 WHERE `entry`=191310;
UPDATE `gameobject_template` SET `faction`=1802 WHERE `entry`=191309;
UPDATE `gameobject_template` SET `faction`=1801 WHERE `entry`=191308;
UPDATE `gameobject_template` SET `faction`=1802 WHERE `entry`=191307;
UPDATE `gameobject_template` SET `faction`=1801 WHERE `entry`=191306;
UPDATE `gameobject_template` SET `faction`=1802 WHERE `entry`=191305;
UPDATE `gameobject_template` SET `faction`=0, `flags`=0 WHERE `entry`=192834;
UPDATE `gameobject_template` SET `ScriptName` = 'go_seaforium_charge' WHERE `entry` = 190753;

UPDATE `creature_template` SET `faction_a`=35, `faction_h`=35 WHERE `entry` IN (34924, 34922, 34918, 34919);

UPDATE `creature_template` SET `unit_flags`=`unit_flags`|33554432, `dynamicflags`=8 WHERE `entry` IN (34935, 34929, 35410, 35427);

UPDATE `creature_classlevelstats` SET `basehp1`=`basehp0` WHERE (`level`>=1 AND `level` <=57) and `basehp1`=1;
UPDATE `creature_classlevelstats` SET `basehp2`=`basehp0` WHERE (`level`>=1 AND `level` <=57) AND `basehp2` = 1;
UPDATE `creature_classlevelstats` SET `basehp3`=`basehp0` WHERE (`level`>=1 AND `level` <=57) AND `basehp3` = 1;

UPDATE `creature_classlevelstats` SET `basehp2`=`basehp1` WHERE (`level`>=58 AND `level` <=67) AND `basehp2` = 1;
UPDATE `creature_classlevelstats` SET `basehp3`=`basehp1` WHERE (`level`>=58 AND `level` <=67) AND `basehp3` = 1;

UPDATE `creature_classlevelstats` SET `basehp3`=`basehp2` WHERE (`level`>=68 AND `level` <=79) AND `basehp3` = 1;

UPDATE `creature_template` SET `spell1`=96212 WHERE `entry`=27894;
UPDATE `creature_template` SET `spell1`=96212 WHERE `entry`=32795;

UPDATE `creature_template` SET `spell1`=96212 WHERE `entry`=27894;
UPDATE `creature_template` SET `spell1`=96212 WHERE `entry`=32795;

DELETE FROM `disables` WHERE `sourceType`=0 AND `entry`=86425;
DELETE FROM `conditions` WHERE `SourceEntry`=86425;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES 
(17, 0, 86425, 0, 0, 31, 1, 3, 46393, 0, 0, 0, '', 'Billy Goat Blaster - Billy Goat Blast');

REPLACE INTO `spell_bonus_data` (`entry`, `direct_bonus`, `dot_bonus`, `ap_bonus`, `ap_dot_bonus`, `comments`) VALUES 
(18222, 0, 0, 0, 0, 'Poached Sunscale Salmon - Health Regeneration');

UPDATE `creature_template` SET `mechanic_immune_mask`=344275770 WHERE `entry` IN (28781, 32796);

UPDATE creature_template SET ScriptName='boss_isle_of_conquest' where entry IN (34922, 34924);
UPDATE creature_template SET ScriptName='npc_four_car_garage' where entry IN (34775, 35069, 35273, 34793, 34776, 34802);

DELETE FROM `creature` WHERE `id` IN (23472, 22515) AND `map`=628;
INSERT INTO `creature` (`id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`) VALUES 
(23472, 628, 15, 1, 0, 0, 1143.25, -779.599, 48.629, 1.64061, 120, 0, 0, 0, 0, 0, 0, 0, 0),
(23472, 628, 15, 1, 0, 0, 1236.53, -669.415, 48.2729, 0.104719, 120, 0, 0, 0, 0, 0, 0, 0, 0),
(22515, 628, 15, 1, 0, 0, 1233.27, -844.526, 48.8824, -0.0174525, 120, 0, 0, 0, 0, 0, 0, 0, 0),
(23472, 628, 15, 1, 0, 0, 311.92, -913.972, 48.8159, 3.08918, 120, 0, 0, 0, 0, 0, 0, 0, 0),
(22515, 628, 15, 1, 0, 0, 1235.53, -683.872, 49.304, -3.08918, 120, 0, 0, 0, 0, 0, 0, 0, 0),
(22515, 628, 15, 1, 0, 0, 397.089, -859.382, 48.8993, 1.64061, 120, 0, 0, 0, 0, 0, 0, 0, 0),
(23472, 628, 15, 1, 0, 0, 324.635, -749.128, 49.3602, 0.0174525, 120, 0, 0, 0, 0, 0, 0, 0, 0),
(23472, 628, 15, 1, 0, 0, 425.675, -857.09, 48.5104, -1.6057, 120, 0, 0, 0, 0, 0, 0, 0, 0),
(22515, 628, 15, 1, 0, 0, 323.54, -888.361, 48.9197, 0.0349063, 120, 0, 0, 0, 0, 0, 0, 0, 0),
(22515, 628, 15, 1, 0, 0, 326.285, -777.366, 49.0208, 3.12412, 120, 0, 0, 0, 0, 0, 0, 0, 0),
(23472, 628, 15, 1, 0, 0, 1235.09, -857.898, 48.9163, 3.07177, 120, 0, 0, 0, 0, 0, 0, 0, 0),
(22515, 628, 15, 1, 0, 0, 1158.76, -746.182, 48.6277, -1.51844, 120, 0, 0, 0, 0, 0, 0, 0, 0);

UPDATE `gameobject_template` SET `data16`=1 WHERE `entry`=180418;
DELETE FROM `gameobject` WHERE `id`=180322 AND `map`=30;

UPDATE `gameobject_template` SET `faction`=0 WHERE `entry`=184142;
UPDATE `gameobject_template` SET `flags`=0 WHERE `entry`=184141;

UPDATE `gameobject_template` SET `faction`=0, `flags`=0 WHERE `entry` IN (195235, 195331, 190752);

DELETE FROM `gameobject` WHERE `map` IN (529, 566) AND `id` IN (179871, 179904, 179905);
