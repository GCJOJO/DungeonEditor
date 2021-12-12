// By G.C*JOJO

#pragma once

#include "CoreMinimal.h"
#include "BlueprintDataDefinitions.h"
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
	/* Player has not logged in or chosen a local profile */
	NotLoggedIn,
	/* Player is using a local profile but is not logged in */
	UsingLocalProfile,
	/* Player has been validated by the platform specific authentication service */
	LoggedIn
};

UCLASS()
class DUNGEONEDITOR_API UEOSLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	// User Management
	UFUNCTION(BlueprintCallable, Category = "EOS", meta = (keywords = "Login"))
	static bool Login(APlayerController* PlayerController, ELoginType loginType);
	UFUNCTION(BlueprintCallable, Category = "EOS", meta = (keywords = "Logout"))
	static bool Logout(APlayerController* PlayerController);
	UFUNCTION(BlueprintCallable, Category="EOS", meta = (keywords = "Try To Auto Login"))
	static bool TryAutoLogin(APlayerController* PlayerController);
	UFUNCTION(BlueprintCallable, Category = "EOS", meta = (keywords = "Get User Login Status"))
	static EUserLoginStatus GetLoginStatus(APlayerController* PlayerController);
	UFUNCTION(BlueprintCallable, Category = "EOS", meta = (keywords = "Get Player Nickname"))
	static FString GetPlayerNickname(APlayerController* PlayerController);

	// Friends
	UFUNCTION(BlueprintCallable, Category = "EOS", meta = (keywords = "Get Player Friends"))
	static void GetPlayerFriends(APlayerController* PlayerController);

	// Stats And Achievements
	UFUNCTION(BlueprintCallable, Category = "EOS", meta = (keywords = "Retrieve Achievements"))
	bool RetrieveAchievements(APlayerController *PlayerController);
	
};