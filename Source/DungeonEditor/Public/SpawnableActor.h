// By G.C*JOJO

#pragma once

#include "CoreMinimal.h"
#include "../../../Plugins/BlueprintJson/Source/BlueprintJson/Classes/BlueprintJsonLibrary.h"
#include "DungeonEditor/Public/Saveable.h"
#include "GameFramework/Actor.h"
#include "SpawnableActor.generated.h"

UCLASS()
class DUNGEONEDITOR_API ASpawnableActor : public AActor, public ISaveable
{
public:
	
private:
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	ASpawnableActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	/**
	 *	@param Event The Event to send
	 *	@param EventData The Event Data
	 *	Should be executed by a client
	 */
	UFUNCTION(reliable, server, WithValidation, BlueprintCallable)
	void SendEventToServer(const FBlueprintJsonObject Event,const FBlueprintJsonObject EventData);
	/**
	 *	@param Event The Event to send
	 *	@param EventData The Event Data
	 *	Should be executed by the server
	 */
	UFUNCTION(reliable, Client, BlueprintCallable)
	void SendEventToClient(const FBlueprintJsonObject Event, const FBlueprintJsonObject EventData);
	/**
	 *	@param Event The Event to send
	 *	@param EventData The Event Data
	 *	Should be executed by the server
	 */
	UFUNCTION(Reliable, NetMulticast, BlueprintCallable)
	void SendEventToAllClient(const FBlueprintJsonObject Event, const FBlueprintJsonObject EventData);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void ServerReceiveEvent(const FBlueprintJsonObject Event, const FBlueprintJsonObject EventData);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void ClientReceiveEvent(const FBlueprintJsonObject Event, const FBlueprintJsonObject EventData);

	virtual bool IsSupportedForNetworking() const override { return true; }
	virtual bool IsNameStableForNetworking() const override { return true; }
};
