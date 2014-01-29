UPDATE `creature_template` SET
    `mindmg` = 9838,
    `maxdmg` = 14331,
    `attackpower` = ROUND((`mindmg` + `maxdmg`) / 4 * 7),
    `mindmg` = ROUND(`mindmg` - `attackpower` / 7),
    `maxdmg` = ROUND(`maxdmg` - `attackpower` / 7)
  WHERE entry = 64183;

UPDATE `creature_template` SET `ScriptName` = 'mob_enormous_stone_quilen' WHERE entry = 64183;

INSERT INTO spell_script_names VALUE (125092, 'spell_mogu_petrification');

INSERT INTO spell_script_names VALUE (125096, 'spell_mogu_monstrous_bite');