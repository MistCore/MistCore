
#include "ScriptMgr.h"
#include "InstanceScript.h"
#include "mechanar.h"

class gatewatcher_gyro_kill : public CreatureScript
{
    public:
        gatewatcher_gyro_kill() : CreatureScript("gatewatcher_gyro_kill") {}

        struct gatewatcher_gyro_killAI : public ScriptedAI
        {
            gatewatcher_gyro_killAI(Creature* creature) : ScriptedAI(creature)
            {
                pInstance = creature->GetInstanceScript();
            }

            InstanceScript* pInstance;

            void Reset()
            {
                if (pInstance)
                {
                    if (GameObject* pGob = pInstance->instance->GetGameObject(pInstance->GetData64(GOB_CACHE_LEGION)))
                        pGob->SetFlag(GAMEOBJECT_FLAGS, GO_FLAG_LOCKED);
                }
            }

            void JustDied(Unit* killer)
            {
                if (pInstance)
                    if (GameObject* pGob = pInstance->instance->GetGameObject(pInstance->GetData64(GOB_CACHE_LEGION)))
                            pGob->RemoveFlag(GAMEOBJECT_FLAGS, GO_FLAG_LOCKED);
            }

            void UpdateAI(const uint32 diff)
            {
            }
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new gatewatcher_gyro_killAI(creature);
        }
};

void AddSC_mechanar()
{
    new gatewatcher_gyro_kill();
}

