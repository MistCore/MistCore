UPDATE creature_template SET ScriptName = 'npc_guardian_of_ancient_kings' WHERE entry IN (46490, 46499, 46506);
DELETE FROM spell_script_names WHERE spell_id IN (86704, 86698);