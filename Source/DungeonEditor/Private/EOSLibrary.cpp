// By G.C*JOJO
#include "EOSLibrary.h"

#include "EOSVoiceChatFactory.h"
#include "OnlineSubsystem.h"
#include "Interfaces/OnlineIdentityInterface.h"
#include "Interfaces/OnlineFriendsInterface.h"
#include "DungeonEditor/Public/DungeonCustomGameInstance.h"
#include "OnlineSessionSettings.h"
#include "AdvancedSessions/Classes/AdvancedSessionsLibrary.h"
#include "DungeonEditor/DungeonEditor.h"

bool UEOSLibrary::Login(int32 UserNum, ELoginType loginType, FString DevIP, FString DevToken )
{
	FOnlineAccountCredentials Credentials;

	// Init the Credentials
	Credentials.Id = TEXT("");
	Credentials.Token = TEXT("");
	Credentials.Type = TEXT("accountportal");
	
	switch (loginType)
	{
	default:
		DISPLAY_LOG("Login Method : Account Portal (Default)");
		break;
		
		case Web:

			Credentials.Id = TEXT("");
			Credentials.Token = TEXT("");
			Credentials.Type = TEXT("accountportal");
		DISPLAY_LOG("Login Method : Account Portal");
		
			break;
		case Code:

			Credentials.Id = TEXT("");
			Credentials.Token = TEXT(""); // Add Token from the Epic Games Launcher, so probably shouldn't use the 'Code' login type
			Credentials.Type = TEXT("exchangecode");
		DISPLAY_LOG("Login Method : Exchange Code");

			break;
		case Dev:
			Credentials.Id = DevIP;
			Credentials.Token = DevToken;
			Credentials.Type = TEXT("Developer");
		DISPLAY_LOG("Login Method : Dev");
	}

	DISPLAY_LOG("Login for User Num : %i", UserNum);
	
	IOnlineSubsystem* OSS = IOnlineSubsystem::Get();
	if (OSS)
	{
		IOnlineIdentityPtr Identity = OSS->GetIdentityInterface();
		if (Identity.IsValid())
		{
			Identity->OnLoginCompleteDelegates->Clear();
			Identity->OnLoginCompleteDelegates->AddLambda([&](int32 LocalUserNum, bool successful, const FUniqueNetId& userID, const FString& error)
			{
				DISPLAY_LOG("Logged In ? %i", successful);
				if(successful)
				{
					// DISPLAY_LOG("Created Unique Player ID : %s", *Identity->CreateUniquePlayerId(FGuid::NewGuid().ToString())->ToString());
					// DISPLAY_LOG("Player (%i) with Unique EOS ID : %s", LocalUserNum, *userID.ToString());
					// DISPLAY_LOG("Player (%i) has a Global ID of : %s", LocalUserNum, *Identity->GetUniquePlayerId(LocalUserNum)->ToString());
				}
			});
			Identity->OnLoginChangedDelegates.Clear();
			Identity->OnLoginChangedDelegates.AddLambda([&](int32 _UserNum)
			{
				
				DISPLAY_LOG("User %i changed logged status now : %d!", _UserNum, Identity->GetLoginStatus(_UserNum));
				if(Identity->GetLoginStatus(_UserNum) == ELoginStatus::LoggedIn)
				{
					// DISPLAY_LOG("Created Unique Player ID : %s", *Identity->CreateUniquePlayerId(FGuid::NewGuid().ToString())->ToString());
				}
			});
			
			DISPLAY_LOG("Loging In...");
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

	DISPLAY_LOG("Logout for User Num : %i", UserNum);
	
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

	DISPLAY_LOG("Auto Login for User Num : %i", UserNum);
	
	IOnlineSubsystem* OSS = IOnlineSubsystem::Get();
	if(OSS)
	{
		IOnlineIdentityPtr Identity = OSS->GetIdentityInterface();
		if(Identity.IsValid())
		{
			DISPLAY_LOG("Trying to Auto Login...")
			return Identity->AutoLogin(UserNum);
		}
		DISPLAY_LOG("Couldn't auto login !")
		return false;
	}
	DISPLAY_LOG("Couldn't auto login !")
	return false;
}

FString UEOSLibrary::GetPlayerNickname(int32 UserNum)
{
	FString playerName = TEXT("Null");

	DISPLAY_LOG("Getting Player Nickname for User (%i)...", UserNum);
	
	IOnlineSubsystem* OSS = IOnlineSubsystem::Get();
	if (OSS)
	{
		IOnlineIdentityPtr Identity = OSS->GetIdentityInterface();
		if (Identity.IsValid())
		{
			playerName = Identity->GetPlayerNickname(UserNum);
			DISPLAY_LOG("Got Player Nickname for User (%i) : %s", UserNum, *playerName);
			return playerName;
		}
		return playerName;
	}
	return playerName;
}

void UEOSLibrary::GetPlayerFriends(int32 UserNum)
{	
	IOnlineSubsystem* OSS = IOnlineSubsystem::Get();
	if (OSS)
	{
		IOnlineFriendsPtr Friends = OSS->GetFriendsInterface();
		Friends->ReadFriendsList(UserNum, EFriendsLists::ToString((EFriendsLists::Default)));
		

		Friends->OnFriendsChangeDelegates->Clear();
		Friends->OnFriendsChangeDelegates->AddLambda([&] 
			{
				DISPLAY_LOG("Finished Retrieving Friends List");
				TArray<TSharedRef<FOnlineFriend>> OutFriends;
				Friends->GetFriendsList(UserNum, EFriendsLists::ToString((EFriendsLists::Default)), OutFriends);
			});
		
	}
}

EUserLoginStatus UEOSLibrary::GetLoginStatus(int32 UserNum)
{
	DISPLAY_LOG("Getting Status for User Num : %i", UserNum);
	
	IOnlineSubsystem* OSS = IOnlineSubsystem::Get();
	if (OSS)
	{
		IOnlineIdentityPtr Identity = OSS->GetIdentityInterface();
		if (Identity.IsValid())
		{
			EUserLoginStatus LoginStatus = EUserLoginStatus::NotLoggedIn;
			switch(Identity->GetLoginStatus(UserNum))
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
			DISPLAY_LOG("Login Status for User %i is %d", UserNum, Identity->GetLoginStatus(UserNum));
			return LoginStatus;
		}
		DISPLAY_LOG("Identity Interface not Valid !");
		return EUserLoginStatus::NotLoggedIn;
	}
	DISPLAY_LOG("OSS not Valid !");
	return EUserLoginStatus::NotLoggedIn;
}

bool UEOSLibrary::QueryAchievements(int32 LocalUserNum)
{
	IOnlineSubsystem* OSS = IOnlineSubsystem::Get();
	if (OSS)
	{
		IOnlineAchievementsPtr Achievements = OSS->GetAchievementsInterface();
		if(Achievements.IsValid())
		{
			/*FOnQueryAchievementsCompleteDelegate QueryComplete;
			QueryComplete.CreateLambda([&](FUniqueNetId& PlayerID, const bool bSuccessful)
			{
				DISPLAY_LOG("Finished Retrieving Achievements");
				if(bSuccessful) { DISPLAY_LOG("Retrieving Achievements Successful !"); }
				else { DISPLAY_LOG("Retrieving Achievements not Successful..."); }
			});
			
			FBPUniqueNetId PlayerID;
			UAdvancedSessionsLibrary::GetUniqueNetIDFromLocalID(LocalUserNum, PlayerID);
			
			Achievements->QueryAchievements(*PlayerID.GetUniqueNetId(), QueryComplete);		
			return true;*/
			return false;
		}
		return false;
	}
	return false;
}

void GetTitleFile(FString FileName)
{
	IOnlineSubsystem* OSS = IOnlineSubsystem::Get();
	if (OSS)
	{
		IOnlineTitleFilePtr TitleFiles = OSS->GetTitleFileInterface();
		if(TitleFiles.IsValid())
		{
			// TitleFiles->EnumerateFiles();
			// TitleFiles->ReadFile(FileName);
		}
	}
}