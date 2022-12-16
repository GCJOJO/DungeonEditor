#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "DungeonEditorTypes.generated.h"

/**
 * 
 */




//													Editor Mode | Test Mode in Editor | Basic Play mode (no Editor)
UENUM(Blueprintable, BlueprintType) enum GameModeTypes { Editor, PlayModeEditor, PlayMode };
UENUM(Blueprintable, BlueprintType) enum ObjectTypes { Basic, Systems, Objects, Props };
UENUM(Blueprintable, BlueprintType) enum ELocalizationCulture { EN,	FR };
UENUM(Blueprintable, BlueprintType) enum EActivatorMethods { Base, FlipFlop };

UCLASS()
class DUNGEONEDITOR_API UDungeonEditorTypes : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
};
