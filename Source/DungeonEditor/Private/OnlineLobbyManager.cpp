// By G.C*JOJO


#include "OnlineLobbyManager.h"

UOnlineLobbyManager* UOnlineLobbyManager::OnlineLobbyManagerInstance = nullptr;

UOnlineLobbyManager::UOnlineLobbyManager()
{
	bCanTick = bTimerStarted = false;
}

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

void UOnlineLobbyManager::SetSaveData(FSaveData NewSaveData)
{
	OnlineLobbyManagerInstance->SaveData = NewSaveData;
}

FSaveData UOnlineLobbyManager::GetSaveData()
{
	return OnlineLobbyManagerInstance->SaveData;
}
void UOnlineLobbyManager::OnSaveDataUpdated_Implementation(FSaveData)
{
	UE_LOG(LogDungeonEditor, Warning, TEXT("[LOBBY MANAGER] : Save Data Changed"));
}


// Stuff (Keep at the bottom)

bool UOnlineLobbyManager::IsSupportedForNetworking() const
{
	return true;
}

bool UOnlineLobbyManager::IsNameStableForNetworking() const
{
	return true;
}

void UOnlineLobbyManager::GetLifetimeReplicatedProps( TArray< FLifetimeProperty > & OutLifetimeProps ) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UOnlineLobbyManager, SaveData);
}