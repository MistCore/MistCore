UPDATE `creature_template` SET MovementType=1 WHERE entry=60122 OR entry=60225 OR entry=60121 OR entry=60224 OR entry=59158;
UPDATE `creature` SET spawndist=8, unit_flags=0, dynamicflags=0, MovementType=1 WHERE id=60122 OR id=60225 OR id=60121 OR id=60224 OR id=59158;
UPDATE creature_template SET ScriptName="mob_subjuged_serpent" WHERE entry=59158;
