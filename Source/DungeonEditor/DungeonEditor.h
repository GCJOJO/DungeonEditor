// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

DECLARE_LOG_CATEGORY_EXTERN(LogDungeonEditor, Log, All);

#define DISPLAY_LOG(fmt, ...) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Red, FString::Printf(TEXT(fmt), __VA_ARGS__));