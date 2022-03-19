// G.C*JOJO

#pragma once

#include "CoreMinimal.h"
#include "DungeonEditor.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Async/AsyncWork.h"
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
	SkyboxDefault,
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

UENUM(BlueprintType)
enum ChangeSubLevelMode
{
	Normal,
	Enter,
	Exit,
	Blueprint
};

UENUM(BlueprintType)
enum ECustomCameraState
{
	Idle,
	BlendingUp,
	BlendingDown,
	Showing
};

UENUM(BlueprintType)
enum EAttackType
{
    Physical,
    Magical,
    Special,
    None
};

USTRUCT( BlueprintType)
struct FSaveData
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite)
    FString SaveFormatVersion;
	UPROPERTY(BlueprintReadWrite)
	FString SaveName;
	UPROPERTY(BlueprintReadWrite)
	FString SaveAuthor;
	UPROPERTY(BlueprintReadWrite)
	FString SaveMinVersion;
	UPROPERTY(BlueprintReadWrite)
	FGuid SaveGUID;
	UPROPERTY(BlueprintReadWrite)
	UTexture2D* SaveIcon;
	/*UPROPERTY(BlueprintReadWrite)
	bool bUseSkybox;
	UPROPERTY(BlueprintReadWrite)
	TEnumAsByte<HoleType> HoleType;
	UPROPERTY(BlueprintReadWrite)
	TEnumAsByte<SkyboxType> SkyboxType;
	UPROPERTY(BlueprintReadWrite)
	int32 ID;
	UPROPERTY(BlueprintReadWrite)
	int32 SizeX;
	UPROPERTY(BlueprintReadWrite)
	int32 SizeY;
	UPROPERTY(BlueprintReadWrite)
	int32 SizeDX;
	UPROPERTY(BlueprintReadWrite)
	int32 SizeDY;*/
	UPROPERTY(BlueprintReadWrite)
    TArray<FString> ActorsSaves;	
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

		UFUNCTION(BlueprintCallable, Category = "Files", meta = (Keywords = "Open File Dialog"))
		static bool OpenFileDialog(FString InitialDir, FString Title, bool UseFilter, FString& Filepath);

		UFUNCTION(BlueprintPure, Category = "User", meta = (Keywords = "Get User ID"))
		static int32 GetUserId(const APlayerController* PlayerController)
		{
			if(!IsValid(PlayerController))
			{
				DISPLAY_LOG("Player Controller Not Valid");
				return 0;
			}
			const ULocalPlayer* Player = Cast<ULocalPlayer>(PlayerController->Player);
			return Player->GetControllerId();
		}
	
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
