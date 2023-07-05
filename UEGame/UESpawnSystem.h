// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "UESpawnSystem.generated.h"


UENUM()
enum class EActorType : uint8
{
	PlayerActor,
	EnemyActor
};

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class SPACEINVADERS_API UUESpawnSystem : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly)
	TMap<EActorType, TSubclassOf<AActor>> SpawnableTypes;

	UPROPERTY(BlueprintReadOnly)	
	TArray<AActor*> SpawnedActors;

	UPROPERTY(BlueprintReadOnly)	
	TMap<FString, AActor*> SpawnedActorsCache;

	void SpawnPendingActors(struct platform_spawning_stack* SpawnStack);
};
