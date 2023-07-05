// Fill out your copyright notice in the Description page of Project Settings.

#include "UERootActor.h"
#include "UEPlatformLayer.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
AUERootActor::AUERootActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AUERootActor::BeginPlay()
{
	Super::BeginPlay();

	PlatformLayer = Cast<UUEPlatformLayer>(UGameplayStatics::GetGameInstance(this));	
}

// Called every frame
void AUERootActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	PlatformLayer->Tick(DeltaTime);
}

