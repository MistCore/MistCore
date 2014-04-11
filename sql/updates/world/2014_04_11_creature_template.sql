-- Mogushan Vault @ The Spirit Kings Fight
UPDATE creature_template SET ScriptName='boss_spirit_kings_controler' WHERE entry ='60984';
UPDATE creature_template SET ScriptName='' WHERE entry='60847';
UPDATE creature SET id='60984' WHERE id='60847';

-- Fix quest http://mop.wowhead.com/quest=31473
UPDATE creature_template SET questitem1='87208', questitem2='87209' WHERE entry='60051' OR entry='60009' OR entry='60143' OR entry='60701' OR entry='60410';