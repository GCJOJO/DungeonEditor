#include "DungeonCustomGameInstance.h"

void UDungeonCustomGameInstance::Init()
{
	// Instnatiate the registry and find mod packages
	UGCRegistry = NewObject<UUGCRegistry>(this);
	UGCRegistry->FindUGCPackages();
	UE_LOG(LogActor, Warning, TEXT("Initialized Custom Game Instance"));
	Super::Init();
}

UDungeonCustomGameInstance::UDungeonCustomGameInstance(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

TArray<FFriendStruct> UDungeonCustomGameInstance::GetFriendsList()
{
	TArray<FFriendStruct> FriendsArray;
	for (auto Friend : FriendsList)
	{
		FString DisplayName = Friend->GetDisplayName();
		FString RealName = Friend->GetRealName();
		FString UniqueNetId = Friend->GetUserId()->ToString();
		//FOnlineUserPresence Presence = Friend->GetPresence();
		FString InviteStatus = ToString(Friend->GetInviteStatus());
		//FFriendStruct NewFriend = FFriendStruct(DisplayName, RealName, UniqueNetId, InviteStatus);
		//FriendsArray.Add(NewFriend);
	}
	return FriendsArray;
}

