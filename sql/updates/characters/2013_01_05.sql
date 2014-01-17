ALTER TABLE transferts 
	ADD COLUMN state INT(10) AFTER nb_attempt,
	ADD COLUMN error INT(10) AFTER state;