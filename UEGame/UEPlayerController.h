// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "UEPlayerController.generated.h"


class UUEPlatformLayer;
struct game_controller_input;
/**
 * 
 */
UCLASS()
class SPACEINVADERS_API AUEPlayerController : public APlayerController
{
	GENERATED_BODY()

	UPROPERTY()
	UUEPlatformLayer* PlatformLayer;
	
	game_controller_input *GameInput;

protected:
	virtual void BeginPlay() override;
	
	virtual void SetupInputComponent() override;

	void ReceiveKeyPressedEvent(FKey Key);

	void ReceiveKeyReleasedEvent(FKey Key);

	void ReceiveForwardAxisEvent(float Value);

	void ReceiveRightAxisEvent(float Value);

	void ReceiveLookUpAxisEvent(float Value);

	void ReceiveLookAroundAxisEvent(float Value);
};
