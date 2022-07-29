//  


#include "DungeonLibrary.h"

bool UDungeonLibrary::FindSaveFiles(TArray<FString>& Files, FString RootFolderFullPath, FString Ext)
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
