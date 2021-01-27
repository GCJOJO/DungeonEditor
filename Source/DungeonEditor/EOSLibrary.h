

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include <OnlineSubsystem.h>
#include "EOSLibrary.generated.h"


/**
 * 
 */
UCLASS()
class EOSBASIC_API UEOSLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
		UFUNCTION(BlueprintCallable, Category = "EOS", meta = (keywords = "Login"))
		static void Login(int32 userNum);
		UFUNCTION(BlueprintCallable, Category = "EOS", meta = (keywords = "Logout"))
		static void Logout(int32 UserNum);
		UFUNCTION(BlueprintCallable, Category = "EOS", meta = (keywords = "Get Player Nickname"))
		static FString GetPlayerNickname(int32 LocalUserNum);
};
