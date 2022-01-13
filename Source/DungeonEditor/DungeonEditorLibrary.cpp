// G.C*JOJO

/*
@TODO : Upload\Download de donjons 0/4
@TODO :		-Serveur où on peut upload les donjons(DungeonEditorServer.exe)
@TODO :		-Menu de téléchargement de donjons
@TODO :		-Upload de donjons(nom, uid, auteur, version minimum)
@TODO :		-Récupération donjons du server

@TODO : Multijoueur ??? (Avec EOS ???)
@TODO :		-Rejoindre/Créer des parties
@TODO :		-Système de chef de groupe
@TODO :		-Chef de groupe qui peut choisir des niveau téléchargés
@TODO :		-Liste d'amis et parties privées
*/

#include "DungeonEditorLibrary.h"

void UDungeonEditorLibrary::ChangeLocalization(ELocalizationCulture culture)
{
	switch(culture)
	{
	case ELocalizationCulture::EN :
		FInternationalization::Get().SetCurrentCulture(TEXT("en"));
		break;
	case ELocalizationCulture::FR :
		FInternationalization::Get().SetCurrentCulture(TEXT("fr-FR"));
		break;
	}
}


bool UDungeonEditorLibrary::LoadFile(FString Path, FString FileName, FString& Text)
{
	return FFileHelper::LoadFileToString(Text, *(Path + FileName));
}

bool UDungeonEditorLibrary::SaveFile(FString Path, FString FileName, FString Text)
{
	return FFileHelper::SaveStringToFile(Text, *(Path + FileName));
}

bool UDungeonEditorLibrary::FindFiles(TArray<FString>& Files, FString RootFolderFullPath, FString Ext)
{
    if (RootFolderFullPath.Len() < 1) return false;

    FPaths::NormalizeDirectoryName(RootFolderFullPath);

    IFileManager& FileManager = IFileManager::Get();

    if (Ext == "")
    {
        Ext = "*.*";
    }
    else
    {
        Ext = (Ext.Left(1) == ".") ? "*" + Ext : "*." + Ext;
    }

    FString FinalPath = RootFolderFullPath + "/" + Ext;
    FileManager.FindFiles(Files, *FinalPath, true, false);
    return true;
}

void UDungeonEditorLibrary::TakeScreenshot(const FString& Filename, bool ShowUI, bool AddUniqueSuffix)
{  
	FScreenshotRequest::RequestScreenshot(Filename, ShowUI, AddUniqueSuffix);
	DISPLAY_LOG("Screenshot taken !");
}

UTexture2D* UDungeonEditorLibrary::LoadTextureFromPath(const FString& Path)
{
	if (Path.IsEmpty()) return nullptr;
	
	return Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), nullptr, *(Path)));
}

AIAction UDungeonEditorLibrary::AIChooseSomething(int RandomInt)
{
	switch (RandomInt)
	{
	case 0:
		return AIAction::AiIdle;
		break;
	case 1:
		return AIAction::AiIdle;
		break;
	case 2:
		return AIAction::AiMove;
		break;
	case 3:
		return AIAction::AiMove;
		break;
	case 4:
		return AIAction::AiIdleShop;
		break;
	case 5:
		return AIAction::AiEnterShop;
		break;
	case 6:
		return AIAction::AiMoveShop;
		break;

	default:
		return AIAction::AiIdle;
	}
	return AIAction::AiIdle;

}

bool UDungeonEditorLibrary::IsWithEditor()
{
		#if WITH_EDITOR
			return true;
		#else
			return false;
		#endif
}

