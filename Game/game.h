#pragma once

#define NO_INCLUDE

#include "eq_globals.h"
#include "eq_common.h"
#include "eq_memory.h"
#include "eq_platform.h"



/**
 *	the character movement could be implemented with direct position, or calculating the velocities
 *	that will be passed through the UE Actor
 *
 * 
 */

struct space_ship
{
	real32 XVelocity;
	real32 YVelocity;
	V3 *Position;
};

internal space_ship
MakeSpaceShip(real32 XVelocity, real32 YVelocity, V3 *Position)
{
	space_ship Result = {};
	Result.XVelocity = XVelocity;
	Result.YVelocity = YVelocity;
	Result.Position = Position;
	return Result;
}

struct game_state
{
	memory_arena WorldArena;
	space_ship PlayerShip;
	space_ship Enemies [10]; //TODO(pipecaniza): Move this to other struct? and define MAX
	V3 ActorPositions [10];
};

//void GameLoop(game_memory* GameMemory, game_controller_input* GameInput);