UPDATE spell_script_names SET spell_id = 44457 WHERE spell_id = -44457;
UPDATE spell_bonus_data SET dot_bonus = 0 WHERE entry = 44461; -- Living Bomb (triggered)
UPDATE spell_bonus_data SET dot_bonus = 0.26, comments = 'Mage - Living Bomb' WHERE entry = 44457; -- Living Bomb