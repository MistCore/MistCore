ALTER TABLE `characters`
  ADD COLUMN `stable_slots` TINYINT(3) UNSIGNED NULL DEFAULT NULL AFTER `extra_flags`;