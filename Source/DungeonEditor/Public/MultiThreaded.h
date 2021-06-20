// By G.C*JOJO

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "MultiThreaded.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UMultiThreaded : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class DUNGEONEDITOR_API IMultiThreaded
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Dungeons", meta = (keywords = "Multi Threaded Function"))
	void MultiThreadedFunction();
};
