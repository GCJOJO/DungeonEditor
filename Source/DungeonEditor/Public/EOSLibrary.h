// By G.C*JOJO

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "EOSLibrary.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum ELoginType
{
	Web,
	Code
};

UCLASS()
class DUNGEONEDITOR_API UEOSLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	/*	UFUNCTION(BlueprintCallable, Category = "EOS", meta = (keywords = "Login"))
		static void Login(int32 UserNum, ELoginType loginType);
		UFUNCTION(BlueprintCallable, Category = "EOS", meta = (keywords = "Logout"))
		static void Logout(int32 UserNum);
		UFUNCTION(BlueprintCallable, Category = "EOS", meta = (keywords = "Get Player Nickname"))
		static FString GetPlayerNickname(int32 LocalUserNum);
		UFUNCTION(BlueprintCallable, Category = "EOS", meta = (keywords = "Get Player Friends"))
		static void GetPlayerFriends(int32 LocalUserNum);

		UFUNCTION(BlueprintCallable, Category = "EOS", meta = (keywords = "Create Lobby"))
		static bool CreateLobby(int32 localUserNum, FText GroupName, FText GroupDesc, FText GroupMotto, bool bIsInviteOnly, FString GroupLanguage);*/
};
