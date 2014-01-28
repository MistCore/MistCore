ALTER TABLE `characters`
  ADD COLUMN `currentpetslot` TINYINT(3) UNSIGNED NULL DEFAULT NULL AFTER `actionBars`,
  ADD COLUMN `petslotused` TINYINT(3) UNSIGNED NULL DEFAULT NULL AFTER `currentpetslot`;
  
ALTER TABLE `characters`
  DROP COLUMN `stable_slots`;