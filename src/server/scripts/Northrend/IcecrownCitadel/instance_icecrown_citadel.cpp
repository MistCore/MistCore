/*
 * Copyright (C) 2008-2011 TrinityCore <http://www.trinitycore.org/>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "ObjectMgr.h"
#include "ScriptMgr.h"
#include "InstanceScript.h"
#include "ScriptedCreature.h"
#include "Map.h"
#include "PoolMgr.h"
#include "icecrown_citadel.h"
#include "Transport.h"
#include "MapManager.h"
#include "Vehicle.h"

enum EventIds
{
    EVENT_QUAKE                     = 23437,
    EVENT_SECOND_REMORSELESS_WINTER = 23507,
    EVENT_TELEPORT_TO_FROSMOURNE    = 23617,
};

enum TimedEvents
{
    EVENT_UPDATE_EXECUTION_TIME = 1,
    EVENT_QUAKE_SHATTER         = 2,
    EVENT_REBUILD_PLATFORM      = 3,
};

DoorData const doorData[] =
{
    {GO_LORD_MARROWGAR_S_ENTRANCE,           DATA_LORD_MARROWGAR,        DOOR_TYPE_ROOM,       BOUNDARY_N   },
    {GO_ICEWALL,                             DATA_LORD_MARROWGAR,        DOOR_TYPE_PASSAGE,    BOUNDARY_NONE},
    {GO_DOODAD_ICECROWN_ICEWALL02,           DATA_LORD_MARROWGAR,        DOOR_TYPE_PASSAGE,    BOUNDARY_NONE},
    {GO_ORATORY_OF_THE_DAMNED_ENTRANCE,      DATA_LADY_DEATHWHISPER,     DOOR_TYPE_ROOM,       BOUNDARY_N   },
    {GO_SAURFANG_S_DOOR,                     DATA_DEATHBRINGER_SAURFANG, DOOR_TYPE_PASSAGE,    BOUNDARY_NONE},
    {GO_ORANGE_PLAGUE_MONSTER_ENTRANCE,      DATA_FESTERGUT,             DOOR_TYPE_ROOM,       BOUNDARY_E   },
    {GO_GREEN_PLAGUE_MONSTER_ENTRANCE,       DATA_ROTFACE,               DOOR_TYPE_ROOM,       BOUNDARY_E   },
    {GO_SCIENTIST_ENTRANCE,                  DATA_PROFESSOR_PUTRICIDE,   DOOR_TYPE_ROOM,       BOUNDARY_E   },
    {GO_CRIMSON_HALL_DOOR,                   DATA_BLOOD_PRINCE_COUNCIL,  DOOR_TYPE_ROOM,       BOUNDARY_S   },
    {GO_BLOOD_ELF_COUNCIL_DOOR,              DATA_BLOOD_PRINCE_COUNCIL,  DOOR_TYPE_PASSAGE,    BOUNDARY_W   },
    {GO_BLOOD_ELF_COUNCIL_DOOR_RIGHT,        DATA_BLOOD_PRINCE_COUNCIL,  DOOR_TYPE_PASSAGE,    BOUNDARY_E   },
    {GO_DOODAD_ICECROWN_BLOODPRINCE_DOOR_01, DATA_BLOOD_QUEEN_LANA_THEL, DOOR_TYPE_ROOM,       BOUNDARY_S   },
    {GO_DOODAD_ICECROWN_GRATE_01,            DATA_BLOOD_QUEEN_LANA_THEL, DOOR_TYPE_PASSAGE,    BOUNDARY_NONE},
    {GO_GREEN_DRAGON_BOSS_ENTRANCE,          DATA_SISTER_SVALNA,         DOOR_TYPE_PASSAGE,    BOUNDARY_S   },
    {GO_GREEN_DRAGON_BOSS_ENTRANCE,          DATA_VALITHRIA_DREAMWALKER, DOOR_TYPE_ROOM,       BOUNDARY_N   },
    {GO_GREEN_DRAGON_BOSS_EXIT,              DATA_VALITHRIA_DREAMWALKER, DOOR_TYPE_PASSAGE,    BOUNDARY_S   },
    {GO_DOODAD_ICECROWN_ROOSTPORTCULLIS_01,  DATA_VALITHRIA_DREAMWALKER, DOOR_TYPE_SPAWN_HOLE, BOUNDARY_N   },
    {GO_DOODAD_ICECROWN_ROOSTPORTCULLIS_02,  DATA_VALITHRIA_DREAMWALKER, DOOR_TYPE_SPAWN_HOLE, BOUNDARY_S   },
    {GO_DOODAD_ICECROWN_ROOSTPORTCULLIS_03,  DATA_VALITHRIA_DREAMWALKER, DOOR_TYPE_SPAWN_HOLE, BOUNDARY_N   },
    {GO_DOODAD_ICECROWN_ROOSTPORTCULLIS_04,  DATA_VALITHRIA_DREAMWALKER, DOOR_TYPE_SPAWN_HOLE, BOUNDARY_S   },
    {GO_SINDRAGOSA_ENTRANCE_DOOR,            DATA_SINDRAGOSA,            DOOR_TYPE_ROOM,       BOUNDARY_S   },
    {GO_SINDRAGOSA_SHORTCUT_ENTRANCE_DOOR,   DATA_SINDRAGOSA,            DOOR_TYPE_PASSAGE,    BOUNDARY_E   },
    {GO_SINDRAGOSA_SHORTCUT_EXIT_DOOR,       DATA_SINDRAGOSA,            DOOR_TYPE_PASSAGE,    BOUNDARY_NONE},
    {GO_ICE_WALL,                            DATA_SINDRAGOSA,            DOOR_TYPE_ROOM,       BOUNDARY_SE  },
    {GO_ICE_WALL,                            DATA_SINDRAGOSA,            DOOR_TYPE_ROOM,       BOUNDARY_SW  },
    {0,                                      0,                          DOOR_TYPE_ROOM,       BOUNDARY_NONE},// END
};

// this doesnt have to only store questgivers, also can be used for related quest spawns
struct WeeklyQuest
{
    uint32 creatureEntry;
    uint32 questId[2];  // 10 and 25 man versions
}

WeeklyQuestData[WeeklyNPCs] =
{
    {NPC_INFILTRATOR_MINCHAR,         {QUEST_DEPROGRAMMING_10,                 QUEST_DEPROGRAMMING_25                }}, // Deprogramming
    {NPC_KOR_KRON_LIEUTENANT,         {QUEST_SECURING_THE_RAMPARTS_10,         QUEST_SECURING_THE_RAMPARTS_25        }}, // Securing the Ramparts
    {NPC_ALCHEMIST_ADRIANNA,          {QUEST_RESIDUE_RENDEZVOUS_10,            QUEST_RESIDUE_RENDEZVOUS_25           }}, // Residue Rendezvous
    {NPC_ALRIN_THE_AGILE,             {QUEST_BLOOD_QUICKENING_10,              QUEST_BLOOD_QUICKENING_25             }}, // Blood Quickening
    {NPC_INFILTRATOR_MINCHAR_BQ,      {QUEST_BLOOD_QUICKENING_10,              QUEST_BLOOD_QUICKENING_25             }}, // Blood Quickening
    {NPC_MINCHAR_BEAM_STALKER,        {QUEST_BLOOD_QUICKENING_10,              QUEST_BLOOD_QUICKENING_25             }}, // Blood Quickening
    {NPC_VALITHRIA_DREAMWALKER_QUEST, {QUEST_RESPITE_FOR_A_TORNMENTED_SOUL_10, QUEST_RESPITE_FOR_A_TORNMENTED_SOUL_25}}, // Respite for a Tormented Soul
};

class instance_icecrown_citadel : public InstanceMapScript
{
    public:
        instance_icecrown_citadel() : InstanceMapScript(ICCScriptName, 631) { }


        struct instance_icecrown_citadel_InstanceMapScript : public InstanceScript
        {
            instance_icecrown_citadel_InstanceMapScript(InstanceMap* map) : InstanceScript(map)
            {
                SetBossNumber(EncounterCount);
                LoadDoorData(doorData);
                TeamInInstance = 0;
                HeroicAttempts = 50;
                LordMarrowgarGUID = 0;
                LadyDeathwisperElevatorGUID = 0;

                FriendGunshipGUID = 0;
                EnnemyGunshipGUID = 0;
                FriendGunshipNPCGUID = 0;
                EnnemyGunshipNPCGUID = 0;
                GunshipcommanderGUID = 0;
                GunshipennemycommanderGUID = 0;
                memset(GunshipCanons, 0, 4 * sizeof(uint64));
                memset(GunshipArtilleurs, 0, 4 * sizeof(uint64));
                memset(GunshipTireurs, 0, 8 * sizeof(uint64));
                memset(GunshipMages, 0, 2 * sizeof(uint64));

                GunshipRespawnMap.clear();

                GunshipIntroBool = false;
                GunshipInCombatBool = false;
                GunshipExtroBool = false;
                GunshipResetBool = false;
                GunshipFirstIceMageBool = true;
                GunshipCheckTimer = 1000;
                GunshipFirstIceMageTimer = 40000;
                GunshipIntroPhase = 1;
                GunshipIntroTimer = 100;
                GunshipExtroPhase = 1;
                GunshipExtroTimer = 100;
                GunshipAliveMagesNumber = 0;
                GunshipPortalTimer = 100;
                GunshipPortalPhase = 1;

                GunshipSpawnPortailTimer = 30000;
                GunshipIsPortalSpawned = false;

                PortalGUID = 0;
                GunshipArmory_A_GUID = 0;
                GunshipArmory_H_GUID = 0;

                DeathbringerSaurfangGUID = 0;
                DeathbringerSaurfangGUID = 0;
                DeathbringerSaurfangDoorGUID = 0;
                DeathbringerSaurfangEventGUID = 0;   // Muradin Bronzebeard or High Overlord Saurfang
                DeathbringersCacheGUID = 0;
                PlagueSigilGUID = 0;
                BloodwingSigilGUID = 0;
                FrostwingSigilGUID = 0;
                memset(PutricidePipeGUIDs, 0, 2*sizeof(uint64));
                memset(PutricideGateGUIDs, 0, 2*sizeof(uint64));
                PutricideCollisionGUID = 0;
                FestergutGUID = 0;
                RotfaceGUID = 0;
                ProfessorPutricideGUID = 0;
                PutricideTableGUID = 0;
                memset(BloodCouncilGUIDs, 0, 3*sizeof(uint64));
                BloodCouncilControllerGUID;
                BloodQueenLanaThelGUID;
                CrokScourgebaneGUID = 0;
                memset(CrokCaptainGUIDs, 0, 4 * sizeof(uint64));
                CaptainCount = 0;
                SisterSvalnaGUID = 0;
                ValithriaDreamwalkerGUID = 0;
                ValithriaCacheGUID = 0;
                ValithriaLichKingGUID = 0;
                ValithriaTriggerGUID = 0;
                SindragosaGUID = 0;
                SpinestalkerGUID = 0;
                RimefangGUID = 0;
                TheLichKingGUID = 0;
                HighlordTirionFordringGUID = 0;
                TerenasMenethilGUID = 0;
                ArthasPlatformGUID = 0;
                ArthasPrecipiceGUID = 0;
                FrozenThroneEdgeGUID = 0;
                FrozenThroneWindGUID = 0;
                FrozenThroneWarningGUID = 0;
                IsBonedEligible = true;
                FrostwyrmCount= 0;
                SpinestalkerTrashCount = 0;
                RimefangTrashCount = 0;
                IsBonedEligible = true;
                IsOozeDanceEligible = true;
                IsNauseaEligible = true;
                IsOrbWhispererEligible = true;
                ColdflameJetsState = NOT_STARTED;
                AreGunshipsSpawned = false;
                m_GunshipMain   = NULL;
                m_GunshipSecond = NULL;
                m_ZeppelinHorde = NULL;
                
                m_blood_doorGUID = 0;
                m_ice_doorGUID = 0;

                BloodQuickeningState = NOT_STARTED;
                BloodQuickeningTimer = 0;
                BloodQuickeningMinutes = 0;

                BloodBolt_proc_count = 1;
            }

            ~instance_icecrown_citadel_InstanceMapScript()
            {
                if (m_GunshipMain)
                {
                    sMapMgr->m_Transports.erase(m_GunshipMain);
                    m_GunshipMain = NULL;
                    delete m_GunshipMain;
                }

                if (m_GunshipSecond)
                {
                    sMapMgr->m_Transports.erase(m_GunshipSecond);
                    m_GunshipSecond = NULL;
                    delete m_GunshipSecond;
                }
            }

            Transport* MakeTransport(uint32 gobentry,uint32 period,std::string nametransport, std::string scriptname)
            {
                Transport *t = new Transport(period, sObjectMgr->GetScriptId(scriptname.c_str()));

                uint32 entry = gobentry;
                std::string name = nametransport;

                const GameObjectTemplate *goinfo = sObjectMgr->GetGameObjectTemplate(entry);

                if (!goinfo)
                {
                    delete t;
                    return NULL;
                }
                std::set<uint32> mapsUsed;
                
                if (!t->GenerateWaypoints(goinfo->moTransport.taxiPathId, mapsUsed))
                    // skip transports with empty waypoints list
                {
                    delete t;
                    return NULL;
                }

                float x, y, z, o;
                uint32 mapid;
                x = t->m_WayPoints[0].x;
                y = t->m_WayPoints[0].y;
                z = t->m_WayPoints[0].z;
                mapid = t->m_WayPoints[0].mapid;
                o = 1;

                // creates the Gameobject
                if (!t->Create(sObjectMgr->GenerateLowGuid(HIGHGUID_GAMEOBJECT),entry, mapid, x, y, z, o, 100, 0))
                {
                    delete t;
                    return NULL;
                }

                t->SetMap(instance);
                t->SetZoneScript();
                t->AddToWorld();

                sMapMgr->m_Transports.insert(t);
                //(sMapMgr->m_TransportsByInstanceMap)[instance].insert(t);

                SpawnTransportNpc(t);

                t->BuildStopMovePacket(instance);

                return t;
            }

            void OnDestroy(InstanceMap* pMap)
            {
                /*printf("void OnDestroy(InstanceMapPtr pMap)\n");
                sMapMgr->m_Transports.erase(m_GunshipMain);
                sMapMgr->m_Transports.erase(m_GunshipSecond);
                delete m_GunshipMain;
                delete m_GunshipSecond;
                m_GunshipMain = NULL;
                m_GunshipSecond = NULL;*/
            }

            Creature * SpawnTransportNpc(Transport * pTransport, uint32 npc_entry = 0, float TransOffsetX = 0, float TransOffsetY = 0, float TransOffsetZ = 0, float TransOffsetO = 0, uint32 emote = 0)
            {
                uint8 MAX_GUNSHIP_ARTILLEURS  = !instance->Is25ManRaid() ? 2: 4;
                uint8 MAX_GUNSHIP_TIREURS     = !instance->Is25ManRaid() ? 4: 8;

                bool mustBeSpawned = false;

                if(!npc_entry)
                {
                    QueryResult npc_transport = WorldDatabase.PQuery("SELECT npc_entry, TransOffsetX, TransOffsetY, TransOffsetZ, TransOffsetO, emote, guid FROM creature_transport WHERE transport_entry = '%u' ORDER BY guid", pTransport->GetEntry());

                    if(!npc_transport)
                        return NULL;

                    do
                    {
                        Field *fields = npc_transport->Fetch();

                        uint32 guid = fields[6].GetUInt32();
                        uint32 npc_entry = fields[0].GetFloat();

                        mustBeSpawned = true;
                            
                        // EVENT ALLIANCE
                        /*if(pTransport->GetEntry() == TRANSPORT_A_THE_SKYBREAKER)
                        {
                            switch(npc_entry)
                            {
                                // Canons : guid 2-5
                                case NPC_CANON_A:
                                    if (guid < 2 || (guid - 2) >= MAX_GUNSHIP_CANONS)
                                        mustBeSpawned = false;

                                    break;
                            }
                        }
                        else */
                        if(pTransport->GetEntry() == TRANSPORT_A_ORGRIM_HAMMER)
                        {
                            switch(npc_entry)
                            {
                                // Tireurs : guid 2-9
                                case NPC_TIREUR_H:
                                    if (guid < 2 || (guid - 2) >= MAX_GUNSHIP_TIREURS)
                                        mustBeSpawned = false;

                                    break;
                                // Artilleurs : guid 10 - 13
                                case NPC_ARTILLEUR_H:
                                    if (guid < 10 || (guid - 10) >= MAX_GUNSHIP_ARTILLEURS)
                                        mustBeSpawned = false;

                                    break;
                            }
                        }
                        // EVENT HORDE
                        /*else if(pTransport->GetEntry() == TRANSPORT_H_ORGRIM_HAMMER)
                        {
                            switch(npc_entry)
                            {
                                // Canons : guid 2-5
                                /*case NPC_CANON_H:
                                    if (guid < 2 || (guid - 2) >= MAX_GUNSHIP_CANONS)
                                        mustBeSpawned = false;

                                    break;
                            }
                        }
                        else */
                        if(pTransport->GetEntry() == TRANSPORT_H_THE_SKYBREAKER)
                        {
                            switch(npc_entry)
                            {
                                // Tireurs : guid 2-9
                                case NPC_TIREUR_A:
                                    if (guid < 2 || (guid - 2) >= MAX_GUNSHIP_TIREURS)
                                        mustBeSpawned = false;

                                    break;
                                // Artilleurs : guid 10 - 13
                                case NPC_ARTILLEUR_A:
                                    if (guid < 10 || (guid - 10) >= MAX_GUNSHIP_ARTILLEURS)
                                        mustBeSpawned = false;

                                    break;
                            }
                        }

                        // On a eliminé ceux qui ne doivent pas etre spawn
                        if (!mustBeSpawned)
                            continue;

                        if (Creature * Passenger = pTransport->AddNPCPassengerCreature(fields[6].GetUInt32(), fields[0].GetFloat(), fields[1].GetFloat(), fields[2].GetFloat(), fields[3].GetFloat(),fields[4].GetUInt32(),fields[5].GetUInt32()))
                        {
                            // EVENT ALLIANCE
                            if(pTransport->GetEntry() == TRANSPORT_A_THE_SKYBREAKER)
                            {
                                switch(npc_entry)
                                {
                                    case NPC_GUNSHIP_A:
                                    {
                                        switch (instance->GetDifficulty())
                                        {
                                            case MAN10_DIFFICULTY:
                                                Passenger->SetMaxHealth(690000);
                                                Passenger->SetHealth(690000);
                                                break;
                                            case MAN25_DIFFICULTY:
                                                Passenger->SetMaxHealth(1380000);
                                                Passenger->SetHealth(1380000);
                                                break;
                                            case MAN10_HEROIC_DIFFICULTY:
                                                Passenger->SetMaxHealth(793500);
                                                Passenger->SetHealth(793500);
                                                break;
                                            case MAN25_HEROIC_DIFFICULTY:
                                                Passenger->SetMaxHealth(1586997);
                                                Passenger->SetHealth(1586997);
                                                break;
                                        }
                                        Passenger->setFaction(35);
                                        Passenger->AI()->DoAction(ACTION_SET_MAIN_GUNSHIP);
                                        if(Passenger->GetInstanceScript())
                                            Passenger->GetInstanceScript()->SetData64(DATA_GUNSHIP_NPC_MAIN, Passenger->GetGUID());
                                        break;
                                    }
                                    case NPC_MURADIN_GUNSHIP:
                                        GunshipcommanderGUID = Passenger->GetGUID();
                                        break;
                                    // Canons : guid 2-5
                                    /*case NPC_CANON_A:
                                        GunshipCanons[guid - 2] = Passenger->GetGUID();
                                        break;*/
                                }
                            }
                            else if(pTransport->GetEntry() == TRANSPORT_A_ORGRIM_HAMMER)
                            {
                                switch(npc_entry)
                                {
                                    case NPC_GUNSHIP_H:
                                    {
                                        switch (instance->GetDifficulty())
                                        {
                                            case MAN10_DIFFICULTY:
                                                Passenger->SetMaxHealth(690000);
                                                Passenger->SetHealth(690000);
                                                break;
                                            case MAN25_DIFFICULTY:
                                                Passenger->SetMaxHealth(1380000);
                                                Passenger->SetHealth(1380000);
                                                break;
                                            case MAN10_HEROIC_DIFFICULTY:
                                                Passenger->SetMaxHealth(793500);
                                                Passenger->SetHealth(793500);
                                                break;
                                            case MAN25_HEROIC_DIFFICULTY:
                                                Passenger->SetMaxHealth(1586997);
                                                Passenger->SetHealth(1586997);
                                                break;
                                        }
                                        Passenger->setFaction(14);
                                        Passenger->AI()->DoAction(ACTION_SET_SECOND_GUNSHIP);
                                        if(Passenger->GetInstanceScript())
                                            Passenger->GetInstanceScript()->SetData64(DATA_GUNSHIP_NPC_SECOND, Passenger->GetGUID());
                                        break;
                                    }
                                    // Saucroc : guid 1
                                    case NPC_SAURCROC_GUNSHIP:
                                        Passenger->AI()->DoAction(ACTION_SET_ENNEMY_COMMANDER);
                                        GunshipennemycommanderGUID = Passenger->GetGUID();
                                        break;
                                    // Tireurs : guid 2-9
                                    case NPC_TIREUR_H:
                                        GunshipTireurs[guid - 2] = Passenger->GetGUID();
                                        break;
                                    // Artilleurs : guid 10 - 13
                                    case NPC_ARTILLEUR_H:
                                        GunshipArtilleurs[guid - 10] = Passenger->GetGUID();
                                        break;
                                    // Artilleurs : guid 16 - 17
                                    case NPC_MAGE_H:
                                        GunshipMages[guid - 16] = Passenger->GetGUID();
                                        break;
                                }
                            }
                            // EVENT HORDE
                            else if(pTransport->GetEntry() == TRANSPORT_H_ORGRIM_HAMMER)
                            {
                                switch(npc_entry)
                                {
                                    case NPC_GUNSHIP_H:
                                    {
                                        switch (instance->GetDifficulty())
                                        {
                                            case MAN10_DIFFICULTY:
                                                Passenger->SetMaxHealth(690000);
                                                Passenger->SetHealth(690000);
                                                break;
                                            case MAN25_DIFFICULTY:
                                                Passenger->SetMaxHealth(1380000);
                                                Passenger->SetHealth(1380000);
                                                break;
                                            case MAN10_HEROIC_DIFFICULTY:
                                                Passenger->SetMaxHealth(793500);
                                                Passenger->SetHealth(793500);
                                                break;
                                            case MAN25_HEROIC_DIFFICULTY:
                                                Passenger->SetMaxHealth(1586997);
                                                Passenger->SetHealth(1586997);
                                                break;
                                        }
                                        Passenger->setFaction(35);
                                        Passenger->AI()->DoAction(ACTION_SET_MAIN_GUNSHIP);
                                        if(Passenger->GetInstanceScript())
                                            Passenger->GetInstanceScript()->SetData64(DATA_GUNSHIP_NPC_MAIN, Passenger->GetGUID());
                                        break;
                                    }
                                    case NPC_SAURCROC_GUNSHIP:
                                        GunshipcommanderGUID = Passenger->GetGUID();
                                        break;
                                    // Canons : guid 2-5
                                    /*case NPC_CANON_H:
                                        GunshipCanons[guid - 2] = Passenger->GetGUID();
                                        break;*/
                                }
                            }
                            else if(pTransport->GetEntry() == TRANSPORT_H_THE_SKYBREAKER)
                            {
                                switch(npc_entry)
                                {
                                    case NPC_GUNSHIP_A:
                                    {
                                        switch (instance->GetDifficulty())
                                        {
                                            case MAN10_DIFFICULTY:
                                                Passenger->SetMaxHealth(690000);
                                                Passenger->SetHealth(690000);
                                                break;
                                            case MAN25_DIFFICULTY:
                                                Passenger->SetMaxHealth(1380000);
                                                Passenger->SetHealth(1380000);
                                                break;
                                            case MAN10_HEROIC_DIFFICULTY:
                                                Passenger->SetMaxHealth(793500);
                                                Passenger->SetHealth(793500);
                                                break;
                                            case MAN25_HEROIC_DIFFICULTY:
                                                Passenger->SetMaxHealth(1586997);
                                                Passenger->SetHealth(1586997);
                                                break;
                                        }
                                        Passenger->setFaction(14);
                                        Passenger->AI()->DoAction(ACTION_SET_SECOND_GUNSHIP);
                                        if(Passenger->GetInstanceScript())
                                            Passenger->GetInstanceScript()->SetData64(DATA_GUNSHIP_NPC_SECOND, Passenger->GetGUID());
                                        break;
                                    }
                                    case NPC_MURADIN_GUNSHIP:
                                        Passenger->AI()->DoAction(ACTION_SET_ENNEMY_COMMANDER);
                                        GunshipennemycommanderGUID = Passenger->GetGUID();
                                        break;
                                    // Tireurs : guid 2-9
                                    case NPC_TIREUR_A:
                                        GunshipTireurs[guid - 2] = Passenger->GetGUID();
                                        break;
                                    // Artilleurs : guid 10 - 13
                                    case NPC_ARTILLEUR_A:
                                        GunshipArtilleurs[guid - 10] = Passenger->GetGUID();
                                        break;
                                }
                            }
                        }
                    }
                    while(npc_transport->NextRow());
                }
                else
                    return pTransport->AddNPCPassengerCreature(0/*tGuid*/, npc_entry, TransOffsetX, TransOffsetY, TransOffsetZ, TransOffsetO, emote);

                 return NULL;
            }

            void FillInitialWorldStates(WorldPacket& data)
            {
                data << uint32(WORLDSTATE_SHOW_TIMER)         << uint32(BloodQuickeningState == IN_PROGRESS);
                data << uint32(WORLDSTATE_EXECUTION_TIME)     << uint32(BloodQuickeningMinutes);
                data << uint32(WORLDSTATE_SHOW_ATTEMPTS)      << uint32(instance->IsHeroic());
                data << uint32(WORLDSTATE_ATTEMPTS_REMAINING) << uint32(HeroicAttempts);
                data << uint32(WORLDSTATE_ATTEMPTS_MAX)       << uint32(50);
            }

            void OnPlayerEnter(Player* player)
            {
                if (!TeamInInstance)
                    TeamInInstance = player->GetTeam();

                if (!AreGunshipsSpawned && TeamInInstance)
                {
                    if(TeamInInstance == ALLIANCE)
                    {
                        m_GunshipMain   = MakeTransport(TRANSPORT_A_THE_SKYBREAKER, 77527,  "ICC - Skybreaker alliance", "transport_icc_gunship");
                        m_GunshipSecond = MakeTransport(TRANSPORT_A_ORGRIM_HAMMER,  115661, "ICC - Orgrim's Hammer alliance", "transport_icc_gunship");
                        //m_ZeppelinHorde = MakeTransport(TRANSPORT_A_THE_MIGHTY_WIND, 154573, "ICC - The Mighty Wind", "");
                        //m_ZeppelinHorde->SetPhaseMask(0, true);

                        AreGunshipsSpawned = true;
                    }
                    else
                    {
                        m_GunshipMain   = MakeTransport(TRANSPORT_H_ORGRIM_HAMMER,  77527,  "ICC - Orgrim's Hammer horde", "transport_icc_gunship");
                        m_GunshipSecond = MakeTransport(TRANSPORT_H_THE_SKYBREAKER, 118797, "ICC - Skybreaker horde", "transport_icc_gunship");
                        AreGunshipsSpawned = true;
                    }

                    if (m_GunshipMain)
                        FriendGunshipGUID = m_GunshipMain->GetGUID();
                    
                    if (m_GunshipSecond)
                        EnnemyGunshipGUID = m_GunshipSecond->GetGUID();
                }
                SendTransportInit(player);
            }

            void SendTransportInit(Player *player)
            {
                if(!m_GunshipMain || !m_GunshipSecond)
                    return;

                UpdateData transData(player->GetMapId());
                m_GunshipMain->BuildCreateUpdateBlockForPlayer(&transData, player);
                m_GunshipSecond->BuildCreateUpdateBlockForPlayer(&transData, player);
                WorldPacket packet;
                transData.BuildPacket(&packet);
                player->GetSession()->SendPacket(&packet);
            }

            void OnCreatureCreate(Creature* creature)
            {
                if (!TeamInInstance)
                {
                    Map::PlayerList const &players = instance->GetPlayers();
                    if (!players.isEmpty())
                        if (Player* player = players.begin()->getSource())
                            TeamInInstance = player->GetTeam();
                }

                switch (creature->GetEntry())
                {
                    case NPC_LORD_MARROWGAR:
                        LordMarrowgarGUID = creature->GetGUID();
                        break;
                    case NPC_KOR_KRON_GENERAL:
                        if (TeamInInstance == ALLIANCE)
                            creature->UpdateEntry(NPC_ALLIANCE_COMMANDER, ALLIANCE);
                        break;
                    case NPC_KOR_KRON_LIEUTENANT:
                        if (TeamInInstance == ALLIANCE)
                            creature->UpdateEntry(NPC_SKYBREAKER_LIEUTENANT, ALLIANCE);
                        break;
                    case NPC_TORTUNOK:
                        if (TeamInInstance == ALLIANCE)
                            creature->UpdateEntry(NPC_ALANA_MOONSTRIKE, ALLIANCE);
                        break;
                    case NPC_GERARDO_THE_SUAVE:
                        if (TeamInInstance == ALLIANCE)
                            creature->UpdateEntry(NPC_TALAN_MOONSTRIKE, ALLIANCE);
                        break;
                    case NPC_UVLUS_BANEFIRE:
                        if (TeamInInstance == ALLIANCE)
                            creature->UpdateEntry(NPC_MALFUS_GRIMFROST, ALLIANCE);
                        break;
                    case NPC_IKFIRUS_THE_VILE:
                        if (TeamInInstance == ALLIANCE)
                            creature->UpdateEntry(NPC_YILI, ALLIANCE);
                        break;
                    case NPC_VOL_GUK:
                        if (TeamInInstance == ALLIANCE)
                            creature->UpdateEntry(NPC_JEDEBIA, ALLIANCE);
                        break;
                    case NPC_HARAGG_THE_UNSEEN:
                        if (TeamInInstance == ALLIANCE)
                            creature->UpdateEntry(NPC_NIBY_THE_ALMIGHTY, ALLIANCE);
                        break;
                    case NPC_GARROSH_HELLSCREAM:
                        if (TeamInInstance == ALLIANCE)
                            creature->UpdateEntry(NPC_KING_VARIAN_WRYNN, ALLIANCE);
                        break;
                    case NPC_DEATHBRINGER_SAURFANG:
                        DeathbringerSaurfangGUID = creature->GetGUID();
                        break;
                    case NPC_SE_HIGH_OVERLORD_SAURFANG:
                        if (TeamInInstance == ALLIANCE)
                            creature->UpdateEntry(NPC_SE_MURADIN_BRONZEBEARD, ALLIANCE, creature->GetCreatureData());
                    case NPC_SE_MURADIN_BRONZEBEARD:
                        DeathbringerSaurfangEventGUID = creature->GetGUID();
                        creature->LastUsedScriptID = creature->GetScriptId();
                        break;
                    case NPC_SE_KOR_KRON_REAVER:
                        if (TeamInInstance == ALLIANCE)
                            creature->UpdateEntry(NPC_SE_SKYBREAKER_MARINE, ALLIANCE);
                        break;
                    case NPC_FROST_FREEZE_TRAP:
                        ColdflameJetGUIDs.insert(creature->GetGUID());
                        break;
                    case NPC_FESTERGUT:
                        FestergutGUID = creature->GetGUID();
                        break;
                    case NPC_ROTFACE:
                        RotfaceGUID = creature->GetGUID();
                        break;
                    case NPC_PROFESSOR_PUTRICIDE:
                        ProfessorPutricideGUID = creature->GetGUID();
                        break;
                    case NPC_PRINCE_KELESETH:
                        BloodCouncilGUIDs[0] = creature->GetGUID();
                        break;
                    case NPC_PRINCE_TALDARAM:
                        BloodCouncilGUIDs[1] = creature->GetGUID();
                        break;
                    case NPC_PRINCE_VALANAR:
                        BloodCouncilGUIDs[2] = creature->GetGUID();
                        break;
                    case NPC_BLOOD_ORB_CONTROLLER:
                        BloodCouncilControllerGUID = creature->GetGUID();
                        break;
                    case NPC_BLOOD_QUEEN_LANA_THEL:
                        BloodQueenLanaThelGUID = creature->GetGUID();
                        break;

                    case NPC_CROK_SCOURGEBANE:
                        CrokScourgebaneGUID = creature->GetGUID();
                        break;
                    // we can only do this because there are no gaps in their entries
                    case NPC_CAPTAIN_ARNATH:
                    case NPC_CAPTAIN_BRANDON:
                    case NPC_CAPTAIN_GRONDEL:
                    case NPC_CAPTAIN_RUPERT:
                        CrokCaptainGUIDs[creature->GetEntry()-NPC_CAPTAIN_ARNATH] = creature->GetGUID();
                        break;
                    case NPC_SISTER_SVALNA:
                        SisterSvalnaGUID = creature->GetGUID();
                        break;
                    case NPC_VALITHRIA_DREAMWALKER:
                        ValithriaDreamwalkerGUID = creature->GetGUID();
                        break;
                    case NPC_THE_LICH_KING_VALITHRIA:
                        if(creature->GetDBTableGUIDLow()) // Seul le vrai spawn doit donner son GUID
                            ValithriaLichKingGUID = creature->GetGUID();
                        break;

                    case NPC_GREEN_DRAGON_COMBAT_TRIGGER:
                        ValithriaTriggerGUID = creature->GetGUID();
                        break;
                    case NPC_SINDRAGOSA:
                        SindragosaGUID = creature->GetGUID();
                        break;
                    case NPC_SPINESTALKER:
                        SpinestalkerGUID = creature->GetGUID();
                        if (!creature->isDead())
                            ++FrostwyrmCount;
                        break;
                    case NPC_RIMEFANG:
                        RimefangGUID = creature->GetGUID();
                        if (!creature->isDead())
                            ++FrostwyrmCount;
                        break;
                    case NPC_THE_LICH_KING:
                        TheLichKingGUID = creature->GetGUID();
                        break;
                    case NPC_HIGHLORD_TIRION_FORDRING_LK:
                        HighlordTirionFordringGUID = creature->GetGUID();
                        break;
                    case NPC_TERENAS_MENETHIL_FROSTMOURNE:
                    case NPC_TERENAS_MENETHIL_FROSTMOURNE_H:
                        TerenasMenethilGUID = creature->GetGUID();
                        break;
                    default:
                        break;
                }

                switch(creature->getFactionTemplateEntry()->ID)
                {
                    // Horde Generic
                    case 83:
                        if (TeamInInstance == ALLIANCE)
                            creature->setFaction(14);
                        else
                            creature->setFaction(35);
                        break;
                    // Alliance Generic
                    case 84:
                        if (TeamInInstance == ALLIANCE)
                            creature->setFaction(35);
                        else
                            creature->setFaction(14);
                        break;
                }
            }

            // Weekly quest spawn prevention
            uint32 GetCreatureEntry(uint32 /*guidLow*/, CreatureData const* data)
            {
                uint32 entry = data->id;
                switch (entry)
                {
                    case NPC_INFILTRATOR_MINCHAR:
                    case NPC_KOR_KRON_LIEUTENANT:
                    case NPC_ALCHEMIST_ADRIANNA:
                    case NPC_ALRIN_THE_AGILE:
                    case NPC_INFILTRATOR_MINCHAR_BQ:
                    case NPC_MINCHAR_BEAM_STALKER:
                    case NPC_VALITHRIA_DREAMWALKER_QUEST:
                    {
                        for (uint8 questIndex = 0; questIndex < WeeklyNPCs; ++questIndex)
                        {
                            if (WeeklyQuestData[questIndex].creatureEntry == entry)
                            {
                                uint8 diffIndex = instance->GetSpawnMode() & 1;
                                if (!sPoolMgr->IsSpawnedObject<Quest>(WeeklyQuestData[questIndex].questId[diffIndex]))
                                    entry = 0;
                                break;
                            }
                        }
                        break;
                    }
                    default:
                        break;
                }

                return entry;
            }

            void OnCreatureRemove(Creature* creature)
            {
                if (creature->GetEntry() == NPC_FROST_FREEZE_TRAP)
                    ColdflameJetGUIDs.erase(creature->GetGUID());
            }

            void OnCreatureDeath(Creature* creature)
            {
                switch (creature->GetEntry())
                {
                    case NPC_YMIRJAR_BATTLE_MAIDEN:
                    case NPC_YMIRJAR_DEATHBRINGER:
                    case NPC_YMIRJAR_FROSTBINDER:
                    case NPC_YMIRJAR_HUNTRESS:
                    case NPC_YMIRJAR_WARLORD:
                        if (Creature* crok = instance->GetCreature(CrokScourgebaneGUID))
                            crok->AI()->SetGUID(creature->GetGUID(), ACTION_VRYKUL_DEATH);
                        break;
                    default:
                        break;
                }
            }

            void OnGameObjectCreate(GameObject* go)
            {
                switch (go->GetEntry())
                {
                    case GO_DOODAD_ICECROWN_ICEWALL02:
                    case GO_ICEWALL:
                    case GO_LORD_MARROWGAR_S_ENTRANCE:
                    case GO_ORATORY_OF_THE_DAMNED_ENTRANCE:
                    case GO_ORANGE_PLAGUE_MONSTER_ENTRANCE:
                    case GO_GREEN_PLAGUE_MONSTER_ENTRANCE:
                    case GO_SCIENTIST_ENTRANCE:
                    case GO_CRIMSON_HALL_DOOR:
                    case GO_BLOOD_ELF_COUNCIL_DOOR:
                    case GO_BLOOD_ELF_COUNCIL_DOOR_RIGHT:
                    case GO_DOODAD_ICECROWN_BLOODPRINCE_DOOR_01:
                    case GO_DOODAD_ICECROWN_GRATE_01:
                    case GO_GREEN_DRAGON_BOSS_ENTRANCE:
                    case GO_GREEN_DRAGON_BOSS_EXIT:
                    case GO_DOODAD_ICECROWN_ROOSTPORTCULLIS_02:
                    case GO_DOODAD_ICECROWN_ROOSTPORTCULLIS_03:
                    case GO_SINDRAGOSA_ENTRANCE_DOOR:
                    case GO_SINDRAGOSA_SHORTCUT_ENTRANCE_DOOR:
                    case GO_SINDRAGOSA_SHORTCUT_EXIT_DOOR:
                    case GO_ICE_WALL:
                        AddDoor(go, true);
                        break;
                    // these 2 gates are functional only on 25man modes
                    case GO_DOODAD_ICECROWN_ROOSTPORTCULLIS_01:
                    case GO_DOODAD_ICECROWN_ROOSTPORTCULLIS_04:
                        if (instance->GetSpawnMode() & 1)
                            AddDoor(go, true);
                        break;
                    case GO_LADY_DEATHWHISPER_ELEVATOR:
                        LadyDeathwisperElevatorGUID = go->GetGUID();
                        if (GetBossState(DATA_LADY_DEATHWHISPER) == DONE)
                        {
                            go->SetUInt32Value(GAMEOBJECT_LEVEL, 0);
                            go->SetGoState(GO_STATE_READY);
                        }
                        break;
                    case GO_SAURFANG_S_DOOR:
                        DeathbringerSaurfangDoorGUID = go->GetGUID();
                        AddDoor(go, true);
                        break;
                    case GO_DEATHBRINGER_S_CACHE_10N:
                    case GO_DEATHBRINGER_S_CACHE_25N:
                    case GO_DEATHBRINGER_S_CACHE_10H:
                    case GO_DEATHBRINGER_S_CACHE_25H:
                        DeathbringersCacheGUID = go->GetGUID();
                        break;
                    case GO_SCOURGE_TRANSPORTER_SAURFANG:
                        SaurfangTeleportGUID = go->GetGUID();
                        break;
                    case GO_PLAGUE_SIGIL:
                        PlagueSigilGUID = go->GetGUID();
                        if (GetBossState(DATA_PROFESSOR_PUTRICIDE))
                            HandleGameObject(PlagueSigilGUID, true, go);
                        break;
                    case GO_BLOODWING_SIGIL:
                        BloodwingSigilGUID = go->GetGUID();
                        if (GetBossState(DATA_PROFESSOR_PUTRICIDE))
                            HandleGameObject(BloodwingSigilGUID, true, go);
                        break;
                    case GO_SIGIL_OF_THE_FROSTWING:
                        FrostwingSigilGUID = go->GetGUID();
                        if (GetBossState(DATA_PROFESSOR_PUTRICIDE))
                            HandleGameObject(FrostwingSigilGUID, true, go);
                        break;
                    case GO_SCIENTIST_AIRLOCK_DOOR_COLLISION:
                        PutricideCollisionGUID = go->GetGUID();
                        if (GetBossState(DATA_FESTERGUT) == DONE && GetBossState(DATA_ROTFACE) == DONE)
                            HandleGameObject(PutricideCollisionGUID, true, go);
                        break;
                    case GO_SCIENTIST_AIRLOCK_DOOR_ORANGE:
                        PutricideGateGUIDs[0] = go->GetGUID();
                        if (GetBossState(DATA_FESTERGUT) == DONE && GetBossState(DATA_ROTFACE) == DONE)
                            go->SetGoState(GO_STATE_ACTIVE_ALTERNATIVE);
                        else if (GetBossState(DATA_FESTERGUT) == DONE)
                            HandleGameObject(PutricideGateGUIDs[1], false, go);
                        break;
                    case GO_SCIENTIST_AIRLOCK_DOOR_GREEN:
                        PutricideGateGUIDs[1] = go->GetGUID();
                        if (GetBossState(DATA_ROTFACE) == DONE && GetBossState(DATA_FESTERGUT) == DONE)
                            go->SetGoState(GO_STATE_ACTIVE_ALTERNATIVE);
                        else if (GetBossState(DATA_ROTFACE) == DONE)
                            HandleGameObject(PutricideGateGUIDs[1], false, go);
                        break;
                    case GO_DOODAD_ICECROWN_ORANGETUBES02:
                        PutricideGateGUIDs[0] = go->GetGUID();
                        if (GetBossState(DATA_FESTERGUT) == DONE)
                            HandleGameObject(PutricidePipeGUIDs[0], true, go);
                        break;
                    case GO_DOODAD_ICECROWN_GREENTUBES02:
                        PutricidePipeGUIDs[1] = go->GetGUID();
                        if (GetBossState(DATA_ROTFACE) == DONE)
                            HandleGameObject(PutricidePipeGUIDs[1], true, go);
                        break;
                    case GO_DRINK_ME:
                        PutricideTableGUID = go->GetGUID();
                        break;
                    case GO_BLOOD_DOOR:
                        m_blood_doorGUID = go->GetGUID();
                        HandleGameObject(go->GetGUID(), true, go);
                        break;
                    case GO_ICE_DOOR:
                        m_ice_doorGUID = go->GetGUID();
                        HandleGameObject(go->GetGUID(), true, go);
                        break;
                    case GO_DREAMWALKER_S_CACHE_10N:
                    case GO_DREAMWALKER_S_CACHE_25N:
                    case GO_DREAMWALKER_S_CACHE_10H:
                    case GO_DREAMWALKER_S_CACHE_25H:
                        ValithriaCacheGUID = go->GetGUID();
                        break;
                    case GO_GUNSHIP_COFFRE_A_10N:
                    case GO_GUNSHIP_COFFRE_A_25N:
                    case GO_GUNSHIP_COFFRE_A_10H:
                    case GO_GUNSHIP_COFFRE_A_25H:
                        GunshipArmory_A_GUID = go->GetGUID();
                        break;
                    case GO_GUNSHIP_COFFRE_H_10N:
                    case GO_GUNSHIP_COFFRE_H_25N:
                    case GO_GUNSHIP_COFFRE_H_10H:
                    case GO_GUNSHIP_COFFRE_H_25H:
                        GunshipArmory_H_GUID = go->GetGUID();
                        break;
                    case GO_ARTHAS_PLATFORM:
                        // this enables movement at The Frozen Throne, when printed this value is 0.000000f
                        // however, when represented as integer client will accept only this value
                        go->SetUInt32Value(GAMEOBJECT_PARENTROTATION, 5535469);
                        ArthasPlatformGUID = go->GetGUID();
                        break;
                    case GO_ARTHAS_PRECIPICE:
                        go->SetUInt32Value(GAMEOBJECT_PARENTROTATION, 4178312);
                        ArthasPrecipiceGUID = go->GetGUID();
                        break;
                    case GO_DOODAD_ICECROWN_THRONEFROSTYEDGE01:
                        FrozenThroneEdgeGUID = go->GetGUID();
                        break;
                    case GO_DOODAD_ICECROWN_THRONEFROSTYWIND01:
                        FrozenThroneWindGUID = go->GetGUID();
                        break;
                    case GO_DOODAD_ICECROWN_SNOWEDGEWARNING01:
                        FrozenThroneWarningGUID = go->GetGUID();
                        break;
                    case GO_FROZEN_LAVAMAN:
                        FrozenBolvarGUID = go->GetGUID();
                        if (GetBossState(DATA_THE_LICH_KING) == DONE)
                            go->SetRespawnTime(7 * DAY);
                        break;
                    case GO_LAVAMAN_PILLARS_CHAINED:
                        PillarsChainedGUID = go->GetGUID();
                        if (GetBossState(DATA_THE_LICH_KING) == DONE)
                            go->SetRespawnTime(7 * DAY);
                        break;
                    case GO_LAVAMAN_PILLARS_UNCHAINED:
                        PillarsUnchainedGUID = go->GetGUID();
                        if (GetBossState(DATA_THE_LICH_KING) == DONE)
                            go->SetRespawnTime(7 * DAY);
                        break;
                    default:
                        break;
                }
            }

            void OnGameObjectRemove(GameObject* go)
            {
                switch (go->GetEntry())
                {
                    case GO_DOODAD_ICECROWN_ICEWALL02:
                    case GO_ICEWALL:
                    case GO_LORD_MARROWGAR_S_ENTRANCE:
                    case GO_ORATORY_OF_THE_DAMNED_ENTRANCE:
                    case GO_SAURFANG_S_DOOR:
                    case GO_ORANGE_PLAGUE_MONSTER_ENTRANCE:
                    case GO_GREEN_PLAGUE_MONSTER_ENTRANCE:
                    case GO_SCIENTIST_ENTRANCE:
                    case GO_CRIMSON_HALL_DOOR:
                    case GO_BLOOD_ELF_COUNCIL_DOOR:
                    case GO_BLOOD_ELF_COUNCIL_DOOR_RIGHT:
                    case GO_DOODAD_ICECROWN_BLOODPRINCE_DOOR_01:
                    case GO_DOODAD_ICECROWN_GRATE_01:
                    case GO_GREEN_DRAGON_BOSS_ENTRANCE:
                    case GO_GREEN_DRAGON_BOSS_EXIT:
                    case GO_SINDRAGOSA_ENTRANCE_DOOR:
                    case GO_SINDRAGOSA_SHORTCUT_ENTRANCE_DOOR:
                    case GO_SINDRAGOSA_SHORTCUT_EXIT_DOOR:
                    case GO_ICE_WALL:
                        AddDoor(go, false);
                        break;
                    default:
                        break;
                }
            }

            uint32 GetData(uint32 type)
            {
                switch (type)
                {
                    case DATA_SINDRAGOSA_FROSTWYRMS:
                        return FrostwyrmCount;
                    case DATA_SPINESTALKER:
                        return SpinestalkerTrashCount;
                    case DATA_RIMEFANG:
                        return RimefangTrashCount;
                    case DATA_COLDFLAME_JETS:
                        return ColdflameJetsState;
                    case DATA_BLOODQUEEN_TARGETS_PROC:
                        return BloodBolt_proc_count;
                    case DATA_BLOODQUEEN_TARGETS_COUNT:
                        return BloodQueen_BloodBolt_TargetsList.size();
                    case DATA_TEAM_IN_INSTANCE:
                        return TeamInInstance;
                    case DATA_HEROIC_ATTEMPTS:
                        return HeroicAttempts;
                    case DATA_GUNSHIP_PORTAL_MAGES:
                        return GunshipAliveMagesNumber;
                    default:
                        break;
                }

                return 0;
            }

            void SetData64(uint32 type, uint64 data)
            {
                switch (type)
                {
                    case DATA_GUNSHIP_NPC_MAIN:
                        FriendGunshipNPCGUID = data;
                        break;
                    case DATA_GUNSHIP_NPC_SECOND:
                        EnnemyGunshipNPCGUID = data;
                        break;
                    case DATA_GUNSHIP_ADD_RESPAWN:
                        if (Creature * c = instance->GetCreature(data))
                        {
                            uint32 TimeToRespawn = getMSTime() + 35000;
                            creatureEntryAndGuid entryAndGuid = { data, c->GetEntry() };

                            GunshipRespawnMap.insert( std::make_pair(TimeToRespawn, entryAndGuid) );
                        }
                        break;
                    case DATA_GUNSHIP_BOARDING_COUNT:
                        // Le joueur est deja monte au moins une fois dessus
                        if (GunshipBoardCount.find(data) != GunshipBoardCount.end())
                        {
                            GunshipBoardCount[data] = GunshipBoardCount[data] + 1;
                        }
                        // Premier abordage du joueur
                        else
                        {
                            GunshipBoardCount[data] = 1;
                        }
                        break;
                    case DATA_BLOODQUEEN_TARGETS:
                        if(data)
                            BloodQueen_BloodBolt_TargetsList.push_back(data);
                        //else
                            //JadeCore::Containers::RandomListOrder<uint64>(BloodQueen_BloodBolt_TargetsList);
                        break;
                    default:
                        break;
                }
            }

            uint64 GetData64(uint32 type)
            {
                switch (type)
                {
                    case DATA_LORD_MARROWGAR:
                        return LordMarrowgarGUID;
                    case DATA_GUNSHIP_TRANSPORT_MAIN:
                        return FriendGunshipGUID;
                    case DATA_GUNSHIP_TRANSPORT_SECOND:
                        return EnnemyGunshipGUID;
                    case DATA_GUNSHIP_NPC_MAIN:
                        return FriendGunshipNPCGUID;
                    case DATA_GUNSHIP_NPC_SECOND:
                        return EnnemyGunshipNPCGUID;
                    case DATA_DEATHBRINGER_SAURFANG:
                        return DeathbringerSaurfangGUID;
                    case DATA_GUNSHIP_COMMANDER:
                        return GunshipcommanderGUID;
                    case DATA_GUNSHIP_ENNEMY_COMMANDER:
                        return GunshipennemycommanderGUID;
                    case DATA_SAURFANG_EVENT_NPC:
                        return DeathbringerSaurfangEventGUID;
                    case GO_SAURFANG_S_DOOR:
                        return DeathbringerSaurfangDoorGUID;
                    case GO_SCOURGE_TRANSPORTER_SAURFANG:
                        return SaurfangTeleportGUID;
                    case DATA_FESTERGUT:
                        return FestergutGUID;
                    case DATA_ROTFACE:
                        return RotfaceGUID;
                    case DATA_PROFESSOR_PUTRICIDE:
                        return ProfessorPutricideGUID;
                    case DATA_PUTRICIDE_TABLE:
                        return PutricideTableGUID;
                    case DATA_PRINCE_KELESETH_GUID:
                        return BloodCouncilGUIDs[0];
                    case DATA_PRINCE_TALDARAM_GUID:
                        return BloodCouncilGUIDs[1];
                    case DATA_PRINCE_VALANAR_GUID:
                        return BloodCouncilGUIDs[2];
                    case DATA_BLOOD_PRINCES_CONTROL:
                        return BloodCouncilControllerGUID;
                    case DATA_BLOOD_QUEEN_LANA_THEL:
                        return BloodQueenLanaThelGUID;
                    case DATA_BLOODQUEEN_TARGETS:
                    {
                        if(BloodQueen_BloodBolt_TargetsList.empty())
                            return 0;

                        uint64 RandomTarget = BloodQueen_BloodBolt_TargetsList.front();
                        BloodQueen_BloodBolt_TargetsList.pop_front();

                        return RandomTarget;
                    }
                    case DATA_CROK_SCOURGEBANE:
                        return CrokScourgebaneGUID;
                    case DATA_CAPTAIN_ARNATH:
                    case DATA_CAPTAIN_BRANDON:
                    case DATA_CAPTAIN_GRONDEL:
                    case DATA_CAPTAIN_RUPERT:
                        return CrokCaptainGUIDs[type - DATA_CAPTAIN_ARNATH];
                    case DATA_SISTER_SVALNA:
                        return SisterSvalnaGUID;
                    case DATA_VALITHRIA_DREAMWALKER:
                        return ValithriaDreamwalkerGUID;
                    case DATA_VALITHRIA_LICH_KING:
                        return ValithriaLichKingGUID;
                    case DATA_VALITHRIA_TRIGGER:
                        return ValithriaTriggerGUID;
                    case DATA_SINDRAGOSA:
                        return SindragosaGUID;
                    case DATA_SPINESTALKER:
                        return SpinestalkerGUID;
                    case DATA_RIMEFANG:
                        return RimefangGUID;
                    case DATA_THE_LICH_KING:
                        return TheLichKingGUID;
                    case DATA_HIGHLORD_TIRION_FORDRING:
                        return HighlordTirionFordringGUID;
                    case DATA_ARTHAS_PLATFORM:
                        return ArthasPlatformGUID;
                    case DATA_TERENAS_MENETHIL:
                        return TerenasMenethilGUID;
                    default:
                        break;
                }

                return 0;
            }

            bool SetBossState(uint32 type, EncounterState state)
            {
                if (!InstanceScript::SetBossState(type, state))
                    return false;

                if(state == IN_PROGRESS)
                    CheckPlayersNumber();

                switch (type)
                {
                    case DATA_LADY_DEATHWHISPER:
                        if (state == DONE)
                        {
                            if (GameObject* elevator = instance->GetGameObject(LadyDeathwisperElevatorGUID))
                            {
                                elevator->SetUInt32Value(GAMEOBJECT_LEVEL, 0);
                                elevator->SetGoState(GO_STATE_READY);
                            }
                        }
                        break;
                    case DATA_DEATHBRINGER_SAURFANG:
                        switch (state)
                        {
                            case DONE:
                                DoRespawnGameObject(DeathbringersCacheGUID, 7*DAY);
                            case NOT_STARTED:
                                if (GameObject* teleporter = instance->GetGameObject(SaurfangTeleportGUID))
                                {
                                    HandleGameObject(SaurfangTeleportGUID, true, teleporter);
                                    teleporter->RemoveFlag(GAMEOBJECT_FLAGS, GO_FLAG_IN_USE);
                                }
                                break;
                            default:
                                break;
                        }
                        break;
                    case DATA_FESTERGUT:
                        if (state == DONE)
                        {
                            if (GetBossState(DATA_ROTFACE) == DONE)
                            {
                                HandleGameObject(PutricideCollisionGUID, true);
                                if (GameObject* go = instance->GetGameObject(PutricideGateGUIDs[0]))
                                    go->SetGoState(GO_STATE_ACTIVE_ALTERNATIVE);
                                if (GameObject* go = instance->GetGameObject(PutricideGateGUIDs[1]))
                                    go->SetGoState(GO_STATE_ACTIVE_ALTERNATIVE);
                            }
                            else
                                HandleGameObject(PutricideGateGUIDs[0], false);
                            HandleGameObject(PutricidePipeGUIDs[0], true);
                        }
                        break;
                    case DATA_ROTFACE:
                        if (state == DONE)
                        {
                            if (GetBossState(DATA_FESTERGUT) == DONE)
                            {
                                HandleGameObject(PutricideCollisionGUID, true);
                                if (GameObject* go = instance->GetGameObject(PutricideGateGUIDs[0]))
                                    go->SetGoState(GO_STATE_ACTIVE_ALTERNATIVE);
                                if (GameObject* go = instance->GetGameObject(PutricideGateGUIDs[1]))
                                    go->SetGoState(GO_STATE_ACTIVE_ALTERNATIVE);
                            }
                            else
                                HandleGameObject(PutricideGateGUIDs[1], false);
                            HandleGameObject(PutricidePipeGUIDs[1], true);
                        }
                        break;
                    case DATA_PROFESSOR_PUTRICIDE:
                        HandleGameObject(PlagueSigilGUID, state != DONE);
                        if (instance->IsHeroic())
                        {
                            if (state == FAIL && HeroicAttempts)
                            {
                                --HeroicAttempts;
                                DoUpdateWorldState(WORLDSTATE_ATTEMPTS_REMAINING, HeroicAttempts);
                                if (!HeroicAttempts)
                                    if (Creature* putricide = instance->GetCreature(ProfessorPutricideGUID))
                                        putricide->DespawnOrUnsummon();

                                HandleGameObject(PlagueSigilGUID, false);
                            }
                        }
                        break;
                    case DATA_BLOOD_QUEEN_LANA_THEL:
                        HandleGameObject(BloodwingSigilGUID, state != DONE);
                        if (instance->IsHeroic())
                        {
                            if (state == FAIL && HeroicAttempts)
                            {
                                --HeroicAttempts;
                                DoUpdateWorldState(WORLDSTATE_ATTEMPTS_REMAINING, HeroicAttempts);
                                if (!HeroicAttempts)
                                    if (Creature* bq = instance->GetCreature(BloodQueenLanaThelGUID))
                                        bq->DespawnOrUnsummon();

                                HandleGameObject(BloodwingSigilGUID, false);
                            }
                        }
                        break;
                    case DATA_VALITHRIA_DREAMWALKER:
                        if (state == DONE)
                            DoRespawnGameObject(ValithriaCacheGUID, 7*DAY);
                        if (state == DONE && sPoolMgr->IsSpawnedObject<Quest>(WeeklyQuestData[8].questId[instance->GetSpawnMode() & 1]))
                            instance->SummonCreature(NPC_VALITHRIA_DREAMWALKER_QUEST, ValithriaSpawnPos);
                        break;
                    case DATA_SINDRAGOSA:
                        HandleGameObject(FrostwingSigilGUID, state != DONE);
                        if (instance->IsHeroic())
                        {
                            if (state == FAIL && HeroicAttempts)
                            {
                                --HeroicAttempts;
                                DoUpdateWorldState(WORLDSTATE_ATTEMPTS_REMAINING, HeroicAttempts);
                                if (!HeroicAttempts)
                                    if (Creature* sindra = instance->GetCreature(SindragosaGUID))
                                        sindra->DespawnOrUnsummon();

                                HandleGameObject(FrostwingSigilGUID, false);
                            }
                        }
                        break;
                    case DATA_THE_LICH_KING:
                    {
                        // set the platform as active object to dramatically increase visibility range
                        // note: "active" gameobjects do not block grid unloading
                        if (GameObject* precipice = instance->GetGameObject(ArthasPrecipiceGUID))
                            precipice->setActive(state == IN_PROGRESS);
                        if (GameObject* platform = instance->GetGameObject(ArthasPlatformGUID))
                            platform->setActive(state == IN_PROGRESS);

                        if (instance->IsHeroic())
                        {
                            if (state == FAIL && HeroicAttempts)
                            {
                                --HeroicAttempts;
                                DoUpdateWorldState(WORLDSTATE_ATTEMPTS_REMAINING, HeroicAttempts);
                                if (!HeroicAttempts)
                                    if (Creature* theLichKing = instance->GetCreature(TheLichKingGUID))
                                        theLichKing->DespawnOrUnsummon();
                            }
                        }

                        if (state == DONE)
                        {
                            if (GameObject* bolvar = instance->GetGameObject(FrozenBolvarGUID))
                                bolvar->SetRespawnTime(7 * DAY);
                            if (GameObject* pillars = instance->GetGameObject(PillarsChainedGUID))
                                pillars->SetRespawnTime(7 * DAY);
                            if (GameObject* pillars = instance->GetGameObject(PillarsUnchainedGUID))
                                pillars->SetRespawnTime(7 * DAY);
                        }
                        break;
                    }
                    default:
                        break;
                 }

                 return true;
            }

            void SetData(uint32 type, uint32 data)
            {
                switch (type)
                {
                    case DATA_BONED_ACHIEVEMENT:
                        IsBonedEligible = data ? true : false;
                        break;
                    case DATA_OOZE_DANCE_ACHIEVEMENT:
                        IsOozeDanceEligible = data ? true : false;
                        break;
                    case DATA_NAUSEA_ACHIEVEMENT:
                        IsNauseaEligible = data ? true : false;
                        break;
                    case DATA_ORB_WHISPERER_ACHIEVEMENT:
                        IsOrbWhispererEligible = data ? true : false;
                        break;
                    case DATA_GUNSHIP_PORTAL_MAGES:
                        if (data == ACTION_ADD_MAGE)
                            GunshipAliveMagesNumber++;
                        else
                            GunshipAliveMagesNumber--;
                        break;
                    case DATA_GUNSHIP_EVENT:

                        switch (data)
                        {
                            case IN_PROGRESS:
                                GunshipIntroBool = true;
                                break;
                            case FAIL:
                                DoResetGunshipEvent();
                                break;
                            case DONE:
                                GunshipExtroBool = true;
                                GunshipInCombatBool = false;
                                if (TeamInInstance == ALLIANCE)
                                    DoRespawnGameObject(GunshipArmory_A_GUID, 7*DAY);
                                else
                                    DoRespawnGameObject(GunshipArmory_H_GUID, 7*DAY);
                                break;
                            default:
                                break;
                        }

                        SetBossState(DATA_GUNSHIP_EVENT, EncounterState(data));
                        break;
                    case DATA_COLDFLAME_JETS:
                        ColdflameJetsState = data;
                        break;
                    case DATA_CAPTAIN_NUMBER:
                        switch(data)
                        {
                            case (uint32)ACTION_RESURRECT_CAPTAINS:
                                CaptainCount++;
                                break;
                            case (uint32)ACTION_KILL_CAPTAIN:
                                CaptainCount--;
                                if(!CaptainCount)
                                    if (Creature* Svalna = instance->GetCreature(GetData64(DATA_SISTER_SVALNA)))
                                        Svalna->AI()->DoAction(0);
                                break;
                        }
                        break;
                    case DATA_BLOODQUEEN_TARGETS_PROC:
                        if(++BloodBolt_proc_count > 3)
                            BloodBolt_proc_count = 1;
                        break;
                    case DATA_SINDRAGOSA_FROSTWYRMS:
                    {
                        if (FrostwyrmCount == 255)
                            return;

                        if (instance->IsHeroic() && !HeroicAttempts)
                            return;

                        if (GetBossState(DATA_SINDRAGOSA) == DONE)
                            return;

                        switch (data)
                        {
                            case 0:
                                if (FrostwyrmCount)
                                {
                                    --FrostwyrmCount;
                                    if (!FrostwyrmCount)
                                    {
                                        instance->LoadGrid(SindragosaSpawnPos.GetPositionX(), SindragosaSpawnPos.GetPositionY());
                                        if (Creature* boss = instance->SummonCreature(NPC_SINDRAGOSA, SindragosaSpawnPos))
                                            boss->AI()->DoAction(ACTION_START_FROSTWYRM);
                                    }
                                }
                                break;
                            case 1:
                                ++FrostwyrmCount;
                                break;
                            default:
                                FrostwyrmCount = data;
                                break;
                        }
                        break;
                    }
                    case DATA_SPINESTALKER:
                    {
                        if (SpinestalkerTrashCount == 255)
                            return;

                        switch (data)
                        {
                            case 0:
                                if (SpinestalkerTrashCount)
                                {
                                    --SpinestalkerTrashCount;
                                    if (!SpinestalkerTrashCount)
                                        if (Creature* spinestalk = instance->GetCreature(SpinestalkerGUID))
                                            spinestalk->AI()->DoAction(ACTION_START_FROSTWYRM);
                                }
                                break;
                            case 1:
                                ++SpinestalkerTrashCount;
                                break;
                            default:
                                SpinestalkerTrashCount = data;
                                break;
                        }
                        break;
                    }
                    case DATA_RIMEFANG:
                    {
                        if (RimefangTrashCount == 255)
                            return;

                        switch (data)
                        {
                            case 0:
                                if (RimefangTrashCount)
                                {
                                    --RimefangTrashCount;
                                    if (!RimefangTrashCount)
                                        if (Creature* rime = instance->GetCreature(RimefangGUID))
                                            rime->AI()->DoAction(ACTION_START_FROSTWYRM);
                                }
                                break;
                            case 1:
                                ++RimefangTrashCount;
                                break;
                            default:
                                RimefangTrashCount = data;
                                break;
                        }
                        break;
                    }
                    case DATA_BLOOD_QUICKENING_STATE:
                    {
                        // skip if nothing changes
                        if (BloodQuickeningState == data)
                            break;

                        // 5 is the index of Blood Quickening
                        if (!sPoolMgr->IsSpawnedObject<Quest>(WeeklyQuestData[5].questId[instance->GetSpawnMode() & 1]))
                            break;

                        switch (data)
                        {
                            case IN_PROGRESS:
                                Events.ScheduleEvent(EVENT_UPDATE_EXECUTION_TIME, 60000);
                                BloodQuickeningTimer = 60000;
                                BloodQuickeningMinutes = 30;
                                DoUpdateWorldState(WORLDSTATE_SHOW_TIMER, 1);
                                DoUpdateWorldState(WORLDSTATE_EXECUTION_TIME, BloodQuickeningMinutes);
                                break;
                            case DONE:
                                Events.CancelEvent(EVENT_UPDATE_EXECUTION_TIME);
                                BloodQuickeningTimer = 0;
                                BloodQuickeningMinutes = 0;
                                DoUpdateWorldState(WORLDSTATE_SHOW_TIMER, 0);
                                break;
                            default:
                                break;
                        }

                        BloodQuickeningState = data;
                        SaveToDB();
                        break;
                    }
                    default:
                        break;
                }
            }

            bool CheckAchievementCriteriaMeet(uint32 criteria_id, Player const* /*source*/, Unit const* /*target*/, uint32 /*miscvalue1*/)
            {
                switch (criteria_id)
                {
                    case CRITERIA_BONED_10N:
                    case CRITERIA_BONED_25N:
                    case CRITERIA_BONED_10H:
                    case CRITERIA_BONED_25H:
                        return IsBonedEligible;
                    case CRITERIA_WIN_GUNSHIP_10N:
                    case CRITERIA_WIN_GUNSHIP_25N:
                    case CRITERIA_WIN_GUNSHIP_10H:
                    case CRITERIA_WIN_GUNSHIP_25H:
                        return GetBossState(DATA_GUNSHIP_EVENT) == DONE;
                    case CRITERIA_DANCES_WITH_OOZES_10N:
                    case CRITERIA_DANCES_WITH_OOZES_25N:
                    case CRITERIA_DANCES_WITH_OOZES_10H:
                    case CRITERIA_DANCES_WITH_OOZES_25H:
                        return IsOozeDanceEligible;
                    case CRITERIA_NAUSEA_10N:
                    case CRITERIA_NAUSEA_25N:
                    case CRITERIA_NAUSEA_10H:
                    case CRITERIA_NAUSEA_25H:
                        return IsNauseaEligible;
                    case CRITERIA_ORB_WHISPERER_10N:
                    case CRITERIA_ORB_WHISPERER_25N:
                    case CRITERIA_ORB_WHISPERER_10H:
                    case CRITERIA_ORB_WHISPERER_25H:
                        return IsOrbWhispererEligible;
                    // Only one criteria for both modes, need to do it like this
                    case CRITERIA_KILL_LANA_THEL_10M:
                    case CRITERIA_ONCE_BITTEN_TWICE_SHY_10N:
                    case CRITERIA_ONCE_BITTEN_TWICE_SHY_10V:
                        return instance->ToInstanceMap()->GetMaxPlayers() == 10;
                    case CRITERIA_KILL_LANA_THEL_25M:
                    case CRITERIA_ONCE_BITTEN_TWICE_SHY_25N:
                    case CRITERIA_ONCE_BITTEN_TWICE_SHY_25V:
                        return instance->ToInstanceMap()->GetMaxPlayers() == 25;
                    default:
                        break;
                }

                return false;
            }

            bool CheckRequiredBosses(uint32 bossId, Player const* player = NULL) const
            {
                if (player && player->isGameMaster())
                    return true;

                if((instance->GetPlayersCountExceptGMs()) > instance->ToInstanceMap()->GetMaxPlayers())
                    return false;

                switch (bossId)
                {
                    case DATA_THE_LICH_KING:
                        if (!CheckPlagueworks(bossId))
                            return false;
                        if (!CheckCrimsonHalls(bossId))
                            return false;
                        if (!CheckFrostwingHalls(bossId))
                            return false;
                        break;
                    case DATA_SINDRAGOSA:
                    case DATA_VALITHRIA_DREAMWALKER:
                        if (!CheckFrostwingHalls(bossId))
                            return false;
                        break;
                    case DATA_BLOOD_QUEEN_LANA_THEL:
                    case DATA_BLOOD_PRINCE_COUNCIL:
                        if (!CheckCrimsonHalls(bossId))
                            return false;
                        break;
                    case DATA_FESTERGUT:
                    case DATA_ROTFACE:
                    case DATA_PROFESSOR_PUTRICIDE:
                        if (!CheckPlagueworks(bossId))
                            return false;
                        break;
                    default:
                        break;
                }

                if (!CheckLowerSpire(bossId))
                    return false;

                return true;
            }

            bool CheckPlagueworks(uint32 bossId) const
            {
                switch (bossId)
                {
                    case DATA_THE_LICH_KING:
                        if (GetBossState(DATA_PROFESSOR_PUTRICIDE) != DONE)
                            return false;
                        // no break
                    case DATA_PROFESSOR_PUTRICIDE:
                        if (GetBossState(DATA_FESTERGUT) != DONE || GetBossState(DATA_ROTFACE) != DONE)
                            return false;
                        break;
                    default:
                        break;
                }

                return true;
            }

            bool CheckCrimsonHalls(uint32 bossId) const
            {
                switch (bossId)
                {
                    case DATA_THE_LICH_KING:
                        if (GetBossState(DATA_BLOOD_QUEEN_LANA_THEL) != DONE)
                            return false;
                        // no break
                    case DATA_BLOOD_QUEEN_LANA_THEL:
                        if (GetBossState(DATA_BLOOD_PRINCE_COUNCIL) != DONE)
                            return false;
                        break;
                    default:
                        break;
                }

                return true;
            }

            bool CheckFrostwingHalls(uint32 bossId) const
            {
                switch (bossId)
                {
                    case DATA_THE_LICH_KING:
                        if (GetBossState(DATA_SINDRAGOSA) != DONE)
                            return false;
                        // no break
                    case DATA_SINDRAGOSA:
                        if (GetBossState(DATA_VALITHRIA_DREAMWALKER) != DONE)
                            return false;
                        break;
                    default:
                        break;
                }

                return true;
            }

            bool CheckLowerSpire(uint32 bossId) const
            {
                switch (bossId)
                {
                    case DATA_DEATHBRINGER_SAURFANG:
                        if (GetBossState(DATA_LADY_DEATHWHISPER) != DONE)
                            return false;
                        // no break
                    case DATA_LADY_DEATHWHISPER:
                        if (GetBossState(DATA_LORD_MARROWGAR) != DONE)
                            return false;
                        // no break
                    case DATA_LORD_MARROWGAR:
                    default:
                        break;
                }

                return true;
            }

            void CheckPlayersNumber()
            {
                uint8 max_players_number = 0;

                switch(instance->GetDifficulty())
                {
                    case MAN10_DIFFICULTY:
                    case MAN25_DIFFICULTY:
                        max_players_number = 10;
                        break;
                    case MAN10_HEROIC_DIFFICULTY:
                    case MAN25_HEROIC_DIFFICULTY:
                        max_players_number = 25;
                        break;
                    default:
                        max_players_number = 0;
                        break;
                }

                if(instance->GetPlayersCountExceptGMs() > max_players_number)
                    DoCastSpellOnPlayers(LIGHT_S_HAMMER_TELEPORT);
            }

            std::string GetSaveData()
            {
                OUT_SAVE_INST_DATA;

                std::ostringstream saveStream;
                saveStream << "I C " << GetBossSaveData() << HeroicAttempts << " "
                    << ColdflameJetsState << " " << BloodQuickeningState << " " << BloodQuickeningMinutes;

                OUT_SAVE_INST_DATA_COMPLETE;
                return saveStream.str();
            }

            void Load(const char* str)
            {
                if (!str)
                {
                    OUT_LOAD_INST_DATA_FAIL;
                    return;
                }

                OUT_LOAD_INST_DATA(str);

                char dataHead1, dataHead2;

                std::istringstream loadStream(str);
                loadStream >> dataHead1 >> dataHead2;

                if (dataHead1 == 'I' && dataHead2 == 'C')
                {
                    for (uint32 i = 0; i < EncounterCount; ++i)
                    {
                        uint32 tmpState;
                        loadStream >> tmpState;
                        if (tmpState == IN_PROGRESS || tmpState > SPECIAL)
                            tmpState = NOT_STARTED;
                        SetBossState(i, EncounterState(tmpState));
                    }

                    loadStream >> HeroicAttempts;

                    uint32 temp = 0;
                    loadStream >> temp;
                    ColdflameJetsState = temp ? DONE : NOT_STARTED;

                    loadStream >> temp;
                    BloodQuickeningState = temp ? DONE : NOT_STARTED;   // DONE means finished (not success/fail)
                    loadStream >> BloodQuickeningMinutes;
                }
                else
                    OUT_LOAD_INST_DATA_FAIL;

                OUT_LOAD_INST_DATA_COMPLETE;
            }

            void Update(uint32 diff)
            {
                // Must be done here before the check becase DATA_GUNSHIP_EVENT will be done
                if (GunshipExtroBool)
                {
                    if (GunshipExtroTimer <= diff)
                        DoGunshipEventExtro();
                    else
                        GunshipExtroTimer -= diff;
                }

                if (BloodQuickeningState != IN_PROGRESS 
                    && GetBossState(DATA_THE_LICH_KING) != IN_PROGRESS
                    && GetBossState(DATA_GUNSHIP_EVENT) != IN_PROGRESS)
                    return;

                Events.Update(diff);

                while (uint32 eventId = Events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_UPDATE_EXECUTION_TIME:
                        {
                            if (BloodQuickeningState != IN_PROGRESS)
                                break;

                            --BloodQuickeningMinutes;
                            if (BloodQuickeningMinutes)
                            {
                                Events.ScheduleEvent(EVENT_UPDATE_EXECUTION_TIME, 60000);
                                DoUpdateWorldState(WORLDSTATE_SHOW_TIMER, 1);
                                DoUpdateWorldState(WORLDSTATE_EXECUTION_TIME, BloodQuickeningMinutes);
                            }
                            else
                            {
                                BloodQuickeningState = DONE;
                                DoUpdateWorldState(WORLDSTATE_SHOW_TIMER, 0);
                                if (Creature* bq = instance->GetCreature(BloodQueenLanaThelGUID))
                                    bq->AI()->DoAction(ACTION_KILL_MINCHAR);
                            }
                            SaveToDB();
                            break;
                        }
                        case EVENT_QUAKE_SHATTER:
                        {
                            if (GameObject* platform = instance->GetGameObject(ArthasPlatformGUID))
                                platform->SetDestructibleState(GO_DESTRUCTIBLE_DAMAGED);
                            if (GameObject* edge = instance->GetGameObject(FrozenThroneEdgeGUID))
                                edge->SetGoState(GO_STATE_ACTIVE);
                            if (GameObject* wind = instance->GetGameObject(FrozenThroneWindGUID))
                                wind->SetGoState(GO_STATE_READY);
                            if (GameObject* warning = instance->GetGameObject(FrozenThroneWarningGUID))
                                warning->SetGoState(GO_STATE_READY);
                            if (Creature* theLichKing = instance->GetCreature(TheLichKingGUID))
                                theLichKing->AI()->DoAction(ACTION_RESTORE_LIGHT);
                            break;
                        }
                        case EVENT_REBUILD_PLATFORM:
                            if (GameObject* platform = instance->GetGameObject(ArthasPlatformGUID))
                                platform->SetDestructibleState(GO_DESTRUCTIBLE_REBUILDING);
                            if (GameObject* edge = instance->GetGameObject(FrozenThroneEdgeGUID))
                                edge->SetGoState(GO_STATE_READY);
                            if (GameObject* wind = instance->GetGameObject(FrozenThroneWindGUID))
                                wind->SetGoState(GO_STATE_ACTIVE);
                            break;
                        default:
                            break;
                    }
                }

                if (GunshipIntroBool)
                {
                    if (GunshipIntroTimer <= diff)
                        DoGunshipEventIntro();
                    else
                        GunshipIntroTimer -= diff;
                }

                if (GunshipInCombatBool)
                {
                    if (GunshipCheckTimer <= diff)
                    {
                        DoCheckRespawnTime();
                        DoCheckWipe();
                        GunshipCheckTimer = 1000;
                    }
                    else
                        GunshipCheckTimer -= diff;

                    if (!GunshipFirstIceMageBool)
                    {
                        if (GunshipFirstIceMageTimer <= diff)
                        {
                            AddNewIceMage();
                            GunshipFirstIceMageBool = true;
                        }
                        else
                            GunshipFirstIceMageTimer -= diff;
                    }

                    if (!GunshipIsPortalSpawned)
                    {
                        if (GunshipSpawnPortailTimer <= diff)
                        {
                            if (DoCheckIfMustSpawnPortal())
                            {
                                GunshipIsPortalSpawned = true;
                                GunshipSpawnPortailTimer = 30000;
                            }
                            else // Sinon on repousse le check de 5 secondes
                                GunshipSpawnPortailTimer = 5000;
                        }
                        else
                            GunshipSpawnPortailTimer -= diff;
                    }
                    else
                    {
                        if (GunshipPortalTimer <= diff)
                        {
                            DoPortalEvent();
                        }
                        else
                            GunshipPortalTimer -= diff;
                    }
                }
            }

            void DoGunshipEventIntro()
            {
                Creature * FriendCommander = instance->GetCreature(GunshipcommanderGUID);
                Creature * EnnemyCommander = instance->GetCreature(GunshipennemycommanderGUID);

                if (!FriendCommander || !EnnemyCommander)
                    return;

                switch(GunshipIntroPhase)
                {
                    case 1:
                        if (TeamInInstance == ALLIANCE)
                            DoScriptText(SAY_EVENT_01_A_A, FriendCommander);
                        else
                            DoScriptText(SAY_EVENT_01_H_H, FriendCommander);

                        GunshipIntroTimer = 5000;
                        GunshipIntroPhase++;
                        GunshipResetBool = false;
                        break;
                    case 2:
                        if(m_GunshipMain)
                            m_GunshipMain->BuildStartMovePacket(instance);

                        if (TeamInInstance == ALLIANCE)
                            DoScriptText(SAY_EVENT_02_A_A, FriendCommander);
                        else
                            DoScriptText(SAY_EVENT_02_H_H, FriendCommander);

                        GunshipIntroTimer = 15000;
                        GunshipIntroPhase++;
                        break;
                    case 3:
                        if (TeamInInstance == ALLIANCE)
                            DoScriptText(SAY_EVENT_03_A_A, FriendCommander);

                        GunshipIntroTimer = 5000;
                        GunshipIntroPhase++;
                        break;
                    case 4:
                        if (TeamInInstance == ALLIANCE)
                            DoScriptText(SAY_EVENT_04_A_A, FriendCommander);
                        else
                            DoScriptText(SAY_EVENT_03_H_H, FriendCommander);

                        // Lancement du deuxième bateau
                        if(m_GunshipSecond)
                            m_GunshipSecond->BuildStartMovePacket(instance);
                        GunshipIntroTimer = 5000;
                        GunshipIntroPhase++;
                        break;
                    case 5:
                        if (TeamInInstance == ALLIANCE)
                            DoScriptText(SAY_EVENT_05_A_A, FriendCommander);

                        GunshipIntroTimer = 4000;
                        GunshipIntroPhase++;
                        break;
                    case 6:
                        if (TeamInInstance == ALLIANCE)
                            DoScriptText(SAY_EVENT_06_A_A, FriendCommander);

                        GunshipIntroTimer = 4000;
                        GunshipIntroPhase++;
                        break;
                    case 7:
                        if (TeamInInstance == ALLIANCE)
                            DoScriptText(SAY_EVENT_07_A_H, EnnemyCommander);
                        else
                            DoScriptText(SAY_EVENT_04_H_A, EnnemyCommander);

                        GunshipIntroTimer = 7000;
                        GunshipIntroPhase++;
                        break;
                    case 8:
                    {
                        if (TeamInInstance == ALLIANCE)
                            DoScriptText(SAY_EVENT_08_A_A, FriendCommander);
                        else
                            DoScriptText(SAY_EVENT_05_H_H, EnnemyCommander);

                        if(m_GunshipMain)
                            m_GunshipMain->BuildStopMovePacket(instance);

                        if(m_GunshipSecond)
                        {
                            m_GunshipSecond->BuildStopMovePacket(instance);
                            // Aucun joueur ne sera monter dessus entre temps donc pas de maj des coordonnees
                            // il faut le faire manuellement
                            if (TeamInInstance == ALLIANCE)
                                m_GunshipSecond->Relocate(-384.79f, 1989.80f, 431.56f, 0.30f);
                            else
                                m_GunshipSecond->Relocate(-435.80f, 2475.27f, 449.38f, 0.08f);

                            m_GunshipSecond->UpdateNPCPositions();
                        }

                        uint8 MAX_GUNSHIP_CANONS      = !instance->Is25ManRaid() ? 2: 4;
                        uint32 CanonsEntry = 0;
                        Position const * CanonsPosition = NULL;

                        if (TeamInInstance == ALLIANCE)
                        {
                            CanonsPosition = AllianceCanonsPosition;
                            CanonsEntry = NPC_CANON_A;
                        }
                        else
                        {
                            CanonsPosition = HordeCanonsPosition;
                            CanonsEntry = NPC_CANON_H;
                        }
                        
                        for (uint8 i = 0; i < MAX_GUNSHIP_CANONS; i++)
                        {
                            if (Creature * canon = SpawnTransportNpc(m_GunshipMain, CanonsEntry, CanonsPosition[i].GetPositionX(), CanonsPosition[i].GetPositionY(), CanonsPosition[i].GetPositionZ(), CanonsPosition[i].GetOrientation()))
                            {
                                GunshipCanons[i] = canon->GetGUID();
                            }
                        }
                        
                        GunshipIntroTimer = 2000;
                        GunshipIntroPhase++;
                        break;
                    }
                    case 9:
                        if (Creature* GunshipCommander = instance->GetCreature(GunshipcommanderGUID))
                            GunshipCommander->AI()->DoAction(ACTION_START_FIGHT);

                        if (Creature* FriendGunshipNpc = instance->GetCreature(FriendGunshipNPCGUID))
                            FriendGunshipNpc->AI()->DoAction(ACTION_ADD_ENCOUNTER_GUNSHIP);

                        if (Creature* EnnemyGunshipNpc = instance->GetCreature(EnnemyGunshipNPCGUID))
                            EnnemyGunshipNpc->AI()->DoAction(ACTION_ADD_ENCOUNTER_GUNSHIP);

                        GunshipFirstIceMageBool = false;
                        GunshipInCombatBool = true;
                        GunshipIntroBool = false;

                        break;
                    default:
                        break;
                }
            }

            bool DoCheckIfMustSpawnPortal()
            {
                // Si plus d'un mage en vie, ok, spawn portail
                if (GetData(DATA_GUNSHIP_PORTAL_MAGES))
                    return true;
                else
                    return false;
            }

            void DoPortalEvent()
            {
                Creature* commander = instance->GetCreature(GunshipcommanderGUID);
                Creature* Ennemycommander = instance->GetCreature(GunshipennemycommanderGUID);
                
                if (!commander || !Ennemycommander)
                    return;

                Position correctPosition;

                if (TeamInInstance == ALLIANCE)
                    correctPosition = HordePortalPosition;
                else
                    correctPosition = AllyPortalPosition;
                
                //float x = Transport::getX(correctPosition.GetPositionX(), correctPosition.GetPositionY(), m_GunshipMain);
                //float y = Transport::getY(correctPosition.GetPositionX(), correctPosition.GetPositionY(), m_GunshipMain);
                //float z = Transport::getZ(correctPosition.GetPositionZ(), m_GunshipMain);
                //float o = correctPosition.GetOrientation();

                float x = correctPosition.GetPositionX();
                float y = correctPosition.GetPositionY();
                float z = correctPosition.GetPositionZ();
                float o = correctPosition.GetOrientation();

                if (!DoCheckIfMustSpawnPortal())
                {
                    // Si les deux sont morts entre temps, on close le portail
                    GunshipPortalPhase = 6;
                }

                uint32 npcToAdd = 0;

                switch (GunshipPortalPhase)
                {
                    case 1:
                    {
                        Creature * portal = m_GunshipMain->AddNPCPassengerCreature(0, NPC_GUNSHIP_PORTAL, x, y, z, o);
                        //Creature * portal = commander->SummonCreature(NPC_GUNSHIP_PORTAL, x, y, z, o);

                        if (portal)
                        {
                            PortalGUID = portal->GetGUID();
                            GunshipTempList.push_back(portal->GetGUID());
                            portal->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PC | UNIT_FLAG_NOT_SELECTABLE);
                        }
                        
                        if (TeamInInstance == ALLIANCE)
                            DoScriptText(SAY_EVENT_FIGHT_START_A_H, Ennemycommander);
                        else
                            DoScriptText(SAY_EVENT_FIGHT_START_H_A, Ennemycommander);

                        // Set cast visual
                        for (uint8 i = 0; i < 2; i++)
                            if (Creature * pMage = instance->GetCreature(GunshipMages[i]))
                                pMage->CastSpell(pMage, 75427);

                        if (Creature* FriendGunshipNpc = instance->GetCreature(FriendGunshipNPCGUID))
                            FriendGunshipNpc->AI()->DoAction(ACTION_ADD_ENCOUNTER_GUNSHIP);

                        if (Creature* EnnemyGunshipNpc = instance->GetCreature(EnnemyGunshipNPCGUID))
                            EnnemyGunshipNpc->AI()->DoAction(ACTION_ADD_ENCOUNTER_GUNSHIP);

                        GunshipPortalTimer = 5000;
                        GunshipPortalPhase++;
                        break;
                    }
                    case 2:
                    case 3:
                    case 4:
                    {
                        if (TeamInInstance == ALLIANCE)
                            npcToAdd = NPC_SOLDAT_H;
                        else
                            npcToAdd = NPC_SOLDAT_A;

                        GunshipPortalTimer = 2500;
                        GunshipPortalPhase++;
                        break;
                    }
                    case 5:
                    {
                        if (TeamInInstance == ALLIANCE)
                            npcToAdd = NPC_SERGENT_H;
                        else
                            npcToAdd = NPC_SERGENT_A;

                        GunshipPortalTimer = 5000;
                        GunshipPortalPhase++;
                        break;
                    }
                    case 6:
                    {
                        if (Creature * pCreature = instance->GetCreature(PortalGUID))
                            pCreature->RemoveFromWorld();
                        
                        // Remove cast visual
                        for (uint8 i = 0; i < 2; i++)
                            if (Creature * pMage = instance->GetCreature(GunshipMages[i]))
                                pMage->RemoveAurasDueToSpell(75427);

                        GunshipPortalTimer = 100;
                        GunshipPortalPhase = 1;
                        GunshipSpawnPortailTimer = 30000;
                        GunshipIsPortalSpawned = false;
                        break;
                    }
                }

                if (npcToAdd)
                {
                    if (Creature* soldier = m_GunshipMain->AddNPCPassengerCreature(0, npcToAdd, x, y, z, o))
                    //if (Creature* soldier = commander->SummonCreature(npcToAdd, x, y, z, o))
                    {
                        Transport * Friendtransport = ObjectAccessor::GetTransport(*commander, FriendGunshipGUID);

                        if (!Friendtransport)
                            return;

                        std::set<Player*> pSet = Friendtransport->GetPassengers();

                        Unit * pTarget = NULL;

                        if (!pSet.empty())
                        {
                            if (urand(0, 1))
                                pTarget = *pSet.begin();
                            else
                                pTarget = commander;
                        }
                        else
                            pTarget = commander;

                        if (!pTarget)
                            return;

                        if (soldier->AI())
                            soldier->AI()->AttackStart(pTarget);

                        GunshipTempList.push_back(soldier->GetGUID());
                    }
                }
            }

            void DoGunshipEventExtro()
            {
                switch(GunshipExtroPhase)
                {
                    case 1:
                    {
                        if(m_GunshipSecond)
                            m_GunshipSecond->BuildStartMovePacket(instance);

                        if (Creature* EnnemyCommander = instance->GetCreature(GunshipennemycommanderGUID))
                        {
                            if (TeamInInstance == ALLIANCE)
                                DoScriptText(SAY_EVENT_VICTORY_A_H, EnnemyCommander);
                            else
                                DoScriptText(SAY_EVENT_VICTORY_H_A, EnnemyCommander);
                        }

                        if (Creature* FriendGunshipNpc = instance->GetCreature(FriendGunshipNPCGUID))
                            FriendGunshipNpc->AI()->DoAction(ACTION_REMOVE_ENCOUNTER_GUNSHIP);

                        if (Creature* EnnemyGunshipNpc = instance->GetCreature(EnnemyGunshipNPCGUID))
                            EnnemyGunshipNpc->AI()->DoAction(ACTION_REMOVE_ENCOUNTER_GUNSHIP);

                        for (uint8 i = 0; i < 4; i++)
                        {
                            if (Creature* canon = instance->GetCreature(GunshipCanons[i]))
                            {
                                canon->GetVehicleKit()->RemoveAllPassengers();
                                canon->RemoveFromWorld();
                            }
                        }

                        
                        const Map::PlayerList &PlayerList = instance->GetPlayers();
                        if (!PlayerList.isEmpty())
                            for (Map::PlayerList::const_iterator i = PlayerList.begin(); i != PlayerList.end(); ++i)
                                if (Player* player = i->getSource())
                                {
                                    player->DestroyItemCount(49278, 1, true, false); // delete le jetpack
                                    player->CombatStop();
                                    player->getHostileRefManager().deleteReferences();
                                }

                        // Despawn Sergents & soldats
                        for (std::list<uint64>::iterator Itr = GunshipTempList.begin(); Itr != GunshipTempList.end(); Itr++)
                            if (Creature * soldier = instance->GetCreature(*Itr))
                                soldier->Kill(soldier);

                        bool CanHaveBoardingAchievement = true;

                        std::map<uint64, uint8>::iterator Itr;
                        for (Itr = GunshipBoardCount.begin(); Itr != GunshipBoardCount.end(); Itr++)
                        {
                            // Le joueur est monté dessus plus de 2 fois
                            if (Itr->second > 2)
                                CanHaveBoardingAchievement = false;
                        }

                        GunshipBoardCount.clear();

                        if (CanHaveBoardingAchievement)
                        {
                            uint32 achievementId = instance->Is25ManRaid() ? I_M_ON_A_BOAT_25 : I_M_ON_A_BOAT_10;
                            //DoCompleteAchievement(achievementId);
                        }

                        DoCastSpellOnPlayers(72959); // Haut-Faits (dummy)
                        GunshipTempList.clear();

                        if (Creature * commander = instance->GetCreature(GunshipcommanderGUID))
                        {
                            if (Transport * Ennemytransport = ObjectAccessor::GetTransport(*commander, EnnemyGunshipGUID))
                            {
                                std::set<Player*>::iterator Itr;
                                std::set<Player*> pSet = Ennemytransport->GetPassengers();

                                for (Itr = pSet.begin(); Itr != pSet.end(); Itr++)
                                    (*Itr)->NearTeleportTo(-560.35f, 2202.73f, 539.28f, 6.25f);

                                //Ennemytransport->RemoveAllCreaturePassengers();

                                for (uint8 i = 0; i < 7; i++)
                                {
                                    float x = 0.0f, y = 0.0f, z = 0.0f;

                                    if (TeamInInstance == ALLIANCE)
                                    {
                                        x = HordeFlammePosition[i].GetPositionX();
                                        y = HordeFlammePosition[i].GetPositionY();
                                        z = HordeFlammePosition[i].GetPositionZ();
                                    }
                                    else
                                    {
                                        x = AllianceFlammePosition[i].GetPositionX();
                                        y = AllianceFlammePosition[i].GetPositionY();
                                        z = AllianceFlammePosition[i].GetPositionZ();
                                    }

                                    if (Creature * fire = SpawnTransportNpc(Ennemytransport, NPC_FIRE_TRIGGER, x, y, z))
                                    {
                                        fire->AddAura(SPELL_FIRE_VISUAL, fire);
                                    }
                                }
                            }
                        }
                        
                        GunshipExtroPhase++;
                        GunshipExtroTimer = 3000;
                        break;
                    }
                    case 2:
                        if (Creature* Commander = instance->GetCreature(GunshipcommanderGUID))
                        {
                            if (TeamInInstance == ALLIANCE)
                                DoScriptText(SAY_EVENT_VICTORY_A_A, Commander);
                            else
                                DoScriptText(SAY_EVENT_VICTORY_H_H, Commander);
                        }

                        if(m_GunshipMain)
                            m_GunshipMain->BuildStartMovePacket(instance);

                        GunshipExtroPhase++;
                        GunshipExtroTimer = 10000;
                        break;
                    case 3:
                        if(m_GunshipMain)
                            m_GunshipMain->BuildStopMovePacket(instance);
                        if(m_GunshipSecond)
                        {
                            m_GunshipSecond->BuildStopMovePacket(instance);
                            m_GunshipSecond->SetPhaseMask(1024, true); // Le fait disparaitre
                        }

                        GunshipExtroBool = false;
                        break;
                }
            }

            void DoCheckRespawnTime()
            {
                std::map<uint32, TypecreatureEntryAndGuid>::iterator Itr;
                
                Creature* EnnemyCommander = instance->GetCreature(GunshipennemycommanderGUID);

                if (!EnnemyCommander)
                    return;

                for (Itr = GunshipRespawnMap.begin(); Itr != GunshipRespawnMap.end();)
                {
                    if (getMSTime() >= Itr->first)
                    {
                        if (Itr->second.entry == NPC_MAGE_A ||
                            Itr->second.entry == NPC_MAGE_H)
                        {
                            Creature * c = instance->GetCreature(Itr->second.guid);

                            // Seul ceux qui s'occupent du givre sont removed a leur mort et ne doivent pas etre respawn
                            if (!c)
                            {
                                if (TeamInInstance == ALLIANCE)
                                    DoScriptText(SAY_EVENT_FIGHT_RESPAWN_ICE_MAGE_A_H, EnnemyCommander);
                                else
                                    DoScriptText(SAY_EVENT_FIGHT_RESPAWN_ICE_MAGE_H_A, EnnemyCommander);
                                AddNewIceMage();
                                GunshipRespawnMap.erase(Itr++);

                                continue;
                            }
                        }

                        if (Creature * c = instance->GetCreature(Itr->second.guid))
                        {
                            switch (Itr->second.entry)
                            {
                                case NPC_ARTILLEUR_H:
                                case NPC_ARTILLEUR_A:
                                    if (TeamInInstance == ALLIANCE)
                                        DoScriptText(SAY_EVENT_FIGHT_RESPAWN_ARTILLEUR_A_H, EnnemyCommander);
                                    else
                                        DoScriptText(SAY_EVENT_FIGHT_RESPAWN_ARTILLEUR_H_A, EnnemyCommander);
                                    break;
                                case NPC_TIREUR_H:
                                case NPC_TIREUR_A:
                                    if (TeamInInstance == ALLIANCE)
                                        DoScriptText(SAY_EVENT_FIGHT_RESPAWN_TIREUR_A_H, EnnemyCommander);
                                    else
                                        DoScriptText(SAY_EVENT_FIGHT_RESPAWN_TIREUR_H_A, EnnemyCommander);
                                    break;
                            }
                            c->Respawn();
                        }
                        
                        GunshipRespawnMap.erase(Itr++);
                    }
                    else
                        Itr++;
                }
            }

            void DoCheckWipe()
            {
                bool wipe = true;

                const Map::PlayerList &PlayerList = instance->GetPlayers();
                if (!PlayerList.isEmpty())
                    for (Map::PlayerList::const_iterator i = PlayerList.begin(); i != PlayerList.end(); ++i)
                        if (Player* player = i->getSource())
                            if (player->isAlive())
                                wipe = false;

                if (wipe)
                    SetData(DATA_GUNSHIP_EVENT, FAIL);
            }

            void AddNewIceMage()
            {
                Creature * commander = instance->GetCreature(GunshipcommanderGUID);

                if (!commander)
                    return;

                Transport * Ennemytransport = ObjectAccessor::GetTransport(*commander, EnnemyGunshipGUID);

                if (!Ennemytransport)
                    return;

                uint32 NewMageEntry = 0;
                float x, y, z;

                if (commander->GetEntry() == NPC_MURADIN_GUNSHIP)
                {
                    NewMageEntry = NPC_MAGE_H;
                    x = HordeIceMageSpawnPosition.GetPositionX();
                    y = HordeIceMageSpawnPosition.GetPositionY();
                    z = HordeIceMageSpawnPosition.GetPositionZ();
                }
                else
                {
                    NewMageEntry = NPC_MAGE_A;
                    x = AllyIceMageSpawnPosition.GetPositionX();
                    y = AllyIceMageSpawnPosition.GetPositionY();
                    z = AllyIceMageSpawnPosition.GetPositionZ();
                }

                std::list<Unit*>::iterator Itr;

                if (GetData(DATA_GUNSHIP_ICE_CANON_EVENT) == IN_PROGRESS)
                    return;

                if (Creature * mage = SpawnTransportNpc(Ennemytransport, NewMageEntry, x, y, z))
                {
                    mage->AI()->DoAction(ACTION_SET_CANON_SPELL);
                    GunshipTempList.push_back(mage->GetGUID());
                }
            }

            void DoResetGunshipEvent()
            {
                if (GunshipResetBool)
                    return;

                const Map::PlayerList &PlayerList = instance->GetPlayers();
                if (!PlayerList.isEmpty())
                {
                    for (Map::PlayerList::const_iterator i = PlayerList.begin(); i != PlayerList.end(); ++i)
                    {
                        if (Player* player = i->getSource())
                        {
                            player->Kill(player);
                        }
                    }
                }

                for (uint8 i = 0; i < 4; i++)
                {
                    if (Creature * canon = instance->GetCreature(GunshipCanons[i]))
                    {
                        canon->GetVehicleKit()->RemoveAllPassengers();
                        canon->RemoveFromWorld();
                    }
                }

                if (Creature* c = instance->GetCreature(FriendGunshipNPCGUID))
                {
                    if (TeamInInstance == ALLIANCE)
                    {
                        if (Transport * Friendtransport = ObjectAccessor::GetTransport(*c, FriendGunshipGUID))
                            Friendtransport->Relocate(-459.10f, 2466.31f, 169.79f);
                    
                        if (Transport * Ennemytransport = ObjectAccessor::GetTransport(*c, EnnemyGunshipGUID))
                            Ennemytransport->Relocate(-69.12f, 1992.20f, 584.49f);
                    }
                    else
                    {
                        if (Transport * Friendtransport = ObjectAccessor::GetTransport(*c, FriendGunshipGUID))
                            Friendtransport->Relocate(-447.69f, 1916.79f, 180.46f);
                    
                        if (Transport * Ennemytransport = ObjectAccessor::GetTransport(*c, EnnemyGunshipGUID))
                            Ennemytransport->Relocate(-94.64f, 2609.88f, 431.07f);
                    }
                }

                if (Creature* FriendGunshipCommander = instance->GetCreature(GunshipcommanderGUID))
                {
                    FriendGunshipCommander->AI()->DoAction(ACTION_WIPE);
                    FriendGunshipCommander->CastSpell(FriendGunshipCommander, 76010, true); // NON-BLIZZLIKE, visuel d'explosion
                }

                if (Creature* FriendGunshipNpc = instance->GetCreature(FriendGunshipNPCGUID))
                    FriendGunshipNpc->SetHealth(FriendGunshipNpc->GetMaxHealth());

                if (Creature* EnnemyGunshipNpc = instance->GetCreature(EnnemyGunshipNPCGUID))
                    EnnemyGunshipNpc->SetHealth(EnnemyGunshipNpc->GetMaxHealth());

                for (std::list<uint64>::iterator Itr = GunshipTempList.begin(); Itr != GunshipTempList.end(); Itr++)
                    if (Unit* tempCreature = instance->GetCreature(*Itr))
                         tempCreature->RemoveFromWorld();

                GunshipTempList.clear();
                GunshipBoardCount.clear();

                GunshipIntroBool = false;
                GunshipInCombatBool = false;
                GunshipExtroBool = false;
                GunshipFirstIceMageBool = true;
                GunshipCheckTimer = 1000;
                GunshipFirstIceMageTimer = 40000;
                GunshipIntroPhase = 1;
                GunshipIntroTimer = 100;
                GunshipExtroPhase = 1;
                GunshipExtroTimer = 100;
                GunshipPortalTimer = 100;
                GunshipPortalPhase = 1;

                GunshipIsPortalSpawned = false;
                GunshipSpawnPortailTimer = 30000;

                GunshipResetBool = true;
                PortalGUID = 0;
            }

            void ProcessEvent(WorldObject* /*source*/, uint32 eventId)
            {
                switch (eventId)
                {
                    case EVENT_QUAKE:
                        if (GameObject* warning = instance->GetGameObject(FrozenThroneWarningGUID))
                            warning->SetGoState(GO_STATE_ACTIVE);
                        Events.ScheduleEvent(EVENT_QUAKE_SHATTER, 5000);
                        break;
                    case EVENT_SECOND_REMORSELESS_WINTER:
                        if (GameObject* platform = instance->GetGameObject(ArthasPlatformGUID))
                        {
                            platform->SetDestructibleState(GO_DESTRUCTIBLE_DESTROYED);
                            Events.ScheduleEvent(EVENT_REBUILD_PLATFORM, 1500);
                        }
                        break;
                    case EVENT_TELEPORT_TO_FROSMOURNE: // Harvest Soul (normal mode)
                        if (Creature* terenas = instance->SummonCreature(NPC_TERENAS_MENETHIL_FROSTMOURNE, TerenasSpawn, NULL, 63000))
                        {
                            terenas->AI()->DoAction(ACTION_FROSTMOURNE_INTRO);
                            std::list<Creature*> triggers;
                            GetCreatureListWithEntryInGrid(triggers, terenas, NPC_WORLD_TRIGGER_INFINITE_AOI, 100.0f);
                            if (!triggers.empty())
                            {
                                triggers.sort(JadeCore::ObjectDistanceOrderPred(terenas, false));
                                Unit* visual = triggers.front();
                                visual->CastSpell(visual, SPELL_FROSTMOURNE_TELEPORT_VISUAL, true);
                            }

                            if (Creature* warden = instance->SummonCreature(NPC_SPIRIT_WARDEN, SpiritWardenSpawn, NULL, 63000))
                            {
                                terenas->AI()->AttackStart(warden);
                                warden->AddThreat(terenas, 300000.0f);
                            }
                        }
                        break;
                }
            }

        protected:
            uint64 LordMarrowgarGUID;

            EventMap Events;
            std::set<uint64> ColdflameJetGUIDs;
            uint64 LadyDeathwisperElevatorGUID;
            uint64 DeathbringerSaurfangGUID;
            uint64 DeathbringerSaurfangDoorGUID;
            uint64 DeathbringerSaurfangEventGUID;   // Muradin Bronzebeard or High Overlord Saurfang
            uint64 DeathbringersCacheGUID;
            uint64 SaurfangTeleportGUID;
            
            uint64 FriendGunshipGUID;
            uint64 EnnemyGunshipGUID;
            uint64 FriendGunshipNPCGUID;
            uint64 EnnemyGunshipNPCGUID;
            uint64 GunshipcommanderGUID;
            uint64 GunshipennemycommanderGUID;
            uint64 GunshipCanons[4];
            uint64 GunshipArtilleurs[4];
            uint64 GunshipTireurs[8];
            uint64 GunshipMages[2];
            
            std::map<uint32, TypecreatureEntryAndGuid> GunshipRespawnMap;
            std::list<uint64> GunshipTempList;
            std::map<uint64, uint8> GunshipBoardCount;
            
            bool GunshipIntroBool;
            bool GunshipInCombatBool;
            bool GunshipExtroBool;
            bool GunshipResetBool;
            bool GunshipFirstIceMageBool;
            uint32 GunshipIntroTimer;
            uint8 GunshipIntroPhase;
            uint32 GunshipExtroTimer;
            uint8 GunshipExtroPhase;

            uint32 GunshipPortalTimer;
            uint8 GunshipPortalPhase;

            uint64 PortalGUID;
            uint64 GunshipArmory_A_GUID;
            uint64 GunshipArmory_H_GUID;

            bool GunshipIsPortalSpawned;
            uint32 GunshipSpawnPortailTimer;
            
            uint8 GunshipAliveMagesNumber;
            
            uint32 GunshipCheckTimer;
            uint32 GunshipFirstIceMageTimer;

            uint64 PlagueSigilGUID;
            uint64 BloodwingSigilGUID;
            uint64 FrostwingSigilGUID;
            uint64 PutricidePipeGUIDs[2];
            uint64 PutricideGateGUIDs[2];
            uint64 PutricideCollisionGUID;
            uint64 FestergutGUID;
            uint64 RotfaceGUID;
            uint64 ProfessorPutricideGUID;
            uint64 PutricideTableGUID;
            uint64 BloodCouncilGUIDs[3];
            uint64 BloodCouncilControllerGUID;
            uint64 BloodQueenLanaThelGUID;
            uint64 CrokScourgebaneGUID;
            uint64 CrokCaptainGUIDs[4];
            uint8  CaptainCount;
            uint64 SisterSvalnaGUID;
            uint64 ValithriaDreamwalkerGUID;
            uint64 ValithriaCacheGUID;
            uint64 ValithriaLichKingGUID;
            uint64 ValithriaTriggerGUID;
            uint64 SindragosaGUID;
            uint64 SpinestalkerGUID;
            uint64 RimefangGUID;
            uint64 TheLichKingGUID;
            uint32 TeamInInstance;
            uint32 BloodQuickeningTimer;
            uint32 ColdflameJetsState;
            uint32 FrostwyrmCount;
            uint32 SpinestalkerTrashCount;
            uint32 RimefangTrashCount;
            uint32 BloodQuickeningState;
            uint32 HeroicAttempts;
            uint16 BloodQuickeningMinutes;
            uint64 HighlordTirionFordringGUID;
            uint64 TerenasMenethilGUID;
            uint64 ArthasPlatformGUID;
            uint64 ArthasPrecipiceGUID;
            uint64 FrozenThroneEdgeGUID;
            uint64 FrozenThroneWindGUID;
            uint64 FrozenThroneWarningGUID;
            uint64 FrozenBolvarGUID;
            uint64 PillarsChainedGUID;
            uint64 PillarsUnchainedGUID;
            bool IsBonedEligible;
            bool IsOozeDanceEligible;
            bool IsNauseaEligible;
            bool IsOrbWhispererEligible;

            bool AreGunshipsSpawned;
            Transport *m_GunshipMain, *m_GunshipSecond, *m_ZeppelinHorde;
            uint32 m_GunshipMainHP, m_GunshipSecondHP;
                
            uint64 m_blood_doorGUID;
            uint64 m_ice_doorGUID;

            uint8 BloodBolt_proc_count;
            std::list<uint64> BloodQueen_BloodBolt_TargetsList;
        };

        InstanceScript* GetInstanceScript(InstanceMap* map) const
        {
            return new instance_icecrown_citadel_InstanceMapScript(map);
        }
};

uint32 GetPhase(const EventMap &em)
{
    switch (em.GetPhaseMask())
    {
        case 0x01: return 0;
        case 0x02: return 1;
        case 0x04: return 2;
        case 0x08: return 3;
        case 0x10: return 4;
        case 0x20: return 5;
        case 0x40: return 6;
        case 0x80: return 7;
        default:
            return 0;
    }
}

void LeaveOnlyPlayers(std::list<Unit*> &targets)
{
    for (std::list<Unit*>::iterator itr = targets.begin(); itr != targets.end();)
    {
        if ((*itr)->GetTypeId() != TYPEID_PLAYER)
            targets.erase(itr++);
        else
            ++itr;
    }

    std::list<Unit*>::iterator itr = targets.begin();
    std::advance(itr, urand(0, targets.size()-1));
    Unit* target = *itr;
    targets.clear();
    targets.push_back(target);
}

class TeleportToFrozenThrone : public BasicEvent
{
    public:
        TeleportToFrozenThrone(Player *player, uint8 attempts): pPlayer(player), attemptsLeft(attempts) { }

        bool Execute(uint64 /*eventTime*/, uint32 /*updateTime*/)
        {
            pPlayer->CastSpell(pPlayer, FROZEN_THRONE_TELEPORT, true);
            if (--attemptsLeft)
                pPlayer->m_Events.AddEvent(new TeleportToFrozenThrone(pPlayer, attemptsLeft), pPlayer->m_Events.CalculateTime(uint64(1500)));
            return true;
        }
    private:
        Player *pPlayer;
        uint8 attemptsLeft;
};

void TeleportPlayerToFrozenThrone(Player *player)
{
    player->m_Events.AddEvent(new TeleportToFrozenThrone(player, 2), player->m_Events.CalculateTime(uint64(5000)));
}

TPlayerList GetPlayersInTheMap(Map *pMap)
{
    TPlayerList players;
    const Map::PlayerList &PlayerList = pMap->GetPlayers();
    if (!PlayerList.isEmpty())
        for (Map::PlayerList::const_iterator i = PlayerList.begin(); i != PlayerList.end(); ++i)
            if (Player* player = i->getSource())
                players.push_back(player);
    return players;
}

TPlayerList GetAttackablePlayersInTheMap(Map *pMap)
{
    TPlayerList players = GetPlayersInTheMap(pMap);
    for (TPlayerList::iterator it = players.begin(); it != players.end();)
        if (!(*it)->isTargetableForAttack())
            players.erase(it++);
        else
            ++it;
    return players;
}

void UnsummonSpecificCreaturesNearby(Creature* ref, uint32 entry, float radius)
{
    std::list<Creature*> allCreaturesWithEntry;
    GetCreatureListWithEntryInGrid(allCreaturesWithEntry, ref, entry, radius);

    for(std::list<Creature*>::iterator itr = allCreaturesWithEntry.begin(); itr != allCreaturesWithEntry.end(); ++itr)
    {
        Creature* candidate = *itr;

        if (!candidate)
            continue;

        if (TempSummon* summon = candidate->ToTempSummon())
            summon->DespawnOrUnsummon();
    }
}

void AddSC_instance_icecrown_citadel()
{
    new instance_icecrown_citadel();
}
