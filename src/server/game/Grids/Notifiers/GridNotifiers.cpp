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

#include "GridNotifiers.h"
#include "GridNotifiersImpl.h"
#include "WorldPacket.h"
#include "WorldSession.h"
#include "UpdateData.h"
#include "Item.h"
#include "Map.h"
#include "Transport.h"
#include "ObjectAccessor.h"
#include "CellImpl.h"
#include "SpellInfo.h"

using namespace JadeCore;

void VisibleNotifier::SendToSelf()
{
    // at this moment i_clientGUIDs have guids that not iterate at grid level checks
    // but exist one case when this possible and object not out of range: transports
    if (Transport* transport = i_player.GetTransport())
        for (Transport::PlayerSet::const_iterator itr = transport->GetPassengers().begin();itr != transport->GetPassengers().end();++itr)
        {
            if (vis_guids.find((*itr)->GetGUID()) != vis_guids.end())
            {
                vis_guids.erase((*itr)->GetGUID());

                i_player.UpdateVisibilityOf((*itr), i_data, i_visibleNow);
                (*itr)->UpdateVisibilityOf(&i_player);
            }
        }

    for (Player::ClientGUIDs::const_iterator it = vis_guids.begin();it != vis_guids.end(); ++it)
    {
        i_player.m_clientGUIDs.erase(*it);
        i_data.AddOutOfRangeGUID(*it);

        if (IS_PLAYER_GUID(*it))
        {
            Player* player = ObjectAccessor::FindPlayer(*it);
            if (player && player->IsInWorld())
                player->UpdateVisibilityOf(&i_player);
        }
    }

    if (!i_data.HasData())
        return;

    WorldPacket packet;
    if (i_data.BuildPacket(&packet))
        i_player.GetSession()->SendPacket(&packet);

    for (std::set<Unit*>::const_iterator it = i_visibleNow.begin(); it != i_visibleNow.end(); ++it)
        i_player.SendInitialVisiblePackets(*it);
}

void VisibleChangesNotifier::Visit(PlayerMapType &m)
{
    for (PlayerMapType::iterator iter = m.begin(); iter != m.end(); ++iter)
    {
        if (iter->getSource() == &i_object)
            continue;

        iter->getSource()->UpdateVisibilityOf(&i_object);

        if (!iter->getSource()->GetSharedVisionList().empty())
            for (SharedVisionList::const_iterator i = iter->getSource()->GetSharedVisionList().begin();
                i != iter->getSource()->GetSharedVisionList().end(); ++i)
                if ((*i)->m_seer == iter->getSource())
                    (*i)->UpdateVisibilityOf(&i_object);
    }
}

void VisibleChangesNotifier::Visit(CreatureMapType &m)
{
    for (CreatureMapType::iterator iter = m.begin(); iter != m.end(); ++iter)
        if (!iter->getSource()->GetSharedVisionList().empty())
            for (SharedVisionList::const_iterator i = iter->getSource()->GetSharedVisionList().begin();
                i != iter->getSource()->GetSharedVisionList().end(); ++i)
                if ((*i)->m_seer == iter->getSource())
                    (*i)->UpdateVisibilityOf(&i_object);
}

void VisibleChangesNotifier::Visit(DynamicObjectMapType &m)
{
    for (DynamicObjectMapType::iterator iter = m.begin(); iter != m.end(); ++iter)
        if (IS_PLAYER_GUID(iter->getSource()->GetCasterGUID()))
            if (Player* caster = (Player*)iter->getSource()->GetCaster())
                if (caster->m_seer == iter->getSource())
                    caster->UpdateVisibilityOf(&i_object);
}

inline void CreatureUnitRelocationWorker(Creature* c, Unit* u)
{
    if (!u->isAlive() || !c->isAlive() || c == u || u->isInFlight())
        return;

    if (!c->HasUnitState(UNIT_STATE_SIGHTLESS))
        if (c->IsAIEnabled && c->canSeeOrDetect(u, false, true))
            if (c->HasReactState(REACT_AGGRESSIVE) || c->AI()->CanSeeEvenInPassiveMode())
                c->AI()->MoveInLineOfSight_Safe(u);
}

void AIRelocationNotifier::Visit(CreatureMapType &m)
{
    for (CreatureMapType::iterator iter = m.begin(); iter != m.end(); ++iter)
    {
        Creature* c = iter->getSource();
        CreatureUnitRelocationWorker(c, &i_unit);
        if (isCreature)
            CreatureUnitRelocationWorker((Creature*)&i_unit, c);
    }
}

void MessageDistDeliverer::Visit(PlayerMapType &m)
{
    for (PlayerMapType::iterator iter = m.begin(); iter != m.end(); ++iter)
    {
        Player* target = iter->getSource();
        if (!target->InSamePhase(i_phaseMask))
            continue;

        if (target->GetExactDist2dSq(i_source) > i_distSq)
            continue;

        // Send packet to all who are sharing the player's vision
        if (!target->GetSharedVisionList().empty())
        {
            SharedVisionList::const_iterator i = target->GetSharedVisionList().begin();
            for (; i != target->GetSharedVisionList().end(); ++i)
                if ((*i)->m_seer == target)
                    SendPacket(*i);
        }

        if (target->m_seer == target || target->GetVehicle())
            SendPacket(target);
    }
}

void MessageDistDeliverer::Visit(CreatureMapType &m)
{
    for (CreatureMapType::iterator iter = m.begin(); iter != m.end(); ++iter)
    {
        Creature* target = iter->getSource();
        if (!target->InSamePhase(i_phaseMask))
            continue;

        if (target->GetExactDist2dSq(i_source) > i_distSq)
            continue;

        // Send packet to all who are sharing the creature's vision
        if (!target->GetSharedVisionList().empty())
        {
            SharedVisionList::const_iterator i = target->GetSharedVisionList().begin();
            for (; i != target->GetSharedVisionList().end(); ++i)
                if ((*i)->m_seer == target)
                    SendPacket(*i);
        }
    }
}

void MessageDistDeliverer::Visit(DynamicObjectMapType &m)
{
    for (DynamicObjectMapType::iterator iter = m.begin(); iter != m.end(); ++iter)
    {
        DynamicObject* target = iter->getSource();
        if (!target->InSamePhase(i_phaseMask))
            continue;

        if (target->GetExactDist2dSq(i_source) > i_distSq)
            continue;

        if (IS_PLAYER_GUID(target->GetCasterGUID()))
        {
            // Send packet back to the caster if the caster has vision of dynamic object
            Player* caster = (Player*)target->GetCaster();
            if (caster && caster->m_seer == target)
                SendPacket(caster);
        }
    }
}

/*
void
MessageDistDeliverer::VisitObject(Player* player)
{
    if (!i_ownTeamOnly || (i_source.GetTypeId() == TYPEID_PLAYER && player->GetTeam() == ((Player&)i_source).GetTeam()))
    {
        SendPacket(player);
    }
}
*/

template<class T>
void ObjectUpdater::Visit(GridRefManager<T> &m)
{
    for (typename GridRefManager<T>::iterator iter = m.begin(); iter != m.end(); ++iter)
    {
        if (iter->getSource()->IsInWorld())
            iter->getSource()->Update(i_timeDiff);
    }
}

bool AnyDeadUnitObjectInRangeCheck::operator()(Player* u)
{
    return !u->isAlive() && !u->HasAuraType(SPELL_AURA_GHOST) && i_searchObj->IsWithinDistInMap(u, i_range);
}

bool AnyDeadUnitObjectInRangeCheck::operator()(Corpse* u)
{
    return u->GetType() != CORPSE_BONES && i_searchObj->IsWithinDistInMap(u, i_range);
}

bool AnyDeadUnitObjectInRangeCheck::operator()(Creature* u)
{
    return !u->isAlive() && i_searchObj->IsWithinDistInMap(u, i_range);
}

bool AnyDeadUnitSpellTargetInRangeCheck::operator()(Player* u)
{
    return AnyDeadUnitObjectInRangeCheck::operator()(u) && i_check(u);
}

bool AnyDeadUnitSpellTargetInRangeCheck::operator()(Corpse* u)
{
    return AnyDeadUnitObjectInRangeCheck::operator()(u) && i_check(u);
}

bool AnyDeadUnitSpellTargetInRangeCheck::operator()(Creature* u)
{
    return AnyDeadUnitObjectInRangeCheck::operator()(u) && i_check(u);
}

template void ObjectUpdater::Visit<GameObject>(GameObjectMapType &);
template void ObjectUpdater::Visit<DynamicObject>(DynamicObjectMapType &);
template void ObjectUpdater::Visit<AreaTrigger>(AreaTriggerMapType &);
