// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "DiscordLibrary.generated.h"

/**
 * 
 */
UCLASS()
class DUNGEONEDITOR_API UDiscordLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

		UFUNCTION(BlueprintCallable, Category = "Dungeons Discord", meta = (Keywords = "Init Discord"))
		static bool InitDiscord();

		UFUNCTION(BlueprintCallable, Category = "Dungeons Discord", meta = (Keywords = "Update Discord"))
		static bool UpdateDiscord();

		UFUNCTION(BlueprintCallable, Category = "Dungeons Discord", meta = (Keywords = "Discord Set Activity"))
		static bool SetDiscordActivity(FString State, FString Details);
};
