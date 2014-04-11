-- Fix Auctioneer Fitch (ID: 8719) now opens the Auctionsframe correctly

UPDATE creature_template SET gossip_menu_id='0' WHERE entry='8719';

--  Removed the spells Well Fed ( ID: 131828 ) and Prismatic Elixir (134873 ) from spell_group table because they were added in 5.3

DELETE FROM spell_group WHERE spell_id='131828';
DELETE FROM spell_group WHERE spell_id='134873';
