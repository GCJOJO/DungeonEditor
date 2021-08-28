// By G.C*JOJO


#include "EOSLibrary.h"

/*#include <complex>
#include "F:/UnrealEngine/Engine/Plugins/Online/OnlineSubsystem/Source/Public/Interfaces/OnlineFriendsInterface.h"
#include "Interfaces/OnlinePresenceInterface.h"
#include "Source\Public\OnlineSubsystem.h"
#include "Source\Public\Interfaces\OnlineGroupsInterface.h"
#include "Source\Public\Interfaces\OnlineIdentityInterface.h"

void UEOSLibrary::Login(int32 UserNum, ELoginType loginType)
{
	FOnlineAccountCredentials Credentials;
	
	switch (loginType) {
	case Web:

		Credentials.Id = TEXT("");
		Credentials.Token = TEXT("");
		Credentials.Type = TEXT("web");

		break;
	case Code:

		Credentials.Id = TEXT("");
		Credentials.Token = TEXT("");
		Credentials.Type = TEXT("exchangecode");

		break;
	default:
		break;
	}
	
	

	IOnlineSubsystem* OSS = IOnlineSubsystem::Get();
	if (OSS)
	{
		IOnlineIdentityPtr Identity = OSS->GetIdentityInterface();
		if (Identity.IsValid())
		{
			Identity->Login(UserNum, Credentials);
		}
	}
}

void UEOSLibrary::Logout(int32 UserNum)
{
	IOnlineSubsystem* OSS = IOnlineSubsystem::Get();
	if (OSS)
	{
		IOnlineIdentityPtr Identity = OSS->GetIdentityInterface();
		if (Identity.IsValid())
		{
			Identity->Logout(UserNum);
		}
	}
}

FString UEOSLibrary::GetPlayerNickname(int32 LocalUserNum)
{
	FString playerName = TEXT("Null");

	IOnlineSubsystem* OSS = IOnlineSubsystem::Get();
	if (OSS)
	{
		IOnlineIdentityPtr Identity = OSS->GetIdentityInterface();
		if (Identity.IsValid())
		{
			playerName = Identity->GetPlayerNickname(0);
			return playerName;
		}
		return playerName;
	}
	return playerName;
}

void UEOSLibrary::GetPlayerFriends(int32 LocalUserNum)
{
	TArray< TSharedRef<FOnlineFriend> > friendList ;
	IOnlineSubsystem* OSS = IOnlineSubsystem::Get();
	if (OSS)
	{
		IOnlineFriendsPtr Friends = OSS->GetFriendsInterface();
		if (Friends.IsValid())
		{
			Friends->GetFriendsList(LocalUserNum, "default", friendList);
			for (auto OnlineFriend : friendList)
			{
				FString friendName = OnlineFriend->GetDisplayName();
				const FOnlineUserPresence friendPresence = OnlineFriend->GetPresence();
				UE_LOG(LogTemp, Warning, TEXT("Friend %s is "), *friendName, &friendPresence);
			}
			if(friendList.Num() == 0)
			{
				UE_LOG(LogTemp, Warning, TEXT("Friends List not found !"));
			}
		}
	}
}
*/