/*
    Dungeon : Stormstout Brewery 85-87
    Instance General Script
*/

#include "ScriptMgr.h"
#include "InstanceScript.h"
#include "stormstout_brewery.h"

class instance_stormstout_brewery : public InstanceMapScript
{
public:
    instance_stormstout_brewery() : InstanceMapScript("instance_stormstout_brewery", 961) { }

    InstanceScript* GetInstanceScript(InstanceMap* map) const
    {
        return new instance_stormstout_brewery_InstanceMapScript(map);
    }

    struct instance_stormstout_brewery_InstanceMapScript : public InstanceScript
    {
        uint64 ookookGuid;
        uint64 hoptallusGuid;
        uint64 yanzhuGuid;

        instance_stormstout_brewery_InstanceMapScript(Map* map) : InstanceScript(map)
        {}

        void Initialize()
        {
            ookookGuid      = 0;
            hoptallusGuid   = 0;
            yanzhuGuid      = 0;
        }

        void OnCreatureCreate(Creature* creature)
        {
            switch (creature->GetEntry())
            {
                case NPC_OOK_OOK:
                    ookookGuid = creature->GetGUID();
                    break;
                case NPC_HOPTALLUS:
                    hoptallusGuid = creature->GetGUID();
                    break;
                case NPC_YAN_ZHU:
                    yanzhuGuid = creature->GetGUID();
                    break;
            }
        }

        void OnGameObjectCreate(GameObject* go)
        {
        }

        void SetData(uint32 type, uint32 data)
        {}

        uint32 GetData(uint32 type)
        {
            return 0;
        }

        uint64 GetData64(uint32 type)
        {
            switch (type)
            {
                case NPC_OOK_OOK:
                    return ookookGuid;
                case NPC_HOPTALLUS:
                    return hoptallusGuid;
                case NPC_YAN_ZHU:
                    return yanzhuGuid;
            }

            return 0;
        }
    };

};

void AddSC_instance_stormstout_brewery()
{
    new instance_stormstout_brewery();
}
