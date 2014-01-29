#50769/NPC - Zai the Outcast

    UPDATE `creature_template` SET `unit_flags` = 0, `unit_flags2` = 0, `type_flags` = 0, `ScriptName` = 'mob_zai_the_outcast' WHERE `entry` = 50769;
    UPDATE `creature_template` SET
    `mindmg` = 9838,
    `maxdmg` = 14331,
    `attackpower` = ROUND((`mindmg` + `maxdmg`) / 4 * 7),
    `mindmg` = ROUND(`mindmg` - `attackpower` / 7),
    `maxdmg` = ROUND(`maxdmg` - `attackpower` / 7)
    WHERE entry = 50769;
    UPDATE creature SET spawntimesecs = 8940 WHERE id = 50338;