// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UERootActor.generated.h"

class UUEPlatformLayer;
UCLASS(Blueprintable, BlueprintType, Placeable)
class SPACEINVADERS_API AUERootActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AUERootActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY()
	UUEPlatformLayer* PlatformLayer;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
