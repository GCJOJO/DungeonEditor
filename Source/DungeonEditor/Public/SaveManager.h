// "By G.C*JOJO"

#pragma once

#include "CoreMinimal.h"
#include "DungeonEditor/DungeonEditorLibrary.h"
#include "GameFramework/Actor.h"
#include "SaveManager.generated.h"

UENUM(BlueprintType)
enum FSaveFileType
{
	SaveFile,
	JSON,
	PlainText
};

UCLASS(BlueprintType, Blueprintable)
class DUNGEONEDITOR_API ASaveManager : public AActor
{
private:
	GENERATED_BODY()

	//static ASaveManager* SaveManager;

public:	
	
	ASaveManager();
	virtual ~ASaveManager() override;

	/**
	 *	Save The Current Dungeon
	 *	@param SaveName The Name Of The Save
	 *	@param FileType The File Type of the File
	 *	@param SaveExists Does The Save Exists
	 *	@param ForceSave Do you want to force a save
	 *	@return Returns true if the save already existed or false if it did not
	 */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Save Manager")
	void SaveDungeon(FString SaveName, FSaveFileType FileType, bool ForceSave, bool& SaveExists);

	/**
	 *	Load the Given Dungeon
	 *	@param SaveName The Name Of The Save
	 *	@param FileType The File Type of the File
	 *	@param SaveExists Does The Save Exists
	 *	@param bIsOldFormat Does The Save Is In Older Format
	 *	@param MinSaveVer The minimum save file version
	 *	@return Returns if the save already existed and if it is saved in an old format
	 */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Save Manager")
	void LoadDungeon(FString SaveName, FSaveFileType FileType, bool& SaveExists, bool& bIsOldFormat, FString& MinSaveVer);

	/**
	 *	Load The Given Dungeon From a Save Data
	 *	@param SaveData The Save Data
	 *	@param FileType The File Type of the File
	 *	@param MinSaveVer The Minimum Save Version
	 *	@param Success If the loading Succeeded
	 */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Save Manager")
	void LoadDungeonFromSaveData(FSaveData SaveData, FString& MinSaveVer, bool& Success);

	/**
	 *	Loads a file and gets the Save Data
	 *	@param SaveName The Name of the File
	 *	@param FileType The File Type of the File
	 *	@param SaveData The Returned Save Data
	 *	@param Success If the loading succeeded 
	 */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Save Manager")
	void LoadSaveDataFromFile(FString SaveName, FSaveFileType FileType, FSaveData& SaveData, bool& Success);
	
	virtual void BeginPlay() override;
	
	virtual void Destroyed() override;
	
	virtual void Tick(float DeltaTime) override;

	virtual bool IsSupportedForNetworking() const override { return true; }
	virtual bool IsNameStableForNetworking() const override { return true; }
};
