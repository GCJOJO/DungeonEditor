// "By G.C*JOJO"


#include "SaveManager.h"


ASaveManager::ASaveManager()
{
	
}

ASaveManager::~ASaveManager()
{
	
}

/*void ASaveManager::CreateSaveManager(TSubclassOf<ASaveManager> ClassType)
{
	if(SaveManager == nullptr)
	{
		SaveManager = NewObject<ASaveManager>(ClassType);
		SaveManager->AddToRoot();
		SaveManager->BeginPlay();
	}
}

ASaveManager* ASaveManager::GetSaveManager()
{
	if (SaveManager != nullptr) return SaveManager;
	return nullptr;
}

void ASaveManager::DestroySaveManager()
{
	if(SaveManager != nullptr)
	{
		SaveManager->OnDestroy();
		SaveManager->RemoveFromRoot();
		SaveManager->ConditionalBeginDestroy();
		SaveManager = nullptr;
	}
}*/

void ASaveManager::BeginPlay()
{
	Super::BeginPlay();
}

void ASaveManager::Destroyed()
{
	Super::Destroyed();
}


void ASaveManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void ASaveManager::LoadDungeon_Implementation(UPARAM() FString SaveName, bool& SaveExists, bool& bIsOldFormat)
{
	
}

void ASaveManager::SaveDungeon_Implementation(UPARAM() FString SaveName, bool ForceSave, bool& SaveExists)
{
	
}
