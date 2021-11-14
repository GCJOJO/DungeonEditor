// By G.C*JOJO


#include "EOSLibrary.h"


#include <complex>
/*#include "F:/UnrealEngine/Engine/Plugins/Online/OnlineSubsystem/Source/Public/Interfaces/OnlineFriendsInterface.h"
#include "Interfaces/OnlinePresenceInterface.h"
#include "D:/UnrealEngine/UE_4.27/UE_4.27/Engine/Plugins/Online/OnlineSubsystemEOS/Source/OnlineSubsystemEOS/Public/OnlineSubsystemEOS.h"
#include "D:/UnrealEngine/UE_4.27/UE_4.27/Engine/Plugins/Online/OnlineSubsystemEOS/Source/OnlineSubsystemEOS/Private/UserManagerEOS.h"
#include "Source\Public\OnlineSubsystem.h"
#include "Source\Public\Interfaces\OnlineGroupsInterface.h"
#include "Source\Public\Interfaces\OnlineIdentityInterface.h"*/

bool UEOSLibrary::Login(int32 UserNum, ELoginType loginType)
{
	/*FOnlineAccountCredentials Credentials;
	
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
			return Identity->Login(UserNum, Credentials);
		}
		return false;
	}*/
	return false;
}

bool UEOSLibrary::Logout(int32 UserNum)
{
	/*IOnlineSubsystem* OSS = IOnlineSubsystem::Get();
	if (OSS)
	{
		IOnlineIdentityPtr Identity = OSS->GetIdentityInterface();
		if (Identity.IsValid())
		{
			return Identity->Logout(UserNum);
		}
		return false;
	}*/
	return false;
}

bool UEOSLibrary::TryAutoLogin(int32 UserNum)
{
	/*IOnlineSubsystem* OSS = IOnlineSubsystem::Get();
	if(OSS)
	{
		IOnlineIdentityPtr Identity = OSS->GetIdentityInterface();
		if(Identity.IsValid())
		{
			return Identity->AutoLogin(UserNum);
		}
		return false;
	}*/
	return false;
}

FString UEOSLibrary::GetPlayerNickname(int32 LocalUserNum)
{
	/*FString playerName = TEXT("Null");

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
	*/
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
	//}
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
	/*IOnlineSubsystem* OSS = IOnlineSubsystem::Get();
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
	}*/
	return EUserLoginStatus::NotLoggedIn;
}