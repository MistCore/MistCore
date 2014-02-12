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

#include "WorldPacket.h"
#include "WorldSession.h"
#include "Opcodes.h"
#include "Vehicle.h"
#include "Player.h"
#include "Log.h"
#include "ObjectAccessor.h"

void WorldSession::HandleDismissControlledVehicle(WorldPacket &recvData)
{
    sLog->outDebug(LOG_FILTER_NETWORKIO, "WORLD: Recvd CMSG_DISMISS_CONTROLLED_VEHICLE");

    uint64 vehicleGUID = _player->GetCharmGUID();

    if (!vehicleGUID)                                       // something wrong here...
    {
        recvData.rfinish();                                // prevent warnings spam
        return;
    }

    // Too lazy to parse all data, just read pos and forge pkt
    MovementInfo mi;
    mi.guid = _player->GetGUID();
    mi.flags2 = MOVEMENTFLAG2_INTERPOLATED_PITCHING;
    mi.pos.m_positionX = recvData.read<float>();
    mi.pos.m_positionZ = recvData.read<float>();
    mi.pos.m_positionY = recvData.read<float>();
    mi.time = getMSTime();

    WorldPacket data(SMSG_MOVE_UPDATE);
    WorldSession::WriteMovementInfo(data, &mi);
    _player->SendMessageToSet(&data, _player);

    _player->m_movementInfo = mi;

    _player->ExitVehicle();

    // prevent warnings spam
    recvData.rfinish();
}

void WorldSession::HandleChangeSeatsOnControlledVehicle(WorldPacket& recvData)
{
    sLog->outDebug(LOG_FILTER_NETWORKIO, "WORLD: Recvd CMSG_CHANGE_SEATS_ON_CONTROLLED_VEHICLE");

    Unit* vehicle_base = GetPlayer()->GetVehicleBase();
    if (!vehicle_base)
    {
        recvData.rfinish();                                // prevent warnings spam
        return;
    }

    VehicleSeatEntry const* seat = GetPlayer()->GetVehicle()->GetSeatForPassenger(GetPlayer());
    if (!seat->CanSwitchFromSeat())
    {
        recvData.rfinish();                                // prevent warnings spam
        sLog->outError(LOG_FILTER_NETWORKIO, "HandleChangeSeatsOnControlledVehicle, Opcode: %u, Player %u tried to switch seats but current seatflags %u don't permit that.",
            recvData.GetOpcode(), GetPlayer()->GetGUIDLow(), seat->m_flags);
        return;
    }

    switch (recvData.GetOpcode())
    {
        case CMSG_REQUEST_VEHICLE_PREV_SEAT:
            GetPlayer()->ChangeSeat(-1, false);
            break;
        case CMSG_REQUEST_VEHICLE_NEXT_SEAT:
            GetPlayer()->ChangeSeat(-1, true);
            break;
        case CMSG_CHANGE_SEATS_ON_CONTROLLED_VEHICLE:
        {
            float x, y, z;
            recvData >> z;
            int8 seatId;
            recvData >> seatId;
            recvData >> y;
            recvData >> x;
            
            uint64 accessory;        // accessory vehicle guid
            recvData >> accessory;

            if (!accessory)
                GetPlayer()->ChangeSeat(-1, seatId > 0); // prev/next
            else if (Unit* vehUnit = Unit::GetUnit(*GetPlayer(), accessory))
            {
                if (Vehicle* vehicle = vehUnit->GetVehicleKit())
                    if (vehicle->HasEmptySeat(seatId))
                        vehUnit->HandleSpellClick(GetPlayer(), seatId);
            }
            break;
        }
        case CMSG_REQUEST_VEHICLE_SWITCH_SEAT:
        {
            ObjectGuid guid;

            int8 seatId;
            recvData >> seatId;

            uint8 bitOrder[8] = {0, 3, 6, 5, 2, 4, 7, 1};
            recvData.ReadBitInOrder(guid, bitOrder);

            uint8 byteOrder[8] = {1, 6, 7, 2, 0, 3, 5, 4};
            recvData.ReadBytesSeq(guid, byteOrder);

            if (vehicle_base->GetGUID() == guid)
                GetPlayer()->ChangeSeat(seatId);
            else if (Unit* vehUnit = Unit::GetUnit(*GetPlayer(), guid))
                if (Vehicle* vehicle = vehUnit->GetVehicleKit())
                    if (vehicle->HasEmptySeat(seatId))
                        vehUnit->HandleSpellClick(GetPlayer(), seatId);
            break;
        }
        default:
            break;
    }
}

void WorldSession::HandleEnterPlayerVehicle(WorldPacket& recvData)
{
    // Read guid
    ObjectGuid guid;

    uint8 bitOrder[8] = {0, 7, 1, 2, 3, 4, 5, 6};
    recvData.ReadBitInOrder(guid, bitOrder);

    uint8 byteOrder[8] = {4, 0, 5, 6, 1, 3, 7, 2};
    recvData.ReadBytesSeq(guid, byteOrder);

    if (Player* player = ObjectAccessor::FindPlayer(guid))
    {
        if (!player->GetVehicleKit())
            return;
        if (!player->IsInRaidWith(_player))
            return;
        if (!player->IsWithinDistInMap(_player, INTERACTION_DISTANCE))
            return;

        _player->EnterVehicle(player);
    }
}

void WorldSession::HandleEjectPassenger(WorldPacket& data)
{
    Vehicle* vehicle = _player->GetVehicleKit();
    if (!vehicle)
    {
        data.rfinish();                                     // prevent warnings spam
        sLog->outError(LOG_FILTER_NETWORKIO, "HandleEjectPassenger: Player %u is not in a vehicle!", GetPlayer()->GetGUIDLow());
        return;
    }

    uint64 guid;
    data >> guid;

    if (IS_PLAYER_GUID(guid))
    {
        Player* player = ObjectAccessor::FindPlayer(guid);
        if (!player)
        {
            sLog->outError(LOG_FILTER_NETWORKIO, "Player %u tried to eject player %u from vehicle, but the latter was not found in world!", GetPlayer()->GetGUIDLow(), GUID_LOPART(guid));
            return;
        }

        if (!player->IsOnVehicle(vehicle->GetBase()))
        {
            sLog->outError(LOG_FILTER_NETWORKIO, "Player %u tried to eject player %u, but they are not in the same vehicle", GetPlayer()->GetGUIDLow(), GUID_LOPART(guid));
            return;
        }

        VehicleSeatEntry const* seat = vehicle->GetSeatForPassenger(player);
        ASSERT(seat);
        if (seat->IsEjectable())
            player->ExitVehicle();
        else
            sLog->outError(LOG_FILTER_NETWORKIO, "Player %u attempted to eject player %u from non-ejectable seat.", GetPlayer()->GetGUIDLow(), GUID_LOPART(guid));
    }

    else if (IS_CREATURE_GUID(guid))
    {
        Unit* unit = ObjectAccessor::GetUnit(*_player, guid);
        if (!unit) // creatures can be ejected too from player mounts
        {
            sLog->outError(LOG_FILTER_NETWORKIO, "Player %u tried to eject creature guid %u from vehicle, but the latter was not found in world!", GetPlayer()->GetGUIDLow(), GUID_LOPART(guid));
            return;
        }

        if (!unit->IsOnVehicle(vehicle->GetBase()))
        {
            sLog->outError(LOG_FILTER_NETWORKIO, "Player %u tried to eject unit %u, but they are not in the same vehicle", GetPlayer()->GetGUIDLow(), GUID_LOPART(guid));
            return;
        }

        VehicleSeatEntry const* seat = vehicle->GetSeatForPassenger(unit);
        ASSERT(seat);
        if (seat->IsEjectable())
        {
            ASSERT(GetPlayer() == vehicle->GetBase());
            unit->ExitVehicle();
        }
        else
            sLog->outError(LOG_FILTER_NETWORKIO, "Player %u attempted to eject creature GUID %u from non-ejectable seat.", GetPlayer()->GetGUIDLow(), GUID_LOPART(guid));
    }
    else
        sLog->outError(LOG_FILTER_NETWORKIO, "HandleEjectPassenger: Player %u tried to eject invalid GUID " UI64FMTD, GetPlayer()->GetGUIDLow(), guid);
}

void WorldSession::HandleRequestVehicleExit(WorldPacket& /*recvData*/)
{
    sLog->outDebug(LOG_FILTER_NETWORKIO, "WORLD: Recvd CMSG_REQUEST_VEHICLE_EXIT");

    if (Vehicle* vehicle = GetPlayer()->GetVehicle())
    {
        if (VehicleSeatEntry const* seat = vehicle->GetSeatForPassenger(GetPlayer()))
        {
            if (seat->CanEnterOrExit())
                GetPlayer()->ExitVehicle();
            else
                sLog->outError(LOG_FILTER_NETWORKIO, "Player %u tried to exit vehicle, but seatflags %u (ID: %u) don't permit that.",
                GetPlayer()->GetGUIDLow(), seat->m_ID, seat->m_flags);
        }
    }
}
