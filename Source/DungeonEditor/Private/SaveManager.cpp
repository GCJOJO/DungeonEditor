// "By G.C*JOJO"


#include "SaveManager.h"

USaveManager* USaveManager::SaveManager = nullptr;

USaveManager::USaveManager()
{
	bCanTick = bTimerStarted = false;
}

void USaveManager::CreateSaveManager(TSubclassOf<USaveManager> ClassType)
{
	if(SaveManager == nullptr)
	{
		SaveManager = NewObject<USaveManager>(ClassType);
		SaveManager->AddToRoot();
		SaveManager->BeginPlay();
		SaveManager->bCanTick = SaveManager->bTimerStarted = true;
	}
}

USaveManager* USaveManager::GetSaveManager()
{
	if (SaveManager != nullptr) return SaveManager;
	return nullptr;
}

void USaveManager::DestroySaveManager()
{
	if(SaveManager != nullptr)
	{
		SaveManager->OnDestroy();
		SaveManager->RemoveFromRoot();
		SaveManager->ConditionalBeginDestroy();
		SaveManager = nullptr;
	}
}

void USaveManager::LoadDungeon_Implementation()
{
	
}

void USaveManager::SaveDungeon_Implementation()
{
	
}
