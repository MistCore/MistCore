-- Add Mist of Pandaria new difficulty (see Difficulty.dbc for more informations)

ALTER TABLE creature_template
ADD COLUMN difficulty_entry_4 MEDIUMINT(8) UNSIGNED DEFAULT 0 NOT NULL AFTER difficulty_entry_3,
ADD COLUMN difficulty_entry_5 MEDIUMINT(8) UNSIGNED DEFAULT 0 NOT NULL AFTER difficulty_entry_4,
ADD COLUMN difficulty_entry_6 MEDIUMINT(8) UNSIGNED DEFAULT 0 NOT NULL AFTER difficulty_entry_5,
ADD COLUMN difficulty_entry_7 MEDIUMINT(8) UNSIGNED DEFAULT 0 NOT NULL AFTER difficulty_entry_6,
ADD COLUMN difficulty_entry_8 MEDIUMINT(8) UNSIGNED DEFAULT 0 NOT NULL AFTER difficulty_entry_7,
ADD COLUMN difficulty_entry_9 MEDIUMINT(8) UNSIGNED DEFAULT 0 NOT NULL AFTER difficulty_entry_8,
ADD COLUMN difficulty_entry_10 MEDIUMINT(8) UNSIGNED DEFAULT 0 NOT NULL AFTER difficulty_entry_9;