#50338/NPC - Kor-nas Nightsavage

    UPDATE `creature_template` SET `exp` = 4, `faction_A` = 14, `faction_H` = 14, `unit_flags2` = 0, `type_flags` = 0, `ScriptName` = 'mob_kor_nas_nightsavage' WHERE `entry` = 50338;
    UPDATE `creature_template` SET
    `mindmg` = 9838,
    `maxdmg` = 14331,
    `attackpower` = ROUND((`mindmg` + `maxdmg`) / 4 * 7),
    `mindmg` = ROUND(`mindmg` - `attackpower` / 7),
    `maxdmg` = ROUND(`maxdmg` - `attackpower` / 7)
    WHERE entry = 50338;
    UPDATE creature SET spawntimesecs = 8940 WHERE id = 50338;