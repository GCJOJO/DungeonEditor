#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include <SimpleUGC/Public/UGCRegistry.h>
#include "OnlineSubsystem.h"
#include "Interfaces/OnlineIdentityInterface.h"
#include "Interfaces/OnlineFriendsInterface.h"
#include "DungeonEditor/DungeonEditor.h"
#include "DungeonCustomGameInstance.generated.h"

/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FFriendsListUpdatedDelegate);

USTRUCT(BlueprintType)
struct FFriendStruct
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite)
	FString DisplayName;
	UPROPERTY(BlueprintReadWrite)
	FString RealName;
	UPROPERTY(BlueprintReadWrite)
	FString UniqueNetId;
	//UPROPERTY(BlueprintReadWrite)
	//FOnlineUserPresence* Presence;

	/* ------------------------------------------------------------------------------------------------------------------------
	 * Presence :
	 *	FUniqueNetIdPtr SessionId;
	 *	uint32 bIsOnline:1;
	 * 	uint32 bIsPlaying:1;
	 *	uint32 bIsPlayingThisGame:1;
	 *	uint32 bIsJoinable:1;
	 *	uint32 bHasVoiceSupport:1;
	 *	FDateTime LastOnline;
	 *	FOnlineUserPresenceStatus Status;
	 *	------------------------------------------------------------------------------------------------------------------------
	 */ 
	
	UPROPERTY(BlueprintReadWrite)
	FString InviteStatus;

	/*FFriendStruct();
	
	FFriendStruct(FString _DisplayName, FString _RealName,FString _UniqueNetId/*, FOnlineUserPresence* _Presence*//*, FString _InviteStatus)
	{
		DisplayName = _DisplayName;
		RealName = _RealName;
		UniqueNetId = _UniqueNetId;
		//Presence = _Presence;
		InviteStatus = _InviteStatus;
	}*/
};

UCLASS()
class DUNGEONEDITOR_API UDungeonCustomGameInstance : public UGameInstance
{
	GENERATED_BODY()
	public:
		virtual void Init() override;
	
		TArray<TSharedRef<FOnlineFriend>> FriendsList;
	
		void UpdateFriendsList(TArray<TSharedRef<FOnlineFriend>> _friendsList)
		{
			FriendsList = _friendsList;
			OnFriendsListUpdatedDelegate.Broadcast();
			DISPLAY_LOG("Friends List Updated")
		}

		UFUNCTION(BlueprintPure, Category = "EOS", meta = (keywords = "Get Friends List"))
		TArray<FFriendStruct> GetFriendsList();
	
	
		// The Registry that holds information about UGC and assigned class overrides
		UPROPERTY(BlueprintReadOnly, Category = "SimpleUGC")
		UUGCRegistry* UGCRegistry;

		UPROPERTY(BlueprintAssignable, Category = "Online", meta = (keywords = "On Friends List Updated"))
		FFriendsListUpdatedDelegate OnFriendsListUpdatedDelegate;
};
