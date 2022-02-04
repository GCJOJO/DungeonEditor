// By G.C*JOJO


#include "OnlineLobbyManager.h"

//AOnlineLobbyManager* AOnlineLobbyManager::OnlineLobbyManagerInstance = nullptr;

AOnlineLobbyManager::AOnlineLobbyManager(): SaveData()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

/*
void UOnlineLobbyManager::CreateLobbyManager(TSubclassOf<UOnlineLobbyManager> ClassType)
{
	if(OnlineLobbyManagerInstance == nullptr)
	{
		OnlineLobbyManagerInstance = NewObject<UOnlineLobbyManager>(ClassType);
		OnlineLobbyManagerInstance->AddToRoot();
		OnlineLobbyManagerInstance->OnBeginPlay();
		OnlineLobbyManagerInstance->bCanTick = OnlineLobbyManagerInstance->bTimerStarted = true;
	}
}

UOnlineLobbyManager* UOnlineLobbyManager::GetLobbyManager()
{
	if(OnlineLobbyManagerInstance != nullptr){ return OnlineLobbyManagerInstance; }
	return nullptr;
}

void UOnlineLobbyManager::DestroyLobbyManager()
{
	if(OnlineLobbyManagerInstance != nullptr)
	{
		OnlineLobbyManagerInstance->OnDestroy();
		OnlineLobbyManagerInstance->RemoveFromRoot();
		OnlineLobbyManagerInstance->ConditionalBeginDestroy();
		OnlineLobbyManagerInstance = nullptr;
	}
}
*/

void AOnlineLobbyManager::SetSaveData(FSaveData NewSaveData)
{
	SaveData = NewSaveData;
}

FSaveData AOnlineLobbyManager::GetSaveData()
{
	return SaveData;
}
void AOnlineLobbyManager::OnSaveDataUpdated_Implementation(FSaveData)
{
	UE_LOG(LogDungeonEditor, Warning, TEXT("[LOBBY MANAGER] : Save Data Changed"));
}


// Stuff (Keep at the bottom)

bool AOnlineLobbyManager::IsSupportedForNetworking() const
{
	return true;
}

bool AOnlineLobbyManager::IsNameStableForNetworking() const
{
	return true;
}

void AOnlineLobbyManager::GetLifetimeReplicatedProps( TArray< FLifetimeProperty > & OutLifetimeProps ) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AOnlineLobbyManager, SaveData);
}

void AOnlineLobbyManager::BeginPlay()
{
	Super::BeginPlay();
}

void AOnlineLobbyManager::Destroyed()
{
	Super::Destroyed();
}

void AOnlineLobbyManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


