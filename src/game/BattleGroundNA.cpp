/*
 * This file is part of the OregonCore Project. See AUTHORS file for Copyright information
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

#include "Object.h"
#include "Player.h"
#include "BattleGround.h"
#include "BattleGroundNA.h"
#include "Creature.h"
#include "ObjectMgr.h"
#include "MapManager.h"
#include "Language.h"

BattleGroundNA::BattleGroundNA()
{
    m_BgObjects.resize(BG_NA_OBJECT_MAX);

    m_StartDelayTimes[BG_STARTING_EVENT_FIRST]  = BG_START_DELAY_1M;
    m_StartDelayTimes[BG_STARTING_EVENT_SECOND] = BG_START_DELAY_30S;
    m_StartDelayTimes[BG_STARTING_EVENT_THIRD]  = BG_START_DELAY_15S;
    m_StartDelayTimes[BG_STARTING_EVENT_FOURTH] = BG_START_DELAY_NONE;
    //we must set messageIds
    m_StartMessageIds[BG_STARTING_EVENT_FIRST]  = LANG_ARENA_ONE_MINUTE;
    m_StartMessageIds[BG_STARTING_EVENT_SECOND] = LANG_ARENA_THIRTY_SECONDS;
    m_StartMessageIds[BG_STARTING_EVENT_THIRD]  = LANG_ARENA_FIFTEEN_SECONDS;
    m_StartMessageIds[BG_STARTING_EVENT_FOURTH] = LANG_ARENA_HAS_BEGUN;
}

BattleGroundNA::~BattleGroundNA()
{

}

void BattleGroundNA::Update(uint32 diff)
{
    BattleGround::Update(diff);
}

void BattleGroundNA::StartingEventCloseDoors()
{
    for (uint32 i = BG_NA_OBJECT_DOOR_1; i <= BG_NA_OBJECT_DOOR_4; ++i)
        SpawnBGObject(i, RESPAWN_IMMEDIATELY);
}

void BattleGroundNA::StartingEventOpenDoors()
{
    for (uint32 i = BG_NA_OBJECT_DOOR_1; i <= BG_NA_OBJECT_DOOR_2; ++i)
        DoorOpen(i);

    for (uint32 i = BG_NA_OBJECT_BUFF_1; i <= BG_NA_OBJECT_BUFF_2; ++i)
        SpawnBGObject(i, 60);
}

void BattleGroundNA::AddPlayer(Player* plr)
{
    BattleGround::AddPlayer(plr);
    //create score and add it to map, default values are set in constructor
    BattleGroundNAScore* sc = new BattleGroundNAScore;

    m_PlayerScores[plr->GetGUID()] = sc;

    UpdateWorldState(0xa0f, GetAlivePlayersCountByTeam(ALLIANCE));
    UpdateWorldState(0xa10, GetAlivePlayersCountByTeam(HORDE));
}

void BattleGroundNA::RemovePlayer(Player* /*plr*/, uint64 /*guid*/)
{
    if (GetStatus() == STATUS_WAIT_LEAVE)
        return;

    UpdateWorldState(0xa0f, GetAlivePlayersCountByTeam(ALLIANCE));
    UpdateWorldState(0xa10, GetAlivePlayersCountByTeam(HORDE));

    CheckArenaWinConditions();
}

void BattleGroundNA::HandleKillPlayer(Player* player, Player* killer)
{
    if (GetStatus() != STATUS_IN_PROGRESS)
        return;

    if (!killer)
    {
        sLog.outError("BattleGroundNA: Killer player not found");
        return;
    }

    BattleGround::HandleKillPlayer(player, killer);

    UpdateWorldState(0xa0f, GetAlivePlayersCountByTeam(ALLIANCE));
    UpdateWorldState(0xa10, GetAlivePlayersCountByTeam(HORDE));

    CheckArenaWinConditions();
}

void BattleGroundNA::HandleAreaTrigger(Player* Source, uint32 Trigger)
{
    if (GetStatus() != STATUS_IN_PROGRESS)
        return;

    //uint32 SpellId = 0;
    //uint64 buff_guid = 0;
    switch (Trigger)
    {
    case 4536:                                          // buff trigger?
    case 4537:                                          // buff trigger?
        break;
    default:
        sLog.outError("WARNING: Unhandled AreaTrigger in Battleground: %u", Trigger);
        Source->GetSession()->SendAreaTriggerMessage("Warning: Unhandled AreaTrigger in Battleground: %u", Trigger);
        break;
    }

    //if (buff_guid)
    //    HandleTriggerBuff(buff_guid,Source);
}

void BattleGroundNA::FillInitialWorldStates(WorldPacket& data)
{
    data << uint32(0xa0f) << uint32(GetAlivePlayersCountByTeam(ALLIANCE));           // 7
    data << uint32(0xa10) << uint32(GetAlivePlayersCountByTeam(HORDE));           // 8
    data << uint32(0xa11) << uint32(1);           // 9
}

void BattleGroundNA::ResetBGSubclass()
{

}

bool BattleGroundNA::SetupBattleGround()
{
    // gates
    if (  !AddObject(BG_NA_OBJECT_DOOR_1, BG_NA_OBJECT_TYPE_DOOR_1, 4031.854f, 2966.833f, 12.6462f, -2.648788f, 0.0f, 0.0f, 0.9697962f, -0.2439165f, RESPAWN_IMMEDIATELY)
          || !AddObject(BG_NA_OBJECT_DOOR_2, BG_NA_OBJECT_TYPE_DOOR_2, 4081.179f, 2874.97f, 12.39171f, 0.4928045f, 0.0f, 0.0f, 0.2439165f, 0.9697962f, RESPAWN_IMMEDIATELY)
          || !AddObject(BG_NA_OBJECT_DOOR_3, BG_NA_OBJECT_TYPE_DOOR_3, 4023.709f, 2981.777f, 10.70117f, -2.648788f, 0.0f, 0.0f, 0.9697962f, -0.2439165f, RESPAWN_IMMEDIATELY)
          || !AddObject(BG_NA_OBJECT_DOOR_4, BG_NA_OBJECT_TYPE_DOOR_4, 4090.064f, 2858.438f, 10.23631f, 0.4928045f, 0.0f, 0.0f, 0.2439165f, 0.9697962f, RESPAWN_IMMEDIATELY)
          // buffs
          || !AddObject(BG_NA_OBJECT_BUFF_1, BG_NA_OBJECT_TYPE_BUFF_1, 4009.189941f, 2895.250000f, 13.052700f, -1.448624f, 0.0f, 0.0f, 0.6626201f, -0.7489557f, 120)
          || !AddObject(BG_NA_OBJECT_BUFF_2, BG_NA_OBJECT_TYPE_BUFF_2, 4103.330078f, 2946.350098f, 13.051300f, -0.06981307f, 0.0f, 0.0f, 0.03489945f, -0.9993908f, 120))
    {
        sLog.outErrorDb("BatteGroundNA: Failed to spawn some object!");
        return false;
    }

    return true;
}

/*
20:12:14 id:036668 [S2C] SMSG_INIT_WORLD_STATES (706 = 0x02C2) len: 86
0000: 2f 02 00 00 72 0e 00 00 00 00 00 00 09 00 11 0a  |  /...r...........
0010: 00 00 01 00 00 00 0f 0a 00 00 00 00 00 00 10 0a  |  ................
0020: 00 00 00 00 00 00 d4 08 00 00 00 00 00 00 d8 08  |  ................
0030: 00 00 00 00 00 00 d7 08 00 00 00 00 00 00 d6 08  |  ................
0040: 00 00 00 00 00 00 d5 08 00 00 00 00 00 00 d3 08  |  ................
0050: 00 00 00 00 00 00                                |  ......
*/

