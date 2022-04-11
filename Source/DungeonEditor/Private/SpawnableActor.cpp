// By G.C*JOJO


#include "SpawnableActor.h"

// Sets default values
ASpawnableActor::ASpawnableActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ASpawnableActor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ASpawnableActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASpawnableActor::ClientReceiveEvent_Implementation(const FBlueprintJsonObject Event, const FBlueprintJsonObject EventData)
{
}

void ASpawnableActor::ServerReceiveEvent_Implementation(const FBlueprintJsonObject Event, const FBlueprintJsonObject EventData)
{
}

void ASpawnableActor::SendEventToServer_Implementation(const FBlueprintJsonObject Event,const FBlueprintJsonObject EventData)
{
	ServerReceiveEvent(Event, EventData);
}

bool ASpawnableActor::SendEventToServer_Validate(const FBlueprintJsonObject Event, const FBlueprintJsonObject EventData)
{
	return true;
}

void ASpawnableActor::SendEventToClient_Implementation(const FBlueprintJsonObject Event, const FBlueprintJsonObject EventData)
{
	ClientReceiveEvent(Event, EventData);
}

void ASpawnableActor::SendEventToAllClient_Implementation(const FBlueprintJsonObject Event, const FBlueprintJsonObject EventData)
{
	ClientReceiveEvent(Event, EventData);
}

