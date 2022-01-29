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


