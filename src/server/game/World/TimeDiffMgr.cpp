#include "TimeDiffMgr.h"
#include "Timer.h"
#include "World.h"
#include "DatabaseEnv.h"

void TimeDiffMgr::Initialize()
{
    for (uint32 i = 0; i < INTERVAL_MAX; ++i)
        InitTimer(UpdateTimeLogInterval(i));
    for (uint32 i = 0; i < INTERVAL_MAX; ++i)
    {
        m_prevLog[i].Average = 0;
        m_prevLog[i].Max = 0;
        m_prevLog[i].Players = 0;
    }
}

void TimeDiffMgr::InitTimer(UpdateTimeLogInterval interval)
{
    if (interval >= INTERVAL_MAX)
        return;

    m_worldSum[interval] = 0;
    m_worldCount[interval] = 0;
    m_worldMax[interval] = 0;
    m_worldUpdate[interval] = getMSTime();
}

void TimeDiffMgr::Update(uint32 diff)
{
    for (uint32 i = 0; i < INTERVAL_MAX; ++i)
    {
        if (diff > m_worldMax[i])
            m_worldMax[i] = diff;

        ++m_worldCount[i];
        m_worldSum[i] += diff;
    }

    if (GetMSTimeDiffToNow(m_worldUpdate[INTERVAL_1_MINUTE]) >= MINUTE * IN_MILLISECONDS)
    {
        m_prevLog[INTERVAL_1_MINUTE].Average = m_worldSum[INTERVAL_1_MINUTE] / m_worldCount[INTERVAL_1_MINUTE];
        m_prevLog[INTERVAL_1_MINUTE].Max = m_worldMax[INTERVAL_1_MINUTE];
        m_prevLog[INTERVAL_1_MINUTE].Players = sWorld->GetActiveSessionCount();
        InitTimer(INTERVAL_1_MINUTE);

        CharacterDatabase.PExecute(
            "INSERT INTO time_diff_log (time, average, max, players) VALUES (UNIX_TIMESTAMP(), %u, %u, %u)",
            m_prevLog[INTERVAL_1_MINUTE].Average, m_prevLog[INTERVAL_1_MINUTE].Max,
            m_prevLog[INTERVAL_1_MINUTE].Players);
    }

    if (GetMSTimeDiffToNow(m_worldUpdate[INTERVAL_5_MINUTE]) >= 5 * MINUTE * IN_MILLISECONDS)
    {
        m_prevLog[INTERVAL_5_MINUTE].Average = m_worldSum[INTERVAL_5_MINUTE] / m_worldCount[INTERVAL_5_MINUTE];
        m_prevLog[INTERVAL_5_MINUTE].Max = m_worldMax[INTERVAL_5_MINUTE];
        m_prevLog[INTERVAL_5_MINUTE].Players = sWorld->GetActiveSessionCount();
        InitTimer(INTERVAL_5_MINUTE);
    }

    if (GetMSTimeDiffToNow(m_worldUpdate[INTERVAL_15_MINUTE]) >= 15 * MINUTE * IN_MILLISECONDS)
    {
        m_prevLog[INTERVAL_15_MINUTE].Average = m_worldSum[INTERVAL_15_MINUTE] / m_worldCount[INTERVAL_15_MINUTE];
        m_prevLog[INTERVAL_15_MINUTE].Max = m_worldMax[INTERVAL_15_MINUTE];
        m_prevLog[INTERVAL_15_MINUTE].Players = sWorld->GetActiveSessionCount();
        InitTimer(INTERVAL_15_MINUTE);
    }
}
