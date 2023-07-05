#pragma once

#ifndef NO_INCLUDE
#include "game.h"
#endif

#define LOG(...) PlatformApi->DebugPlatformLog(__VA_ARGS__)

#define DEBUG_PLATFORM_LOG(name) void name(const char* Format, ...)
typedef DEBUG_PLATFORM_LOG(debug_platform_log);

// NOTE(pipecaniza): contains all the function pointers to the platform layer
struct platform_api
{
	debug_platform_log *DebugPlatformLog;
};

/** spawning*/

enum spawn_actor_type
{
	PLAYER_ACTOR,
	ENEMY_ACTOR
};

struct spawn_actor_params
{
	char Id [15];
	spawn_actor_type Type;
	V3 Position;
};

#define MAX_SPAWNING_STACK 50
struct platform_spawning_stack
{
	spawn_actor_params PendingToSpawn[MAX_SPAWNING_STACK];
	int32 Size;
};

// TODO(pipecaniza): review if this is needed
#define MAX_ACTORS_STACK 200
struct platform_actors_stack
{
	void* ActorsAlive[MAX_ACTORS_STACK];
	int32 Size;
};
/*
void AddActorToSpawn(platform_spawning_stack* SpawningStack, spawn_actor_params* ActorToSpawn)
{
	// TODO(pipecaniza): Assert
	SpawningStack->PendingToSpawn[SpawningStack->Size++] = *ActorToSpawn;
}*/

// NOTE(pipecaniza): the state of UE execution that will be used by the game,
// it can contains the collisions or other simulations that the engine will perform
// maybe the raw input to??

struct platform_state
{
	uint32 ScreenWidth;
	uint32 ScreenHeight;
	platform_spawning_stack SpawningStack;
};

struct game_memory
{
	int32 Size;
	void* BaseAddress;
	bool32 HasBeenInitialized;

	platform_state PlatformState;
	platform_api PlatformApi;
	struct game_state* GameState;
};


// TODO(pipecaniza): refine this to support any interaction in order to be a eq_ file
struct game_button_state
{
	bool32 EndedDown;
};

struct game_controller_input
{
	union
	{
		game_button_state Buttons[5];
		struct
		{
			game_button_state MoveUp;
			game_button_state MoveDown;
			game_button_state MoveLeft;
			game_button_state MoveRight;
			game_button_state Action;	
		};
	};
};

#define GAME_LOOP(name) void name(game_memory* GameMemory, game_controller_input* GameInput)
typedef GAME_LOOP(game_loop);


internal void
AddToSpawnStack(platform_spawning_stack *SpawningStack, spawn_actor_params *SpawnParams)
{
	// TODO(pipecaniza): Assert
	SpawningStack->PendingToSpawn[SpawningStack->Size++] = *SpawnParams;
}