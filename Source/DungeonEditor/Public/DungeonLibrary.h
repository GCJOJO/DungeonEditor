//  

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "DungeonLibrary.generated.h"

/**
 * 
 */
UCLASS()
class DUNGEONEDITOR_API UDungeonLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	UFUNCTION(BlueprintCallable, Category = "Dungeons", meta = (Keywords = "Find Save Files"))
	static bool FindSaveFiles(TArray<FString>& Files, FString RootFolderFullPath, FString Ext);
};
