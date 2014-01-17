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

#include "ScriptMgr.h"
#include "Common.h"
#include "Chat.h"
#include "Player.h"
#include "World.h"
#include "Config.h"
#include "WorldSession.h"
#include "Language.h"
#include "Log.h"
#include "SpellAuras.h"


class vip_commandscript : public CommandScript
{
public:
    vip_commandscript() : CommandScript("vip_commandscript") { }

    ChatCommand* GetCommands() const
    {

        static ChatCommand vipCommandTable[] =
        {
            { "bank",           SEC_PLAYER,         false, &HandleVipBankCommand,               "", NULL },
            { "home",           SEC_PLAYER,         false, &HandleVipHomeCommand,               "", NULL },
            { NULL,             0,                  false, NULL,                                "", NULL }
        };


        static ChatCommand commandTable[] =
        {
            { "vip",            SEC_PLAYER,      false, NULL,                                "", vipCommandTable },
            { NULL,             0,               false, NULL,                                "", NULL }
        };
        return commandTable;
    }


    static bool HandleVipBankCommand(ChatHandler* handler, const char* /*args*/)
    {
        Player *plr = handler->GetSession()->GetPlayer();

        if(!handler->GetSession()->IsPremium())
        {
            handler->SendSysMessage(LANG_PLAYER_NOT_VIP);
            handler->SetSentErrorMessage(true);
            return false;
        }

        if (!sWorld->getBoolConfig(CONFIG_VIP_BANK_COMMAND))
        {
            handler->SendSysMessage(LANG_VIP_COMMAND_DISABLED);
            handler->SetSentErrorMessage(true);
            return false;
        }

        if (plr->isInCombat() || plr->isInFlight() || plr->GetMap()->IsBattlegroundOrArena() || plr->HasStealthAura() || plr->HasFlag(UNIT_FIELD_FLAGS_2, UNIT_FLAG2_FEIGN_DEATH) || plr->isDead())
        {
            handler->SendSysMessage(LANG_VIP_ERROR);
            handler->SetSentErrorMessage(true);
            return false;
        }

        handler->GetSession()->SendShowBank(handler->GetSession()->GetPlayer()->GetGUID());

        return true;
    }

    static bool HandleVipHomeCommand(ChatHandler* handler, const char* /*args*/)
    {
        Player *plr = handler->GetSession()->GetPlayer();

        if (!handler->GetSession()->IsPremium())
        {
            handler->SendSysMessage(LANG_PLAYER_NOT_VIP);
            handler->SetSentErrorMessage(true);
            return false;
        }

        if (!sWorld->getBoolConfig(CONFIG_VIP_HOME_COMMAND))
        {
            handler->SendSysMessage(LANG_VIP_COMMAND_DISABLED);
            handler->SetSentErrorMessage(true);
            return false;
        }

        if (plr->isInCombat() || plr->isInFlight() || plr->GetMap()->IsBattlegroundOrArena() || plr->HasStealthAura() || plr->HasFlag(UNIT_FIELD_FLAGS_2, UNIT_FLAG2_FEIGN_DEATH) || plr->isDead())
        {
            handler->SendSysMessage(LANG_VIP_ERROR);
            handler->SetSentErrorMessage(true);
            return false;
        }

        plr->RemoveSpellCooldown(8690,true);
        plr->CastSpell(plr,8690,false);

        return true;
    }

};

void AddSC_vip_commandscript()
{
    new vip_commandscript();
}
