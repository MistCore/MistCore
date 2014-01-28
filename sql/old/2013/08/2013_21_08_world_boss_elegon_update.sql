-- Creatures
UPDATE creature_template SET ScriptName = 'boss_elegon' WHERE entry = 60410;
UPDATE creature_template SET ScriptName = 'mob_empyreal_focus' WHERE entry = 60776;
UPDATE creature_template SET ScriptName = 'mob_celestial_protector' WHERE entry = 60793;
UPDATE creature_template SET ScriptName = 'mob_cosmic_spark' WHERE entry = 62618;
UPDATE creature_template SET ScriptName = 'mob_infinite_energy' WHERE entry = 65293;
UPDATE creature SET unit_flags = 0, position_z = 360 WHERE id = 60410;
UPDATE `creature_template` SET `modelid1` = 11686, `type` = 10, `type_flags` = 1024, `flags_extra` = 128 WHERE `entry` = 60960;
UPDATE creature_template SET speed_fly = 0.3, ScriptName = 'mob_energy_charge' WHERE entry = 60913;
UPDATE creature_model_info SET bounding_radius = 6.5, combat_reach = 6.5 WHERE modelid = 41399;
UPDATE creature_template SET minlevel = 90, maxlevel = 90 WHERE entry = 62618;

-- Gameobjects
UPDATE gameobject_template SET ScriptName = 'go_celestial_control_console' WHERE entry = 211650;
DELETE FROM `gameobject` WHERE `id` = 213526;
insert into `gameobject` (`guid`, `id`, `map`, `zoneId`, `areaId`, `spawnMask`, `phaseMask`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `isActive`) values
('527739','213526','1008','6125','6125','8','65535','4023.15','1907.6','360','3.14159','0.000488281','0.00030613','0.292623','0.995623','300','0','1','0');

-- Only summons during fight !
DELETE FROM creature WHERE id IN (60793,60913,62618);

-- Spells
INSERT INTO spell_script_names VALUES
(127785, 'spell_spawn_flash_1_periodic'),
(127783, 'spell_spawn_flash_2_periodic'),
(127781, 'spell_spawn_flash_3_periodic');
INSERT INTO spell_script_names VALUE (117874, 'spell_touch_of_titans');
INSERT INTO spell_script_names VALUES
(118313, 'spell_radiating_energies'),
(122741, 'spell_radiating_energies');
INSERT INTO spell_script_names VALUES
(119360, 'spell_draw_power'),
(124967, 'spell_draw_power');
INSERT INTO spell_script_names VALUE (118024, 'spell_core_checker');
INSERT INTO spell_script_names VALUE (127362, 'spell_grasping_energy_tendrils');
INSERT INTO spell_script_names VALUE (116994, 'spell_unstable_energy');

-- Text
DELETE FROM creature_text WHERE entry = 60410;
INSERT INTO creature_text VALUES
(60410, 0, 0, "Sensors online. All cores operating at peak efficiency.", 14, 0, 100, 0, 0, 28544, 'ELEGON_INTRO_1'),
(60410, 1, 0, "Identification matrix mismatch. Unknown entities detected.", 14, 0, 100, 0, 0, 28545, 'ELEGON_INTRO_2'),
(60410, 2, 0, "Entering defensive mode. Disabling output failsafes.", 14, 0, 100, 0, 0, 28534, 'ELEGON_AGGRO'),
(60410, 3, 0, "Existence ends ... I become nothing ...", 14, 0, 100, 0, 0, 28535, 'ELEGON_DEATH_1'),
(60410, 4, 0, "Conduits offline.", 14, 0, 100, 0, 0, 28536, 'ELEGON_A_TO_B_1'),
(60410, 5, 0, "Approach ! Feel the power of the titans !", 14, 0, 100, 0, 0, 28537, 'ELEGON_A_TO_B_2'),
(60410, 6, 0, "Drawing from reserve power.", 14, 0, 100, 0, 0, 28538, 'ELEGON_B_TO_C_1'),
(60410, 7, 0, "Energy Vortex ramping down.", 14, 0, 100, 0, 0, 28539, 'ELEGON_C_TO_A_1'),
(60410, 8, 0, "Redirecting power.", 14, 0, 100, 0, 0, 28540, 'ELEGON_C_TO_A_2'),
(60410, 9, 0, "Energy Conduits active, draw stable.", 14, 0, 100, 0, 0, 28541, 'ELEGON_C_TO_A_3'),
(60410, 10, 0, "Engaging total destruction sequence. Good bye.", 14, 0, 100, 0, 0, 28542, 'ELEGON_ENRAGE_HARD'),
(60410, 11, 0, "Let the energies consume you !", 14, 0, 100, 0, 0, 28543, 'ELEGON_ENRAGE_SOFT'),
(60410, 12, 0, "The spark of life fades.", 14, 0, 100, 0, 0, 28546, 'ELEGON_SLAY_1'),
(60410, 12, 1, "What was is no longer.", 14, 0, 100, 0, 0, 28547, 'ELEGON_SLAY_2'),
(60410, 12, 2, "Countermeasures successful.", 14, 0, 100, 0, 0, 28548, 'ELEGON_SLAY_3');