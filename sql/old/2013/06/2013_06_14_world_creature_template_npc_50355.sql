#50355/NPC - Kah tir

    UPDATE `creature_template` SET `faction_A` = 14, `faction_H` = 14, `type_flags` = 0, `ScriptName` = 'mob_kah_tir' WHERE `entry` = 50355;
    UPDATE `creature_template` SET
    `mindmg` = 9838,
    `maxdmg` = 14331,
    `attackpower` = ROUND((`mindmg` + `maxdmg`) / 4 * 7),
    `mindmg` = ROUND(`mindmg` - `attackpower` / 7),
    `maxdmg` = ROUND(`maxdmg` - `attackpower` / 7)
    WHERE entry = 50355;
    UPDATE creature SET spawntimesecs = 8940 WHERE id = 50338;