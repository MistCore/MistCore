-- Mutiliplier : 
-- 3.00f pour les elites d'instances (pandarie)
-- 2.00f pour les elites outdoors (pandarie)

-- Outdoors
UPDATE creature_template SET dmg_multiplier = 2 WHERE rank = 1 AND EXP = 4;

-- Generic, Rare Elite : 7.5
UPDATE creature_template SET dmg_multiplier = 7.5 WHERE rank = 2 AND EXP = 4;

-- Instance
UPDATE creature, creature_template SET creature_template.dmg_multiplier = 3 WHERE creature.id = creature_template.entry AND creature_template.exp = 4 AND creature.map != 870 AND rank = 1;


-- Base min-max dmg and attack power (missing range dmg, armor, armor_mod)
-- class_unit 1 (CLASS_UNIT_WARRIOR)
UPDATE `creature_template` SET 
    `mindmg` = 2737, 
    `maxdmg` = 4012, 
    `attackpower` = ROUND((`mindmg` + `maxdmg`) / 4 * 7), 
    `mindmg` = ROUND(`mindmg` - `attackpower` / 7), 
    `maxdmg` = ROUND(`maxdmg` - `attackpower` / 7) 
  WHERE `exp` = 4 AND minlevel = 84 AND unit_class = 1;
  
 UPDATE `creature_template` SET 
    `mindmg` = 5431, 
    `maxdmg` = 6428, 
    `attackpower` = ROUND((`mindmg` + `maxdmg`) / 4 * 7), 
    `mindmg` = ROUND(`mindmg` - `attackpower` / 7), 
    `maxdmg` = ROUND(`maxdmg` - `attackpower` / 7) 
  WHERE `EXP` = 4 AND minlevel = 85  AND unit_class = 1;

UPDATE `creature_template` SET 
    `mindmg` = 6422, 
    `maxdmg` = 7548, 
    `attackpower` = ROUND((`mindmg` + `maxdmg`) / 4 * 7), 
    `mindmg` = ROUND(`mindmg` - `attackpower` / 7), 
    `maxdmg` = ROUND(`maxdmg` - `attackpower` / 7) 
  WHERE `EXP` = 4 AND minlevel = 86 AND unit_class = 1;

UPDATE `creature_template` SET 
    `mindmg` = 6939, 
    `maxdmg` = 9786, 
    `attackpower` = ROUND((`mindmg` + `maxdmg`) / 4 * 7), 
    `mindmg` = ROUND(`mindmg` - `attackpower` / 7), 
    `maxdmg` = ROUND(`maxdmg` - `attackpower` / 7) 
  WHERE `EXP` = 4 AND minlevel = 87 AND unit_class = 1;

UPDATE `creature_template` SET 
    `mindmg` = 7107, 
    `maxdmg` = 10452, 
    `attackpower` = ROUND((`mindmg` + `maxdmg`) / 4 * 7), 
    `mindmg` = ROUND(`mindmg` - `attackpower` / 7), 
    `maxdmg` = ROUND(`maxdmg` - `attackpower` / 7) 
  WHERE `EXP` = 4 AND minlevel = 88 AND unit_class = 1;

UPDATE `creature_template` SET 
    `mindmg` = 8321, 
    `maxdmg` = 12024, 
    `attackpower` = ROUND((`mindmg` + `maxdmg`) / 4 * 7), 
    `mindmg` = ROUND(`mindmg` - `attackpower` / 7), 
    `maxdmg` = ROUND(`maxdmg` - `attackpower` / 7) 
  WHERE `EXP` = 4 AND minlevel = 89 AND unit_class = 1;

UPDATE `creature_template` SET 
    `mindmg` = 9838, 
    `maxdmg` = 14331, 
    `attackpower` = ROUND((`mindmg` + `maxdmg`) / 4 * 7), 
    `mindmg` = ROUND(`mindmg` - `attackpower` / 7), 
    `maxdmg` = ROUND(`maxdmg` - `attackpower` / 7) 
  WHERE `EXP` = 4 AND minlevel = 90 AND unit_class = 1;

 -- Valeur estimé, aucune donnée de référence
UPDATE `creature_template` SET 
    `mindmg` = 11321, 
    `maxdmg` = 16657, 
    `attackpower` = ROUND((`mindmg` + `maxdmg`) / 4 * 7), 
    `mindmg` = ROUND(`mindmg` - `attackpower` / 7), 
    `maxdmg` = ROUND(`maxdmg` - `attackpower` / 7) 
  WHERE `EXP` = 4 AND minlevel = 91 AND unit_class = 1;  
 
 -- Valeur estimé, aucune donnée de référence 
UPDATE `creature_template` SET 
    `mindmg` = 12684, 
    `maxdmg` = 19052, 
    `attackpower` = ROUND((`mindmg` + `maxdmg`) / 4 * 7), 
    `mindmg` = ROUND(`mindmg` - `attackpower` / 7), 
    `maxdmg` = ROUND(`maxdmg` - `attackpower` / 7) 
  WHERE `EXP` = 4 AND minlevel = 92 AND unit_class = 1;  

   -- Valeur estimé, aucune donnée de référence
UPDATE `creature_template` SET 
    `mindmg` = 14026, 
    `maxdmg` = 21467, 
    `attackpower` = ROUND((`mindmg` + `maxdmg`) / 4 * 7), 
    `mindmg` = ROUND(`mindmg` - `attackpower` / 7), 
    `maxdmg` = ROUND(`maxdmg` - `attackpower` / 7) 
  WHERE `EXP` = 4 AND minlevel = 93 AND unit_class = 1;    
  
 -- class_unit 2 (CLASS_UNIT_PALADIN) 
 
 -- Valeur WAR, aucune donnée de référence
 UPDATE `creature_template` SET 
    `mindmg` = 2737, 
    `maxdmg` = 4012, 
    `attackpower` = ROUND((`mindmg` + `maxdmg`) / 4 * 7), 
    `mindmg` = ROUND(`mindmg` - `attackpower` / 7), 
    `maxdmg` = ROUND(`maxdmg` - `attackpower` / 7) 
  WHERE `EXP` = 4 AND minlevel = 84 AND unit_class = 2;
  
  -- Valeur WAR, aucune donnée de référence 
 UPDATE `creature_template` SET 
    `mindmg` = 5431, 
    `maxdmg` = 6428, 
    `attackpower` = ROUND((`mindmg` + `maxdmg`) / 4 * 7), 
    `mindmg` = ROUND(`mindmg` - `attackpower` / 7), 
    `maxdmg` = ROUND(`maxdmg` - `attackpower` / 7) 
  WHERE `EXP` = 4 AND minlevel = 85  AND unit_class = 2;

UPDATE `creature_template` SET 
    `mindmg` = 6384, 
    `maxdmg` = 8409, 
    `attackpower` = ROUND((`mindmg` + `maxdmg`) / 4 * 7), 
    `mindmg` = ROUND(`mindmg` - `attackpower` / 7), 
    `maxdmg` = ROUND(`maxdmg` - `attackpower` / 7) 
  WHERE `EXP` = 4 AND minlevel = 86 AND unit_class = 2;

UPDATE `creature_template` SET 
    `mindmg` = 7326, 
    `maxdmg` = 9786, 
    `attackpower` = ROUND((`mindmg` + `maxdmg`) / 4 * 7), 
    `mindmg` = ROUND(`mindmg` - `attackpower` / 7), 
    `maxdmg` = ROUND(`maxdmg` - `attackpower` / 7) 
  WHERE `EXP` = 4 AND minlevel = 87 AND unit_class = 2;

UPDATE `creature_template` SET 
    `mindmg` = 8922, 
    `maxdmg` = 10164, 
    `attackpower` = ROUND((`mindmg` + `maxdmg`) / 4 * 7), 
    `mindmg` = ROUND(`mindmg` - `attackpower` / 7), 
    `maxdmg` = ROUND(`maxdmg` - `attackpower` / 7) 
  WHERE `EXP` = 4 AND minlevel = 88 AND unit_class = 2;

UPDATE `creature_template` SET 
    `mindmg` = 9352, 
    `maxdmg` = 12526, 
    `attackpower` = ROUND((`mindmg` + `maxdmg`) / 4 * 7), 
    `mindmg` = ROUND(`mindmg` - `attackpower` / 7), 
    `maxdmg` = ROUND(`maxdmg` - `attackpower` / 7) 
  WHERE `EXP` = 4 AND minlevel = 89 AND unit_class = 2;

UPDATE `creature_template` SET 
    `mindmg` = 9840, 
    `maxdmg` = 13534, 
    `attackpower` = ROUND((`mindmg` + `maxdmg`) / 4 * 7), 
    `mindmg` = ROUND(`mindmg` - `attackpower` / 7), 
    `maxdmg` = ROUND(`maxdmg` - `attackpower` / 7) 
  WHERE `EXP` = 4 AND minlevel = 90 AND unit_class = 2;

 -- Valeur estimé, aucune donnée de référence
UPDATE `creature_template` SET 
    `mindmg` = 11321, 
    `maxdmg` = 16657, 
    `attackpower` = ROUND((`mindmg` + `maxdmg`) / 4 * 7), 
    `mindmg` = ROUND(`mindmg` - `attackpower` / 7), 
    `maxdmg` = ROUND(`maxdmg` - `attackpower` / 7) 
  WHERE `EXP` = 4 AND minlevel = 91 AND unit_class = 2;  
 
 -- Valeur estimé, aucune donnée de référence 
UPDATE `creature_template` SET 
    `mindmg` = 12684, 
    `maxdmg` = 19052, 
    `attackpower` = ROUND((`mindmg` + `maxdmg`) / 4 * 7), 
    `mindmg` = ROUND(`mindmg` - `attackpower` / 7), 
    `maxdmg` = ROUND(`maxdmg` - `attackpower` / 7) 
  WHERE `EXP` = 4 AND minlevel = 92 AND unit_class = 2;  

   -- Valeur estimé, aucune donnée de référence
UPDATE `creature_template` SET 
    `mindmg` = 14026, 
    `maxdmg` = 21467, 
    `attackpower` = ROUND((`mindmg` + `maxdmg`) / 4 * 7), 
    `mindmg` = ROUND(`mindmg` - `attackpower` / 7), 
    `maxdmg` = ROUND(`maxdmg` - `attackpower` / 7) 
  WHERE `EXP` = 4 AND minlevel = 93 AND unit_class = 2;   

-- class_unit 4 (CLASS_UNIT_ROGUE)
-- Aucune donnée sur le rogue (classe très peut utiliser sur les PNJ par blizzard), meme valeur que les warriors
UPDATE `creature_template` SET 
    `mindmg` = 2737, 
    `maxdmg` = 4012, 
    `attackpower` = ROUND((`mindmg` + `maxdmg`) / 4 * 7), 
    `mindmg` = ROUND(`mindmg` - `attackpower` / 7), 
    `maxdmg` = ROUND(`maxdmg` - `attackpower` / 7) 
  WHERE `EXP` = 4 AND minlevel = 84 AND unit_class = 4;
  
 UPDATE `creature_template` SET 
    `mindmg` = 5431, 
    `maxdmg` = 6428, 
    `attackpower` = ROUND((`mindmg` + `maxdmg`) / 4 * 7), 
    `mindmg` = ROUND(`mindmg` - `attackpower` / 7), 
    `maxdmg` = ROUND(`maxdmg` - `attackpower` / 7) 
  WHERE `EXP` = 4 AND minlevel = 85  AND unit_class = 4;

UPDATE `creature_template` SET 
    `mindmg` = 6422, 
    `maxdmg` = 7548, 
    `attackpower` = ROUND((`mindmg` + `maxdmg`) / 4 * 7), 
    `mindmg` = ROUND(`mindmg` - `attackpower` / 7), 
    `maxdmg` = ROUND(`maxdmg` - `attackpower` / 7) 
  WHERE `EXP` = 4 AND minlevel = 86 AND unit_class = 4;

UPDATE `creature_template` SET 
    `mindmg` = 6939, 
    `maxdmg` = 9786, 
    `attackpower` = ROUND((`mindmg` + `maxdmg`) / 4 * 7), 
    `mindmg` = ROUND(`mindmg` - `attackpower` / 7), 
    `maxdmg` = ROUND(`maxdmg` - `attackpower` / 7) 
  WHERE `EXP` = 4 AND minlevel = 87 AND unit_class = 4;

UPDATE `creature_template` SET 
    `mindmg` = 7107, 
    `maxdmg` = 10452, 
    `attackpower` = ROUND((`mindmg` + `maxdmg`) / 4 * 7), 
    `mindmg` = ROUND(`mindmg` - `attackpower` / 7), 
    `maxdmg` = ROUND(`maxdmg` - `attackpower` / 7) 
  WHERE `EXP` = 4 AND minlevel = 88 AND unit_class = 4;

UPDATE `creature_template` SET 
    `mindmg` = 8321, 
    `maxdmg` = 12024, 
    `attackpower` = ROUND((`mindmg` + `maxdmg`) / 4 * 7), 
    `mindmg` = ROUND(`mindmg` - `attackpower` / 7), 
    `maxdmg` = ROUND(`maxdmg` - `attackpower` / 7) 
  WHERE `EXP` = 4 AND minlevel = 89 AND unit_class = 4;

UPDATE `creature_template` SET 
    `mindmg` = 9838, 
    `maxdmg` = 14331, 
    `attackpower` = ROUND((`mindmg` + `maxdmg`) / 4 * 7), 
    `mindmg` = ROUND(`mindmg` - `attackpower` / 7), 
    `maxdmg` = ROUND(`maxdmg` - `attackpower` / 7) 
  WHERE `EXP` = 4 AND minlevel = 90 AND unit_class = 4;

 -- Valeur estimé, aucune donnée de référence
UPDATE `creature_template` SET 
    `mindmg` = 11321, 
    `maxdmg` = 16657, 
    `attackpower` = ROUND((`mindmg` + `maxdmg`) / 4 * 7), 
    `mindmg` = ROUND(`mindmg` - `attackpower` / 7), 
    `maxdmg` = ROUND(`maxdmg` - `attackpower` / 7) 
  WHERE `EXP` = 4 AND minlevel = 91 AND unit_class = 4;  
 
 -- Valeur estimé, aucune donnée de référence 
UPDATE `creature_template` SET 
    `mindmg` = 12684, 
    `maxdmg` = 19052, 
    `attackpower` = ROUND((`mindmg` + `maxdmg`) / 4 * 7), 
    `mindmg` = ROUND(`mindmg` - `attackpower` / 7), 
    `maxdmg` = ROUND(`maxdmg` - `attackpower` / 7) 
  WHERE `EXP` = 4 AND minlevel = 92 AND unit_class = 4;  

   -- Valeur estimé, aucune donnée de référence
UPDATE `creature_template` SET 
    `mindmg` = 14026, 
    `maxdmg` = 21467, 
    `attackpower` = ROUND((`mindmg` + `maxdmg`) / 4 * 7), 
    `mindmg` = ROUND(`mindmg` - `attackpower` / 7), 
    `maxdmg` = ROUND(`maxdmg` - `attackpower` / 7) 
  WHERE `EXP` = 4 AND minlevel = 93 AND unit_class = 4;   

-- class_unit 8 (CLASS_UNIT_MAGE)
UPDATE `creature_template` SET 
    `mindmg` = 2737, 
    `maxdmg` = 4012, 
    `attackpower` = ROUND((`mindmg` + `maxdmg`) / 4 * 7), 
    `mindmg` = ROUND(`mindmg` - `attackpower` / 7), 
    `maxdmg` = ROUND(`maxdmg` - `attackpower` / 7) 
  WHERE `EXP` = 4 AND minlevel = 84 AND unit_class = 8;
  
 UPDATE `creature_template` SET 
    `mindmg` = 5364, 
    `maxdmg` = 7903, 
    `attackpower` = ROUND((`mindmg` + `maxdmg`) / 4 * 7), 
    `mindmg` = ROUND(`mindmg` - `attackpower` / 7), 
    `maxdmg` = ROUND(`maxdmg` - `attackpower` / 7) 
  WHERE `EXP` = 4 AND minlevel = 85  AND unit_class = 8;

UPDATE `creature_template` SET 
    `mindmg` = 7275, 
    `maxdmg` = 10317, 
    `attackpower` = ROUND((`mindmg` + `maxdmg`) / 4 * 7), 
    `mindmg` = ROUND(`mindmg` - `attackpower` / 7), 
    `maxdmg` = ROUND(`maxdmg` - `attackpower` / 7) 
  WHERE `EXP` = 4 AND minlevel = 86 AND unit_class = 8;

UPDATE `creature_template` SET 
    `mindmg` = 7421, 
    `maxdmg` = 11084, 
    `attackpower` = ROUND((`mindmg` + `maxdmg`) / 4 * 7), 
    `mindmg` = ROUND(`mindmg` - `attackpower` / 7), 
    `maxdmg` = ROUND(`maxdmg` - `attackpower` / 7) 
  WHERE `EXP` = 4 AND minlevel = 87 AND unit_class = 8;

UPDATE `creature_template` SET 
    `mindmg` = 7785, 
    `maxdmg` = 12463, 
    `attackpower` = ROUND((`mindmg` + `maxdmg`) / 4 * 7), 
    `mindmg` = ROUND(`mindmg` - `attackpower` / 7), 
    `maxdmg` = ROUND(`maxdmg` - `attackpower` / 7) 
  WHERE `EXP` = 4 AND minlevel = 88 AND unit_class = 8;

UPDATE `creature_template` SET 
    `mindmg` = 8348, 
    `maxdmg` = 12822, 
    `attackpower` = ROUND((`mindmg` + `maxdmg`) / 4 * 7), 
    `mindmg` = ROUND(`mindmg` - `attackpower` / 7), 
    `maxdmg` = ROUND(`maxdmg` - `attackpower` / 7) 
  WHERE `EXP` = 4 AND minlevel = 89 AND unit_class = 8;

UPDATE `creature_template` SET 
    `mindmg` = 9271, 
    `maxdmg` = 13126, 
    `attackpower` = ROUND((`mindmg` + `maxdmg`) / 4 * 7), 
    `mindmg` = ROUND(`mindmg` - `attackpower` / 7), 
    `maxdmg` = ROUND(`maxdmg` - `attackpower` / 7) 
  WHERE `EXP` = 4 AND minlevel = 90 AND unit_class = 8;

 -- Valeur estimé, aucune donnée de référence
UPDATE `creature_template` SET 
    `mindmg` = 11321, 
    `maxdmg` = 16657, 
    `attackpower` = ROUND((`mindmg` + `maxdmg`) / 4 * 7), 
    `mindmg` = ROUND(`mindmg` - `attackpower` / 7), 
    `maxdmg` = ROUND(`maxdmg` - `attackpower` / 7) 
  WHERE `EXP` = 4 AND minlevel = 91 AND unit_class = 8;  
 
 -- Valeur estimé, aucune donnée de référence 
UPDATE `creature_template` SET 
    `mindmg` = 12684, 
    `maxdmg` = 19052, 
    `attackpower` = ROUND((`mindmg` + `maxdmg`) / 4 * 7), 
    `mindmg` = ROUND(`mindmg` - `attackpower` / 7), 
    `maxdmg` = ROUND(`maxdmg` - `attackpower` / 7) 
  WHERE `EXP` = 4 AND minlevel = 92 AND unit_class = 8;  

   -- Valeur estimé, aucune donnée de référence
UPDATE `creature_template` SET 
    `mindmg` = 14026, 
    `maxdmg` = 21467, 
    `attackpower` = ROUND((`mindmg` + `maxdmg`) / 4 * 7), 
    `mindmg` = ROUND(`mindmg` - `attackpower` / 7), 
    `maxdmg` = ROUND(`maxdmg` - `attackpower` / 7)
WHERE `EXP` = 4 AND minlevel = 93 AND unit_class = 8;      
  
