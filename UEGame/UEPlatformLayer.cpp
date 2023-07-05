// Fill out your copyright notice in the Description page of Project Settings.


#include "UEPlatformLayer.h"
#include <dlfcn.h>
#include "UESpawnSystem.h"
#include "HAL/FileManagerGeneric.h"
#include "Kismet/GameplayStatics.h"
#include "UECommon.h"

DEBUG_PLATFORM_LOG(UELog)
{
	FString FormattedErrorMessage;
	va_list Args, ArgsCopy;
	va_start(Args, Format);
	va_copy(ArgsCopy, Args);
	{
		int32 Size = vsnprintf(nullptr, 0, Format, ArgsCopy) + 1;
		char* Buffer = new char[Size];
		vsnprintf(Buffer, Size, Format, Args);
		FormattedErrorMessage = FString(UTF8_TO_TCHAR(Buffer));
		delete[] Buffer;
	}
	va_end(ArgsCopy);
	va_end(Args);
	UE_LOG(LogTemp, Error, TEXT("%s"), *FormattedErrorMessage);
}


UUEPlatformLayer::UUEPlatformLayer()
{
	DLLPath = FPaths::ConvertRelativePathToFull(FPaths::ProjectDir());
	DLLName = TEXT("Binaries/Linux/spaceinvaders.os");
	DLLTempName = TEXT("Binaries/Linux/spaceinvaders_temp.os");
}


void UUEPlatformLayer::LoadGameCode()
{
	//TODO(pipecaniza): this is just a temporal solution
	FFileManagerGeneric FileManager;
	TArray<uint8> BinaryFile;

	FString DLLFullPath = DLLPath / DLLName;
	FString DLLTempFullPath = DLLPath / DLLTempName;
	
	FFileHelper::LoadFileToArray(BinaryFile, *DLLFullPath);
	FFileHelper::SaveArrayToFile(BinaryFile, *DLLTempFullPath);
	
	GameCode.DLLLastWriteTime = FileManager.GetTimeStamp(*DLLFullPath);
	GameCode.DLLHandler = dlopen(TCHAR_TO_UTF8(*DLLTempFullPath), RTLD_LAZY);
	
	if (GameCode.DLLHandler)
	{
		UE_LOG(LogTemp, Error, TEXT("Reload game code"))
		void *Proc = dlsym(GameCode.DLLHandler, TCHAR_TO_UTF8(TEXT("GameLoop")));
		if (Proc)
		{
			GameCode.GameLoop = (game_loop*)Proc;	
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Unable to load the game code"));
	}
}


void UUEPlatformLayer::UnloadGameCode()
{
	if (GameCode.DLLHandler)
	{
		UE_LOG(LogTemp, Error, TEXT("Unload game code"))
		dlclose(GameCode.DLLHandler);
	}
	GameCode = {};	
}


void UUEPlatformLayer::ReloadGameCode()
{
	UnloadGameCode();
	FPlatformProcess::Sleep(1.0f);
	LoadGameCode();
}


void UUEPlatformLayer::Init()
{
	Super::Init();
	
	{
		int32 MemorySize = Megabytes(100);
		MemoryBlock = (uint8*)FMemory::MallocZeroed(sizeof(game_memory) + MemorySize);
		GameMemory = (game_memory*)MemoryBlock;
		GameMemory->Size = MemorySize - sizeof(game_state);
		GameMemory->BaseAddress = (MemoryBlock + (sizeof(game_memory) + sizeof(game_state)));
		GameMemory->PlatformApi.DebugPlatformLog = UELog;

		GameMemory->GameState = (game_state*)(MemoryBlock + sizeof(game_memory));
	
		GameInput = { };

		LoadGameCode();
	}
	SpawnSystem = NewObject<UUESpawnSystem>(this, SpawnSystemClass.Get());
}

void UUEPlatformLayer::Shutdown()
{
	Super::Shutdown();
	UnloadGameCode();
}


void UUEPlatformLayer::BeginGameLoop()
{
	UE_LOG(LogTemp, Log, TEXT("Beginning"));
	if (RootClass)
	{
		FActorSpawnParameters Params;
		Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		Root = this->GetWorld()->SpawnActor<AActor>(RootClass.Get(), FVector::Zero(),
			FRotator::ZeroRotator, Params);
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("No root class"));
	}

	// TODO(pipecaniza): do we need this??
	if (AnchorPoint)
	{
		FActorSpawnParameters Params;
		Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		AnchorPoint = this->GetWorld()->SpawnActor<AActor>(AnchorPointClass.Get(), FVector::Zero(),
			FRotator::ZeroRotator, Params);
	}else
	{
		UE_LOG(LogTemp, Log, TEXT("No anchor class"));
	}
}


void UUEPlatformLayer::Tick(float DeltaSeconds)
{
	auto HasBeenInitialized = GameMemory->HasBeenInitialized;
	// TODO(pipecaniza): this should only be executed in debug mode
	{
		FFileManagerGeneric FileManager;
		FDateTime CurrentDLLTime = FileManager.GetTimeStamp(*(DLLPath / DLLName));
	
		if (CurrentDLLTime != GameCode.DLLLastWriteTime)
		{
			ReloadGameCode();
		}
	}
	
	if (GameCode.GameLoop)
	{
		GameCode.GameLoop(GameMemory, &GameInput);

		if (HasBeenInitialized != GameMemory->HasBeenInitialized)
		{
			// TODO(pipecaniza): initialize
		}

		// TODO(pipecaniza): define loop stages
		SpawnSystem->SpawnPendingActors(&GameMemory->PlatformState.SpawningStack);

		// NOTE(pipecaniza): Apply game actors movement
		{
			for (uint32 Index = 0 ; Index < SpawnSystem->SpawnedActors.Num(); ++Index)
			{
				AActor* Actor =  SpawnSystem->SpawnedActors[Index];
				if (Actor)
				{
					// TODO(pipecaniza): how to ensure that we keep the spawn system (ue) with the
					// actor positions sync so the correct V3 is pointing to the owner
					Actor->SetActorRelativeLocation(V3ToFVector(&GameMemory->GameState->ActorPositions[Index]));
				}
			}
			
		}
	}
}
