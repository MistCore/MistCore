-- .. / sql / updates / world / 2014_01_25_world_instance_template.sql
-- Fix Dungeons and Raids Entrance (MoP Content) by MENZ411 for Public Jadecore

DELETE FROM `access_requirement` WHERE `mapId`=189;
INSERT INTO `access_requirement` VALUES 
(189, 1, 20, 0, 0, 0, 0, 0, 0, '', 'OLD - Scarlet Monastery (Entrance)');

DELETE FROM `areatrigger_teleport` WHERE `id` IN (614, 612, 610, 45, 608, 606, 604, 602);
INSERT INTO `areatrigger_teleport` VALUES 
(608, 'OLD - Scarlet Monastery - Library (Exit)', 0, 2870.9, -820.164, 160.333, 0.387856),
(606, 'OLD - Scarlet Monastery - Armory (Exit)', 0, 2884.45, -822.01, 160.333, 1.95268),
(604, 'OLD - Scarlet Monastery - Cathedral (Exit)', 0, 2906.14, -813.772, 160.333, 1.95739),
(602, 'OLD - Scarlet Monastery - Graveyard (Exit)', 0, 2913.92, -802.404, 160.333, 3.50405);

DELETE FROM `access_requirement` WHERE `mapId`=289;
INSERT INTO `access_requirement` VALUES 
(289, 1, 45, 0, 0, 0, 0, 0, 0, '', 'OLD - Scholomance (Entrance)');

DELETE FROM `areatrigger_teleport` WHERE `id` IN (2567, 2568);
INSERT INTO `areatrigger_teleport` VALUES 
(2568, 'OLD - Scholomance (Exit)', 0, 1273.91, -2553.09, 91.8393, 3.57792);


DELETE FROM `access_requirement` WHERE `mapId`=961;
INSERT INTO `access_requirement` VALUES 
(961, 1, 85, 0, 0, 0, 0, 0, 0, '', 'Stormstout Brewery (Entrance)'),
(961, 2, 90, 0, 0, 0, 0, 0, 0, '', 'Stormstout Brewery (Entrance) - Heroic');

DELETE FROM `areatrigger_teleport` WHERE `id` IN (7705, 7755);
INSERT INTO `areatrigger_teleport` VALUES 
(7705, 'Stormstout Brewery (Entrance)', 961, -733.359, 1269.48, 116.208, 0.0),
(7755, 'Stormstout Brewery (Exit)', 870, -709.609, 1264.54, 136.124, 0.0);

DELETE FROM `instance_template` WHERE `map`=961;
INSERT INTO `instance_template` VALUES (961, 870, 'instance_stormstout_brewery', 0); -- Stormstout Brewery

DELETE FROM `access_requirement` WHERE `mapId`=960;
INSERT INTO `access_requirement` VALUES 
(960, 1, 85, 0, 0, 0, 0, 0, 0, '', 'Temple of the Jade Serpent (Entrance)'),
(960, 2, 90, 0, 0, 0, 0, 0, 0, '', 'Temple of the Jade Serpent (Entrance) - Heroic');

DELETE FROM `areatrigger_teleport` WHERE `id` IN (7687, 7854);
INSERT INTO `areatrigger_teleport` VALUES 
(7854, 'Temple of the Jade Serpent (Entrance)', 960, 953.369, -2487.49, 180.531, 0.0),
(7687, 'Temple of the Jade Serpent (Exit)', 870, 957.884, -2474.01, 180.605, 0.0);

DELETE FROM `instance_template` WHERE `map`=960;
INSERT INTO `instance_template` VALUES (960, 870, 'instance_temple_of_jade_serpent', 0); -- Temple of the Jade Serpent

DELETE FROM `access_requirement` WHERE `mapId`=994;
INSERT INTO `access_requirement` VALUES 
(994, 1, 87, 0, 0, 0, 0, 0, 0, '', 'Mogu\'shan Palace (Entrance)'),
(994, 2, 90, 0, 0, 0, 0, 0, 0, '', 'Mogu\'shan Palace (Entrance) - Heroic');

DELETE FROM `areatrigger_teleport` WHERE `id` IN (8134, 8135);
INSERT INTO `areatrigger_teleport` VALUES 
(8134, 'Mogu\'shan Palace (Entrance)', 994, -3969.67, -2542.71, 26.8537, 0.0),
(8135, 'Mogu\'shan Palace (Exit)', 870, 1391.83, 437.694, 479.041, 0.0);

DELETE FROM `instance_template` WHERE `map`=994;
INSERT INTO `instance_template` VALUES (994, 870, 'instance_mogu_shan_palace', 0); -- Mogu\'shan Palace

DELETE FROM `access_requirement` WHERE `mapId`=959;
INSERT INTO `access_requirement` VALUES 
(959, 1, 87, 0, 0, 0, 0, 0, 0, '', 'Shado-Pan Monastery (Entrance)'),
(959, 2, 90, 0, 0, 0, 0, 0, 0, '', 'Shado-Pan Monastery (Entrance) - Heroic');

DELETE FROM `areatrigger_teleport` WHERE `id` IN (7694, 7699);
INSERT INTO `areatrigger_teleport` VALUES 
(7694, 'Shado-Pan Monastery (Entrance)', 959, 3657.29, 2551.92, 767.066, 0.0),
(7699, 'Shado-Pan Monastery (Exit)', 870, 3631.29, 2538.41, 770.012, 0.0);

DELETE FROM `instance_template` WHERE `map`=959;
INSERT INTO `instance_template` VALUES (959, 870, 'instance_shadopan_monastery', 0); -- Shado-Pan Monastery

DELETE FROM `access_requirement` WHERE `mapId`=1011;
INSERT INTO `access_requirement` VALUES 
(1011, 1, 90, 0, 0, 0, 0, 0, 0, '', 'Siege of Niuzao Temple (Entrance)'),
(1011, 2, 90, 0, 0, 0, 0, 0, 0, '', 'Siege of Niuzao Temple (Entrance) - Heroic');

DELETE FROM `areatrigger_teleport` WHERE `id` IN (8312, 8315);
INSERT INTO `areatrigger_teleport` VALUES 
(8315, 'Siege of Niuzao Temple (Entrance)', 1011, 1463.89, 5110.86, 156.954, 0.0),
(8312, 'Siege of Niuzao Temple (Exit)', 870, 1433.27, 5085.39, 133.911, 0.0);

DELETE FROM `instance_template` WHERE `map`=1011;
INSERT INTO `instance_template` VALUES (1011, 870, 'instance_siege_of_the_niuzoa_temple', 0); -- Siege of Niuzao Temple

DELETE FROM `access_requirement` WHERE `mapId`=962;
INSERT INTO `access_requirement` VALUES 
(962, 1, 90, 0, 0, 0, 0, 0, 0, '', 'Gate of the Setting Sun (Entrance)'),
(962, 2, 90, 0, 0, 0, 0, 0, 0, '', 'Gate of the Setting Sun (Entrance) - Heroic');

DELETE FROM `areatrigger_teleport` WHERE `id` IN (7725, 7726);
INSERT INTO `areatrigger_teleport` VALUES 
(7726, 'Gate of the Setting Sun (Entrance)', 962, 722.09, 2108.08, 403.07, 0.0),
(7725, 'Gate of the Setting Sun (Exit)', 870, 692.36, 2080.17, 374.79, 0.0);

DELETE FROM `instance_template` WHERE `map`=962;
INSERT INTO `instance_template` VALUES (962, 870, 'instance_gate_setting_sun', 0); -- Gate of the Setting Sun

DELETE FROM `access_requirement` WHERE `mapId`=1001;
INSERT INTO `access_requirement` VALUES 
(1001, 1, 21, 0, 0, 0, 0, 0, 0, '', 'Scarlet Halls (Entrance)'),
(1001, 2, 90, 0, 0, 0, 0, 0, 0, '', 'Scarlet Halls (Entrance) - Heroic');

DELETE FROM `areatrigger_teleport` WHERE `id` IN (614, 7801);
INSERT INTO `areatrigger_teleport` VALUES 
(614, 'Scarlet Halls (Entrance)', 1001, 831.075, 608.399, 12.9123, 0.0),
(7801, 'Scarlet Halls (Exit)', 0, 2870.89, -820.164, 160.433, 0.0);

DELETE FROM `instance_template` WHERE `map`=1001;
INSERT INTO `instance_template` VALUES (1001, 0, '', 0); -- Scarlet Halls

DELETE FROM `access_requirement` WHERE `mapId`=1004;
INSERT INTO `access_requirement` VALUES 
(1004, 1, 23, 0, 0, 0, 0, 0, 0, '', 'Scarlet Monastery (Entrance)'),
(1004, 2, 90, 0, 0, 0, 0, 0, 0, '', 'Scarlet Monastery (Entrance) - Heroic');

DELETE FROM `areatrigger_teleport` WHERE `id` IN (45, 7802);
INSERT INTO `areatrigger_teleport` VALUES 
(45, 'Scarlet Monastery (Entrance)', 1004, 1124.89, 516.455, 1.08925, 0.0),
(7802, 'Scarlet Monastery (Exit)', 0, 2913.92, -802.404, 160.433, 0.0);

DELETE FROM `instance_template` WHERE `map`=1004;
INSERT INTO `instance_template` VALUES (1004, 0, '', 0); -- Scarlet Monastery

DELETE FROM `access_requirement` WHERE `mapId`=1007;
INSERT INTO `access_requirement` VALUES 
(1007, 1, 33, 0, 0, 0, 0, 0, 0, '', 'Scholomance (Entrance)'),
(1007, 2, 90, 0, 0, 0, 0, 0, 0, '', 'Scholomance (Entrance) - Heroic');

DELETE FROM `areatrigger_teleport` WHERE `id` IN (2567, 7539);
INSERT INTO `areatrigger_teleport` VALUES 
(2567, 'Scholomance (Entrance)', 1007, 200.035, 110.249, 133.099, 0.0),
(7539, 'Scholomance (Exit)', 0, 1273.91, -2553.09, 91.9393, 0.0);

DELETE FROM `instance_template` WHERE `map`=1007;
INSERT INTO `instance_template` VALUES (1007, 0, '', 0); -- Scholomance

DELETE FROM `access_requirement` WHERE `mapId`=1008;
INSERT INTO `access_requirement` VALUES 
(1008, 3, 90, 0, 0, 0, 0, 0, 0, '', 'Mogu\'shan Vaults (Entrance) - 10N'),
(1008, 4, 90, 0, 0, 0, 0, 0, 0, '', 'Mogu\'shan Vaults (Entrance) - 25N'),
(1008, 5, 90, 0, 0, 0, 0, 0, 0, '', 'Mogu\'shan Vaults (Entrance) - 10H'),
(1008, 6, 90, 0, 0, 0, 0, 0, 0, '', 'Mogu\'shan Vaults (Entrance) - 25H');

DELETE FROM `areatrigger_teleport` WHERE `id` IN (7838, 7839);
INSERT INTO `areatrigger_teleport` VALUES 
(7838, 'Mogu\'shan Vaults (Entrance)', 1008, 3861.55, 1045.11, 490.17, 0.0),
(7839, 'Mogu\'shan Vaults (Exit)', 870, 3982.09, 1111.19, 497.31, 0.0);

DELETE FROM `instance_template` WHERE `map`=1008;
INSERT INTO `instance_template` VALUES (1008, 870, 'instance_mogu_shan_vault', 0); -- Mogu\'shan Vaults

DELETE FROM `access_requirement` WHERE `mapId`=996;
INSERT INTO `access_requirement` VALUES 
(996, 3, 90, 0, 0, 0, 0, 0, 0, '', 'Terrace of Endless Spring (Entrance) - 10N'),
(996, 4, 90, 0, 0, 0, 0, 0, 0, '', 'Terrace of Endless Spring (Entrance) - 25N'),
(996, 5, 90, 0, 0, 0, 0, 0, 0, '', 'Terrace of Endless Spring (Entrance) - 10H'),
(996, 6, 90, 0, 0, 0, 0, 0, 0, '', 'Terrace of Endless Spring (Entrance) - 25H');

DELETE FROM `areatrigger_teleport` WHERE `id` IN (8027, 8028);
INSERT INTO `areatrigger_teleport` VALUES 
(8027, 'Terrace of Endless Spring (Entrance)', 996, -1020.99, -3145.79, 28.3346, 0.0),
(8028, 'Terrace of Endless Spring (Exit)', 870, 955.523, -55.8068, 512.152, 0.0);

DELETE FROM `instance_template` WHERE `map`=996;
INSERT INTO `instance_template` VALUES (996, 0, '', 0); -- Terrace of Endless Spring

DELETE FROM `access_requirement` WHERE `mapId`=1009;
INSERT INTO `access_requirement` VALUES 
(1009, 3, 90, 0, 0, 0, 0, 0, 0, '', 'Heart of Fear (Entrance) - 10N'),
(1009, 4, 90, 0, 0, 0, 0, 0, 0, '', 'Heart of Fear (Entrance) - 25N'),
(1009, 5, 90, 0, 0, 0, 0, 0, 0, '', 'Heart of Fear (Entrance) - 10H'),
(1009, 6, 90, 0, 0, 0, 0, 0, 0, '', 'Heart of Fear (Entrance) - 25H');

DELETE FROM `areatrigger_teleport` WHERE `id` IN (8313, 8314);
INSERT INTO `areatrigger_teleport` VALUES 
(8314, 'Heart of Fear (Entrance)', 1009, -2378.92, 459.879, 422.441, 0.0),
(8313, 'Heart of Fear (Exit)', 870, 168.066, 4053.84, 256.013, 0.0);

DELETE FROM `instance_template` WHERE `map`=1009;
INSERT INTO `instance_template` VALUES (1009, 0, '', 0); -- Heart of Fear