//  


#include "DungeonLibrary.h"

void UDungeonLibrary::ChangeLocalization(ELocalizationCulture culture)
{
    switch (culture)
    {
    case ELocalizationCulture::EN:
        FInternationalization::Get().SetCurrentCulture(TEXT("en"));
        break;
    case ELocalizationCulture::FR:
        FInternationalization::Get().SetCurrentCulture(TEXT("fr-FR"));
        break;
    }
}

bool UDungeonLibrary::LoadFile(FString Path, FString FileName, FString& Text)
{
    return FFileHelper::LoadFileToString(Text, *(Path + FileName));
}

bool UDungeonLibrary::SaveFile(FString Path, FString FileName, FString Text)
{
    return FFileHelper::SaveStringToFile(Text, *(Path + FileName));
}

bool UDungeonLibrary::FindFiles(TArray<FString>& Files, FString RootFolderFullPath, FString Ext)
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


bool UDungeonLibrary::WriteToFile(FString Path, FString FileName, bool Overwrite, FString Text)
{
    if (!Overwrite)
    {
        FString OldText;
        LoadFile(Path, FileName, OldText);

        const FString NewText = OldText + Text;

        return SaveFile(Path, FileName, NewText);
    }
    return SaveFile(Path, FileName, Text);
}

FString UDungeonLibrary::GetPersistentDataPath()
{
    return FPaths::ProjectSavedDir() + "\\PersistentData\\";
}

bool UDungeonLibrary::Log(FString Text, bool Overwrite, float Duration)
{
    GEngine->AddOnScreenDebugMessage(-1, Duration, FColor(255, 0, 0), Text);
    return WriteToFile(FPaths::ProjectSavedDir(), "Dungeon.log", Overwrite, Text + "\n");
}

bool UDungeonLibrary::IsEditor()
{
#if WITH_EDITOR
    return true;
#else
    return false;
#endif
}