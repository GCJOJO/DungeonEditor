#include "DungeonCustomGameInstance.h"

void UDungeonCustomGameInstance::Init()
{
	// Instnatiate the registry and find mod packages
	UGCRegistry = NewObject<UUGCRegistry>(this);
	UGCRegistry->FindUGCPackages();
	UE_LOG(LogActor, Warning, TEXT("Initialized Custom Game Instance"));
	Super::Init();
}