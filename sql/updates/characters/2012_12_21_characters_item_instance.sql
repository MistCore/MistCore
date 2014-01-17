-- Last SQL before the end of everything ! ~21.12.2012
ALTER TABLE item_instance ADD COLUMN reforgeId mediumint(8) AFTER randomPropertyId;
ALTER TABLE item_instance ADD COLUMN transmogrifyId mediumint(8) AFTER reforgeId;
