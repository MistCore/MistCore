CREATE TABLE `lfg_required_ilevel` (
`ID`  int(10) UNSIGNED NOT NULL AUTO_INCREMENT COMMENT 'Dungeon Id' ,
`ItemLevel`  int(10) UNSIGNED NOT NULL DEFAULT 0 COMMENT 'Item level, that is required for dungeon' ,
`Comment` varchar(30),
PRIMARY KEY (`ID`)
)
ENGINE=InnoDB DEFAULT CHARACTER SET=utf8 AUTO_INCREMENT=1 ROW_FORMAT=COMPACT;

INSERT INTO `lfg_required_ilevel`(`ID`, `ItemLevel`, `Comment`)
VALUES
("529","470","The Dread Approach LFR"),
("530","470","Nightmare of Shek'zeer LFR"),
("526","470","Terrace of Endless Spring LFR"),
("527","460","Guardians of Mogu'shan LFR"),
("528","460","The Vault of Mysteries LFR"),
("468","435","Gates of Setting Sun HC"),
("469","435","Mogu'shan Palace HC"),
("470","435","Scarlet Halls HC"),
("471","435","Scarlet Monastery HC"),
("472","435","Scholomance HC"),
("473","435","Shado-Pan Monastery HC"),
("474","435","Siege of Niuzao Temple HC"),
("519","435","Stormstout Brewery HC"),
("554","435","Temple of Jade Serpent HC"),
("466","393","Shado-Pan Monastery NORM"),
("467","393","Mogu'shan Palace NORM"),
("464","358","Temple of Jade Serpent NORM"),
("465","358","Stormstout Brewery NORM");