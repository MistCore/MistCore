DELETE FROM `spell_proc_event` WHERE `entry` IN (86703);
INSERT INTO `spell_proc_event` VALUES (86703, 0x00, 0x00, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000403, 0, 100, 0);

DELETE FROM `spell_proc_event` WHERE `entry` IN (86701);
INSERT INTO `spell_proc_event` VALUES (86701, 0x00, 0x00, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000403, 0, 100, 0);

DELETE FROM `spell_proc_event` WHERE `entry` IN (78202, 78203, 78204);
INSERT INTO `spell_proc_event` (`entry`, `SchoolMask`, `SpellFamilyName`, `SpellFamilyMask0`, `SpellFamilyMask1`, `SpellFamilyMask2`, `procFlags`, `procEx`, `ppmRate`, `CustomChance`, `Cooldown`) VALUES 
(78202, 0, 6, 32768, 0, 0, 0, 1027, 0, 100, 0),
(78203, 0, 6, 32768, 0, 0, 0, 1027, 0, 100, 0),
(78204, 0, 6, 32768, 0, 0, 0, 1027, 0, 100, 0);

REPLACE INTO creature_template
(entry , difficulty_entry_1 , difficulty_entry_2 , difficulty_entry_3 , KillCredit1 , KillCredit2 , modelid1 , modelid2 , modelid3 , modelid4 , name               , subname , IconName , gossip_menu_id , minlevel , maxlevel , exp , exp_unk , faction_A , faction_H , npcflag , speed_walk , speed_run , scale , rank , mindmg , maxdmg , dmgschool , attackpower , dmg_multiplier , baseattacktime , rangeattacktime , unit_class , unit_flags , unit_flags2 , dynamicflags , family , trainer_type , trainer_spell , trainer_class , trainer_race , minrangedmg , maxrangedmg , rangedattackpower , type , type_flags , type_flags2 , lootid , pickpocketloot , skinloot , resistance1 , resistance2 , resistance3 , resistance4 , resistance5 , resistance6 , spell1 , spell2 , spell3 , spell4 , spell5 , spell6 , spell7 , spell8 , PetSpellDataId , VehicleId , mingold , maxgold , AIName , MovementType , InhabitType , HoverHeight , Health_mod , Mana_mod , Mana_mod_extra , Armor_mod , RacialLeader , questItem1 , questItem2 , questItem3 , questItem4 , questItem5 , questItem6 , movementId , RegenHealth , equipment_id , mechanic_immune_mask , flags_extra , ScriptName             , WDBVerified )
VALUES
( 46954 ,                  0 ,                  0 ,                  0 ,           0 ,           0 ,     1126 ,    11686 ,        0 ,        0 , 'Shadowy Apparition' ,     ''    ,  ''        ,              0 ,       85 ,       85 ,   3 ,       0 ,        35 ,        35 ,       0 ,          1 ,       0.5 ,     1 ,    0 ,    550 ,    950 ,         0 ,          36 ,              7 ,           2000 ,            2000 ,          1 ,      32792 ,        2064 ,           12 ,      0 ,            0 ,             0 ,             0 ,            0 ,         400 ,         600 ,               150 ,   10 ,   16778240 ,           0 ,      0 ,              0 ,        0 ,           0 ,           0 ,           0 ,           0 ,           0 ,           0 ,      0 ,      0 ,      0 ,      0 ,      0 ,      0 ,      0 ,      0 ,              0 ,         0 ,       0 ,       0 ,  ''      ,            0 ,           3 ,           1 ,   0.119048 ,        1 ,              1 ,         1 ,            0 ,          0 ,          0 ,          0 ,          0 ,          0 ,          0 ,         78 ,           1 ,            0 ,                    0 ,           0 ,'npc_shadowy_apparition',       15595 );

REPLACE INTO creature_template
(entry , difficulty_entry_1 , difficulty_entry_2 , difficulty_entry_3 , KillCredit1 , KillCredit2 , modelid1 , modelid2 , modelid3 , modelid4 , name               , subname , IconName , gossip_menu_id , minlevel , maxlevel , exp , exp_unk , faction_A , faction_H , npcflag , speed_walk , speed_run , scale , rank , mindmg , maxdmg , dmgschool , attackpower , dmg_multiplier , baseattacktime , rangeattacktime , unit_class , unit_flags , unit_flags2 , dynamicflags , family , trainer_type , trainer_spell , trainer_class , trainer_race , minrangedmg , maxrangedmg , rangedattackpower , type , type_flags , type_flags2 , lootid , pickpocketloot , skinloot , resistance1 , resistance2 , resistance3 , resistance4 , resistance5 , resistance6 , spell1 , spell2 , spell3 , spell4 , spell5 , spell6 , spell7 , spell8 , PetSpellDataId , VehicleId , mingold , maxgold , AIName , MovementType , InhabitType , HoverHeight , Health_mod , Mana_mod , Mana_mod_extra , Armor_mod , RacialLeader , questItem1 , questItem2 , questItem3 , questItem4 , questItem5 , questItem6 , movementId , RegenHealth , equipment_id , mechanic_immune_mask , flags_extra , ScriptName             , WDBVerified )
VALUES
( 61699 ,                  0 ,                  0 ,                  0 ,           0 ,           0 ,     1126 ,    11686 ,        0 ,        0 , 'Shadowy Apparition' ,     ''    ,  ''        ,              0 ,       85 ,       85 ,   3 ,       0 ,        35 ,        35 ,       0 ,          1 ,       0.5 ,     1 ,    0 ,    550 ,    950 ,         0 ,          36 ,              7 ,           2000 ,            2000 ,          1 ,      32792 ,        2064 ,           12 ,      0 ,            0 ,             0 ,             0 ,            0 ,         400 ,         600 ,               150 ,   10 ,   16778240 ,           0 ,      0 ,              0 ,        0 ,           0 ,           0 ,           0 ,           0 ,           0 ,           0 ,      0 ,      0 ,      0 ,      0 ,      0 ,      0 ,      0 ,      0 ,              0 ,         0 ,       0 ,       0 ,  ''      ,            0 ,           3 ,           1 ,   0.119048 ,        1 ,              1 ,         1 ,            0 ,          0 ,          0 ,          0 ,          0 ,          0 ,          0 ,         78 ,           1 ,            0 ,                    0 ,           0 ,'npc_shadowy_apparition',       15595 );

UPDATE `creature_template` SET `ScriptName`='npc_shadowy_apparition' WHERE `entry`=46954;

UPDATE `creature_template` SET `ScriptName`='npc_shadowy_apparition' WHERE `entry`=61699;

UPDATE `creature_template_addon` SET auras=NULL WHERE entry IN (823,951,1642,49874,50039);
UPDATE `creature_template` SET `ScriptName` = '' WHERE `entry` = 49874;

insert ignore into spell_script_names value (87426, 'spell_pri_shadowy_apparition');

REPLACE INTO `spell_proc_event` (`entry`, `procEx`) VALUES ('81333', '1027'), ('81332', '1027'), ('81330', '1027');

DELETE FROM `spell_proc_event` WHERE `entry`=77755;
DELETE FROM `spell_proc_event` WHERE `entry`=77756;
INSERT INTO `spell_proc_event` (`entry`, `SchoolMask`, `SpellFamilyName`, `SpellFamilyMask0`, `SpellFamilyMask1`, `SpellFamilyMask2`, `procFlags`, `procEx`, `ppmRate`, `CustomChance`, `Cooldown`) VALUES (77755, 0, 11, 268435456, 0, 0, 262144, 1027, 0, 10, 0);
INSERT INTO `spell_proc_event` (`entry`, `SchoolMask`, `SpellFamilyName`, `SpellFamilyMask0`, `SpellFamilyMask1`, `SpellFamilyMask2`, `procFlags`, `procEx`, `ppmRate`, `CustomChance`, `Cooldown`) VALUES (77756, 0, 11, 268435456, 0, 0, 262144, 1027, 0, 20, 0);

update battleground_template set Weight=4 where id in (1, 30);
update battleground_template set MinPlayersPerTeam=10 where id in (1, 30);
update battleground_template set MinPlayersPerTeam=5, MaxPlayersPerTeam=40 where id=32;
update battleground_template set MinLvl=71, MaxLvl=90 where id in (30, 108);
