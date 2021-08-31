#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include <SimpleUGC/Public/UGCRegistry.h>
#include "DungeonCustomGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class DUNGEONEDITOR_API UDungeonCustomGameInstance : public UGameInstance
{
	GENERATED_BODY()
	public:
		virtual void Init() override;

		// The Registry that holds information about UGC and assigned class overrides
		UPROPERTY(BlueprintReadOnly, Category = "SimpleUGC")
		UUGCRegistry* UGCRegistry;
};
