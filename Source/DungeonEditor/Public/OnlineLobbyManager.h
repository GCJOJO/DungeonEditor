// By G.C*JOJO

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Tickable.h"
#include "DungeonEditor/DungeonEditorLibrary.h"
#include "OnlineLobbyManager.generated.h"

UCLASS(BlueprintType, Blueprintable)
class DUNGEONEDITOR_API UOnlineLobbyManager : public UObject, public FTickableGameObject
{
	GENERATED_BODY()

private:

	static UOnlineLobbyManager* OnlineLobbyManagerInstance;
	
	uint8 bCanTick : 1;
	uint8 bTimerStarted : 1;

public:
	
	UOnlineLobbyManager();

	UPROPERTY(BlueprintReadWrite, Replicated)
	FSaveData SaveData;
	
	UFUNCTION(BlueprintCallable, Category = "Online Lobby")
	static void CreateLobbyManager(TSubclassOf<UOnlineLobbyManager> ClassType);

	/**
	 *
	 * Returns A UOnlineLobbyManager Reference
	 *	
	 **/
	UFUNCTION(BlueprintCallable, Category = "Online Lobby")
	static UOnlineLobbyManager* GetLobbyManager();

	UFUNCTION(BlueprintCallable, Category = "Online Lobby")
	static void DestroyLobbyManager();

	UFUNCTION(BlueprintImplementableEvent, meta = (keywords = "BeginPlay"))
	void OnBeginPlay();
	
	UFUNCTION(BlueprintImplementableEvent,  meta = (keywords = "Destory"))
	void OnDestroy();

	UFUNCTION(BlueprintSetter)
	static void SetSaveData(FSaveData NewSaveData);

	UFUNCTION(BlueprintGetter)
	static FSaveData GetSaveData();

	// Stuff (Keep at the bottom)
	
	UFUNCTION(BlueprintImplementableEvent)
	void Tick(float DeltaTime) override;

	bool IsTickable() const override { return bCanTick; }
	bool IsTickableInEditor() const override { return true; }
	bool IsTickableWhenPaused() const override { return true; }
	TStatId GetStatId() const override { return TStatId(); }
	
	bool IsSupportedForNetworking() const override;
	bool IsNameStableForNetworking() const override;
};
