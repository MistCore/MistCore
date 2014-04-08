-- This Quest Should Not Be Here :D

DELETE FROM creature_involvedrelation WHERE quest='14153';
DELETE FROM creature_questrelation WHERE quest='14153';

-- Missing GO Scripts
UPDATE gameobject_template SET ScriptName='npc_bank_vault' WHERE Entry='195525';
UPDATE gameobject_template SET ScriptName='npc_bank_vault' WHERE Entry='195449';


UPDATE creature_template SET npcflag='16777216' WHERE entry='35486';

INSERT INTO `npc_spellclick_spells`(`npc_entry`,`spell_id`,`cast_flags`,`user_type`) VALUES ( '35486','67526','1','0');
INSERT INTO `npc_spellclick_spells`(`npc_entry`,`spell_id`,`cast_flags`,`user_type`) VALUES ( '35486','67508','1','0');
INSERT INTO `npc_spellclick_spells`(`npc_entry`,`spell_id`,`cast_flags`,`user_type`) VALUES ( '35486','67524','1','0');
INSERT INTO `npc_spellclick_spells`(`npc_entry`,`spell_id`,`cast_flags`,`user_type`) VALUES ( '35486','67525','1','0');
INSERT INTO `npc_spellclick_spells`(`npc_entry`,`spell_id`,`cast_flags`,`user_type`) VALUES ( '35486','67522','1','0');

-- Temporarly Disable this quest while script is being working on

UPDATE quest_template SET method='0',Flags='0' WHERE Id='14122';

-- GasBot Template
replace into `creature_template` (`entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `KillCredit1`, `KillCredit2`, `modelid1`, `modelid2`, `modelid3`, `modelid4`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `exp_unk`, `faction_A`, `faction_H`, `npcflag`, `speed_walk`, `speed_run`, `scale`, `rank`, `mindmg`, `maxdmg`, `dmgschool`, `attackpower`, `dmg_multiplier`, `baseattacktime`, `rangeattacktime`, `unit_class`, `unit_flags`, `unit_flags2`, `dynamicflags`, `family`, `trainer_type`, `trainer_class`, `trainer_race`, `minrangedmg`, `maxrangedmg`, `rangedattackpower`, `type`, `type_flags`, `type_flags2`, `lootid`, `pickpocketloot`, `skinloot`, `resistance1`, `resistance2`, `resistance3`, `resistance4`, `resistance5`, `resistance6`, `spell1`, `spell2`, `spell3`, `spell4`, `spell5`, `spell6`, `spell7`, `spell8`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `InhabitType`, `HoverHeight`, `Health_mod`, `Mana_mod`, `Mana_mod_extra`, `Armor_mod`, `RacialLeader`, `questItem1`, `questItem2`, `questItem3`, `questItem4`, `questItem5`, `questItem6`, `movementId`, `RegenHealth`, `mechanic_immune_mask`, `flags_extra`, `ScriptName`, `WDBVerified`) values('37598','0','0','0','0','0','30702','0','0','0','Gasbot','','','0','1','1','0','0','35','35','3','1','1.14286','1','0','3.8','3.8','0','46','1','0','0','1','0','2048','0','0','0','0','0','1.9','1.9','0','9','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','','0','3','1','1','1','1','1','0','0','0','0','0','0','0','121','1','0','0','','1');

UPDATE creature_template SET ScriptName='npc_gas_bot' WHERE entry='37598';

-- More PhaseMask Fixes

UPDATE creature SET PhaseMask='1' WHERE id='37602';

-- Delete wrong spawn

DELETE FROM creature WHERE id='37680';

-- Corrected 447 fire phase

UPDATE gameobject SET PhaseMask='8' WHERE id='201745';

-- Place a portal in the end as a workaround


insert into `gameobject` (`guid`, `id`, `map`, `zoneId`, `areaId`, `spawnMask`, `phaseMask`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `isActive`) values('527443','183323','648','4737','4737','1','1','-7843.61','1840.39','7.55274','3.1117','0','0','0.999888','0.0149442','300','0','1','0');

