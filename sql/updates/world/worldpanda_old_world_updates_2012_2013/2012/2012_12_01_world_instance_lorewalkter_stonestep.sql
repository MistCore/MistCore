insert into creature_text values ('56843', '0', '0', 'You there! In the rafters! My sacred library has become possessed by the Sha!', '12', '0', '100', '0', '0', '30887', 'Talk of lorewalkter stonestep 0');
insert into creature_text values ('56843', '1', '0', 'See how they pour from every letter of these sacred scrolls... corrupting them! Defiling them!', '12', '0', '100', '0', '0', '30888', 'Talk of lorewalkter stonestep 1');
insert into creature_text values ('56843', '2', '0', 'I beseech you, kind strangers. Cleanse this place of their foul presence! Lay our stories to rest!', '12', '0', '100', '0', '0', '30889', 'Talk of lorewalkter stonestep 2');
insert into creature_text values ('56843', '3', '0', 'You must destroy the source of the corruption! Quickly, before our cherished history is erased forever!', '12', '0', '100', '0', '0', '30890', 'Talk of lorewalkter stonestep 3');
insert into creature_text values ('56843', '4', '0', 'Oh, my. If I am not mistaken, it appears that the tale of Zao Sunseeker has come to life before us.', '12', '0', '100', '0', '0', '30901', 'Zao appears 0');
insert into creature_text values ('56843', '5', '0', 'According to the legend, long ago, there were five suns that burned brightly in the sky. When the winds blew, their intense heat caused great wildfires.', '12', '0', '100', '0', '0', '30902', 'Zao appears 1');
insert into creature_text values ('56843', '6', '0', 'Crops wilted, villages burned, and families wandered endlessly to seek refuge from the flames...', '12', '0', '100', '0', '0', '30903', 'Zao appears 2');
insert into creature_text values ('56843', '7', '0', 'I can allow this no longer!', '12', '0', '100', '0', '0', '27747', 'Zao appears 3');
insert into creature_text values ('56843', '8', '0', 'The fires, they are burning the library! Please, heroes! Purge this evil before the temple crumbles to ash!', '12', '0', '100', '0', '0', '30904', 'Zao appears 4');
insert into creature_text values ('56843', '9', '0', 'Zao has become corrupted too! Please, fight him with dignity...', '12', '0', '100', '0', '0', '30906', 'Zao enters combat 0');
insert into creature_text values ('56843', '10', '0', 'Ah, it is not yet over. From what see, we face the trial of the yaungol. Let me shed some light...', '12', '0', '100', '0', '0', '0', 'trial appears 1');
insert into creature_text values ('56843', '11', '0', 'As the tale goes, the yaungol was traveling across the Kun\'lai plains when suddenly he was ambushed by two strange creatures!', '12', '0', '100', '0', '0', '0', 'trial appears 2');
insert into creature_text values ('56843', '12', '0', 'The yaungol attacked the beasts with great determination and ferocity. Yet, the more he attacked, the more fearsome the beasts grew!', '12', '0', '100', '0', '0', '0', 'trial appears 3');
insert into creature_text values ('56843', '13', '0', 'However, when he let it alone, the beast shrank to near nothingness.', '12', '0', '100', '0', '0', '', 'trial appears 4');
insert into creature_text values ('56843', '14', '0', 'For you see, strife feeds on conflict. when you have peace in your heart, strife will find somewhere else to roam.', '12', '0', '100', '0', '0', '0', 'trial appears 5');

insert into creature_text values ('56872', '0', '0', 'FOR THE ANCIENTS!', '12', '0', '100', '0', '0', '0', 'EnterCombat Osong');

insert into creature_text values ('58826', '0', '0', 'The blistering heat must have dulled my senses... mirages! All of you!', '12', '0', '100', '0', '0', '27748', 'Entering combat of Zao Sunseeker');

update creature_template set ScriptName = 'boss_lorewalker_stonestep' where entry = 56843;
update creature_template set ScriptName = 'mob_sun' where entry = 56915;
update creature_template set ScriptName = 'mob_zao' where entry = 58826;
update creature_template set ScriptName = 'mob_haunting_sha' where entry = 58856;

update creature_template set ScriptName = 'mob_peril' where entry = 59726;
update creature_template set ScriptName = 'mob_strife' where entry = 59051;

update creature_template set ScriptName = 'boss_liu_flameheart' where entry = 56732;
update creature_template set ScriptName = 'boss_yu_lon' where entry = 56762;
update creature_template set ScriptName = 'mob_trigger_liu_flameheart' where entry = 56789;


update gameobject_template set flags=4 where entry = 213548;
update gameobject_template set flags=4 where entry = 213549;
update gameobject_template set flags=4 where entry = 213544;
update gameobject_template set flags=4 where entry = 213550;

insert into creature_text values ('56732', '0', '0', 'The heart of the Great Serpent will not fall into your hands!', '12', '0', '100', '0', '0', '27603', 'LIU FLAME AGRO 01');
insert into creature_text values ('56732', '1', '0', 'The haze has been lifted from my eyes... forgive me for doubting you...', '12', '0', '100', '0', '0', '27604', 'LIU FLAME DEATH 01');
insert into creature_text values ('56732', '2', '0', 'Jade Serpent, grant me strength!', '12', '0', '100', '0', '0', '27605', 'LIU FLAME EVENT 01');
insert into creature_text values ('56732', '3', '0', 'The cycle must continue, the Jade Serpent must be reborn!', '12', '0', '100', '0', '0', '27606', 'LIU FLAME EVENT 02');
insert into creature_text values ('56732', '4', '0', 'Your forces are weak!', '12', '0', '100', '0', '0', '27607', 'LIU FLAME INTRO 01');
insert into creature_text values ('56732', '5', '0', 'The heart is MINE!', '12', '0', '100', '0', '0', '27608', 'LIU FLAME KILL 01');
insert into creature_text values ('56732', '6', '0', 'Leave this place.', '12', '0', '100', '0', '0', '27609', 'LIU FLAME KILL 02');


update creature_template set ScriptName = 'boss_sha_of_doubt' where entry = 56439;
update creature_template set ScriptName = 'mob_figment_of_doubt' where entry = 56792;

update creature_template set ScriptName = 'mob_minion_of_doubt' where entry = 57109;
update creature_template set ScriptName = 'mob_minion_of_doubt' where entry = 65362;

update creature_template set ScriptName = 'mob_lesser_sha' where entry = 59598;
update creature_template set ScriptName = 'mob_lesser_sha' where entry = 58319;


insert into creature_text values ('59546', '0', '0', '\'Tis hard to decipher his true wish...', '12', '0', '100', '0', '0', '0', '');
insert into creature_text values ('59546', '1', '0', 'He often seeks a lordly dish...', '12', '0', '100', '0', '0', '0', '');
insert into creature_text values ('59546', '2', '0', 'To serve upon his table.', '12', '0', '100', '0', '0', '0', '');
insert into creature_text values ('59546', '3', '0', 'When man asks favor of a fish...', '12', '0', '100', '0', '0', '0', '');

insert into creature_text values ('56439', '0', '0', 'Die or surrender. You cannot defeat me.', '12', '0', '100', '0', '0', '29633', 'VO_TJS_DOUBT_AGGRO');
insert into creature_text values ('56439', '1', '0', 'You cannot escape me. I am... in... every... breath...', '12', '0', '100', '0', '0', '29634', 'VO_TJS_DOUBT_DEATH');
insert into creature_text values ('56439', '2', '0', 'See how effortlessly you become unraveled.', '12', '0', '100', '0', '0', '29635', 'VO_TJS_DOUBT_FIGMENT_01');
insert into creature_text values ('56439', '3', '0', 'Succumb to the darkness inside your soul.', '12', '0', '100', '0', '0', '29636', 'VO_TJS_DOUBT_FIGMENT_02');
insert into creature_text values ('56439', '4', '0', 'All is lost.', '12', '0', '100', '0', '0', '29637', 'VO_TJS_DOUBT_RESET');
insert into creature_text values ('56439', '5', '0', 'Abandon all hope.', '12', '0', '100', '0', '0', '29638', 'VO_TJS_DOUBT_SLAY_01');
insert into creature_text values ('56439', '6', '0', 'Embrace your despair.', '12', '0', '100', '0', '0', '29639', 'VO_TJS_DOUBT_SLAY_02');
