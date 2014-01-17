-- smallint is too small now
ALTER TABLE `wandering_work`.`creature_equip_template` CHANGE `entry` `entry` MEDIUMINT(8) UNSIGNED DEFAULT '0' NOT NULL; 