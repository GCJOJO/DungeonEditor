// Fill out your copyright notice in the Description page of Project Settings.


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