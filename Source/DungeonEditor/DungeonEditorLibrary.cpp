// G.C*JOJO

/*
@TODO : Upload\Download de donjons 0/4
@TODO :		-Serveur o? on peut upload les donjons(DungeonEditorServer.exe)
@TODO :		-Menu de t?l?chargement de donjons
@TODO :		-Upload de donjons(nom, uid, auteur, version minimum)
@TODO :		-R?cup?ration donjons du server
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
	UE_LOG(LogTemp, Log, TEXT("Screenshot taken !"));
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
		return AIAction::idle;
		break;
	case 1:
		return AIAction::idle;
		break;
	case 2:
		return AIAction::move;
		break;
	case 3:
		return AIAction::move;
		break;
	case 4:
		return AIAction::idleShop;
		break;
	case 5:
		return AIAction::enterShop;
		break;
	case 6:
		return AIAction::moveShop;
		break;

	default:
		return AIAction::idle;
	}
	return AIAction::idle;

}

bool UDungeonEditorLibrary::IsWithEditor()
{
		#if WITH_EDITOR
			return true;
		#else
			return false;
		#endif
}

