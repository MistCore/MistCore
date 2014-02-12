/*
	Dragons of Nightmare are removed on Cataclysm
	Ysondre: Quest giver on Cataclysm wowhead.com/npc=39407
	Other are dead
*/

UPDATE `creature_template` SET `ScriptName`='' WHERE `entry`='14887';
UPDATE `creature_template` SET `ScriptName`='' WHERE `entry`='14890';
UPDATE `creature_template` SET `ScriptName`='' WHERE `entry`='14889';
UPDATE `creature_template` SET `ScriptName`='' WHERE `entry`='14888';
UPDATE `creature_template` SET `ScriptName`='' WHERE `entry`='15224';


DELETE FROM creature WHERE id IN
(14887,  14890, 14889, 14888);

DELETE FROM `spell_script_names` WHERE `spell_id`='24778';