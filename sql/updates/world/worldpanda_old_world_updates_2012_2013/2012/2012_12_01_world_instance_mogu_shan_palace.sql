INSERT INTO instance_template VALUES (994, 870, "instance_mogu_shan_palace", 0);

DELETE FROM areatrigger_teleport WHERE id IN (8134, 8135);
INSERT INTO areatrigger_teleport VALUES
(8134, "Mogu'shan Palace - Entrance", 994, -3969.67016602,-2542.71191406, 26.7537002563, 0),
(8135, "Mogu'shan Palace - Exi", 870, 1391.83166504, 437.694458008, 478.941467285, 0);

update creature_template set ScriptName = 'mob_xian_the_weaponmaster_trigger' where entry = 61884;
update creature_template set ScriptName = 'boss_ming_the_cunning' where entry = 61444;
update creature_template set ScriptName = 'mob_whirling_dervish' where entry = 61626;
update creature_template set ScriptName = 'boss_kuai_the_brute' where entry = 61442;


update creature_template set ScriptName = 'mob_adepts' where entry = 61447;
update creature_template set ScriptName = 'mob_adepts' where entry = 61449;
update creature_template set ScriptName = 'mob_adepts' where entry = 61450;


update creature_template set ScriptName = 'mob_mu_shiba' where entry = 61453;

update creature_template set ScriptName = 'boss_haiyan_the_unstoppable' where entry = 61445;

#Ming the cunning
INSERT INTO creature_text VALUES ('61444', '0', '0', 'Our clan holds true to the ways set forth by the ancients. We deserve the king\'s favor above all others!', '12', '0', '100', '0', '0', '27950', 'intro1');
INSERT INTO creature_text VALUES ('61444', '1', '0', 'Clan Harthak will show all why they are the truest of Mogu!', '12', '0', '100', '0', '0', '27947', 'aggro');
INSERT INTO creature_text VALUES ('61444', '2', '0', 'Our clan is the true clan! No interloper can change that!', '12', '0', '100', '0', '0', '27948', 'defeated');
INSERT INTO creature_text VALUES ('61444', '3', '0', 'This is the might of Harthak!', '12', '0', '100', '0', '0', '27957', 'killing a player');
INSERT INTO creature_text VALUES ('61444', '4', '0', 'Only the dogs of clan Gurthan would point fingers at others for their own failures! Your clan is the most desperate! It must have been you!', '12', '0', '100', '0', '0', '27955', 'outro');
INSERT INTO creature_text VALUES ('61444', '5', '0', 'Silence, you motherless mu\'shan herders! I\'d blame your clan, but your skulls are too thick to figure out a child\'z puzzle box, let alone how to usurp power.', '12', '0', '100', '0', '0', '27956', 'outro02');

#Haiyan the Unstoppable
INSERT INTO creature_text VALUES ('61445', '0', '0', 'Clan Kargesh will demonstrate why only the strong deserve to stand at our King\'s side!', '12', '0', '100', '0', '0', '28246', 'Aggro');
INSERT INTO creature_text VALUES ('61445', '1', '0', 'Impossible! Our might is the greatest in all the empire!', '12', '0', '100', '0', '0', '28247', 'Defeated');
INSERT INTO creature_text VALUES ('61445', '2', '0', 'For Korgesh!', '12', '0', '100', '0', '0', '28256', 'Killing a player');
INSERT INTO creature_text VALUES ('61445', '3', '0', 'Clan Gurthan is right! Only the honorous Clan Harthak could bring in a lesser race to do their bidding! You must be traitors!', '12', '0', '100', '0', '0', '28254', 'outro');
INSERT INTO creature_text VALUES ('61445', '4', '0', 'Clan Korgesh will not suffer these insults! We will have your heads to offer to the King as proof of our might soon enough!', '12', '0', '100', '0', '0', '28255', 'outro2');

#Kuai the brute
INSERT INTO creature_text VALUES ('61442', '0', '0', 'Clan Gurthan will show our King and the rest of you power-hungry imposters why we are the rightful ones at his side!', '12', '0', '100', '0', '0', '27932', 'aggro');
INSERT INTO creature_text VALUES ('61442', '1', '0', 'We will never surrender our right to rule the destiny of our people!', '12', '0', '100', '0', '0', '27933', 'defeated');
INSERT INTO creature_text VALUES ('61442', '2', '0', 'The glory of Gurthan!', '12', '0', '100', '0', '0', '27942', 'killing a player');
INSERT INTO creature_text VALUES ('61442', '3', '0', 'Who allowed these outsiders in our halls!? Only Clan Harthak or Clan Korgesh would stoop to such treachery!', '12', '0', '100', '0', '0', '27940', 'outro');
INSERT INTO creature_text VALUES ('61442', '4', '0', 'A well-scripted exchange, but we are not fooled! Your clans are clearly in league with one another! For the glory of our King, our empire, we will put you all down!', '12', '0', '100', '0', '0', '27941', 'outro2');


#Xin trigger
INSERT INTO creature_text VALUES ('61884', '0', '0', 'Useless, all of you! Even the guards you give me in tribute can\'t keep these lesser beings from my palace.', '12', '0', '100', '0', '0', '28353', 'TALK02');
INSERT INTO creature_text VALUES ('61884', '1', '0', 'Redeem, nay, PROVE yourselves now. Deal with these intruders. The clan who brings me their heads will have my favor!', '12', '0', '100', '0', '0', '28354', 'TALK02');

#Adepts
INSERT INTO creature_text VALUES ('61447', '0', '0', 'You\'re messing with the wrong Mogu, Human.', '12', '0', '100', '0', '0', '0', 'TALK02');
INSERT INTO creature_text VALUES ('61447', '1', '0', 'The fight is THAT way, Human.', '12', '0', '100', '0', '0', '0', 'TALK02');
INSERT INTO creature_text VALUES ('61447', '2', '0', 'Get back out there and fight!', '12', '0', '100', '0', '0', '0', 'TALK02');
INSERT INTO creature_text VALUES ('61447', '3', '0', 'You\'re supposed to hit the big guy, not me.', '12', '0', '100', '0', '0', '0', 'TALK02');
INSERT INTO creature_text VALUES ('61447', '4', '0', 'You\'re lucky our clan leader is holding me back.', '12', '0', '100', '0', '0', '0', 'TALK02');

INSERT INTO creature_text VALUES ('61449', '0', '0', 'You\'re messing with the wrong Mogu, Human.', '12', '0', '100', '0', '0', '0', 'TALK02');
INSERT INTO creature_text VALUES ('61449', '1', '0', 'The fight is THAT way, Human.', '12', '0', '100', '0', '0', '0', 'TALK02');
INSERT INTO creature_text VALUES ('61449', '2', '0', 'Get back out there and fight!', '12', '0', '100', '0', '0', '0', 'TALK02');
INSERT INTO creature_text VALUES ('61449', '3', '0', 'You\'re supposed to hit the big guy, not me.', '12', '0', '100', '0', '0', '0', 'TALK02');
INSERT INTO creature_text VALUES ('61449', '4', '0', 'You\'re lucky our clan leader is holding me back.', '12', '0', '100', '0', '0', '0', 'TALK02');

INSERT INTO creature_text VALUES ('61450', '0', '0', 'You\'re messing with the wrong Mogu, Human.', '12', '0', '100', '0', '0', '0', 'TALK02');
INSERT INTO creature_text VALUES ('61450', '1', '0', 'The fight is THAT way, Human.', '12', '0', '100', '0', '0', '0', 'TALK02');
INSERT INTO creature_text VALUES ('61450', '2', '0', 'Get back out there and fight!', '12', '0', '100', '0', '0', '0', 'TALK02');
INSERT INTO creature_text VALUES ('61450', '3', '0', 'You\'re supposed to hit the big guy, not me.', '12', '0', '100', '0', '0', '0', 'TALK02');
INSERT INTO creature_text VALUES ('61450', '4', '0', 'You\'re lucky our clan leader is holding me back.', '12', '0', '100', '0', '0', '0', 'TALK02');


#EVENT OF GEKKAN

update creature_template set ScriptName = 'boss_gekkan' where entry = 61243;

update creature_template set ScriptName = 'mob_glintrok_ironhide' where entry = 61337;
update creature_template set ScriptName = 'mob_glintrok_oracle' where entry = 61339;
update creature_template set ScriptName = 'mob_glintrok_skulker' where entry = 61338;
update creature_template set ScriptName = 'mob_glintrok_hexxer' where entry = 61340;


INSERT INTO creature_text VALUES ('61243', '0', '0', 'I hear something...', '14', '0', '100', '0', '0', '32495', 'INTRO');
INSERT INTO creature_text VALUES ('61243', '1', '0', 'Search his corpse!', '14', '0', '100', '0', '0', '32496', 'killing a player');
INSERT INTO creature_text VALUES ('61243', '2', '0', 'Slay them!', '14', '0', '100', '0', '0', '32497', 'SPELL');
INSERT INTO creature_text VALUES ('61243', '3', '0', 'Stop them!', '14', '0', '100', '0', '0', '32488', 'AGGRO');
INSERT INTO creature_text VALUES ('61243', '4', '0', 'Such a waste...', '14', '0', '100', '0', '0', '32494', 'DEATH');


#EVENT XIN THE WEAPONMASTER

update creature_template set ScriptName = 'boss_xin_the_weaponmaster' where entry = 61398;

update creature_template set ScriptName = 'mob_animated_staff' where entry = 61433;
update creature_template set ScriptName = 'mob_ring_of_fire' where entry = 61499;

insert into spell_script_names values ('120142', 'spell_dart');


insert into spell_script_names values ('123127', 'spell_dart');
insert into spell_script_names values ('119311', 'spell_dart');
insert into spell_script_names values ('123128', 'spell_dart');
insert into spell_script_names values ('124321', 'spell_dart');

insert into spell_script_names values ('119314', 'spell_dart');
insert into spell_script_names values ('119337', 'spell_dart');
insert into spell_script_names values ('119338', 'spell_dart');
insert into spell_script_names values ('124320', 'spell_dart');