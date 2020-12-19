// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "DungeonEditorLibrary.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum ELocalizationCulture 
{
	EN,
	FR
};

UENUM(BlueprintType)
enum EActivatorType
{
	Button,
	PressurePlate,
	Lever,
	Default
};

UENUM(BlueprintType)
enum EActivatorArray
{
	ArrayList1,
	ArrayList2
};

UENUM(BlueprintType)
enum EActorSearchMode
{
	All,
	InList
};

UCLASS()
class DUNGEONEDITOR_API UDungeonEditorLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
		UFUNCTION(BlueprintCallable, Category = "Dungeons", meta = (keywords = "Change Localization"))
		static void ChangeLocalization(ELocalizationCulture culture);
		UFUNCTION(BlueprintPure, Category = "Dungeons", meta = (Keywords = "Load File"))
		static bool LoadFile(FString Path, FString FileName, FString& Text);
		UFUNCTION(BlueprintCallable, Category = "Dungeons", meta = (Keywords = "Save File"))
		static bool SaveFile(FString Path, FString FileName, FString Text);
		UFUNCTION(BlueprintCallable, Category = "Dungeons", meta = (Keywords = "Search Files in directory"))
		static bool FindFiles(TArray<FString>& Files, FString RootFolderFullPath, FString Ext);
};
