ALTER TABLE `gameobject` 
    ADD COLUMN zoneId int(8) unsigned NOT NULL AFTER map,
    ADD COLUMN areaId int(8) unsigned NOT NULL AFTER zoneId;