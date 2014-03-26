UPDATE `quest_template` SET `RewardSpell`='0' WHERE `Id`='14078';

UPDATE creature SET phasemask='1' WHERE id='34864';
UPDATE gameobject_template SET ScriptName='go_merchant_square_door' WHERE entry='195327';


UPDATE `creature_template` SET `ScriptName`='npc_gwen_armstead_p2' WHERE `entry`='35840';
UPDATE `quest_template` SET `RewardSpell`='0' WHERE `Id`='14099';

DELETE FROM `creature_equip_template` WHERE `entry`='34864';
INSERT INTO `creature_equip_template` (`entry`,`itemEntry1`,`itemEntry2`,`itemEntry3`) VALUES
(34864,5305,0,0);

DELETE FROM `creature_equip_template` WHERE `entry`='34916';
INSERT INTO `creature_equip_template` (`entry`,`itemEntry1`,`itemEntry2`,`itemEntry3`) VALUES
(34916,5305,0,0);

insert into `creature` (`guid`, `id`, `map`, `zoneId`, `areaId`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`, `isActive`)
 values(NULL,'35840','638','4714','4755','1','4','0','0','-1632.76','1304.06','19.6632','3.25077','300','0','0','84','0','0','0','0','0','0');

UPDATE quest_template SET NextQuestId='0' WHERE Id='14157';

UPDATE quest_template SET Method='0' WHERE Id='14293';

UPDATE creature_template SET ScriptName='npc_lord_darius_crowley' WHERE entry='35552';

UPDATE creature_template SET ScriptName='npc_lord_darius_crowley_c3' WHERE entry='35566';

insert into `creature` (`guid`, `id`, `map`, `zoneId`, `areaId`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`, `isActive`) 
values(NULL,'35566','638','4755','4761','1','2','0','0','-1619.29','1498.77','32.7997','0.829971','300','0','0','6336','0','0','0','0','0','0');

UPDATE creature_template SET ScriptName='npc_king_g_final' WHERE entry='36332';