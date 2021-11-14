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

UENUM(BlueprintType)
enum EUserLoginStatus
{
	/** Player has not logged in or chosen a local profile */
	NotLoggedIn,
	/** Player is using a local profile but is not logged in */
	UsingLocalProfile,
	/** Player has been validated by the platform specific authentication service */
	LoggedIn
};

UCLASS()
class DUNGEONEDITOR_API UEOSLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
		// User Management
		UFUNCTION(BlueprintCallable, Category = "EOS", meta = (keywords = "Login"))
		static bool Login(int32 UserNum, ELoginType loginType);
		UFUNCTION(BlueprintCallable, Category = "EOS", meta = (keywords = "Logout"))
		static bool Logout(int32 UserNum);
		UFUNCTION(BlueprintCallable, Category="EOS", meta = (keywords = "Try To Auto Login"))
		static bool TryAutoLogin(int32 UserNum);
		UFUNCTION(BlueprintCallable, Category = "EOS", meta = (keywords = "Get User Login Status"))
		static EUserLoginStatus GetLoginStatus(int32 localUserNum);
		UFUNCTION(BlueprintCallable, Category = "EOS", meta = (keywords = "Get Player Nickname"))
		static FString GetPlayerNickname(int32 LocalUserNum);

		// Friends
		UFUNCTION(BlueprintCallable, Category = "EOS", meta = (keywords = "Get Player Friends"))
		static void GetPlayerFriends(int32 LocalUserNum);

		// Lobbies
		UFUNCTION(BlueprintCallable, Category = "EOS", meta = (keywords = "Create Lobby"))
		static bool CreateLobby(int32 localUserNum, FText GroupName, FText GroupDesc, FText GroupMotto, bool bIsInviteOnly, FString GroupLanguage);
};
