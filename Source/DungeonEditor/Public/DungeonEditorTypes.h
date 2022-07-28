#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "DungeonEditorTypes.generated.h"

/**
 * 
 */





UENUM(Blueprintable, BlueprintType) enum GameModeTypes { Editor, PlayMode };
UENUM(Blueprintable, BlueprintType) enum ObjectTypes { Basic, Systems, Objects, Props };

UCLASS()
class DUNGEONEDITOR_API UDungeonEditorTypes : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
};
