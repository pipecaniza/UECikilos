// Fill out your copyright notice in the Description page of Project Settings.

#include "UESpawnSystem.h"
#include "SpaceInvaders/Game/eq_globals.h"
#include "SpaceInvaders/Game/eq_common.h"
#include "SpaceInvaders/Game/eq_platform.h"
#include "UECommon.h"

// TODO(pipecaniza): how to differentiate each actor so the game can understand when the
// spawn succeeded
void UUESpawnSystem::SpawnPendingActors(platform_spawning_stack* SpawnStack)
{	
	while (SpawnStack->Size > 0)
	{
		spawn_actor_params *SpawnParams = &SpawnStack->PendingToSpawn[SpawnStack->Size - 1];

		EActorType ActorType = (EActorType)SpawnParams->Type;
		if (SpawnableTypes.Contains(ActorType))
		{
			TSubclassOf<AActor> SpawnClass = SpawnableTypes[ActorType];
			if (SpawnClass)
			{
				FActorSpawnParameters Params;
				Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
				AActor* SpawnedActor = this->GetWorld()->SpawnActor<AActor>(SpawnClass.Get(),
					V3ToFVector(&SpawnParams->Position), FRotator::ZeroRotator, Params);	

				//SpawnedActor->OnActorBeginOverlap.Add()
				SpawnedActors.Add(SpawnedActor);
				//SpawnedActorsCache.Add()
			}			
			else
			{
				// TODO(pipecaniza): enhance log
				UE_LOG(LogTemp, Error, TEXT("Spawn class not found"))	
			}			
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Spawn type not found"))
		}
		
		// NOTE(pipecaniza): right now, we're ignoring the spawn actors that we won't find
		--SpawnStack->Size;
	}
}
