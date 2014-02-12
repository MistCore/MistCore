/*
 * Copyright (C) 2008-2012 TrinityCore <http://www.trinitycore.org/>
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

#include "Opcodes.h"
#include "WorldSession.h"
#include "WorldPacket.h"

void WorldSession::SendAuthResponse(uint8 code, bool queued, uint32 queuePos)
{
    WorldPacket packet(SMSG_AUTH_RESPONSE);

    uint32 realmRaceCount = 15;
    uint32 realmClassCount = 11;

    packet.WriteBit(1);                                    // has account info
    packet.WriteBit(0);                                    // Unk
    packet.WriteBits(realmClassCount, 25);                  // Read realmRaceResult.count // 11 (class ?)
    packet.WriteBits(0, 22);                               // Unk
    packet.WriteBits(realmRaceCount, 25);                 // Read realmClassResult.count // 15 (race ?)

    packet.WriteBit(queued);
    if(queued)
    {
        packet.WriteBit(0);
        packet << uint32(queuePos);
    }
    packet.FlushBits();

    packet << uint8(Expansion());
    packet << uint8(Expansion());

    for(uint32 i = 0; i < realmClassCount; i++)
    {
        switch(i)
        {
            case 0:
                packet << uint8(CLASS_WARRIOR);
                packet << uint8(0); // Prebc       
                break;
            case 1:
                packet << uint8(CLASS_PALADIN);
                packet << uint8(0); // Prebc              
                break;
            case 2:               
                packet << uint8(CLASS_HUNTER);
                packet << uint8(0); // Prebc
                break;
            case 3:
                packet << uint8(CLASS_ROGUE);
                packet << uint8(0); // Prebc            
                break;
            case 4:
                packet << uint8(CLASS_PRIEST);
                packet << uint8(0); // Prebc              
                break;
            case 5:                
                packet << uint8(CLASS_DEATH_KNIGHT);
                packet << uint8(2); // Wotlk
                break;
            case 6:               
                packet << uint8(CLASS_SHAMAN);
                packet << uint8(0); // Prebc
                break;
            case 7:               
                packet << uint8(CLASS_MAGE);
                packet << uint8(0); // Prebc
                break;
            case 8:                
                packet << uint8(CLASS_WARLOCK);
                packet << uint8(0); // Prebc
                break;
            case 9:
                packet << uint8(CLASS_DRUID);
                packet << uint8(0); // Prebc               
                break;
            case 10:
                packet << uint8(CLASS_MONK);
                packet << uint8(4); // MoP            
                break;
        }
    }

    packet << uint32(0);
    packet << uint32(0);
    packet << uint32(0);

    packet << uint8(RACE_HUMAN);
    packet << uint8(0);
    packet << uint8(RACE_ORC);
    packet << uint8(0);
    packet << uint8(RACE_DWARF);
    packet << uint8(0);
    packet << uint8(RACE_NIGHTELF);
    packet << uint8(0);
    packet << uint8(RACE_UNDEAD_PLAYER);
    packet << uint8(0);
    packet << uint8(RACE_TAUREN);
    packet << uint8(0);
    packet << uint8(RACE_GNOME);
    packet << uint8(0);
    packet << uint8(RACE_TROLL);
    packet << uint8(0);
    packet << uint8(RACE_GOBLIN);
    packet << uint8(3);
    packet << uint8(RACE_BLOODELF);
    packet << uint8(1);
    packet << uint8(RACE_DRAENEI);
    packet << uint8(1);
    packet << uint8(RACE_WORGEN);
    packet << uint8(3);
    packet << uint8(RACE_PANDAREN_NEUTRAL);
    packet << uint8(4);
    packet << uint8(RACE_PANDAREN_ALLI);
    packet << uint8(4);
    packet << uint8(RACE_PANDAREN_HORDE);
    packet << uint8(4);
    
    /*for(uint32 i = 0; i < realmRaceCount; i++)
    {
        packet << uint8(0);                                // class
        packet << uint8(0);                                // expansion
    }*/

    packet << uint8(Expansion());                                    // BillingPlanFlags
    packet << uint8(code);   

    SendPacket(&packet);
}

void WorldSession::SendClientCacheVersion(uint32 version)
{
    WorldPacket data(SMSG_CLIENTCACHE_VERSION, 4);
    data << uint32(version);
    SendPacket(&data);
}
