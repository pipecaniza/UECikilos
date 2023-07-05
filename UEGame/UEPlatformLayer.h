// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpaceInvaders/Game/eq_platform.h"
#include "UEPlatformLayer.generated.h"


class UUESpawnSystem;

DEBUG_PLATFORM_LOG(UELog);

struct ue_game_code
{
	void *DLLHandler;
	FDateTime DLLLastWriteTime;
	game_loop *GameLoop;
};



UCLASS()
class SPACEINVADERS_API UUEPlatformLayer : public UGameInstance
{
	GENERATED_BODY()

	uint8* MemoryBlock;

	ue_game_code GameCode;
	
	FString DLLPath;
	FString DLLName;
	FString DLLTempName;
	
	void LoadGameCode();
	void UnloadGameCode();
	void ReloadGameCode();

public:	
	// Sets default values for this actor's properties
	UUEPlatformLayer();

	// Game section
	game_memory* GameMemory;

	game_controller_input GameInput;
	
public:
	virtual void Init() override;

	virtual void Shutdown() override;

	UFUNCTION(BlueprintCallable)
	void BeginGameLoop();

	void Tick(float DeltaSeconds);	

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUESpawnSystem> SpawnSystemClass;
	
	UPROPERTY()
	UUESpawnSystem* SpawnSystem;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AActor> RootClass;

	UPROPERTY()
	AActor* Root;

	// Game code
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AActor> AnchorPointClass;
	
	UPROPERTY()
	AActor* AnchorPoint;
};
