// "By G.C*JOJO"


#include "SaveManager.h"


ASaveManager::ASaveManager()
{
	
}

ASaveManager::~ASaveManager()
{
	
}

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


void ASaveManager::LoadDungeon_Implementation( FString SaveName, bool& SaveExists, bool& bIsOldFormat, FString& MinSaveVer)
{
	
}

void ASaveManager::SaveDungeon_Implementation( FString SaveName, bool ForceSave, bool& SaveExists)
{
	
}
