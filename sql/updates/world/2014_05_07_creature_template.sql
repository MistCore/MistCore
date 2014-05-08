-- http://wowhead.com/quest=29421
UPDATE `creature_template` SET `faction_A`=2357 AND `faction_H`=2357 WHERE `entry`=54856;
-- delete double http://wowhead.com/npc=55020
DELETE FROM `creature` WHERE `guid`=1340023;
