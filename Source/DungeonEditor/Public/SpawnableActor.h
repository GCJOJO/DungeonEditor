// By G.C*JOJO

#pragma once

#include "CoreMinimal.h"
#include "DungeonEditor/Public/Saveable.h"
#include "GameFramework/Actor.h"
#include "SpawnableActor.generated.h"

UCLASS()
class DUNGEONEDITOR_API ASpawnableActor : public AActor, public ISaveable
{
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

	virtual bool IsSupportedForNetworking() const override { return true; }
	virtual bool IsNameStableForNetworking() const override { return true; }
};
