// G.C*JOJO

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "MultiThreaded.h"
#include "Async/AsyncWork.h"
#include "DungeonEditorLibrary.generated.h"

class MultiThreadedTask : public FNonAbandonableTask
{
public:
	MultiThreadedTask(UObject* object) {this->object = object;}

	UObject* object;

	FORCEINLINE TStatId GetStatId() const
	{
		RETURN_QUICK_DECLARE_CYCLE_STAT(MultiThreadedTask, STATGROUP_ThreadPoolAsyncTasks);
	}

	void DoWork()
	{
		IMultiThreaded::Execute_MultiThreadedFunction(object);
	}
	
};

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
	idle,
	move,
	idleShop,
	enterShop,
	exitShop,
	moveShop
};

UENUM(BlueprintType)
enum HoleType
{
	Void,
	Lava
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
		UFUNCTION(BlueprintCallable, Category = "Dungeons", meta = (keywords = "Call Multi Threaded Function"))
		static void CallMultiThreadedFunction(UObject* object)
		{
			(new FAutoDeleteAsyncTask<MultiThreadedTask>(object))->StartBackgroundTask();
		}
	
		// Check if running in the editor
		UFUNCTION(BlueprintPure, Category = "Dungeons", meta = (Keywords = "Is In Editor"))
		static bool IsWithEditor();

	// NPC AI
		UFUNCTION(BlueprintCallable, Category = "Dungeons", meta = (Keywords = "AI : Choose Something"))
		static AIAction AIChooseSomething(int RandomInt);
};
