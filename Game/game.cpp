#include "game.h"
#include "eq_globals.h"
#include "eq_platform.h"


#define DEV_MODE

extern "C" GAME_LOOP(GameLoop)
{
	game_state *GameState = GameMemory->GameState;
	platform_state *PlatformState = &GameMemory->PlatformState;
	global_variable platform_api *PlatformApi = &GameMemory->PlatformApi;

	// TODO(pipecaniza): Initialize
#ifndef DEV_MODE
	if (!GameMemory->HasBeenInitialized)
#endif
	{
		// NOTE(pipecaniza): Code that will be inititalized only once
	#ifdef DEV_MODE
		if (!GameMemory->HasBeenInitialized)
	#endif
		{
			InitializeArena(&GameState->WorldArena, Megabytes(10), (uint8*)GameMemory->BaseAddress);

			spawn_actor_params SpawnPlayerSpaceShipParams = {};
			V3 SpawnPosition = MakeV3(0.0f, 0.0f, 100.0f);
			SpawnPlayerSpaceShipParams.Type = PLAYER_ACTOR;
			SpawnPlayerSpaceShipParams.Position = SpawnPosition;			
			AddToSpawnStack(&PlatformState->SpawningStack, &SpawnPlayerSpaceShipParams);
			// TODO(pipecaniza): Should we only store the actor position if and only if we succeeded in the spawn process?
			GameState->ActorPositions[0] = SpawnPosition;

			SpawnPosition = MakeV3(10.0f, 10.0f, 10.0f);
			SpawnPlayerSpaceShipParams.Type = ENEMY_ACTOR;
			SpawnPlayerSpaceShipParams.Position = MakeV3(10.0f, 10.0f, 10.0f);
			AddToSpawnStack(&PlatformState->SpawningStack, &SpawnPlayerSpaceShipParams);
			GameState->ActorPositions[1] = SpawnPosition;

			SpawnPosition = MakeV3(20.0f, 10.0f, 10.0f);
			SpawnPlayerSpaceShipParams.Position = MakeV3(20.0f, 10.0f, 10.0f);
			AddToSpawnStack(&PlatformState->SpawningStack, &SpawnPlayerSpaceShipParams);
			GameState->ActorPositions[2] = SpawnPosition;
		}

		// TODO(pipecaniza): Should we only store the space ships only if the platform returned a success in the spawn?
		GameState->PlayerShip = MakeSpaceShip(10.0f, 10.0f, &(GameState->ActorPositions[0]));
		GameState->Enemies[0] = MakeSpaceShip(1.0f, 0.0f, &GameState->ActorPositions[1]);
		GameState->Enemies[1] = MakeSpaceShip(1.0f, 0.5f, &GameState->ActorPositions[2]);

		GameMemory->HasBeenInitialized = true;
	}
		
	// NOTE(pipecaniza): Movement code
	{
		if (GameInput->MoveUp.EndedDown)
		{
			GameState->PlayerShip.Position->Y -= GameState->PlayerShip.YVelocity;
		}
		if (GameInput->MoveDown.EndedDown)
		{
			GameState->PlayerShip.Position->Y += GameState->PlayerShip.YVelocity;
		}
		if (GameInput->MoveLeft.EndedDown)
		{
			GameState->PlayerShip.Position->X -= GameState->PlayerShip.XVelocity;
		}
		if (GameInput->MoveRight.EndedDown)
		{
			GameState->PlayerShip.Position->X += GameState->PlayerShip.XVelocity;
		}
		LOG("X: %f,   Y: %f", GameState->PlayerShip.Position->X, GameState->PlayerShip.Position->Y);
	}
	// NOTE(pipecaniza): Enemy movement
	{
		GameState->Enemies[0].Position->X += GameState->Enemies[0].XVelocity;
		GameState->Enemies[1].Position->X += GameState->Enemies[1].XVelocity;
		GameState->Enemies[1].Position->Y += GameState->Enemies[1].YVelocity;
	}
}

