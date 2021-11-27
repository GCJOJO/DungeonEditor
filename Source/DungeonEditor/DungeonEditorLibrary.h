// G.C*JOJO

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Async/AsyncWork.h"
#include "DungeonEditorLibrary.generated.h"

/*class FloorThreadFunctions : public FNonAbandonableTask
{
public:
	FloorThreadFunctions(int floorWidth, int floodHeight)
	{
		this->floorWidth = floorWidth;
		this->floorHeight = floorHeight;
	}

	int floorWidth;
	int floorHeight;

	FORCEINLINE TStatId GetStatId() const
	{
		RETURN_QUICK_DECLARE_CYCLE_STAT(MultiThreadedTask, STATGROUP_ThreadPoolAsyncTasks);
	}

	static void GenerateFloor()
	{
		UObject* FloorObjectToSpawn = Cast<UObject>(StaticLoadObject(UObject::StaticClass(), NULL, TEXT("/Game/BPs/Spawnalbes/Tiles/Floor.Floor")));

		UBlueprint* GeneratedBP = Cast<UBlueprint>(FloorObjectToSpawn);
		if (!FloorObjectToSpawn)
		{
			GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("Cannot Spawn Floor Tiles : CANT FIND OBJECT TO SPAWN")));
			return;
		}

		UClass* SpawnClass = FloorObjectToSpawn->StaticClass();
		if (SpawnClass == NULL)
		{
			GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("Cannot Spawn Floor Tiles : CLASS = NULL")));
			return;
		}

		UWorld* World = GEngine->GetWorld();
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		for(int x = 0; x < 255; x++)
		{
		    for(int y = 0; y < 255; y++)
		    {
				FVector SpawnLocation = FVector(x * 200, y * 200, -100);
		    	const FRotator SpawnRotator = FRotator(0, 0, 0);
		    	const FVector SpawnScale = FVector(2, 2, 2);

		    	
		    	AActor* NewActor = World->SpawnActor<AActor>(GeneratedBP->GeneratedClass, SpawnLocation, SpawnRotator, SpawnParams);
		    	NewActor->SetActorScale3D(SpawnScale);
		    }
		}
		return;
	}
	
};*/

UENUM(BlueprintType)
enum ELocalizationCulture 
{
	EN,
	FR
};

UENUM(BlueprintType)
enum EActivatorType
{
	Button,
	PressurePlate,
	Lever,
	Default
};

UENUM(BlueprintType)
enum EActivatorArray
{
	ArrayList1,
	ArrayList2
};

UENUM(BlueprintType)
enum EActorSearchMode
{
	All,
	InList
};

UENUM(BlueprintType)
enum ParticleLOD
{
	HIGH,
	MEDIUM,
	LOW,
	NONE
};

UENUM(BlueprintType)
enum DungeonEditorErrorType
{
	FileNotFound,
	NoError
};

UENUM(BlueprintType)
enum AIAction
{
	AiIdle,
	AiMove,
	AiIdleShop,
	AiEnterShop,
	AiExitShop,
	AiMoveShop
};

UENUM(BlueprintType)
enum HoleType
{
	Void,
	Lava
};

UENUM(BlueprintType)
enum SkyboxType
{
	SkyboxLava,
	SkyboxCastle,
	SkyboxSpace,
	SkyboxForest
};

UENUM(BlueprintType)
enum Direction
{
	X,
	Y,
	Z,
	NegativeX,
	NegativeY,
	NegativeZ
};

/*UENUM(BlueprintType)
enum ChangeSubLevelMode
{
	Single,
	Multiple
};*/

UENUM(BlueprintType)
enum ChangeSubLevelMode
{
	Normal,
	Enter,
	Exit
};

UENUM(BlueprintType)
enum ECustomCameraState
{
	Idle,
	BlendingUp,
	BlendingDown,
	Showing
};

UCLASS()
class DUNGEONEDITOR_API UDungeonEditorLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
		UFUNCTION(BlueprintCallable, Category = "Dungeons", meta = (keywords = "Change Localization"))
		static void ChangeLocalization(ELocalizationCulture culture);
		UFUNCTION(BlueprintPure, Category = "Dungeons", meta = (Keywords = "Load File"))
		static bool LoadFile(FString Path, FString FileName, FString& Text);
		UFUNCTION(BlueprintCallable, Category = "Dungeons", meta = (Keywords = "Save File"))
		static bool SaveFile(FString Path, FString FileName, FString Text);
		UFUNCTION(BlueprintCallable, Category = "Dungeons", meta = (Keywords = "Search Files in directory"))
		static bool FindFiles(TArray<FString>& Files, FString RootFolderFullPath, FString Ext);
		UFUNCTION(BlueprintCallable, Category = "Dungeons", meta = (Keywords = "Take a Screenshot"))
		static void TakeScreenshot(const FString & Filename, bool ShowUI, bool AddUniqueSuffix);
		UFUNCTION(BlueprintPure, Category = "Dungeons", meta = (Keywords = "Load Texture from Image"))
		static UTexture2D* LoadTextureFromPath(const FString& Path);

		// MULTI THREADING
		/*UFUNCTION(BlueprintCallable, Category = "Dungeons", meta = (Keywords = "Generate Floor On Other Thread"))
		static void GenerateFloorOnThread(int floorWidth, int floorHeight)
		{
			FloorThreadFunctions* floorGenerator = new FloorThreadFunctions(floorWidth, floorHeight);
			floorGenerator->GenerateFloor();
		}*/
	
		// Check if running in the editor
		UFUNCTION(BlueprintPure, Category = "Dungeons", meta = (Keywords = "Is In Editor"))
		static bool IsWithEditor();

	// NPC AI
		UFUNCTION(BlueprintCallable, Category = "Dungeons", meta = (Keywords = "AI : Choose Something"))
		static AIAction AIChooseSomething(int RandomInt);
};
