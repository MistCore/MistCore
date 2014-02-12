ALTER TABLE `battleground_template` ADD COLUMN `holiday` INT(3) DEFAULT '0' NOT NULL AFTER `Weight`; 

REPLACE INTO battleground_template VALUES
(108, 8, 15, 91, 91, 1726, 0, 1727, 0, 0, 0, 436, '', 'Twin Peaks'),
(120, 8, 15, 91, 91, 1798, 0, 1799, 0, 0, 0, 435, '', 'Battle for Gilneas'),
(708, 8, 15, 91, 91, 4062, 0, 4061, 0, 0, 0, 488, '', 'SilverShard Mines');

UPDATE battleground_template SET holiday = 283 WHERE id = 1;
UPDATE battleground_template SET holiday = 284 WHERE id = 2;
UPDATE battleground_template SET holiday = 285 WHERE id = 3;
UPDATE battleground_template SET holiday = 353 WHERE id = 7;
UPDATE battleground_template SET holiday = 400 WHERE id = 9;
UPDATE battleground_template SET holiday = 420 WHERE id = 30;
UPDATE battleground_template SET holiday = 489 WHERE id = 699;
UPDATE battleground_template SET holiday = 488 WHERE id = 708;
UPDATE battleground_template SET holiday = 436 WHERE id = 108;
UPDATE battleground_template SET holiday = 435 WHERE id = 120;
