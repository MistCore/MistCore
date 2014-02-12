CREATE TABLE `transferts` (
	`id` INT (11),
	`account` INT (11),
	`perso_guid` INT (11),
	`from` INT (11),
	`to` INT (11),
	`revision` BLOB ,
	`dump` BLOB ,
	`last_error` BLOB ,
	`nb_attempt` INT (11)
); 
CREATE TABLE `transferts_logs` (
	`id` INT (11),
	`account` INT (11),
	`perso_guid` INT (11),
	`from` INT (2),
	`to` INT (2),
	`dump` BLOB 
); 