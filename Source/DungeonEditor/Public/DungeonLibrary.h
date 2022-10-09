//  

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include <DungeonEditor/Public/DungeonEditorTypes.h>
#include "DungeonLibrary.generated.h"

/**
 * 
 */


UENUM(BlueprintType, Blueprintable) enum EMoveAxis 
{
	X,
	Y,
	Z,
	XY,
	YZ,
	XZ,
	XYZ
};

UCLASS()
class DUNGEONEDITOR_API UDungeonLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable)
	static void ChangeLocalization(ELocalizationCulture culture);

	UFUNCTION(BlueprintCallable, Category = "File Utilities", meta = (Keywords = "Load File"))
	static bool LoadFile(FString Path, FString FileName, FString& Text);
	UFUNCTION(BlueprintCallable, Category = "File Utilities", meta = (Keywords = "Save File"))
	static bool SaveFile(FString Path, FString FileName, FString Text);
	UFUNCTION(BlueprintCallable, Category = "Dungeons", meta = (Keywords = "Find Save Files"))
	static bool FindFiles(TArray<FString>& Files, FString RootFolderFullPath, FString Ext);

	UFUNCTION(BlueprintCallable, Category = "File Utilities", meta = (Keywords = "Write to File"))
	static bool WriteToFile(FString Path, FString FileName, bool Overwrite, FString Text);

	UFUNCTION(BlueprintPure, Category = "File Utilities")
	static FString GetPersistentDataPath();

	UFUNCTION(BlueprintCallable, Category = "Utilities", meta = (Keywords = "Log"))
	static bool Log(FString Text, bool Overwrite, float Duration = 2.0f);

	UFUNCTION(BlueprintPure, Category="Utilities")
	static bool IsEditor();
};
