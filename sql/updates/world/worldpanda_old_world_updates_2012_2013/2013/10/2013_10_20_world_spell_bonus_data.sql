-- Wild Mushroom : Bloom, fix coefficient (for us it is 20,1% idk why. Must be 62,1% of SPD, at the moment on official server it is 124,2% of SPD but it was increased to x2 in 5.3.0 patch, so 124,2/2=62,1%.)
UPDATE spell_bonus_data SET direct_bonus='0,621' WHERE entry=102792; 

-- Druid Starsurge, for patch 5.0.5 it is 213,3% of SPD.
UPDATE spell_bonus_data SET direct_bonus='2,133' WHERE entry=78674;