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

#ifndef LOG_H
#define LOG_H

#include "Define.h"
#include "Appender.h"
#include "LogWorker.h"
#include "Logger.h"

#include <ace/Singleton.h>

#include <string>
#include <set>

class Log
{
    friend class ACE_Singleton<Log, ACE_Thread_Mutex>;

    typedef std::map<uint8, Logger> LoggerMap;

    private:
        Log();
        ~Log();

    public:
        void LoadFromConfig();
        void Close();
        bool ShouldLog(LogFilterType type, LogLevel level) const;
        bool SetLogLevel(std::string const& name, char const* level, bool isLogger = true);

        void outTrace(LogFilterType f, char const* str, ...) ATTR_PRINTF(3,4);
        void outDebug(LogFilterType f, char const* str, ...) ATTR_PRINTF(3,4);
        void outInfo (LogFilterType f, char const* str, ...) ATTR_PRINTF(3,4);
        void outWarn (LogFilterType f, char const* str, ...) ATTR_PRINTF(3,4);
        void outError(LogFilterType f, char const* str, ...) ATTR_PRINTF(3,4);
        void outFatal(LogFilterType f, char const* str, ...) ATTR_PRINTF(3,4);
        void outArena( const char * str, ... )               ATTR_PRINTF(2, 3);
        void outCommand( uint32 gm_account_id  , std::string gm_account_name,
                         uint32 gm_character_id, std::string gm_character_name,
                         uint32 sc_account_id  , std::string sc_account_name,
                         uint32 sc_character_id, std::string sc_character_name,
                         const char * str, ...)              ATTR_PRINTF(10,11);
        void outGmChat( uint32 message_type,
                        uint32 from_account_id  , std::string from_account_name,
                        uint32 from_character_id, std::string from_character_name,
                        uint32 to_account_id  , std::string to_account_name,
                        uint32 to_character_id, std::string to_character_name,
                        const char * str);
        void outCharDump(char const* str, uint32 account_id, uint32 guid, char const* name);

        void OutPandashan(const char* str, ...);

        void EnableDBAppenders();
        static std::string GetTimestampStr();
        
        void SetRealmID(uint32 id);
        uint32 GetRealmID() const { return realm; }

    private:
        void vlog(LogFilterType f, LogLevel level, char const* str, va_list argptr);
        void write(LogMessage* msg);

        Logger* GetLoggerByType(LogFilterType filter);
        Appender* GetAppenderByName(std::string const& name);
        uint8 NextAppenderId();
        void CreateAppenderFromConfig(const char* name);
        void CreateLoggerFromConfig(const char* name);
        void ReadAppendersFromConfig();
        void ReadLoggersFromConfig();

        AppenderMap appenders;
        LoggerMap loggers;
        uint8 AppenderId;

        std::string m_logsDir;
        std::string m_logsTimestamp;

        uint32 realm;
        LogWorker* worker;

        FILE* pandashanLog;
};

#define sLog ACE_Singleton<Log, ACE_Thread_Mutex>::instance()

#endif
