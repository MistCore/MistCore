#50836/NPC - Ik-Ik the Nimble

    UPDATE `creature_template` SET `ScriptName` = 'mob_ik_ik_the_nimble' WHERE `entry` = 50836;
    UPDATE `creature_template` SET
    `mindmg` = 9838,
    `maxdmg` = 14331,
    `attackpower` = ROUND((`mindmg` + `maxdmg`) / 4 * 7),
    `mindmg` = ROUND(`mindmg` - `attackpower` / 7),
    `maxdmg` = ROUND(`maxdmg` - `attackpower` / 7)
    WHERE entry = 50836;
    UPDATE creature SET spawntimesecs = 8940 WHERE id = 50836;