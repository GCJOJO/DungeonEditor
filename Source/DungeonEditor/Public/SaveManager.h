// "By G.C*JOJO"

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SaveManager.generated.h"

UCLASS(BlueprintType, Blueprintable)
class DUNGEONEDITOR_API ASaveManager : public AActor
{
private:
	GENERATED_BODY()

	//static ASaveManager* SaveManager;

public:	
	
	ASaveManager();
	~ASaveManager();

	/*UFUNCTION(BlueprintCallable, Category = "Save Manager")
	static void CreateSaveManager(TSubclassOf<ASaveManager> ClassType);
	
	UFUNCTION(BlueprintCallable, Category = "Save Manager")
	static ASaveManager* GetSaveManager();

	UFUNCTION(BlueprintCallable, Category = "Save Manager")
	static void DestroySaveManager();*/


	/**
	 *	Save The Current Dungeon
	 *	@param SaveName The Name Of The Save
	 *	@param SaveExists Does The Save Exists
	 *	@return Returns true if the save already existed or false if it did not
	 */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Save Manager")
	void SaveDungeon(UPARAM() FString SaveName, bool ForceSave, bool& SaveExists);

	/**
	 *	Load the Given Dungeon
	 *	@param SaveName The Name Of The Save
	 *	@param SaveExists Does The Save Exists
	 *	@param bIsOldFormat Does The Save Is In Older Format
	 *	@return Returns if the save already existed and if it is saved in an old format
	 */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Save Manager")
	void LoadDungeon(UPARAM() FString SaveName, bool& SaveExists, bool& bIsOldFormat);
	
	virtual void BeginPlay() override;
	
	virtual void Destroyed() override;
	
	virtual void Tick(float DeltaTime) override;

	virtual bool IsSupportedForNetworking() const override { return true; }
	virtual bool IsNameStableForNetworking() const override { return true; }
};
