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
	Code,
	Dev
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
	UFUNCTION(BlueprintCallable, Category = "EOS", meta = (keywords = "Login", AdvancedDisplay = "DevIP, DevToken"))
	static bool Login(int32 UserNum, ELoginType loginType, FString DevIP = "127.0.0.1:1024", FString DevToken = "UE4");
	UFUNCTION(BlueprintCallable, Category = "EOS", meta = (keywords = "Logout"))
	static bool Logout(int32 UserNum);
	UFUNCTION(BlueprintCallable, Category="EOS", meta = (keywords = "Try To Auto Login"))
	static bool TryAutoLogin(int32 UserNum);
	UFUNCTION(BlueprintCallable, Category = "EOS", meta = (keywords = "Get User Login Status"))
	static EUserLoginStatus GetLoginStatus(int32 UserNum);
	UFUNCTION(BlueprintCallable, Category = "EOS", meta = (keywords = "Get Player Nickname"))
	static FString GetPlayerNickname(int32 UserNum);

	// Friends
	UFUNCTION(BlueprintCallable, Category = "EOS", meta = (keywords = "Get Player Friends"))
	static void GetPlayerFriends(int32 UserNum);

	// Stats And Achievements
	UFUNCTION(BlueprintCallable, Category = "EOS", meta = (keywords = "Retrieve Achievements"))
	bool QueryAchievements(FBPUniqueNetId* UniqueNetId);
};