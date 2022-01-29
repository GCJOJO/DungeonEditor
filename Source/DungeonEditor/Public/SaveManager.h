// "By G.C*JOJO"

#pragma once

#include "CoreMinimal.h"

#include "SaveManager.generated.h"

/**
 * 
 */
UCLASS()
class DUNGEONEDITOR_API USaveManager : public UObject, public FTickableGameObject
{
	GENERATED_BODY()

private:
	static USaveManager* SaveManager;

	uint8 bCanTick : 1;
	uint8 bTimerStarted : 1;

public:

	USaveManager();

	UFUNCTION(BlueprintCallable, Category = "Save Manager")
	static void CreateSaveManager(TSubclassOf<USaveManager> ClassType);
	
	UFUNCTION(BlueprintCallable, Category = "Save Manager")
	static USaveManager* GetSaveManager();

	UFUNCTION(BlueprintCallable, Category = "Save Manager")
	static void DestroySaveManager();

	UFUNCTION(BlueprintNativeEvent, Category = "Save Manager")
	void SaveDungeon();

	UFUNCTION(BlueprintNativeEvent, Category = "Save Manager")
	void LoadDungeon();
	
	UFUNCTION(BlueprintImplementableEvent, meta = (keywords = "BeginPlay"))
	void BeginPlay();
	
	UFUNCTION(BlueprintImplementableEvent,  meta = (keywords = "Destory"))
	void OnDestroy();
	
	UFUNCTION(BlueprintImplementableEvent)
	void Tick(float DeltaTime) override;

	bool IsTickable() const override { return bCanTick; }
	bool IsTickableInEditor() const override { return true; }
	bool IsTickableWhenPaused() const override { return true; }
	TStatId GetStatId() const override { return TStatId(); }

	virtual bool IsSupportedForNetworking() const override { return true; }
	virtual bool IsNameStableForNetworking() const override { return true; }
};
