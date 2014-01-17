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

/** \file
    \ingroup Trinityd
*/

#include <ace/Sig_Handler.h>

#include "Common.h"
#include "SystemConfig.h"
#include "SignalHandler.h"
#include "World.h"
#include "WorldRunnable.h"
#include "WorldSocket.h"
#include "WorldSocketMgr.h"
#include "Configuration/Config.h"
#include "Database/DatabaseEnv.h"
#include "Database/DatabaseWorkerPool.h"
#include "PlayerDump.h"
#include "Player.h"
#include "ObjectMgr.h"

#include "CliRunnable.h"
#include "Log.h"
#include "Master.h"
#include "RARunnable.h"
#include "TCSoap.h"
#include "Timer.h"
#include "Util.h"
#include "AuthSocket.h"
#include "RealmList.h"

#include "BigNumber.h"

#ifdef _WIN32
#include "ServiceWin32.h"
extern int m_ServiceStatus;
#endif

/// Handle worldservers's termination signals
class WorldServerSignalHandler : public JadeCore::SignalHandler
{
    public:
        virtual void HandleSignal(int SigNum)
        {
            switch (SigNum)
            {
                case SIGINT:
                    World::StopNow(RESTART_EXIT_CODE);
                    break;
                case SIGTERM:
                #ifdef _WIN32
                case SIGBREAK:
                    if (m_ServiceStatus != 1)
                #endif /* _WIN32 */
                    World::StopNow(SHUTDOWN_EXIT_CODE);
                    break;
            }
        }
};

class FreezeDetectorRunnable : public ACE_Based::Runnable
{
public:
    FreezeDetectorRunnable() { _delaytime = 0; }
    uint32 m_loops, m_lastchange;
    uint32 w_loops, w_lastchange;
    uint32 _delaytime;
    void SetDelayTime(uint32 t) { _delaytime = t; }
    void run(void)
    {
        if (!_delaytime)
            return;
        sLog->outInfo(LOG_FILTER_WORLDSERVER, "Starting up anti-freeze thread (%u seconds max stuck time)...", _delaytime/1000);
        m_loops = 0;
        w_loops = 0;
        m_lastchange = 0;
        w_lastchange = 0;
        while (!World::IsStopped())
        {
            ACE_Based::Thread::Sleep(1000);
            uint32 curtime = getMSTime();
            // normal work
            uint32 worldLoopCounter = World::m_worldLoopCounter.value();
            if (w_loops != worldLoopCounter)
            {
                w_lastchange = curtime;
                w_loops = worldLoopCounter;
            }
            // possible freeze
            else if (getMSTimeDiff(w_lastchange, curtime) > _delaytime)
            {
                sLog->outError(LOG_FILTER_WORLDSERVER, "World Thread hangs, kicking out server!");
                ASSERT(false);
            }
        }
        sLog->outInfo(LOG_FILTER_WORLDSERVER, "Anti-freeze thread exiting without problems.");
    }
};

class GmLogToDBRunnable : public ACE_Based::Runnable
{
public:

    void run ()
    {
        while (!World::IsStopped())
        {
            GmCommand * command;
            while(!GmLogQueue.empty())
            {
                GmLogQueue.next(command);
                CharacterDatabase.EscapeString(command->accountName[0]);
                CharacterDatabase.EscapeString(command->accountName[1]);
                CharacterDatabase.EscapeString(command->characterName[0]);
                CharacterDatabase.EscapeString(command->characterName[1]);
                CharacterDatabase.EscapeString(command->command);
                //No sql injections. Strings are escaped.

                //au cas ou on a pas les infos...
                if(command->accountName[0] == "" && command->accountID[0] != 0)
                {
                    QueryResult result = LoginDatabase.PQuery("SELECT username FROM account WHERE id = %u", command->accountID[0]);
                    if (result)
                    {
                        Field *fields = result->Fetch();
                        command->accountName[0] = fields[0].GetString();
                        CharacterDatabase.EscapeString(command->accountName[0]);
                    }
                }

                if(command->accountName[1] == "" && command->accountID[1] != 0)
                {
                    QueryResult result = LoginDatabase.PQuery("SELECT username FROM account WHERE id = %u", command->accountID[1]);
                    if (result)
                    {
                        Field *fields = result->Fetch();
                        command->accountName[1] = fields[0].GetString();
                        CharacterDatabase.EscapeString(command->accountName[1]);
                    }
                }

                if(command->characterName[0] == "" && command->characterID[0] != 0)
                {
                    QueryResult result = CharacterDatabase.PQuery("SELECT name FROM character WHERE guid = %u", command->characterID[0]);
                    if (result)
                    {
                        Field *fields = result->Fetch();
                        command->characterName[0] = fields[0].GetString();
                        CharacterDatabase.EscapeString(command->characterName[0]);
                    }
                }

                if(command->characterName[0] == "" && command->characterID[0] != 0)
                {
                    QueryResult result = CharacterDatabase.PQuery("SELECT name FROM character WHERE guid = %u", command->characterID[0]);
                    if (result)
                    {
                        Field *fields = result->Fetch();
                        command->characterName[0] = fields[0].GetString();
                        CharacterDatabase.EscapeString(command->characterName[0]);
                    }
                }

                if(command->characterName[1] == "" && command->characterID[1] != 0)
                {
                    QueryResult result = CharacterDatabase.PQuery("SELECT name FROM character WHERE guid = %u", command->characterID[1]);
                    if (result)
                    {
                        Field *fields = result->Fetch();
                        command->characterName[1] = fields[0].GetString();
                        CharacterDatabase.EscapeString(command->characterName[1]);
                    }
                }

                std::string last_ip = " ";

                QueryResult result = LoginDatabase.PQuery("SELECT last_ip FROM account WHERE id = %u", command->accountID[0]);
                if (result)
                {
                    Field *fields_ip = result->Fetch();
                    last_ip = fields_ip[0].GetString();
                }

                if(command->accountID[1] == 0 && command->characterID == 0)
                {
                    command->accountID[1] = command->accountID[0];
                    command->characterID[1] = command->characterID[0];
                    command->accountName[1] = command->accountName[0];
                    command->characterName[1] = command->characterName[0];
                }

                CharacterDatabase.PExecute(	"INSERT INTO log_gm(`date`, "
                    "`gm_account_id`, `gm_account_name`, `gm_character_id`, `gm_character_name`, `gm_last_ip`,"
                    "`sc_account_id`, `sc_account_name`, `sc_character_id`, `sc_character_name`,"
                    "`command`)"
                    "VALUES(NOW(),"
                    "%u,'%s',%u,'%s','%s',"
                    "%u,'%s',%u,'%s',"
                    "'%s')",
                    command->accountID[0], command->accountName[0].c_str(), command->characterID[0], command->characterName[0].c_str(), last_ip.c_str(),
                    command->accountID[1], command->accountName[1].c_str(), command->characterID[1], command->characterName[1].c_str(),
                    command->command.c_str());
                delete command;
            }
            ACE_Based::Thread::Sleep(1000);
        }
    }
};

class GmChatLogToDBRunnable : public ACE_Based::Runnable
{
public:

    void run ()
    {
        while (!World::IsStopped())
        {
            GmChat * ChatLog;
            while(!GmChatLogQueue.empty())
            {
                GmChatLogQueue.next(ChatLog);
                CharacterDatabase.EscapeString(ChatLog->accountName[0]);
                CharacterDatabase.EscapeString(ChatLog->accountName[1]);
                CharacterDatabase.EscapeString(ChatLog->characterName[0]);
                CharacterDatabase.EscapeString(ChatLog->characterName[1]);
                CharacterDatabase.EscapeString(ChatLog->message);
                //No sql injections. Strings are escaped.

                //au cas ou on a pas les infos...
                if(ChatLog->accountName[0] == "" && ChatLog->accountID[0] != 0)
                {
                    QueryResult result = LoginDatabase.PQuery("SELECT username FROM account WHERE id = %u", ChatLog->accountID[0]);
                    if (result)
                    {
                        Field *fields = result->Fetch();
                        ChatLog->accountName[0] = fields[0].GetString();
                        CharacterDatabase.EscapeString(ChatLog->accountName[0]);
                    }
                }

                if(ChatLog->accountName[1] == "" && ChatLog->accountID[1] != 0)
                {
                    QueryResult result = LoginDatabase.PQuery("SELECT username FROM account WHERE id = %u", ChatLog->accountID[1]);
                    if (result)
                    {
                        Field *fields = result->Fetch();
                        ChatLog->accountName[1] = fields[0].GetString();
                        CharacterDatabase.EscapeString(ChatLog->accountName[1]);
                    }
                }

                if(ChatLog->characterName[0] == "" && ChatLog->characterID[0] != 0)
                {
                    QueryResult result = CharacterDatabase.PQuery("SELECT name FROM character WHERE guid = %u", ChatLog->characterID[0]);
                    if (result)
                    {
                        Field *fields = result->Fetch();
                        ChatLog->characterName[0] = fields[0].GetString();
                        CharacterDatabase.EscapeString(ChatLog->characterName[0]);
                    }
                }

                if(ChatLog->characterName[1] == "" && ChatLog->characterID[1] != 0)
                {
                    QueryResult result = CharacterDatabase.PQuery("SELECT name FROM character WHERE guid = %u", ChatLog->characterID[1]);
                    if (result)
                    {
                        Field *fields = result->Fetch();
                        ChatLog->characterName[1] = fields[0].GetString();
                        CharacterDatabase.EscapeString(ChatLog->characterName[1]);
                    }
                }

                CharacterDatabase.PExecute(	"INSERT INTO log_gm_chat(`type`, `date`, "
                    "`from_account_id`, `from_account_name`, `from_character_id`, `from_character_name`,"
                    "`to_account_id`, `to_account_name`, `to_character_id`, `to_character_name`,"
                    "`message`)"
                    "VALUES(%u, NOW(),"
                    "%u,'%s',%u,'%s',"
                    "%u,'%s',%u,'%s',"
                    "'%s')",
                    ChatLog->type,
                    ChatLog->accountID[0], ChatLog->accountName[0].c_str(), ChatLog->characterID[0], ChatLog->characterName[0].c_str(),
                    ChatLog->accountID[1], ChatLog->accountName[1].c_str(), ChatLog->characterID[1], ChatLog->characterName[1].c_str(),
                    ChatLog->message.c_str());
                delete ChatLog;
            }
            ACE_Based::Thread::Sleep(1000);
        }
    }
};

class ArenaLogToDBRunnable : public ACE_Based::Runnable
{
public:

    void run ()
    {
        while (!World::IsStopped())
        {
            ArenaLog * log;
            while(!ArenaLogQueue.empty())
            {
                ArenaLogQueue.next(log);
                CharacterDatabase.EscapeString(log->str);
                //No sql injections. Strings are escaped.

                CharacterDatabase.PExecute("INSERT INTO log_arena (`id`, `timestamp`, `string`) VALUES (0, %u, '%s');", log->timestamp, log->str.c_str());
                delete log;
            }
            ACE_Based::Thread::Sleep(1000);
        }
    }
};

const char* dumpTables[32] =
{
    "characters",
    "character_account_data",
    "character_achievement",
    "character_achievement_progress",
    "character_action",
    "character_aura",
    "character_aura_effect",
    "character_currency",
    //{ "character_cuf_profiles",
    "character_declinedname",
    "character_equipmentsets",
    "character_gifts",
    "character_glyphs",
    "character_homebind",
    "character_inventory",
    "character_pet",
    "character_pet_declinedname",
    "character_queststatus",
    "character_queststatus_rewarded",
    "character_rates",
    "character_reputation",
    "character_skills",
    "character_spell",
    "character_spell_cooldown",
    "character_talent",
    "character_void_storage",
    "item_instance",
    "mail",
    "mail_items",
    "pet_aura",
    "pet_aura_effect",
    "pet_spell",
    "pet_spell_cooldown"
};

const char* ipTransfert[4] =
{
    "37.187.68.78",      // Rassharom
    "37.187.68.57",    // Taran'Zhu
    "37.187.68.57",     // Elegon
    "37.187.68.78"      // Hellscream
};

class CharactersTransfertRunnable : public ACE_Based::Runnable
{
public:
    CharactersTransfertRunnable() {}
    void run(void)
    {
        printf("Thread de transfert de perso demarre.\n");

        std::string hash_transfert = "";

        for (int i = 0; i < 32; i++)
        {
            const char* tableName = dumpTables[i];
            QueryResult tableInfo = CharacterDatabase.PQuery("select data_type from information_schema.columns where table_name = '%s' AND table_schema IN ('505_characters', '505_characters_us')", tableName);
            if(tableInfo)
            {
                do
                {
                    Field* fieldInfo = tableInfo->Fetch();
                    hash_transfert += fieldInfo[0].GetString().substr(0, 1);
                }
                while
                    (tableInfo->NextRow());
            }
        }

        printf("hash_transfert : %s\n", hash_transfert.c_str());

        while (!World::IsStopped())
        {
            ACE_Based::Thread::Sleep(5000);
            QueryResult toDump = LoginDatabase.PQuery("SELECT `id`, `account`, `perso_guid` FROM transferts WHERE `from` = %u AND (state = 0 OR revision <> '%s')", sLog->GetRealmID(), hash_transfert.c_str());
            QueryResult toLoad = LoginDatabase.PQuery("SELECT `id`, `account`, `perso_guid`, `from` FROM transferts WHERE `to` = %u AND state = 1 AND revision = '%s'", sLog->GetRealmID(), hash_transfert.c_str());


            //id account perso_guid from to revision dump last_error nb_attempt
            if(toDump)
            {
                do
                {
                    Field* field = toDump->Fetch();
                    uint32 transaction = field[0].GetUInt32();
                    uint32 perso_guid = field[2].GetUInt32();

                    if (Player * pPlayer = sObjectMgr->GetPlayerByLowGUID(perso_guid))
                    {
                        pPlayer->GetSession()->SendNotification("Vous devez vous deconnecter pour pouvoir transferer votre personnage");
                        continue;
                    }

                    CharacterDatabase.PExecute("DELETE FROM group_member WHERE memberGuid = '%u'",  perso_guid);
                    CharacterDatabase.PExecute("DELETE FROM guild_member WHERE guid = '%u'",        perso_guid);

                    std::ostringstream fileName;

                    fileName << "/home/transfert" << sLog->GetRealmID() << "/" << perso_guid << ".dump";

                    DumpReturn dump = PlayerDumpWriter().WriteDump(fileName.str().c_str(), perso_guid);

                    if (dump == DUMP_SUCCESS)
                    {
                        CharacterDatabase.PExecute("UPDATE characters SET at_login = '%u' WHERE guid = '%u'", AT_LOGIN_LOCKED_FOR_TRANSFER, perso_guid);
                        CharacterDatabase.PExecute("UPDATE characters SET deleteInfos_Name=name, deleteInfos_Account=account, deleteDate='" UI64FMTD "', name='', account=0 WHERE guid=%u", uint64(time(NULL)), perso_guid);
                        LoginDatabase.PQuery("UPDATE transferts SET state = 1, revision = '%s' WHERE id = %u", hash_transfert.c_str(), transaction);
                    }
                    else
                    {
                    	LoginDatabase.PQuery("UPDATE transferts SET error = %u WHERE id = %u", dump, transaction);
                    	continue;
                    }

                    /*std::string result = "";
                    if(PlayerDumpWriter().GetDump(perso_guid, result))
                    {
                        std::string result2 = "";
                        PlayerDumpWriter().GetDump(perso_guid, result2);
                        if(result != result2)
                            continue;

                        std::string new_string = "";
                        for(std::string::iterator i = result.begin(); i < result.end(); i++)
                        {
                            if((*i) == '\\')
                                new_string.push_back('\\');
                            new_string.push_back(*i);
                        }

                        PreparedStatement * stmt = LoginDatabase.GetPreparedStatement(LOGIN_SET_DUMP);
                        if(stmt)
                        {
                            stmt->setString(0, new_string);
                            stmt->setString(1, hash_transfert.c_str());
                            stmt->setUInt32(2, transaction);
                            LoginDatabase.Execute(stmt);

                            CharacterDatabase.PExecute("UPDATE characters SET at_login = '%u' WHERE guid = '%u'", AT_LOGIN_LOCKED_FOR_TRANSFER, perso_guid);
                            CharacterDatabase.PExecute("UPDATE characters SET deleteInfos_Name=name, deleteInfos_Account=account, deleteDate='" UI64FMTD "', name='', account=0 WHERE guid=%u", uint64(time(NULL)), perso_guid);
                        }
                    }*/
                }
                while(toDump->NextRow());
            }

            if(toLoad)
            {
                do
                {
                    Field* field = toLoad->Fetch();
                    uint32 transaction = field[0].GetUInt32();
                    uint32 account = field[1].GetUInt32();
                    uint32 perso_guid = field[2].GetUInt32();
                    uint32 from = field[3].GetUInt32();
                    std::ostringstream cmd;

                    // Get new dump
                    cmd << "wget " << ipTransfert[from-1] << "/transfert" << from << "/" << perso_guid << ".dump --directory-prefix=/home/transfert" << from << "/";
                    system(cmd.str().c_str());
                    cmd.str("");
                    cmd.clear();
                    
                    cmd << "/home/transfert" << from << "/" << perso_guid << ".dump";
                    DumpReturn dump = PlayerDumpReader().LoadDump(cmd.str(), account, "", 0);

                    cmd.str("");
                    cmd.clear();

                    if (dump == DUMP_SUCCESS)
                    {
                        // Delete old dump
                        cmd << "rm /home/transfert" << from << "/" << perso_guid << ".dump";
                        system(cmd.str().c_str());
                        cmd.str("");
                        cmd.clear();

                    	LoginDatabase.PQuery("DELETE FROM transferts WHERE id = %u", transaction);
                        PreparedStatement * stmt = LoginDatabase.GetPreparedStatement(LOGIN_ADD_TRANSFERTS_LOGS);
                        if(stmt)
                        {
                            stmt->setUInt32(0, transaction);
                            stmt->setUInt32(1, account);
                            stmt->setUInt32(2, perso_guid);
                            stmt->setUInt32(3, from);
                            stmt->setUInt32(4, sLog->GetRealmID());
                            stmt->setString(5, "");
                            LoginDatabase.Execute(stmt);
                        }
                    }
                    else
                    {
                    	LoginDatabase.PQuery("UPDATE transferts SET error = %u, nb_attempt = nb_attempt + 1 WHERE id = %u", dump, transaction);
                    	continue;
                    }


                    /*FILE *fout = fopen("temp.dump", "w");
                    if(!fout)
                        continue;
                    fprintf(fout, "%s\n", dump.c_str());
                    fclose(fout);

                    switch(PlayerDumpReader().LoadDump("temp.dump", account, "", 0, AT_LOGIN_RENAME))
                    {
                        case DUMP_SUCCESS:
                        {
                            sLog->outString("Personne ok.");
                            LoginDatabase.PQuery("DELETE FROM transferts WHERE id = %u", transaction);
                            LoginDatabase.EscapeString(dump);

                            PreparedStatement * stmt = LoginDatabase.GetPreparedStatement(LOGIN_ADD_TRANSFERTS_LOGS);
                            if(stmt)
                            {
                                stmt->setUInt32(0, transaction);
                                stmt->setUInt32(1, account);
                                stmt->setUInt32(2, perso_guid);
                                stmt->setUInt32(3, from);
                                stmt->setUInt32(4, sLog->GetRealmID());
                                stmt->setString(5, dump.c_str());
                                LoginDatabase.Execute(stmt);
                            }
                            break;
                        }
                        case DUMP_FILE_OPEN_ERROR:
                            LoginDatabase.PQuery("UPDATE transferts SET last_error = 'DUMP_FILE_OPEN_ERROR', nb_attempt = nb_attempt + 1 WHERE id = %u", transaction);
                            break;
                        case DUMP_FILE_BROKEN:
                            LoginDatabase.PQuery("UPDATE transferts SET last_error = 'DUMP_FILE_BROKEN', nb_attempt = nb_attempt + 1 WHERE id = %u", transaction);
                            break;
                        case DUMP_TOO_MANY_CHARS:
                            LoginDatabase.PQuery("UPDATE transferts SET last_error = 'DUMP_TOO_MANY_CHARS', nb_attempt = nb_attempt + 1 WHERE id = %u", transaction);
                            break;
                        default:
                            break;
                    }*/
                }
                while (toLoad->NextRow());
            }
        }
    }
};

Master::Master()
{
}

Master::~Master()
{
}

/// Main function
int Master::Run()
{
    BigNumber seed1;
    seed1.SetRand(16 * 8);

    sLog->outInfo(LOG_FILTER_WORLDSERVER, "%s (worldserver-daemon)", _FULLVERSION);
    sLog->outInfo(LOG_FILTER_WORLDSERVER, "<Ctrl-C> to stop.\n");

    sLog->outInfo(LOG_FILTER_WORLDSERVER, "       __          __     ______              ");
    sLog->outInfo(LOG_FILTER_WORLDSERVER, "      / /___ _____/ /__  / ____/___  ________ ");
    sLog->outInfo(LOG_FILTER_WORLDSERVER, " __  / / __ `/ __  / _ \\/ /   / __ \\/ ___/ _ \\");
    sLog->outInfo(LOG_FILTER_WORLDSERVER, "/ /_/ / /_/ / /_/ /  __/ /___/ /_/ / /  /  __/");
    sLog->outInfo(LOG_FILTER_WORLDSERVER, "\\____/\\__,_/\\__,_/\\___/\\____/\\____/_/   \\___/");
    sLog->outInfo(LOG_FILTER_WORLDSERVER, "http://www.pandashan.com\n");

    /// worldserver PID file creation
    std::string pidfile = ConfigMgr::GetStringDefault("PidFile", "");
    if (!pidfile.empty())
    {
        uint32 pid = CreatePIDFile(pidfile);
        if (!pid)
        {
            sLog->outError(LOG_FILTER_WORLDSERVER, "Cannot create PID file %s.\n", pidfile.c_str());
            return 1;
        }

        sLog->outInfo(LOG_FILTER_WORLDSERVER, "Daemon PID: %u\n", pid);
    }

    ///- Start the databases
    if (!_StartDB())
        return 1;

    // set server offline (not connectable)
    LoginDatabase.DirectPExecute("UPDATE realmlist SET flag = (flag & ~%u) | %u WHERE id = '%d'", REALM_FLAG_OFFLINE, REALM_FLAG_INVALID, realmID);

    ///- Initialize the World
    sWorld->SetInitialWorldSettings();

    ///- Initialize the signal handlers
    WorldServerSignalHandler SignalINT, SignalTERM;
    #ifdef _WIN32
    WorldServerSignalHandler SignalBREAK;
    #endif /* _WIN32 */

    ///- Register worldserver's signal handlers
    ACE_Sig_Handler Handler;
    Handler.register_handler(SIGINT, &SignalINT);
    Handler.register_handler(SIGTERM, &SignalTERM);
    #ifdef _WIN32
    Handler.register_handler(SIGBREAK, &SignalBREAK);
    #endif /* _WIN32 */

    ///- Launch WorldRunnable thread
    ACE_Based::Thread world_thread(new WorldRunnable);
    world_thread.setPriority(ACE_Based::Highest);

    ACE_Based::Thread* cliThread = NULL;

#ifdef _WIN32
    if (ConfigMgr::GetBoolDefault("Console.Enable", true) && (m_ServiceStatus == -1)/* need disable console in service mode*/)
#else
    if (ConfigMgr::GetBoolDefault("Console.Enable", true))
#endif
    {
        ///- Launch CliRunnable thread
        cliThread = new ACE_Based::Thread(new CliRunnable);
    }

    ACE_Based::Thread rar_thread(new RARunnable);
    ACE_Based::Thread gmLogToDB_thread(new GmLogToDBRunnable);
    ACE_Based::Thread gmChatLogToDB_thread(new GmChatLogToDBRunnable);
    ACE_Based::Thread arenaLogToDB_thread(new ArenaLogToDBRunnable);
    ACE_Based::Thread CharactersTransfertRunnable_thread(new CharactersTransfertRunnable);

    ///- Handle affinity for multiple processors and process priority on Windows
    #ifdef _WIN32
    {
        HANDLE hProcess = GetCurrentProcess();

        uint32 Aff = ConfigMgr::GetIntDefault("UseProcessors", 0);
        if (Aff > 0)
        {
            ULONG_PTR appAff;
            ULONG_PTR sysAff;

            if (GetProcessAffinityMask(hProcess, &appAff, &sysAff))
            {
                ULONG_PTR curAff = Aff & appAff;            // remove non accessible processors

                if (!curAff)
                {
                    sLog->outError(LOG_FILTER_WORLDSERVER, "Processors marked in UseProcessors bitmask (hex) %x are not accessible for the worldserver. Accessible processors bitmask (hex): %x", Aff, appAff);
                }
                else
                {
                    if (SetProcessAffinityMask(hProcess, curAff))
                        sLog->outInfo(LOG_FILTER_WORLDSERVER, "Using processors (bitmask, hex): %x", curAff);
                    else
                        sLog->outError(LOG_FILTER_WORLDSERVER, "Can't set used processors (hex): %x", curAff);
                }
            }
        }

        bool Prio = ConfigMgr::GetBoolDefault("ProcessPriority", false);

        //if (Prio && (m_ServiceStatus == -1)  /* need set to default process priority class in service mode*/)
        if (Prio)
        {
            if (SetPriorityClass(hProcess, HIGH_PRIORITY_CLASS))
                sLog->outInfo(LOG_FILTER_WORLDSERVER, "worldserver process priority class set to HIGH");
            else
                sLog->outError(LOG_FILTER_WORLDSERVER, "Can't set worldserver process priority class.");
        }
    }
    #endif
    //Start soap serving thread
    ACE_Based::Thread* soap_thread = NULL;

    if (ConfigMgr::GetBoolDefault("SOAP.Enabled", false))
    {
        TCSoapRunnable* runnable = new TCSoapRunnable();
        runnable->setListenArguments(ConfigMgr::GetStringDefault("SOAP.IP", "127.0.0.1"), uint16(ConfigMgr::GetIntDefault("SOAP.Port", 7878)));
        soap_thread = new ACE_Based::Thread(runnable);
    }

    ///- Start up freeze catcher thread
    if (uint32 freeze_delay = ConfigMgr::GetIntDefault("MaxCoreStuckTime", 0))
    {
        FreezeDetectorRunnable* fdr = new FreezeDetectorRunnable();
        fdr->SetDelayTime(freeze_delay * 1000);
        ACE_Based::Thread freeze_thread(fdr);
        freeze_thread.setPriority(ACE_Based::Highest);
    }

    ///- Launch the world listener socket
    uint16 wsport = sWorld->getIntConfig(CONFIG_PORT_WORLD);
    std::string bind_ip = ConfigMgr::GetStringDefault("BindIP", "0.0.0.0");

    if (sWorldSocketMgr->StartNetwork(wsport, bind_ip.c_str()) == -1)
    {
        sLog->outError(LOG_FILTER_WORLDSERVER, "Failed to start network");
        World::StopNow(ERROR_EXIT_CODE);
        // go down and shutdown the server
    }

    // set server online (allow connecting now)
    LoginDatabase.DirectPExecute("UPDATE realmlist SET flag = flag & ~%u, population = 0 WHERE id = '%u'", REALM_FLAG_INVALID, realmID);

    sLog->outInfo(LOG_FILTER_WORLDSERVER, "%s (worldserver-daemon) ready...", _FULLVERSION);

    // when the main thread closes the singletons get unloaded
    // since worldrunnable uses them, it will crash if unloaded after master
    world_thread.wait();
    rar_thread.wait();

    if (soap_thread)
    {
        soap_thread->wait();
        soap_thread->destroy();
        delete soap_thread;
    }

    // set server offline
    LoginDatabase.DirectPExecute("UPDATE realmlist SET flag = flag | %u WHERE id = '%d'", REALM_FLAG_OFFLINE, realmID);

    ///- Clean database before leaving
    ClearOnlineAccounts();

    _StopDB();

    sLog->outInfo(LOG_FILTER_WORLDSERVER, "Halting process...");

    if (cliThread)
    {
        #ifdef _WIN32

        // this only way to terminate CLI thread exist at Win32 (alt. way exist only in Windows Vista API)
        //_exit(1);
        // send keyboard input to safely unblock the CLI thread
        INPUT_RECORD b[5];
        HANDLE hStdIn = GetStdHandle(STD_INPUT_HANDLE);
        b[0].EventType = KEY_EVENT;
        b[0].Event.KeyEvent.bKeyDown = TRUE;
        b[0].Event.KeyEvent.uChar.AsciiChar = 'X';
        b[0].Event.KeyEvent.wVirtualKeyCode = 'X';
        b[0].Event.KeyEvent.wRepeatCount = 1;

        b[1].EventType = KEY_EVENT;
        b[1].Event.KeyEvent.bKeyDown = FALSE;
        b[1].Event.KeyEvent.uChar.AsciiChar = 'X';
        b[1].Event.KeyEvent.wVirtualKeyCode = 'X';
        b[1].Event.KeyEvent.wRepeatCount = 1;

        b[2].EventType = KEY_EVENT;
        b[2].Event.KeyEvent.bKeyDown = TRUE;
        b[2].Event.KeyEvent.dwControlKeyState = 0;
        b[2].Event.KeyEvent.uChar.AsciiChar = '\r';
        b[2].Event.KeyEvent.wVirtualKeyCode = VK_RETURN;
        b[2].Event.KeyEvent.wRepeatCount = 1;
        b[2].Event.KeyEvent.wVirtualScanCode = 0x1c;

        b[3].EventType = KEY_EVENT;
        b[3].Event.KeyEvent.bKeyDown = FALSE;
        b[3].Event.KeyEvent.dwControlKeyState = 0;
        b[3].Event.KeyEvent.uChar.AsciiChar = '\r';
        b[3].Event.KeyEvent.wVirtualKeyCode = VK_RETURN;
        b[3].Event.KeyEvent.wVirtualScanCode = 0x1c;
        b[3].Event.KeyEvent.wRepeatCount = 1;
        DWORD numb;
        WriteConsoleInput(hStdIn, b, 4, &numb);

        cliThread->wait();

        #else

        cliThread->destroy();

        #endif

        delete cliThread;
    }

    // for some unknown reason, unloading scripts here and not in worldrunnable
    // fixes a memory leak related to detaching threads from the module
    //UnloadScriptingModule();

    // Exit the process with specified return value
    return World::GetExitCode();
}

/// Initialize connection to the databases
bool Master::_StartDB()
{
    MySQL::Library_Init();

    std::string dbstring;
    uint8 async_threads, synch_threads;

    dbstring = ConfigMgr::GetStringDefault("WorldDatabaseInfo", "");
    if (dbstring.empty())
    {
        sLog->outError(LOG_FILTER_WORLDSERVER, "World database not specified in configuration file");
        return false;
    }

    async_threads = ConfigMgr::GetIntDefault("WorldDatabase.WorkerThreads", 1);
    if (async_threads < 1 || async_threads > 32)
    {
        sLog->outError(LOG_FILTER_WORLDSERVER, "World database: invalid number of worker threads specified. "
            "Please pick a value between 1 and 32.");
        return false;
    }

    synch_threads = ConfigMgr::GetIntDefault("WorldDatabase.SynchThreads", 1);
    ///- Initialise the world database
    if (!WorldDatabase.Open(dbstring, async_threads, synch_threads))
    {
        sLog->outError(LOG_FILTER_WORLDSERVER, "Cannot connect to world database %s", dbstring.c_str());
        return false;
    }

    ///- Get character database info from configuration file
    dbstring = ConfigMgr::GetStringDefault("CharacterDatabaseInfo", "");
    if (dbstring.empty())
    {
        sLog->outError(LOG_FILTER_WORLDSERVER, "Character database not specified in configuration file");
        return false;
    }

    async_threads = ConfigMgr::GetIntDefault("CharacterDatabase.WorkerThreads", 1);
    if (async_threads < 1 || async_threads > 32)
    {
        sLog->outError(LOG_FILTER_WORLDSERVER, "Character database: invalid number of worker threads specified. "
            "Please pick a value between 1 and 32.");
        return false;
    }

    synch_threads = ConfigMgr::GetIntDefault("CharacterDatabase.SynchThreads", 2);

    ///- Initialise the Character database
    if (!CharacterDatabase.Open(dbstring, async_threads, synch_threads))
    {
        sLog->outError(LOG_FILTER_WORLDSERVER, "Cannot connect to Character database %s", dbstring.c_str());
        return false;
    }

    ///- Get login database info from configuration file
    dbstring = ConfigMgr::GetStringDefault("LoginDatabaseInfo", "");
    if (dbstring.empty())
    {
        sLog->outError(LOG_FILTER_WORLDSERVER, "Login database not specified in configuration file");
        return false;
    }

    async_threads = ConfigMgr::GetIntDefault("LoginDatabase.WorkerThreads", 1);
    if (async_threads < 1 || async_threads > 32)
    {
        sLog->outError(LOG_FILTER_WORLDSERVER, "Login database: invalid number of worker threads specified. "
            "Please pick a value between 1 and 32.");
        return false;
    }

    synch_threads = ConfigMgr::GetIntDefault("LoginDatabase.SynchThreads", 1);
    ///- Initialise the login database
    if (!LoginDatabase.Open(dbstring, async_threads, synch_threads))
    {
        sLog->outError(LOG_FILTER_WORLDSERVER, "Cannot connect to login database %s", dbstring.c_str());
        return false;
    }

    ///- Get the realm Id from the configuration file
    realmID = ConfigMgr::GetIntDefault("RealmID", 0);
    if (!realmID)
    {
        sLog->outError(LOG_FILTER_WORLDSERVER, "Realm ID not defined in configuration file");
        return false;
    }
    sLog->outInfo(LOG_FILTER_WORLDSERVER, "Realm running as realm ID %d", realmID);

    sLog->SetRealmID(realmID);

    ///- Clean the database before starting
    ClearOnlineAccounts();

    ///- Insert version info into DB
    WorldDatabase.PExecute("UPDATE version SET core_version = '%s', core_revision = '%s'", _FULLVERSION, _HASH);        // One-time query

    sWorld->LoadDBVersion();

    sLog->outInfo(LOG_FILTER_WORLDSERVER, "Using World DB: %s", sWorld->GetDBVersion());
    return true;
}

void Master::_StopDB()
{
    CharacterDatabase.Close();
    WorldDatabase.Close();
    LoginDatabase.Close();

    MySQL::Library_End();
}

/// Clear 'online' status for all accounts with characters in this realm
void Master::ClearOnlineAccounts()
{
    // Reset online status for all accounts with characters on the current realm
    LoginDatabase.DirectPExecute("UPDATE account SET online = 0 WHERE online > 0 AND id IN (SELECT acctid FROM realmcharacters WHERE realmid = %d)", realmID);

    // Reset online status for all characters
    CharacterDatabase.DirectExecute("UPDATE characters SET online = 0 WHERE online <> 0");

    // Battleground instance ids reset at server restart
    CharacterDatabase.DirectExecute("UPDATE character_battleground_data SET instanceId = 0");
}
