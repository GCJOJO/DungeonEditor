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

	// UI
	UFUNCTION(BlueprintCallable, Category = "EOS", meta = (keywords = "Show Friends UI"))
	static void ShowFriendsUI(int32 LocalUserNum);
	
	UFUNCTION(BlueprintCallable, Category = "EOS", meta = (keywords = "Show Invite UI"))
	static void ShowInviteUI(int32 LocalUserNum);
	
	// Stats And Achievements
	UFUNCTION(BlueprintCallable, Category = "EOS", meta = (keywords = "Retrieve Achievements"))
	static bool QueryAchievements(int32 LocalUserNum);
	UFUNCTION(BlueprintCallable, Category= "EOS", meta = (keywords = "Retrieve Achievements Definition"))
	static bool QueryAchievementDefinitions(int32 LocalUserNum);

	UFUNCTION(BlueprintCallable, Category= "EOS", meta = (keywords = "Get Cached Achievement Progression"))
	static void GetCachedAchievementProgress(int32 LocalUserNum, FName AchievementID, /*out*/ bool& bFoundID, /*out*/ float& Progress);

	UFUNCTION(BlueprintCallable, Category= "EOS", meta = (keywords = "Get Cached Achievement Definition"))
	static void GetCachedAchievementDescription(FName AchievementID, /*out*/ bool& bFoundID, /*out*/ FText& Title, /*out*/ FText& LockedDescription, /*out*/ FText& UnlockedDescription, /*out*/ bool& bHidden);

	static void OnGetAllFriendsComplete(int32 LocalUserNum, bool bWasSuccessful, const FString& ListName, const FString& ErrorStr);

	
};