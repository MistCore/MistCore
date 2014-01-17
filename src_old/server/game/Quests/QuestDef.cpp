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

#include "QuestDef.h"
#include "Player.h"
#include "World.h"
#include "ObjectMgr.h"

Quest::Quest(Field* questRecord)
{
    uint8 index = 0;

    Id                      = questRecord[index++].GetUInt32();
    Method                  = questRecord[index++].GetUInt8();
    Level                   = questRecord[index++].GetInt16();
    MinLevel                = uint32(questRecord[index++].GetInt16());
    MaxLevel                = uint32(questRecord[index++].GetInt16());
    ZoneOrSort              = questRecord[index++].GetInt16();
    Type                    = questRecord[index++].GetUInt16();
    SuggestedPlayers        = questRecord[index++].GetUInt8();
    LimitTime               = questRecord[index++].GetUInt32();
    RequiredTeam            = questRecord[index++].GetInt8();
    RequiredClasses         = questRecord[index++].GetInt16();
    RequiredRaces           = questRecord[index++].GetInt32();
    RequiredSkillId         = questRecord[index++].GetUInt16();
    RequiredSkillPoints     = questRecord[index++].GetUInt16();
    RequiredFactionId1      = questRecord[index++].GetUInt16();
    RequiredFactionId2      = questRecord[index++].GetUInt16();
    RequiredFactionValue1   = questRecord[index++].GetInt32();
    RequiredFactionValue2   = questRecord[index++].GetInt32();
    RequiredMinRepFaction   = questRecord[index++].GetUInt16();
    RequiredMaxRepFaction   = questRecord[index++].GetUInt16();
    RequiredMinRepValue     = questRecord[index++].GetInt32();
    RequiredMaxRepValue     = questRecord[index++].GetInt32();
    PrevQuestId             = questRecord[index++].GetInt32();
    NextQuestId             = questRecord[index++].GetInt32();
    ExclusiveGroup          = questRecord[index++].GetInt32();
    NextQuestIdChain        = questRecord[index++].GetUInt32();
    RewardXPId              = questRecord[index++].GetUInt8();
    RewardOrRequiredMoney   = questRecord[index++].GetInt32();
    RewardMoneyMaxLevel     = questRecord[index++].GetUInt32();
    RewardSpell             = questRecord[index++].GetUInt32();
    RewardSpellCast         = questRecord[index++].GetInt32();
    RewardHonor             = questRecord[index++].GetUInt32();
    RewardHonorMultiplier   = questRecord[index++].GetFloat();
    RewardMailTemplateId    = questRecord[index++].GetUInt32();
    RewardMailDelay         = questRecord[index++].GetUInt32();
    SourceItemId            = questRecord[index++].GetUInt32();
    SourceItemIdCount       = questRecord[index++].GetUInt8();
    SourceSpellid           = questRecord[index++].GetUInt32();
    Flags                   = questRecord[index++].GetUInt32();
    SpecialFlags            = questRecord[index++].GetUInt8();
    MinimapTargetMark       = questRecord[index++].GetUInt8();
    RewardTitleId           = questRecord[index++].GetUInt8();
    RequiredPlayerKills     = questRecord[index++].GetUInt8();
    RewardTalents           = questRecord[index++].GetUInt8();
    RewardArenaPoints       = questRecord[index++].GetUInt16();
    RewardSkillId           = questRecord[index++].GetUInt16();
    RewardSkillPoints       = questRecord[index++].GetUInt8();
    RewardReputationMask    = questRecord[index++].GetUInt8();
    QuestGiverPortrait      = questRecord[index++].GetUInt32();
    QuestTurnInPortrait     = questRecord[index++].GetUInt32();

    for (int i = 0; i < QUEST_REWARDS_COUNT; ++i)
        RewardItemId[i] = questRecord[index++].GetUInt32();

    for (int i = 0; i < QUEST_REWARDS_COUNT; ++i)
        RewardItemIdCount[i] = questRecord[index++].GetUInt16();

    for (int i = 0; i < QUEST_REWARD_CHOICES_COUNT; ++i)
        RewardChoiceItemId[i] = questRecord[index++].GetUInt32();

    for (int i = 0; i < QUEST_REWARD_CHOICES_COUNT; ++i)
        RewardChoiceItemCount[i] = questRecord[index++].GetUInt16();

    for (int i = 0; i < QUEST_REPUTATIONS_COUNT; ++i)
        RewardFactionId[i] = questRecord[index++].GetUInt16();

    for (int i = 0; i < QUEST_REPUTATIONS_COUNT; ++i)
        RewardFactionValueId[i] = questRecord[index++].GetInt32();

    for (int i = 0; i < QUEST_REPUTATIONS_COUNT; ++i)
        RewardFactionValueIdOverride[i] = questRecord[index++].GetInt32();

    PointMapId              = questRecord[index++].GetUInt16();
    PointX                  = questRecord[index++].GetFloat();
    PointY                  = questRecord[index++].GetFloat();
    PointOption             = questRecord[index++].GetUInt32();
    Title                   = questRecord[index++].GetString();
    Objectives              = questRecord[index++].GetString();
    Details                 = questRecord[index++].GetString();
    EndText                 = questRecord[index++].GetString();
    CompletedText           = questRecord[index++].GetString();
    OfferRewardText         = questRecord[index++].GetString();
    RequestItemsText        = questRecord[index++].GetString();

    for (int i = 0; i < QUEST_OBJECTIVES_COUNT; ++i)
        RequiredNpcOrGo[i] = questRecord[index++].GetInt32();

    for (int i = 0; i < QUEST_OBJECTIVES_COUNT; ++i)
        RequiredNpcOrGoCount[i] = questRecord[index++].GetUInt16();

    for (int i = 0; i < QUEST_SOURCE_ITEM_IDS_COUNT; ++i)
        RequiredSourceItemId[i] = questRecord[index++].GetUInt32();

    for (int i = 0; i < QUEST_SOURCE_ITEM_IDS_COUNT; ++i)
        RequiredSourceItemCount[i] = questRecord[index++].GetUInt16();

    for (int i = 0; i < QUEST_ITEM_OBJECTIVES_COUNT; ++i)
        RequiredItemId[i] = questRecord[index++].GetUInt32();

    for (int i = 0; i < QUEST_ITEM_OBJECTIVES_COUNT; ++i)
        RequiredItemCount[i] = questRecord[index++].GetUInt16();

    RequiredSpell           = questRecord[index++].GetUInt32();

    for (int i = 0; i < QUEST_OBJECTIVES_COUNT; ++i) // To be removed
        RequiredSpellCast[i] = questRecord[index++].GetUInt32();

    for (int i = 0; i < QUEST_OBJECTIVES_COUNT; ++i)
        ObjectiveText[i] = questRecord[index++].GetString();

    for (int i = 0; i < QUEST_REWARD_CURRENCY_COUNT; ++i)
        RewardCurrencyId[i] = questRecord[index++].GetUInt16();

    for (int i = 0; i < QUEST_REWARD_CURRENCY_COUNT; ++i)
        RewardCurrencyCount[i] = questRecord[index++].GetUInt8();

    for (int i = 0; i < QUEST_REQUIRED_CURRENCY_COUNT; ++i)
        RequiredCurrencyId[i] = questRecord[index++].GetUInt16();

    for (int i = 0; i < QUEST_REQUIRED_CURRENCY_COUNT; ++i)
        RequiredCurrencyCount[i] = questRecord[index++].GetUInt8();

    QuestGiverTextWindow    = questRecord[index++].GetString();
    QuestGiverTargetName    = questRecord[index++].GetString();
    QuestTurnTextWindow     = questRecord[index++].GetString();
    QuestTurnTargetName     = questRecord[index++].GetString();
    SoundAccept             = questRecord[index++].GetUInt16();
    SoundTurnIn             = questRecord[index++].GetUInt16();

    for (int i = 0; i < QUEST_EMOTE_COUNT; ++i)
        DetailsEmote[i] = questRecord[index++].GetUInt16();

    for (int i = 0; i < QUEST_EMOTE_COUNT; ++i)
        DetailsEmoteDelay[i] = questRecord[index++].GetUInt32();

    EmoteOnIncomplete       = questRecord[index++].GetUInt16();
    EmoteOnComplete         = questRecord[index++].GetUInt16();

    for (int i = 0; i < QUEST_EMOTE_COUNT; ++i)
        OfferRewardEmote[i] = questRecord[index++].GetInt16();

    for (int i = 0; i < QUEST_EMOTE_COUNT; ++i)
        OfferRewardEmoteDelay[i] = questRecord[index++].GetInt32();

    StartScript             = questRecord[index++].GetUInt32();
    CompleteScript          = questRecord[index++].GetUInt32();

    // int32 WDBVerified = questRecord[index++].GetInt32();

    if (SpecialFlags & QUEST_SPECIAL_FLAGS_AUTO_ACCEPT)
        Flags |= QUEST_FLAGS_AUTO_ACCEPT;

    m_reqItemsCount = 0;
    m_reqNpcOrGoCount = 0;
    m_rewItemsCount = 0;
    m_rewChoiceItemsCount = 0;
    m_rewCurrencyCount = 0;
    m_reqCurrencyCount = 0;

    for (int i = 0; i < QUEST_ITEM_OBJECTIVES_COUNT; ++i)
        if (RequiredItemId[i])
            ++m_reqItemsCount;

    for (int i = 0; i < QUEST_OBJECTIVES_COUNT; ++i)
        if (RequiredNpcOrGo[i])
            ++m_reqNpcOrGoCount;

    for (int i = 0; i < QUEST_REWARDS_COUNT; ++i)
        if (RewardItemId[i])
            ++m_rewItemsCount;

    for (int i = 0; i < QUEST_REWARD_CHOICES_COUNT; ++i)
        if (RewardChoiceItemId[i])
            ++m_rewChoiceItemsCount;

    for (int i = 0; i < QUEST_REWARD_CURRENCY_COUNT; ++i)
        if (RewardCurrencyId[i])
            ++m_rewCurrencyCount;

    for (int i = 0; i < QUEST_REQUIRED_CURRENCY_COUNT; ++i)
        if (RequiredCurrencyId[i])
            ++m_reqCurrencyCount;

}

uint32 Quest::XPValue(Player* player) const
{
    if (player)
    {
        int32 quest_level = (Level == -1 ? player->getLevel() : Level);
        const QuestXPEntry* xpentry = sQuestXPStore.LookupEntry(quest_level);
        if (!xpentry)
            return 0;

        int32 diffFactor = 2 * (quest_level - player->getLevel()) + 20;
        if (diffFactor < 1)
            diffFactor = 1;
        else if (diffFactor > 10)
            diffFactor = 10;

        uint32 xp = diffFactor * xpentry->Exp[RewardXPId] / 10;
        if (xp <= 100)
            xp = 5 * ((xp + 2) / 5);
        else if (xp <= 500)
            xp = 10 * ((xp + 5) / 10);
        else if (xp <= 1000)
            xp = 25 * ((xp + 12) / 25);
        else
            xp = 50 * ((xp + 25) / 50);

        return xp;
    }

    return 0;
}

int32 Quest::GetRewOrReqMoney() const
{
    if (RewardOrRequiredMoney <= 0)
        return RewardOrRequiredMoney;

    return int32(RewardOrRequiredMoney * sWorld->getRate(RATE_DROP_MONEY));
}

void Quest::BuildExtraQuestInfo(WorldPacket& data, Player* player) const
{
    data << uint32(GetRewChoiceItemsCount());
    for (uint8 i = 0; i < QUEST_REWARD_CHOICES_COUNT; ++i)
    {
        data << uint32(RewardChoiceItemId[i]);
        data << uint32(RewardChoiceItemCount[i]);
        if (ItemTemplate const* itemTemplate = sObjectMgr->GetItemTemplate(RewardChoiceItemId[i]))
            data << uint32(itemTemplate->DisplayInfoID);
        else
            data << uint32(0);
    }

    data << uint32(GetReqItemsCount());
    for (uint8 i = 0; i < QUEST_REWARDS_COUNT; ++i)
        data << uint32(RewardItemId[i]);
    for (uint8 i = 0; i < QUEST_REWARDS_COUNT; ++i)
        data << uint32(RewardItemIdCount[i]);
    for (uint8 i = 0; i < QUEST_REWARDS_COUNT; ++i)
    {
        if (ItemTemplate const* itemTemplate = sObjectMgr->GetItemTemplate(RewardItemId[i]))
            data << uint32(itemTemplate->DisplayInfoID);
        else
            data << uint32(0);
    }

    data << uint32(GetRewOrReqMoney());

    float QuestXpRate = 1;
    if(player->GetPersonnalXpRate())
        QuestXpRate = player->GetPersonnalXpRate();
    else
        QuestXpRate = sWorld->getRate(RATE_XP_QUEST);

    data << uint32(XPValue(player) * QuestXpRate);

    data << uint32(0);                                      // unk
    data << uint32(GetBonusTalents());
    data << uint32(GetRewardReputationMask());

    /* Pre cata struct, some of these unks might be the missing values in cata:
    // rewarded honor points. Multiply with 10 to satisfy client
    data << uint32(10 * quest->CalculateHonorGain(_session->GetPlayer()->GetQuestLevel(quest)));
    data << float(0.0f);                                    // unk, honor multiplier?
    data << uint32(0x08);                                   // unused by client?
    data << uint32(quest->GetRewSpell());                   // reward spell, this spell will display (icon) (casted if RewSpellCast == 0)
    data << int32(quest->GetRewSpellCast());                // casted spell
    data << uint32(0);                                      // unknown
    data << uint32(quest->GetBonusTalents());               // bonus talents
    data << uint32(quest->GetRewArenaPoints());             // arena points
    data << uint32(0);
    */

    for (uint8 i = 0; i < QUEST_REPUTATIONS_COUNT; ++i)    // reward factions ids
        data << uint32(RewardFactionId[i]);

    for (uint8 i = 0; i < QUEST_REPUTATIONS_COUNT; ++i)    // columnid in QuestFactionReward.dbc (zero based)?
        data << int32(RewardFactionValueId[i]);

    for (uint8 i = 0; i < QUEST_REPUTATIONS_COUNT; ++i)    // reward reputation override?
        data << uint32(RewardFactionValueIdOverride[i]);

    data << uint32(GetRewSpell());
    data << uint32(GetRewSpellCast());

    for (uint8 i = 0; i < QUEST_REWARD_CURRENCY_COUNT; ++i)
        data << uint32(RewardCurrencyId[i]);

    for (uint8 i = 0; i < QUEST_REWARD_CURRENCY_COUNT; ++i)
        data << uint32(RewardCurrencyCount[i]);

    data << uint32(GetRewardSkillId());
    data << uint32(GetRewardSkillPoints());
}

bool Quest::IsAutoAccept() const
{
    return sWorld->getBoolConfig(CONFIG_QUEST_IGNORE_AUTO_ACCEPT) ? false : (Flags & QUEST_FLAGS_AUTO_ACCEPT);
}

bool Quest::IsAutoComplete() const
{
    return sWorld->getBoolConfig(CONFIG_QUEST_IGNORE_AUTO_COMPLETE) ? false : (Method == 0 || HasFlag(QUEST_FLAGS_AUTOCOMPLETE));
}

bool Quest::IsAllowedInRaid() const
{
    if (IsRaidQuest())
        return true;

    return sWorld->getBoolConfig(CONFIG_QUEST_IGNORE_RAID);
}

uint32 Quest::CalculateHonorGain(uint8 level) const
{
    if (level > GT_MAX_LEVEL)
        level = GT_MAX_LEVEL;

    uint32 honor = 0;

    /*if (GetRewHonorAddition() > 0 || GetRewHonorMultiplier() > 0.0f)
    {
        // values stored from 0.. for 1...
        TeamContributionPointsEntry const* tc = sTeamContributionPointsStore.LookupEntry(level);
        if (!tc)
            return 0;
        honor = uint32(tc->value * GetRewHonorMultiplier() * 0.1f);
        honor += GetRewHonorAddition();
    }*/

    return honor;
}
