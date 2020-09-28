// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "FindSaveFiles.generated.h"

/**
 * 
 */
UCLASS()
class DUNGEONEDITOR_API UFindFiles : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	UFUNCTION(BlueprintCallable, Category="Dungeons", meta = (Keywords = "Find Save Files"))
	static bool FindFiles(TArray<FString>& Files, FString RootFolderFullPath, FString Ext);
};
