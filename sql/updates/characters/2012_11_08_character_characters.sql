ALTER TABLE characters
ADD COLUMN resetspecialization_cost INT(10) NOT NULL DEFAULT 0 AFTER resettalents_time,
ADD COLUMN resetspecialization_time INT(10) NOT NULL DEFAULT 0 AFTER resetspecialization_cost;