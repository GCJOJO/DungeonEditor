// By G.C*JOJO

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Tickable.h"
#include "Net/UnrealNetwork.h"
#include "DungeonEditor/DungeonEditorLibrary.h"
#include "OnlineLobbyManager.generated.h"

UCLASS(BlueprintType, Blueprintable)
class DUNGEONEDITOR_API AOnlineLobbyManager : public AActor
{
private:
	GENERATED_BODY()

public:
	
	AOnlineLobbyManager();

	UPROPERTY(BlueprintReadWrite, ReplicatedUsing=OnSaveDataUpdated)
	FSaveData SaveData;
	
	/*UFUNCTION(BlueprintCallable, Category = "Online Lobby")
	static void CreateLobbyManager(TSubclassOf<UOnlineLobbyManager> ClassType);

	/**
	 *
	 * Returns A UOnlineLobbyManager Reference
	 *	
	 *c un slash -------->  #1# 
	UFUNCTION(BlueprintCallable, Category = "Online Lobby")
	static UOnlineLobbyManager* GetLobbyManager();

	UFUNCTION(BlueprintCallable, Category = "Online Lobby")
	static void DestroyLobbyManager();*/

	
	virtual void BeginPlay() override;
	
	
	virtual void Destroyed() override;

	UFUNCTION(BlueprintSetter)
	void SetSaveData(FSaveData NewSaveData);

	UFUNCTION(BlueprintGetter)
	FSaveData GetSaveData();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Online Lobby Manager")
	void OnSaveDataUpdated(FSaveData Data);
	
	// Stuff (Keep at the bottom)
	
	virtual void Tick(float DeltaTime) override;

	/*virtual bool IsTickable() const override { return bCanTick; }
	virtual bool IsTickableInEditor() const override { return true; }
	virtual bool IsTickableWhenPaused() const override { return true; }
	virtual TStatId GetStatId() const override { return TStatId(); }*/

	virtual bool IsSupportedForNetworking() const override;
	virtual bool IsNameStableForNetworking() const override;
	
};
