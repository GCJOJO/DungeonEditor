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
#include "Interfaces/OnlineStatsInterface.h"
#include "Kismet/GameplayStatics.h"
#include <DungeonEditor/Public/DungeonCustomGameInstance.h>
#include "DungeonEditor/DungeonEditor.h"

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
		DISPLAY_LOG("Couldn't login !")
		return false;
	}
	DISPLAY_LOG("Couldn't login !")
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
			DISPLAY_LOG("Logged Out !")
			return Identity->Logout(UserNum);
		}
		DISPLAY_LOG("Couldn't logout !")
		return false;
	}
	DISPLAY_LOG("Couldn't logout !")
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
			DISPLAY_LOG("Auto Logged In !")
			return Identity->AutoLogin(UserNum);
		}
		DISPLAY_LOG("Couldn't auto login !")
		return false;
	}
	DISPLAY_LOG("Couldn't auto login !")
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
	
	IOnlineSubsystem* OSS = IOnlineSubsystem::Get();
	if (OSS)
	{
		IOnlineFriendsPtr Friends = OSS->GetFriendsInterface();
		Friends->ReadFriendsList(LocalUserNum, "default");
		

		Friends->OnFriendsChangeDelegates->AddLambda([&] 
			{
				DISPLAY_LOG("Finished Retrieving Friends List");
				/*TArray<TSharedRef<FOnlineFriend>> OutFriends;
				Friends->GetFriendsList(LocalUserNum, "default", OutFriends);
				if (GEngine->GetWorld() != nullptr && GEngine->GetWorld()->GetGameInstance() != nullptr)
				{
					UDungeonCustomGameInstance* gameInstance = Cast<UDungeonCustomGameInstance>(GEngine->GetWorld()->GetGameInstance());
					gameInstance->UpdateFriendsList(OutFriends);
				}*/
			});
		
	}
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