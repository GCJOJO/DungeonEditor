// By G.C*JOJO


#include "EOSLibrary.h"
#include <complex>
/*#include <OnlineSubsystemEOS.h>
#include "UserManagerEOS.h"
#include "Interfaces/OnlineFriendsInterface.h"
#include "Interfaces/OnlinePresenceInterface.h"
#include "Interfaces\OnlineGroupsInterface.h"
#include "Interfaces\OnlineIdentityInterface.h"
#include "Source\Public\OnlineSubsystem.h"
*/
#include "OnlineSubsystem.h"
#include "Interfaces/OnlineIdentityInterface.h"
#include "Interfaces/OnlineFriendsInterface.h"

#define DISPLAY_LOG(fmt, ...) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT(fmt), __VA_ARGS__));

bool UEOSLibrary::Login(int32 UserNum, ELoginType loginType)
{
	FOnlineAccountCredentials Credentials;
	
	switch (loginType)
	{
		case Web:

			Credentials.Id = TEXT("");
			Credentials.Token = TEXT("");
			Credentials.Type = TEXT("accountportal");

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
			Identity->OnLoginCompleteDelegates->Clear();
			Identity->OnLoginCompleteDelegates->AddLambda([&](int32 i, bool successful, const FUniqueNetId& userID, const FString& error)
			{
					DISPLAY_LOG("Logged In !")
			});//Don't forget the ";" in the end of your parenthesis!

			return Identity->Login(UserNum, Credentials);
		}
		return false;
	}
	return false;
}

bool UEOSLibrary::Logout(int32 UserNum)
{
	IOnlineSubsystem* OSS = IOnlineSubsystem::Get();
	if (OSS)
	{
		IOnlineIdentityPtr Identity = OSS->GetIdentityInterface();
		if (Identity.IsValid())
		{
			return Identity->Logout(UserNum);
		}
		return false;
	}
	return false;
}

bool UEOSLibrary::TryAutoLogin(int32 UserNum)
{
	IOnlineSubsystem* OSS = IOnlineSubsystem::Get();
	if(OSS)
	{
		IOnlineIdentityPtr Identity = OSS->GetIdentityInterface();
		if(Identity.IsValid())
		{
			return Identity->AutoLogin(UserNum);
		}
		return false;
	}
	return false;
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
	
	return "NULL";
}

void UEOSLibrary::GetPlayerFriends(int32 LocalUserNum)
{
//	TArray< TSharedRef<FOnlineFriend> > friendList;
//	IOnlineSubsystem* OSS = IOnlineSubsystem::Get();
//	if (OSS)
//	{
		/*IOnlineFriendsPtr Friends = OSS->GetFriendsInterface();
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
		}*/
//	}
}

bool UEOSLibrary::CreateLobby(int32 localUserNum, FText GroupName, FText GroupDesc, FText GroupMotto,
	bool bIsInviteOnly, FString GroupLanguage)
{
	/*IOnlineSubsystem* OSS = IOnlineSubsystem::Get();
	if(OSS)
	{
		IOnlineGroupsPtr Groups = OSS->GetGroupsInterface();
		FGroupDisplayInfo groupInfo;
		groupInfo.Name = GroupName;
		groupInfo.Description = GroupDesc;
		groupInfo.Language = GroupLanguage;
		groupInfo.Motto = GroupMotto;
		groupInfo.InviteOnly = bIsInviteOnly;
		//Groups->CreateGroup();
		return false;
	}*/
	return false;
}

EUserLoginStatus UEOSLibrary::GetLoginStatus(int32 localUserNum)
{
	IOnlineSubsystem* OSS = IOnlineSubsystem::Get();
	if (OSS)
	{
		IOnlineIdentityPtr Identity = OSS->GetIdentityInterface();
		if (Identity.IsValid())
		{
			EUserLoginStatus LoginStatus;
			switch(Identity->GetLoginStatus(localUserNum))
			{
				default : LoginStatus = EUserLoginStatus::NotLoggedIn;
					break;
				case ELoginStatus::LoggedIn : LoginStatus = EUserLoginStatus::LoggedIn;
					break;
				case ELoginStatus::NotLoggedIn : LoginStatus = EUserLoginStatus::NotLoggedIn;
					break;
				case ELoginStatus::UsingLocalProfile : LoginStatus = EUserLoginStatus::UsingLocalProfile;
					break;
			}
			return LoginStatus;
		}
		return EUserLoginStatus::NotLoggedIn;
	}
	return EUserLoginStatus::NotLoggedIn;
}