ALTER TABLE characters 
ADD COLUMN specialization1 INT(11) NOT NULL AFTER activespec,
ADD COLUMN specialization2 INT(11) NOT NULL AFTER specialization1;