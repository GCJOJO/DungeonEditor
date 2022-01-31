// "By G.C*JOJO"

#pragma once

#include "CoreMinimal.h"

#include "Saveable.generated.h"

// This class does not need to be modified.
UINTERFACE(Blueprintable, BlueprintType)
class USaveable : public UInterface
{
	GENERATED_BODY()
};

class DUNGEONEDITOR_API ISaveable
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	/**
	*  @details This will return what the actor wants to save.
	**/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Saveable Interface")
	FString SaveSaveData();

	/**
	 *  @param SaveData The Data for an actor (Do not pass the class with it) 
	 **/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Saveable Interface")
	void LoadSaveData(UPARAM() FString SaveData);
};
