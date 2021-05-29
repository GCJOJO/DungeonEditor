// G.C*JOJO

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "DungeonEditorLibrary.generated.h"


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

	// NPC AI
		UFUNCTION(BlueprintCallable, Category = "Dungeons", meta = (Keywords = "AI : Choose Something"))
		static AIAction AIChooseSomething(int RandomInt);
};
