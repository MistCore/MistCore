/*
 * Copyright (C) 2008-2010 Trinity <http://www.trinitycore.org/>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include "ScriptPCH.h"
#include "icecrown_citadel.h"
#include "MapManager.h"
#include "Transport.h"
#include "Unit.h"
#include "Log.h"
#include "Vehicle.h"
#include "Spell.h"

/* TODO :
Poix Ardente

Liste créatures :
NEUTRE :
    37227 - Portail de téléportation

ALLIANCE :
    37540 - Le brise-ciel (creature)
    36948 - Muradin
    36838 - Canon
    36969 - Fusilier
    37116 - Sorcier
    36961 - Sergent
    36978 - Artilleur

HORDE :
    37215 - Marteau d'Orgrim (creature)
    36939 - Saurcroc
    36839 - Canon
    36968 - Lanceur de Hache
    37117 - Mage de bataille Kor'Kron
    36960 - Sergent
    36982 - Missilier

   Liste sorts :
   formats :
   1 : unique
   2 : Normal - HM

-- Sorts partagés
71335 - Poix ardente

71188 - Experimenté
71193 - Vétéran
71195 - Elite

-- Commandants
15284 - Enchainement (cac)
70309 - Lancer tranchant (distance)

-- Sorts Lanceur/Fusilier
70162 - 72567 - Tir
//Poix ardente

-- Sorts Sorcier/Mage de bataille
69705 - En dessous de zéro

-- Sorts Soldat-Artilleur/Missilier
69679 - Artillerie à roquettes

-- Sorts Sergents
69651 - 72570 - Frappe de lésion
69647 - 72537 - Résolution désespérée
69652 - Tempête de lames
//Poix ardente

*/

enum Configs
{
    CONFIG_RESPAWN_TIMER                = 30000,
    CONFIG_RESPAWN_CHECK_TIMER          = 2000,
    CONFIG_RANK_TIMER                   = 60000,

    // Commandant
    CONFIG_CLEAVE_TIMER                 = 6000,
    CONFIG_THROW_TIMER                  = 12000,
    CONFIG_MAX_BATTLE_FURY_TIMER        = 1000,

    // Tireurs
    CONFIG_TIR_TIMER                    = 5000,

    // Artilleurs
    CONFIG_MISSILE_TIMER                = 12000,

    // Portail
    CONFIG_RESPAWN_VISUAL_PORTAL_TIMER  = 60000,
    CONFIG_SPAWN_FROST_MAGE_TIMER       = 90000,
    CONFIG_SPAWN_SOLDIER_TIMER          = 5000,

    // Soldats
    CONFIG_FRAPPE_TIMER                 = 10000,
    CONFIG_RESOLUTION_TIMER             = 15000,
    CONFIG_TEMPETE_LAME_TIMER           = 30000,
    CONFIG_POIX_TIMER                   = 5000,
};

enum Npc_Ranks
{
    Start       = 0,
    Experimente = 1,
    Veteran     = 2,
    Elite       = 3,
};

enum Gunships
{
    GUNSHIP_FRIEND = 0,
    GUNSHIP_ENNEMY = 1,
};

enum RespawnListEnums
{
    RESPAWN_LIST_ENTRY = 0,
    RESPAWN_LIST_TIMER = 1,
};

enum Spells
{
    SPELL_EXPERIMENTE               = 71188,
    SPELL_VETERAN                   = 71193,
    SPELL_ELITE                     = 71195,

    //Transports
    SPELL_ON_TRANSPORT_A            = 70120,
    SPELL_ON_TRANSPORT_H            = 70121,

    //Commandants
    SPELL_CLEAVE                    = 15284,
    SPELL_RENDING_THROW             = 70309,

    //Lanceur de Hache / Fusillier
    //SPELL_TIR                    = 70162 - 72567

    //Artiller
    SPELL_MISSILE                   = 69679,
    SPELL_MISSILE_VISUAL            = 71371,

    //Portail
    SPELL_INVOCATION_VISUEL         = 66899,

    //Sergent
    //SPELL_FRAPPE_LESION           = 69651 - 72570
    //SPELL_RESOLUTION_DESESPEREE   = 69647 - 72537
    SPELL_TEMPETE_DE_LAME           = 69652,
    SPELL_POIX_ARDENTE              = 71335,

    //Mage
    SPELL_RAYON_VISUEL              = 72735, // Not Blizzlike
    SPELL_BEHIND_ZERO               = 69705,

    //Canon
    SPELL_CANON_FIRE                = 69400,

    //Divers
    SPELL_TELEPORT_VISUAL           = 64446,
    SPELL_CANALISATION_VISUAL       = 75427,
};

enum Events_Gunship
{
    EVENT_CLEAVE                = 1,
    EVENT_THROW                 = 2,

    EVENT_TIR                   = 3,

    EVENT_FRAPPE_LESION         = 4,
    EVENT_RESOLUTION_DESESPEREE = 5,
    EVENT_TEMPETE_DE_LAME       = 6,
    EVENT_POIX_ARDENTE          = 7,

    EVENT_MISSILE               = 8,
    EVENT_MISSILE_VISUAL        = 9,
    EVENT_MISSILE_DAMAGE_TRANS  = 10,

    EVENT_SPAWN_FROST_MAGE      = 11,
    EVENT_RESPAWN_VISUAL_PORTAL = 12,
    EVENT_SPAWN_SOLDIERS        = 13,
};

enum MovePoints
{
    MOVE_ICE_MAGE               = 1,
};

Position const AllyIceMageSpawnPosition     = {4.94889f,  0.074566f, 20.7875f, 6.26172f};
Position const AllyIceMageCastPosition      = {-17.6053f, 0.229648f, 20.8197f, 3.13584f};
Position const AllyPortalPosition           = {1.91465f,  0.128489f, 34.5151f, 6.28182f};

Position const HordeIceMageSpawnPosition    = {33.8192f, -0.219071f, 36.3922f, 3.15252f};
Position const HordeIceMageCastPosition     = {2.15674f, 0.027226f, 34.5214f, 1.52754f};
Position const HordePortalPosition          = {-17.5156f, -0.097261f, 20.8184f, 6.27579f};

Position const AllianceCanonsPosition[4] =
{
    {-3.35344f, -23.9042f, 21.6553f, 4.94481f},
    {-38.3162f, -22.0068f, 22.0963f, 4.94481f},
    {-26.673f,  -22.8883f, 21.6389f, 4.94481f},
    {-15.4007f, -23.5381f, 21.6143f, 4.94481f},
};

Position const HordeCanonsPosition[4] =
{
    {10.7665f,  30.2526f, 35.7623f, 1.56651f},
    {-6.74033f, 31.3597f, 34.5273f, 1.56651f},
    {-19.5026f, 30.1697f, 34.2795f, 1.56651f},
    {22.1048f,  29.2354f, 36.3666f, 1.56651f},
};

Position const HordeFlammePosition[7] =
{
    {17.858f, 15.8014f, 35.5001f, 1.55576f},
    {-5.76047f, 18.4625f, 34.0726f, 1.55576f},
    {9.97011f, 1.49712f, 34.848f, 5.2008f},
    {21.3401f, -18.1582f, 35.7324f, 5.35003f},
    {-10.2053f, -0.469428f, 41.6866f, 2.83282f},
    {-5.41809f, -16.4467f, 34.0703f, 4.68401f},
    {38.742f, 5.82782f, 37.0774f, 2.61134f}
};

Position const AllianceFlammePosition[7] =
{
    {-7.11019f, -23.7713f, 21.6428f, 1.53856f},
    {-29.7886f, -19.3212f, 21.2061f, 4.02827f},
    {-5.0532f, 4.45115f, 20.4552f, 5.55587f},
    {-24.7823f, 9.31166f, 20.4699f, 1.05475f},
    {-32.7114f, -2.20607f, 20.7931f, 2.24699f},
    {-14.1884f, -8.7113f, 20.4231f, 3.03396f},
    {1.84347f, -10.8836f, 20.4659f, 2.79834f}
};

#define IS_TEAM_ALLIANCE  pInstance->GetData(DATA_TEAM_IN_INSTANCE) == ALLIANCE

#define SPELL_TIR_A                 RAID_MODE<uint32>(70162, 72567)
#define SPELL_TIR_H                 RAID_MODE<uint32>(70161, 72540)
#define SPELL_TIR                   (IS_TEAM_ALLIANCE ? SPELL_TIR_H : SPELL_TIR_A)

#define SPELL_BATTLE_FURY           RAID_MODE<uint32>(69638, 72306, 72307, 72308)
#define SPELL_FRAPPE_LESION         RAID_MODE<uint32>(69651, 72570)
#define SPELL_RESOLUTION_DESESPEREE RAID_MODE<uint32>(69647, 72537)

#define NPC_GUNSHIP_FRIEND          (IS_TEAM_ALLIANCE ? NPC_GUNSHIP_A : NPC_GUNSHIP_H)
#define NPC_GUNSHIP_ENNEMY          (IS_TEAM_ALLIANCE ? NPC_GUNSHIP_H : NPC_GUNSHIP_A)

#define NPC_CANON                   (IS_TEAM_ALLIANCE ? NPC_CANON_A : NPC_CANON_H)

#define NPC_TIREUR                  (IS_TEAM_ALLIANCE ? NPC_TIREUR_H : NPC_TIREUR_A)
#define NPC_ARTILLEUR               (IS_TEAM_ALLIANCE ? NPC_ARTILLEUR_H : NPC_ARTILLEUR_A)

Transport * GetTransportByGUID(Unit* u, uint64 GUID)
{
    if (Transport * transport = ObjectAccessor::GetTransport(*u, GUID))
        return transport;

    return NULL;
}

class npc_gunship_commander : public CreatureScript
{
public:
    npc_gunship_commander() : CreatureScript("npc_gunship_commander") { }

    bool OnGossipHello(Player* pPlayer, Creature* pCreature)
    {
        if (InstanceScript * instance = pCreature->GetInstanceScript())
        {
            if (instance->GetData(DATA_GUNSHIP_EVENT) == DONE)
                return false;

            if(pCreature->GetEntry() == NPC_MURADIN_GUNSHIP)
                pPlayer->ADD_GOSSIP_ITEM(0, "Mes compagnons sont en bon ordre, Muradin. Allons-y !", 631, ALLIANCE);
			else
                pPlayer->ADD_GOSSIP_ITEM(0, "Mes compagnons sont en bon ordre, Saurcroc. Allons-y !", 631, HORDE);


            pPlayer->SEND_GOSSIP_MENU(pPlayer->GetGossipTextId(pCreature), pCreature->GetGUID());
            return true;
        }

        return false;
    }

    bool OnGossipSelect(Player* player, Creature* pCreature, uint32 /*sender*/, uint32 action)
    {
        player->PlayerTalkClass->ClearMenus();
        player->CLOSE_GOSSIP_MENU();

        pCreature->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);

        if(InstanceScript* pInstance = pCreature->GetInstanceScript())
        {
            pInstance->SetData(DATA_TEAM_IN_INSTANCE, action); // Pour s'assurer que le TeamInInstance correspond bien
            pInstance->SetData(DATA_GUNSHIP_EVENT, IN_PROGRESS); // Lance l'event cote instance
        }
		return true;
    }

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new npc_gunship_commander_AI (pCreature);
    }

    struct npc_gunship_commander_AI : public ScriptedAI
    {
        npc_gunship_commander_AI(Creature *pCreature) : ScriptedAI(pCreature)
        {
            pInstance = pCreature->GetInstanceScript();
            IsFriendlyCommander = true;
            me->setFaction(35);
            me->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
            alreadyStartedFight = false;
        }

        InstanceScript* pInstance;

        uint64 CommanderGUID;
        uint32 lastBattleFuryBuffTimer;

        bool IsFriendlyCommander, alreadyStartedFight;

        EventMap events;

        void Reset()
        {
            events.ScheduleEvent(EVENT_CLEAVE, CONFIG_CLEAVE_TIMER);
            events.ScheduleEvent(EVENT_THROW,  CONFIG_THROW_TIMER);

            me->SetHealth(me->GetMaxHealth());

            me->RemoveAurasDueToSpell(SPELL_BATTLE_FURY);

            lastBattleFuryBuffTimer = 0;
        }

        void DoStartFight()
        {
            if(!pInstance)
                return;

            DoZoneInCombat();
        }

        void EnterCombat(Unit* /*who*/)
        {
            if (!alreadyStartedFight)
            {
                if (IsFriendlyCommander)
                {
                    if (pInstance)
                    {
                        if (pInstance->GetData(DATA_TEAM_IN_INSTANCE) == ALLIANCE)
                            DoScriptText(SAY_EVENT_FIGHT_START_A_A, me);
                        else
                            DoScriptText(SAY_EVENT_FIGHT_START_H_H, me);

                        alreadyStartedFight = true;
                    }
                }
            }
        }

        void DoAction(const int32 actionId)
        {
            switch(actionId)
            {
                case ACTION_START_FIGHT:
                    DoStartFight();
                    break;
                case ACTION_SET_ENNEMY_COMMANDER:
                    IsFriendlyCommander = false;
                    me->setFaction(14);
                    me->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
                    break;
                case ACTION_WIPE:
                    me->CombatStop();
                    me->DeleteThreatList();
                    me->getHostileRefManager().deleteReferences();
                    IsFriendlyCommander = true;
                    me->setFaction(35);
                    me->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
                    break;
            }
        }

        void AddBattleFury()
        {
            if (GetMSTimeDiffToNow(lastBattleFuryBuffTimer) > CONFIG_MAX_BATTLE_FURY_TIMER)
            {
                me->AddAura(SPELL_BATTLE_FURY, me);
                lastBattleFuryBuffTimer = getMSTime();
            }
        }

        void DamageDealt(Unit* /*victim*/, uint32& /*damage*/, DamageEffectType damageType)
        {
            if (damageType == DIRECT_DAMAGE)
                AddBattleFury();
        }

        void SpellHitTarget(Unit* /*target*/, SpellInfo const* spell)
        {
            if (spell->Id == SPELL_RENDING_THROW || spell->Id == SPELL_CLEAVE)
                AddBattleFury();
        }

        void DamageTaken(Unit* pDone_by, uint32& uiDamage)
        {
            if(!pInstance)
                return;

            if(IsFriendlyCommander)
            {
                if (Creature* FriendGunshipNpc = pInstance->instance->GetCreature(pInstance->GetData64(DATA_GUNSHIP_NPC_MAIN)))
                    me->DealDamage(FriendGunshipNpc, uiDamage);
            }
            else
            {
                if (Creature* EnnemyGunshipNpc = pInstance->instance->GetCreature(pInstance->GetData64(DATA_GUNSHIP_NPC_SECOND)))
                    me->DealDamage(EnnemyGunshipNpc, uiDamage / 10);
            }

            if(uiDamage >= me->GetHealth()) // Les commandants ne sont pas censés mourir
                uiDamage = 0;
        }

        bool CheckPlayerOnTransport()
        {
            Transport * pTransport = NULL;

            if (!pInstance)
                return false;

            if (IsFriendlyCommander)
                return false; // Le commandant ami ne doit pas check les joueurs sur le transport

            pTransport = GetTransportByGUID(me, pInstance->GetData64(DATA_GUNSHIP_TRANSPORT_SECOND));

            if (!pTransport)
                return false;

            std::set<Player*> pSet = pTransport->GetPassengers();


            if(pSet.empty()) // Stop l'attaque si personne sur le transport
            {
                if (me->isInCombat())
                    EnterEvadeMode();

                return false;
            }

            bool checkPassed = true;

            if (!me->isInCombat()) // Débute l'attaque si un joueur arrive sur le transport
            {
                checkPassed = false;
            }
            else
            {
                if (Unit * victim = me->getVictim())
                {
                    if (victim->GetTypeId() != TYPEID_PLAYER)
                    {
                        checkPassed = false;
                    }
                    else if (victim->GetTransport())
                    {
                        if (victim->GetTransport()->GetGUID() != pInstance->GetData64(DATA_GUNSHIP_TRANSPORT_SECOND))
                            checkPassed = false;

                        if (victim->GetVehicle())
                            checkPassed = false;

                        if (!victim->isAlive())
                            checkPassed = false;
                    }
                    else
                        checkPassed = false;
                }
                else
                    checkPassed = false;
            }

            if (!checkPassed)
            {
                Player * pPassenger = JadeCore::Containers::SelectRandomContainerElement(pSet);

                if (!pPassenger)
                    if (me->isInCombat())
                        EnterEvadeMode();

                if(!pPassenger->IsHostileTo(me))
                    if (me->isInCombat())
                        EnterEvadeMode();

                me->CombatStop();
                AttackStart(pPassenger);
                return false;
            }

            return true;
        }

        void UpdateAI(const uint32 diff)
        {
            if(!pInstance)
                return;
            
            if (pInstance)
                if (pInstance->GetBossState(DATA_GUNSHIP_EVENT) != IN_PROGRESS)
                    return;

            if (!CheckPlayerOnTransport())
                return;

            events.Update(diff);

            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;

            while(uint32 eventId = events.ExecuteEvent())
            {
                switch(eventId)
                {
                    case EVENT_CLEAVE:
                        DoCast(SPELL_CLEAVE);
                        events.ScheduleEvent(EVENT_CLEAVE, CONFIG_CLEAVE_TIMER);
                        break;
                    case EVENT_THROW:
                        if (!me->getVictim() || me->IsWithinMeleeRange(me->getVictim()))
                        {
                            events.ScheduleEvent(EVENT_THROW, CONFIG_THROW_TIMER);
                            break;
                        }
                        else
                            DoCast(me->getVictim(), SPELL_RENDING_THROW);

                        events.ScheduleEvent(EVENT_THROW, CONFIG_THROW_TIMER);
                        break;
                }
            }
            DoMeleeAttackIfReady();
        }
    };
};

// Classe de base pour les adds
struct npc_gunship_adds_AI : ScriptedAI
{
    npc_gunship_adds_AI(Creature *pCreature) : ScriptedAI(pCreature)
    {pInstance = pCreature->GetInstanceScript();}

    InstanceScript* pInstance;

    uint8 NpcRank;
    uint32 RankTimer;
    uint32 PoixTimer;
    uint64 SummonerGUID;
    EventMap events;

    bool mustBeRespawned;

    void Reset()
    {
        NpcRank = 0;
        RankTimer = CONFIG_RANK_TIMER;
        SummonerGUID = 0;
        me->SetVisible(true);
        me->CastSpell(me, SPELL_TELEPORT_VISUAL, true);
        mustBeRespawned = true;

        me->setFaction(14);
    }

    void JustDied(Unit *victim)
    {
        if (mustBeRespawned)
            pInstance->SetData64(DATA_GUNSHIP_ADD_RESPAWN, me->GetGUID());

        me->SetVisible(false);
    }

    void DoUpdateRank()
    {
        RankTimer = CONFIG_RANK_TIMER;
        switch(NpcRank)
        {
            case Start:
                NpcRank++;
                me->CastSpell(me, SPELL_EXPERIMENTE, true);
                break;
            case Experimente:
                NpcRank++;
                me->RemoveAurasDueToSpell(SPELL_EXPERIMENTE);
                me->CastSpell(me, SPELL_VETERAN, true);
                break;
            case Veteran:
                NpcRank++;
                me->RemoveAurasDueToSpell(SPELL_VETERAN);
                me->CastSpell(me, SPELL_ELITE, true);
                break;
            case Elite: // Rang max
            default:
                break;
        }
    }

    void DoTransportInCombat(Transport* pTransport)
    {
        if(!pTransport)
            return;

        std::set<Player*> pSet = pTransport->GetPassengers();

        if(pSet.empty())
            return;

        for(std::set<Player*>::iterator itr = pSet.begin(); itr != pSet.end(); ++itr)
        {
            me->SetInCombatWith(*itr);
            (*itr)->SetInCombatWith(me);
            me->AddThreat((*itr), 0.0f);
        }
    }

    void IsSummonedBy(Unit* summoner)
    {
        if(summoner)
            SummonerGUID = summoner->GetGUID();
    }

    void UpdateAI(const uint32 diff)
    {
        if (RankTimer <= diff)
        {
            DoUpdateRank();
        }
		else
            RankTimer -= diff;
    }

    bool CanSeeAlways(WorldObject const* obj)
    {
        if (obj->ToPlayer())
            return true;
        else
            return false;
    }
};

// gère les pvs des cannonières
class npc_gunship : public CreatureScript
{
public:
    npc_gunship() : CreatureScript("npc_gunship") { }

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new npc_gunship_AI (pCreature);
    }

    struct npc_gunship_AI : public ScriptedAI
    {
        npc_gunship_AI(Creature *pCreature) : ScriptedAI(pCreature)
        {pInstance = pCreature->GetInstanceScript();}

        InstanceScript* pInstance;
        bool IsFriendlyGunship;

        void Reset()
        {
            IsFriendlyGunship = false;
            me->SetReactState(REACT_PASSIVE);
        }

        void MoveInLineOfSight(Unit* /*who*/)
        {
            return;
        }
            
        void EnterCombat(Unit* /*who*/)
        {
            return;
        }

        void DoAction(const int32 actionId)
        {
            switch(actionId)
            {
                // Défini au summon si le pnj s'occupe de la canno amie(true) ou ennemie(false)
                case ACTION_SET_MAIN_GUNSHIP:
                    IsFriendlyGunship = true;
                    me->setFaction(35);
                    break;
                case ACTION_SET_SECOND_GUNSHIP:
                    IsFriendlyGunship = false;
                    me->setFaction(14);
                    break;
                case ACTION_ADD_ENCOUNTER_GUNSHIP:
                    pInstance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, me);
                    break;
                case ACTION_REMOVE_ENCOUNTER_GUNSHIP:
                    pInstance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
                    break;
            }
        }

        void JustDied(Unit *victim)
        {}

        void DamageTaken(Unit* pDone_by, uint32& uiDamage)
        {
            if (pDone_by->ToPet() || pDone_by->ToPlayer())
            {
                uiDamage = 0;
                return;
            }

            if (uiDamage >= me->GetHealth())
            {
                uiDamage = 0;

                if (pInstance)
                {
                    if (IsFriendlyGunship)
                        pInstance->SetData(DATA_GUNSHIP_EVENT, FAIL);
                    else
                        pInstance->SetData(DATA_GUNSHIP_EVENT, DONE);
                }
            }
        }
         
        void SpellHit(Unit* /*caster*/, const SpellInfo * spell)
        {}

        void UpdateAI(const uint32 diff)
        {}
    };
};

class npc_gunship_tireur : public CreatureScript
{
public:
    npc_gunship_tireur() : CreatureScript("npc_gunship_tireur") { }

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new npc_gunship_tireur_AI (pCreature);
    }

    struct npc_gunship_tireur_AI : public npc_gunship_adds_AI
    {
        npc_gunship_tireur_AI(Creature *pCreature) : npc_gunship_adds_AI(pCreature) {}

        Transport * FriendlyTransport;

        void Reset()
        {
            npc_gunship_adds_AI::Reset();
            events.ScheduleEvent(EVENT_TIR, CONFIG_TIR_TIMER);

            FriendlyTransport = NULL;

            if (pInstance)
                FriendlyTransport = GetTransportByGUID(me, pInstance->GetData64(DATA_GUNSHIP_TRANSPORT_MAIN));
        }

        void AttackStart(Unit* target)
        {
            if (!target)
                return;

            if (me->Attack(target, true))
                DoStartNoMovement(target);
        }

        void JustDied(Unit *victim)
        {
             npc_gunship_adds_AI::JustDied(victim);
        }

        void IsSummonedBy(Unit* summoner)
        {
            npc_gunship_adds_AI::IsSummonedBy(summoner);
        }

        void UpdateAI(const uint32 diff)
        {
            if (pInstance)
                if (pInstance->GetBossState(DATA_GUNSHIP_EVENT) != IN_PROGRESS)
                    return;

            npc_gunship_adds_AI::UpdateAI(diff);

            events.Update(diff);

            while(uint32 eventId = events.ExecuteEvent())
            {
                switch(eventId)
                {
                    case EVENT_TIR:
                    {
                        if(!FriendlyTransport)
                            if (!(FriendlyTransport = GetTransportByGUID(me, pInstance->GetData64(DATA_GUNSHIP_TRANSPORT_MAIN))))
                                break;

                        DoTransportInCombat(FriendlyTransport);

                        if(Unit* unit = SelectTarget(SELECT_TARGET_RANDOM, 0))
                        {
                            if (unit->GetTransport() == me->GetTransport())
                            {
                                events.ScheduleEvent(EVENT_TIR, 100);
                                break;
                            }

                            DoCast(unit, SPELL_TIR);
                            me->getHostileRefManager().addThreatPercent(100);
                            events.ScheduleEvent(EVENT_TIR, CONFIG_TIR_TIMER);
                        }

                        break;
                    }
                }
            }
        }
    };
};

class npc_gunship_soldier : public CreatureScript
{
public:
    npc_gunship_soldier() : CreatureScript("npc_gunship_soldier") { }

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new npc_gunship_soldier_AI (pCreature);
    }

    struct npc_gunship_soldier_AI : public npc_gunship_adds_AI
    {
        npc_gunship_soldier_AI(Creature *pCreature) : npc_gunship_adds_AI(pCreature) {}

        uint32 lastTimeAttackedByPlayer;
        bool PoixArdentScheduled;

        void Reset()
        {
            npc_gunship_adds_AI::Reset();
            events.ScheduleEvent(EVENT_FRAPPE_LESION, CONFIG_FRAPPE_TIMER);
            events.ScheduleEvent(EVENT_RESOLUTION_DESESPEREE, CONFIG_RESOLUTION_TIMER);
            events.ScheduleEvent(EVENT_TEMPETE_DE_LAME, CONFIG_TEMPETE_LAME_TIMER);
            events.ScheduleEvent(EVENT_POIX_ARDENTE, 15000);

            lastTimeAttackedByPlayer = 0;
            PoixArdentScheduled = false;

            mustBeRespawned = false;

            if (pInstance)
                if (Transport * FriendlyTransport = GetTransportByGUID(me, pInstance->GetData64(DATA_GUNSHIP_TRANSPORT_MAIN)))
                    DoTransportInCombat(FriendlyTransport);
        }

        void JustDied(Unit *victim)
        {
            npc_gunship_adds_AI::JustDied(victim);
        }

        void IsSummonedBy(Unit* summoner)
        {
            npc_gunship_adds_AI::IsSummonedBy(summoner);

            DoCast(me, SPELL_INVOCATION_VISUEL);
        }

        void DamageTaken(Unit* pDone_by, uint32& uiDamage)
        {
            if (pDone_by->GetTypeId() == TYPEID_PLAYER)
            {
                lastTimeAttackedByPlayer = getMSTime();
                PoixArdentScheduled = false;
                events.CancelEvent(EVENT_POIX_ARDENTE);
            }
        }

        void UpdateAI(const uint32 diff)
        {
            if (!pInstance)
                return;

            if (pInstance->GetBossState(DATA_GUNSHIP_EVENT) != IN_PROGRESS)
                return;

            npc_gunship_adds_AI::UpdateAI(diff);

            if(!UpdateVictim())
                return;

            events.Update(diff);

            if (me->getVictim())
            {
                if (me->getVictim()->GetTransport())
                {
                    if (me->getVictim()->GetTransport()->GetGUID() != pInstance->GetData64(DATA_GUNSHIP_TRANSPORT_MAIN))
                    {
                        if (Transport * FriendlyTransport = GetTransportByGUID(me, pInstance->GetData64(DATA_GUNSHIP_TRANSPORT_MAIN)))
                        {
                            std::set<Player*> players = FriendlyTransport->GetPassengers();

                            Creature * commander = me->GetMap()->GetCreature(pInstance->GetData64(DATA_GUNSHIP_COMMANDER));

                            if (!commander)
                                return;

                            if (players.empty())
                                me->AI()->AttackStart(commander);
                            else
                            {
                                if (urand(0, 1))
                                    me->AI()->AttackStart(*players.begin());
                                else
                                    me->AI()->AttackStart(commander);
                            }
                        }
                    }
                }

            }

            if (!PoixArdentScheduled)
            {
                if (GetMSTimeDiffToNow(lastTimeAttackedByPlayer) > 15000)
                {
                    PoixArdentScheduled = true;
                    events.ScheduleEvent(EVENT_POIX_ARDENTE, CONFIG_POIX_TIMER);
                }
            }

            while(uint32 eventId = events.ExecuteEvent())
            {
                switch(eventId)
                {
                    case EVENT_FRAPPE_LESION:
                        DoCastVictim(SPELL_FRAPPE_LESION);
                        events.ScheduleEvent(EVENT_FRAPPE_LESION, CONFIG_FRAPPE_TIMER);
                        break;
                    case EVENT_RESOLUTION_DESESPEREE:
                        DoCast(SPELL_RESOLUTION_DESESPEREE);
                        events.ScheduleEvent(EVENT_RESOLUTION_DESESPEREE, CONFIG_RESOLUTION_TIMER);
                        break;
                    case EVENT_TEMPETE_DE_LAME:
                        DoCast(SPELL_TEMPETE_DE_LAME);
                        events.ScheduleEvent(EVENT_TEMPETE_DE_LAME, CONFIG_TEMPETE_LAME_TIMER);
                        break;
                    case EVENT_POIX_ARDENTE:
                        if (Creature * pCommander = ObjectAccessor::GetCreature(*me, pInstance->GetData64(DATA_GUNSHIP_COMMANDER)))
                            me->CastSpell(pCommander, SPELL_POIX_ARDENTE, false);
                        events.ScheduleEvent(EVENT_POIX_ARDENTE, CONFIG_POIX_TIMER);
                        break;
                    default:
                        break;
                }
            }

            DoMeleeAttackIfReady();
        }
    };
};

class npc_gunship_artilleur : public CreatureScript
{
public:
    npc_gunship_artilleur() : CreatureScript("npc_gunship_artilleur") { }

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new npc_gunship_artilleur_AI (pCreature);
    }

    struct npc_gunship_artilleur_AI : public npc_gunship_adds_AI
    {
        npc_gunship_artilleur_AI(Creature *pCreature) : npc_gunship_adds_AI(pCreature) {}

        Transport * FriendlyTransport;
        uint64 targetGuid;

        void Reset()
        {
            npc_gunship_adds_AI::Reset();
            
            if (pInstance)
                FriendlyTransport = GetTransportByGUID(me, pInstance->GetData64(DATA_GUNSHIP_TRANSPORT_MAIN));
            
            targetGuid = 0;
            events.ScheduleEvent(EVENT_MISSILE, CONFIG_MISSILE_TIMER);
        }

        void JustDied(Unit *victim)
        {
             npc_gunship_adds_AI::JustDied(victim);
        }

        void AttackStart(Unit* target)
        {
            if (!target)
                return;

            if (me->Attack(target, true))
                DoStartNoMovement(target);
        }

        void IsSummonedBy(Unit* summoner)
        {
            npc_gunship_adds_AI::IsSummonedBy(summoner);
        }

        void UpdateAI(const uint32 diff)
        {
            if (pInstance)
                if (pInstance->GetBossState(DATA_GUNSHIP_EVENT) != IN_PROGRESS)
                    return;

            npc_gunship_adds_AI::UpdateAI(diff);

            events.Update(diff);

            while(uint32 eventId = events.ExecuteEvent())
            {
                switch(eventId)
                {
                    case EVENT_MISSILE:
                    {
                        if(!FriendlyTransport)
                            if (!(FriendlyTransport = GetTransportByGUID(me, pInstance->GetData64(DATA_GUNSHIP_TRANSPORT_MAIN))))
                                break;

                        DoTransportInCombat(FriendlyTransport);

                        if(Unit* unit = SelectTarget(SELECT_TARGET_RANDOM, 0))
                        {
                            if (unit->GetTransport() == me->GetTransport())
                            {
                                events.ScheduleEvent(EVENT_MISSILE, 100);
                                break;
                            }

                            me->CastSpell(unit, SPELL_MISSILE, false);
                            targetGuid = unit->GetGUID();
                            events.ScheduleEvent(EVENT_MISSILE_VISUAL, 4900);
                            events.ScheduleEvent(EVENT_MISSILE_DAMAGE_TRANS, 10000);

                            events.ScheduleEvent(EVENT_MISSILE, CONFIG_MISSILE_TIMER);
                        }
                        break;
                    }
                    case EVENT_MISSILE_VISUAL:
                    {
                        me->CastSpell(ObjectAccessor::GetPlayer(*me, targetGuid), SPELL_MISSILE_VISUAL, true);
                        events.CancelEvent(EVENT_MISSILE_VISUAL);
                        break;
                    }
                    case EVENT_MISSILE_DAMAGE_TRANS:
                    {
                        if (Creature* FriendGunshipNpc = pInstance->instance->GetCreature(pInstance->GetData64(DATA_GUNSHIP_NPC_MAIN)))
                            me->DealDamage(FriendGunshipNpc, urand(6300, 7701));
                        events.CancelEvent(EVENT_MISSILE_DAMAGE_TRANS);
                        break;
                    }
                    default:
                        break;
                }
            }
        }
    };
};

class npc_gunship_sorcier_mage : public CreatureScript
{
public:
    npc_gunship_sorcier_mage() : CreatureScript("npc_gunship_sorcier_mage") { }

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new npc_gunship_sorcier_mage_AI (pCreature);
    }

    struct npc_gunship_sorcier_mage_AI : public npc_gunship_adds_AI
    {
        npc_gunship_sorcier_mage_AI(Creature *pCreature) : npc_gunship_adds_AI(pCreature)
        {pInstance = pCreature->GetInstanceScript();}

        InstanceScript* pInstance;
        EventMap events;

        bool IsPortalMage;
        bool MovementDone;
        bool IsCasting;

        void Reset()
        {
            IsPortalMage = true;
            MovementDone = false;
            IsCasting = false;
            me->setFaction(14);
            me->SetReactState(REACT_PASSIVE);

            if (pInstance)
                pInstance->SetData(DATA_GUNSHIP_PORTAL_MAGES, ACTION_ADD_MAGE);
        }

        void MoveInLineOfSight(Unit* /*who*/)
        {
            return;
        }

        void EnterCombat(Unit* /*who*/)
        {
            return;
        }

        void DoAction(const int32 actionId)
        {
            switch(actionId)
            {
                case ACTION_SET_CANON_SPELL:
                    IsPortalMage = false;

                    if (pInstance)
                        pInstance->SetData(DATA_GUNSHIP_PORTAL_MAGES, ACTION_REMOVE_MAGE); // Le mage de givre ne compte pas pour le spawn du portail

                    break;
            }
        }

        void JustDied(Unit *victim)
        {
            if (!pInstance)
                return;

            pInstance->SetData64(DATA_GUNSHIP_ADD_RESPAWN, me->GetGUID());

            if (IsPortalMage)
                pInstance->SetData(DATA_GUNSHIP_PORTAL_MAGES, ACTION_REMOVE_MAGE);
            else
            {
                pInstance->SetData(DATA_GUNSHIP_ICE_CANON_EVENT, DONE);
                me->RemoveFromWorld();
            }
        }

        void MovementInform(uint32 type, uint32 pointId)
        {
            if (type != POINT_MOTION_TYPE)
                return;

            switch (pointId)
            {
                case MOVE_ICE_MAGE:
                    me->CastSpell(me, SPELL_BEHIND_ZERO, false);
                    pInstance->SetData(DATA_GUNSHIP_ICE_CANON_EVENT, IN_PROGRESS);
                    IsCasting = true;
                    break;
                default:
                    break;
            }
        }

        void UpdateAI(const uint32 diff)
        {
            if (!pInstance)
                return;
            
            if (pInstance)
                if (pInstance->GetBossState(DATA_GUNSHIP_EVENT) != IN_PROGRESS)
                    return;

            if (IsPortalMage)
                return;

            if (me->isAlive() && IsCasting && !me->HasUnitState(UNIT_STATE_CASTING))
                me->CastSpell(me, SPELL_BEHIND_ZERO, false);

            if (!MovementDone)
            {
                Transport * pTransport = GetTransportByGUID(me, pInstance->GetData64(DATA_GUNSHIP_TRANSPORT_SECOND));

                if (!pTransport)
                    return;

                Position correctPosition;

                if (pInstance->GetData(DATA_TEAM_IN_INSTANCE) == ALLIANCE)
                    correctPosition = HordeIceMageCastPosition;
                else
                    correctPosition = AllyIceMageCastPosition;
                
                float x = correctPosition.GetPositionX();
                float y = correctPosition.GetPositionY();
                float z = correctPosition.GetPositionZ();

                me->GetMotionMaster()->MovePoint(MOVE_ICE_MAGE, Transport::getX(x, y, pTransport), Transport::getY(x, y, pTransport), Transport::getZ(z, pTransport));
                MovementDone = true;
            }
        }
    };
};

class npc_gunship_canon : public CreatureScript
{
public:
    npc_gunship_canon() : CreatureScript("npc_gunship_canon") { }

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new npc_gunship_canon_AI (pCreature);
    }

    struct npc_gunship_canon_AI : public ScriptedAI
    {
        npc_gunship_canon_AI(Creature *pCreature) : ScriptedAI(pCreature)
        {pInstance = pCreature->GetInstanceScript();}

        InstanceScript* pInstance;
        EventMap events;

        void Reset()
        {}

        void JustDied(Unit *victim)
        {}

        void MoveInLineOfSight(Unit* /*who*/)
        {
            return;
        }
            
        void EnterCombat(Unit* /*who*/)
        {
            return;
        }

        void DamageTaken(Unit* /*pDone_by*/, uint32& uiDamage)
        {
			uiDamage = 0; // Les canons ne peuvent pas mourir
        }

        void UpdateAI(const uint32 diff)
        {
            if (me->GetPower(POWER_ENERGY) == 100)
                if (!me->HasAura(69487)) // Surchauffe
                    me->AddAura(69487, me);
        }
    };
};

class npc_gunship_zafod : public CreatureScript
{
public:
    npc_gunship_zafod() : CreatureScript("npc_gunship_zafod") { }

    bool OnGossipHello(Player* pPlayer, Creature* pCreature)
    {
        if (pCreature->GetInstanceScript())
        {
            if (InstanceScript * pInstance = pCreature->GetInstanceScript())
                if (pInstance->GetData(DATA_GUNSHIP_EVENT) != DONE)
                    pPlayer->ADD_GOSSIP_ITEM(0, "Zafod, fournissez-moi des fusees d'appoint", 1, 1);

            pPlayer->SEND_GOSSIP_MENU(pPlayer->GetGossipTextId(pCreature), pCreature->GetGUID());
            return true;
        }

        return false;
    }

    bool OnGossipSelect(Player* player, Creature* pCreature, uint32 /*sender*/, uint32 action)
    {
        player->AddItem(49278, 1);
        player->PlayerTalkClass->ClearMenus();
        player->CLOSE_GOSSIP_MENU();
        return true;
    }
};

/*######
## transport_icc_gunship
######*/

class transport_icc_gunship : public TransportScript
{
public:
    transport_icc_gunship() : TransportScript("transport_icc_gunship") { }

    void OnAddPassenger(Transport* transport, Player* player)
    {
        switch(transport->GetEntry())
        {
            case TRANSPORT_A_ORGRIM_HAMMER:
                //if (player->GetInstanceScript())
                //    player->GetInstanceScript()->SetData64(DATA_GUNSHIP_BOARDING_COUNT, player->GetGUID());
                break;
            case TRANSPORT_A_THE_SKYBREAKER:
                player->AddAura(SPELL_ON_TRANSPORT_A, player);
                break;
            case TRANSPORT_H_ORGRIM_HAMMER:
                player->AddAura(SPELL_ON_TRANSPORT_H, player);
                break;
            case TRANSPORT_H_THE_SKYBREAKER:
                //if (player->GetInstanceScript())
                //    player->GetInstanceScript()->SetData64(DATA_GUNSHIP_BOARDING_COUNT, player->GetGUID());
                break;
        }
    }

    // Called when a player exits the transport.
    void OnRemovePassenger(Transport* transport, Player* player)
    {
        switch(transport->GetEntry())
        {
            case TRANSPORT_A_ORGRIM_HAMMER:
                break;
            case TRANSPORT_A_THE_SKYBREAKER:
                player->RemoveAurasDueToSpell(SPELL_ON_TRANSPORT_A);
                break;
            case TRANSPORT_H_ORGRIM_HAMMER:
                player->RemoveAurasDueToSpell(SPELL_ON_TRANSPORT_H);
                break;
            case TRANSPORT_H_THE_SKYBREAKER:
                break;
        }
    }
};

// Canon Blast - 69400
class spell_gunship_canon_blast : public SpellScriptLoader
{
    public:
        spell_gunship_canon_blast() : SpellScriptLoader("spell_gunship_canon_blast") { }

        class spell_gunship_canon_blast_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_gunship_canon_blast_SpellScript);

            void RecalculateDamage(SpellEffIndex /*effIndex*/)
            {
                SetHitDamage(1500);
            }

            void GetOnlyEnnemyGunshipTarget(std::list<WorldObject*>& targets)
            {
                targets.clear();

                if (!GetCaster())
                    return;

                if (InstanceScript * pInstance = GetCaster()->GetInstanceScript())
                    if (Creature* EnnemyGunshipNpc = pInstance->instance->GetCreature(pInstance->GetData64(DATA_GUNSHIP_NPC_SECOND)))
                        targets.push_back(EnnemyGunshipNpc);
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_gunship_canon_blast_SpellScript::RecalculateDamage, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
                OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_gunship_canon_blast_SpellScript::GetOnlyEnnemyGunshipTarget, EFFECT_1, TARGET_UNIT_DEST_AREA_ENTRY);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_gunship_canon_blast_SpellScript();
        }
};

// Incinerating Blast - 70175
class spell_gunship_incinerating_blast : public SpellScriptLoader
{
    public:
        spell_gunship_incinerating_blast() : SpellScriptLoader("spell_gunship_incinerating_blast") { }

        class spell_gunship_incinerating_blast_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_gunship_incinerating_blast_SpellScript);

            void GetOnlyEnnemyGunshipTarget(std::list<WorldObject*>& targets)
            {
                targets.clear();

                if (!GetCaster())
                    return;

                if (InstanceScript * pInstance = GetCaster()->GetInstanceScript())
                    if (Creature* EnnemyGunshipNpc = pInstance->instance->GetCreature(pInstance->GetData64(DATA_GUNSHIP_NPC_SECOND)))
                        targets.push_back(EnnemyGunshipNpc);
            }

            void RecalculateDamage(SpellEffIndex /*effIndex*/)
            {
                if (!GetCaster())
                    return;

                int32 baseDamages = GetHitDamage();

                int32 additionalDamages = GetCaster()->GetPower(POWER_ENERGY) * 100;

                SetHitDamage(baseDamages + additionalDamages);

                GetCaster()->SetPower(POWER_ENERGY, 0);
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_gunship_incinerating_blast_SpellScript::RecalculateDamage, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
                OnEffectHitTarget += SpellEffectFn(spell_gunship_incinerating_blast_SpellScript::RecalculateDamage, EFFECT_1, SPELL_EFFECT_SCHOOL_DAMAGE);
                OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_gunship_incinerating_blast_SpellScript::GetOnlyEnnemyGunshipTarget, EFFECT_1, TARGET_UNIT_DEST_AREA_ENTRY);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_gunship_incinerating_blast_SpellScript();
        }
};

class CheckCanonOnly
{
    public:
        bool operator() (WorldObject* target)
        {
            if (Unit* unit = target->ToUnit())
                return unit->GetEntry() != NPC_CANON_A && unit->GetEntry() != NPC_CANON_H;

            return true;
        }
};

// Behind Zero - 69705
class spell_gunship_behind_zero : public SpellScriptLoader
{
    public:
        spell_gunship_behind_zero() : SpellScriptLoader("spell_gunship_behind_zero") { }

        class spell_gunship_behind_zero_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_gunship_behind_zero_SpellScript);

            void resizeTargets(std::list<WorldObject*>& targets)
            {
                if (!GetCaster())
                    return;

                targets.remove_if(CheckCanonOnly());

                std::list<WorldObject*>::iterator Itr;

                for (Itr = targets.begin(); Itr != targets.end(); Itr++)
                    if (Unit* target = (*Itr)->ToUnit())
                        if (Vehicle * canon = target->GetVehicleKit())
                            canon->RemoveAllPassengers();
            }

            void Register()
            {
                OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_gunship_behind_zero_SpellScript::resizeTargets, EFFECT_0, TARGET_UNIT_SRC_AREA_ENTRY);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_gunship_behind_zero_SpellScript();
        }
};

// Burning Pitch - 71335
class spell_poix_ardente : public SpellScriptLoader
{
    public:
        spell_poix_ardente() : SpellScriptLoader("spell_poix_ardente") { }

        class spell_poix_ardente_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_poix_ardente_SpellScript);

            bool Load()
            {
                return GetCaster()->IsVehicle();
            }

            void HandleDummy(SpellEffIndex effIndex)
            {
                PreventHitDefaultEffect(effIndex);

                if (!GetCaster())
                    return;

                if (InstanceScript * pInstance = GetCaster()->GetInstanceScript())
                {
                    if (Creature* GunshipNpc = pInstance->instance->GetCreature(pInstance->GetData64(DATA_GUNSHIP_NPC_MAIN)))
                    {
                        GetCaster()->DealDamage(GunshipNpc, GetSpellValue()->EffectBasePoints[EFFECT_0]);
                    }
                }
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_poix_ardente_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_poix_ardente_SpellScript();
        }
};

void AddSC_event_gunship_battle()
{
    new npc_gunship_commander();
    new npc_gunship();
    new npc_gunship_tireur();
    new npc_gunship_soldier();
    new npc_gunship_artilleur();
    new npc_gunship_sorcier_mage();
    new npc_gunship_canon();
    new npc_gunship_zafod();
    new transport_icc_gunship();
    new spell_gunship_canon_blast();
    new spell_gunship_incinerating_blast();
    new spell_gunship_behind_zero();
    new spell_poix_ardente();
}
