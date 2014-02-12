#ifndef TIMEDIFFMGR_H
#define TIMEDIFFMGR_H

#include <ace/Singleton.h>
#include "Common.h"

enum UpdateTimeLogInterval
{
    INTERVAL_1_MINUTE     = 0,
    INTERVAL_5_MINUTE     = 1,
    INTERVAL_15_MINUTE    = 2
};

#define INTERVAL_MAX 3

struct PerfLog
{
    uint32 Average;
    uint32 Max;
    uint32 Players;
};

class TimeDiffMgr
{
public:
    TimeDiffMgr() {}
    void Initialize();
    void Update(uint32 diff);
    const PerfLog GetPerfLog(UpdateTimeLogInterval interval) const { return m_prevLog[interval]; }

private:
    void InitTimer(UpdateTimeLogInterval interval);
    uint32 m_worldCount[INTERVAL_MAX];
    uint32 m_worldSum[INTERVAL_MAX];
    uint32 m_worldUpdate[INTERVAL_MAX];
    uint32 m_worldMax[INTERVAL_MAX];
    PerfLog m_prevLog[INTERVAL_MAX];
};

#define sTimeDiffMgr ACE_Singleton<TimeDiffMgr, ACE_Null_Mutex>::instance()

#endif // TIMEDIFFMGR_H
