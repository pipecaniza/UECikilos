// Fill out your copyright notice in the Description page of Project Settings.


#include "UEPlayerController.h"

#include "UEPlatformLayer.h"


void AUEPlayerController::BeginPlay()
{
	Super::BeginPlay();

	PlatformLayer = Cast<UUEPlatformLayer>(GetGameInstance());
	GameInput = &PlatformLayer->GameInput;
}

void AUEPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (InputComponent)
	{
		const FKey Key = EKeys::AnyKey;
		InputComponent->BindKey(Key, EInputEvent::IE_Pressed, this, &AUEPlayerController::ReceiveKeyPressedEvent);
		InputComponent->BindKey(Key, EInputEvent::IE_Released, this, &AUEPlayerController::ReceiveKeyReleasedEvent);		

		FName AxisName = "ForwardAxis";
		FInputAxisKeyMapping LeftStickYMapping(AxisName, EKeys::Gamepad_LeftY, 1.0f);
		FInputAxisKeyMapping WMapping(AxisName, EKeys::W, 1.0f);
		FInputAxisKeyMapping SMapping(AxisName, EKeys::S, -1.0f);

		PlayerInput->AddAxisMapping(LeftStickYMapping);
		PlayerInput->AddAxisMapping(WMapping);
		PlayerInput->AddAxisMapping(SMapping);
		
		InputComponent->BindAxis(AxisName, this, &AUEPlayerController::ReceiveForwardAxisEvent);


		AxisName = "RightAxis";
		FInputAxisKeyMapping LeftStickXMapping(AxisName, EKeys::Gamepad_LeftX, 1.0f);
		FInputAxisKeyMapping DMapping(AxisName, EKeys::D, 1.0f);
		FInputAxisKeyMapping AMapping(AxisName, EKeys::A, -1.0f);

		PlayerInput->AddAxisMapping(LeftStickXMapping);
		PlayerInput->AddAxisMapping(DMapping);
		PlayerInput->AddAxisMapping(AMapping);
		
		InputComponent->BindAxis(AxisName, this, &AUEPlayerController::ReceiveRightAxisEvent);


		AxisName = "LookUpAxis";		
		FInputAxisKeyMapping RightStickYMapping(AxisName, EKeys::Gamepad_RightY, -1.0f);		
		FInputAxisKeyMapping MouseYMapping(AxisName, EKeys::MouseY, 1.0f);		

		PlayerInput->AddAxisMapping(RightStickYMapping);
		PlayerInput->AddAxisMapping(MouseYMapping);
		
		InputComponent->BindAxis(AxisName, this, &AUEPlayerController::ReceiveLookUpAxisEvent);

		
		AxisName = "LookAroundAxis";		
		FInputAxisKeyMapping RightStickXMapping(AxisName, EKeys::Gamepad_RightX, 1.0f);		
		FInputAxisKeyMapping MouseXMapping(AxisName, EKeys::MouseX, 1.0f);		

		PlayerInput->AddAxisMapping(RightStickXMapping);
		PlayerInput->AddAxisMapping(MouseXMapping);
		
		InputComponent->BindAxis(AxisName, this, &AUEPlayerController::ReceiveLookAroundAxisEvent);
	}
}

void AUEPlayerController::ReceiveKeyPressedEvent(FKey Key)
{
	UE_LOG(LogTemp, Log, TEXT("Key %s pressed"), *Key.GetDisplayName().ToString());
	if (Key == EKeys::W)
	{
		GameInput->MoveUp.EndedDown = true;
	}
	else if (Key == EKeys::S)
	{
		GameInput->MoveDown.EndedDown = true;
	}
	else if (Key == EKeys::A)
	{
		GameInput->MoveLeft.EndedDown = true;
	}
	else if (Key == EKeys::D)
	{
		GameInput->MoveRight.EndedDown = true;
	}
}

void AUEPlayerController::ReceiveKeyReleasedEvent(FKey Key)
{
	UE_LOG(LogTemp, Log, TEXT("Key %s released"), *Key.GetDisplayName().ToString());
	if (Key == EKeys::W)
	{
		GameInput->MoveUp.EndedDown = false;
	}
	else if (Key == EKeys::S)
	{
		GameInput->MoveDown.EndedDown = false;
	}
	else if (Key == EKeys::A)
	{
		GameInput->MoveLeft.EndedDown = false;
	}
	else if (Key == EKeys::D)
	{
		GameInput->MoveRight.EndedDown = false;
	}
}

void AUEPlayerController::ReceiveForwardAxisEvent(float Value)
{
	//UE_LOG(LogTemp, Log, TEXT("Axis forward %f"), Value);
}

void AUEPlayerController::ReceiveRightAxisEvent(float Value)
{
	//UE_LOG(LogTemp, Log, TEXT("Axis right %f"), Value);
}

void AUEPlayerController::ReceiveLookUpAxisEvent(float Value)
{
	//UE_LOG(LogTemp, Log, TEXT("Axis look up %f"), Value);
}

void AUEPlayerController::ReceiveLookAroundAxisEvent(float Value)
{
	//UE_LOG(LogTemp, Log, TEXT("Axis look around %f"), Value);
}
