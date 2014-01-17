/*
 * Copyright (C) 2008-2012 TrinityCore <http://www.trinitycore.org/>
 * Copyright (C) 2005-2009 MaNGOS <http://getmangos.com/>
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

#ifndef __BATTLEGROUNDMGR_H
#define __BATTLEGROUNDMGR_H

#include "Common.h"
#include "DBCEnums.h"
#include "Battleground.h"
#include "BattlegroundQueue.h"
#include "Object.h"
#include <ace/Singleton.h>

typedef std::map<uint32, Battleground*> BattlegroundSet;

typedef UNORDERED_MAP<uint32, BattlegroundTypeId> BattleMastersMap;

#define WS_CURRENCY_RESET_TIME 20001                    // Custom worldstate

struct CreateBattlegroundData
{
    BattlegroundTypeId bgTypeId;
    bool IsArena;
    uint32 MinPlayersPerTeam;
    uint32 MaxPlayersPerTeam;
    uint32 LevelMin;
    uint32 LevelMax;
    char* BattlegroundName;
    uint32 MapID;
    float Team1StartLocX;
    float Team1StartLocY;
    float Team1StartLocZ;
    float Team1StartLocO;
    float Team2StartLocX;
    float Team2StartLocY;
    float Team2StartLocZ;
    float Team2StartLocO;
    float StartMaxDist;
    uint32 holiday;
    uint32 scriptId;
};

struct QueueSchedulerItem
{
    QueueSchedulerItem(uint32 arenaMMRating,
        uint8 arenaType,
        BattlegroundQueueTypeId bgQueueTypeId,
        BattlegroundTypeId bgTypeId,
        BattlegroundBracketId bracketid)
        : _arenaMMRating (arenaMMRating),
        _arenaType (arenaType),
        _bgQueueTypeId (bgQueueTypeId),
        _bgTypeId (bgTypeId),
        _bracket_id (bracketid)
    {
    }

    const uint32 _arenaMMRating;
    const uint8 _arenaType;
    const BattlegroundQueueTypeId _bgQueueTypeId;
    const BattlegroundTypeId _bgTypeId;
    const BattlegroundBracketId _bracket_id;
};

class BattlegroundMgr
{
    friend class ACE_Singleton<BattlegroundMgr, ACE_Null_Mutex>;

    private:
        BattlegroundMgr();
        ~BattlegroundMgr();

    public:
        void Update(uint32 diff);

        /* Packet Building */
        void BuildPlayerJoinedBattlegroundPacket(WorldPacket* data, uint64 guid);
        void BuildPlayerLeftBattlegroundPacket(WorldPacket* data, uint64 guid);
        void BuildBattlegroundListPacket(WorldPacket* data, ObjectGuid guid, Player* player, BattlegroundTypeId bgTypeId);
        void BuildStatusFailedPacket(WorldPacket* data, Battleground* bg, Player* player, uint8 QueueSlot, GroupJoinBattlegroundResult result);
        void BuildUpdateWorldStatePacket(WorldPacket* data, uint32 field, uint32 value);
        void BuildPvpLogDataPacket(WorldPacket* data, Battleground* bg);
        void BuildBattlegroundStatusPacket(WorldPacket* data, Battleground* bg, Player * pPlayer, uint8 QueueSlot, uint8 StatusID, uint32 Time1, uint32 Time2, uint8 arenatype, uint8 uiFrame = 1);
        void BuildPlaySoundPacket(WorldPacket* data, uint32 soundid);
        void SendAreaSpiritHealerQueryOpcode(Player* player, Battleground* bg, uint64 guid);

        /* Battlegrounds */
        Battleground* GetBattlegroundThroughClientInstance(uint32 instanceId, BattlegroundTypeId bgTypeId);
        Battleground* GetBattleground(uint32 InstanceID, BattlegroundTypeId bgTypeId); //there must be uint32 because MAX_BATTLEGROUND_TYPE_ID means unknown

        Battleground* GetBattlegroundTemplate(BattlegroundTypeId bgTypeId);
        Battleground* CreateNewBattleground(BattlegroundTypeId bgTypeId, PvPDifficultyEntry const* bracketEntry, uint8 arenaType, bool isRated);

        uint32 CreateBattleground(CreateBattlegroundData& data);

        void AddBattleground(uint32 InstanceID, BattlegroundTypeId bgTypeId, Battleground* BG) { m_Battlegrounds[bgTypeId][InstanceID] = BG; };
        void RemoveBattleground(uint32 instanceID, BattlegroundTypeId bgTypeId) { m_Battlegrounds[bgTypeId].erase(instanceID); }
        uint32 CreateClientVisibleInstanceId(BattlegroundTypeId bgTypeId, BattlegroundBracketId bracket_id);

        void CreateInitialBattlegrounds();
        void InitAutomaticArenaPointDistribution();
        void DeleteAllBattlegrounds();

        void SendToBattleground(Player* player, uint32 InstanceID, BattlegroundTypeId bgTypeId);

        /* Battleground queues */
        //these queues are instantiated when creating BattlegroundMrg
        BattlegroundQueue& GetBattlegroundQueue(BattlegroundQueueTypeId bgQueueTypeId) { return m_BattlegroundQueues[bgQueueTypeId]; }
        BattlegroundQueue m_BattlegroundQueues[MAX_BATTLEGROUND_QUEUE_TYPES]; // public, because we need to access them in BG handler code

        BGFreeSlotQueueType BGFreeSlotQueue[MAX_BATTLEGROUND_TYPE_ID];

        void ScheduleQueueUpdate(uint32 arenaMatchmakerRating, uint8 arenaType, BattlegroundQueueTypeId bgQueueTypeId, BattlegroundTypeId bgTypeId, BattlegroundBracketId bracket_id);
        uint32 GetMaxRatingDifference() const;
        uint32 GetRatingDiscardTimer()  const;
        uint32 GetPrematureFinishTime() const;

        void ToggleArenaTesting();
        void ToggleTesting();

        void SetHolidayWeekends(std::list<uint32> activeHolidayId);
        void LoadBattleMastersEntry();
        BattlegroundTypeId GetBattleMasterBG(uint32 entry) const
        {
            BattleMastersMap::const_iterator itr = mBattleMastersMap.find(entry);
            if (itr != mBattleMastersMap.end())
                return itr->second;
            return BATTLEGROUND_WS;
        }

        bool isArenaTesting() const { return m_ArenaTesting; }
        bool isTesting() const { return m_Testing; }

        static bool IsArenaType(BattlegroundTypeId bgTypeId);
        static bool IsBattlegroundType(BattlegroundTypeId bgTypeId) { return !IsArenaType(bgTypeId); }
        static BattlegroundQueueTypeId BGQueueTypeId(BattlegroundTypeId bgTypeId, uint8 arenaType);
        static BattlegroundTypeId BGTemplateId(BattlegroundQueueTypeId bgQueueTypeId);
        static uint8 BGArenaType(BattlegroundQueueTypeId bgQueueTypeId);

        static HolidayIds BGTypeToWeekendHolidayId(BattlegroundTypeId bgTypeId);
        static BattlegroundTypeId WeekendHolidayIdToBGType(HolidayIds holiday);
        static bool IsBGWeekend(BattlegroundTypeId bgTypeId);
    private:
        BattleMastersMap    mBattleMastersMap;

        typedef std::map<BattlegroundTypeId, uint8> BattlegroundSelectionWeightMap; // TypeId and its selectionWeight
        /* Battlegrounds */
        BattlegroundSet m_Battlegrounds[MAX_BATTLEGROUND_TYPE_ID];
        BattlegroundSelectionWeightMap m_ArenaSelectionWeights;
        BattlegroundSelectionWeightMap m_BGSelectionWeights;
        std::vector<QueueSchedulerItem*> m_QueueUpdateScheduler;
        std::set<uint32> m_ClientBattlegroundIds[MAX_BATTLEGROUND_TYPE_ID][MAX_BATTLEGROUND_BRACKETS]; //the instanceids just visible for the client
        uint32 m_NextRatedArenaUpdate;
        bool   m_ArenaTesting;
        bool   m_Testing;
};

#define sBattlegroundMgr ACE_Singleton<BattlegroundMgr, ACE_Null_Mutex>::instance()
#endif

