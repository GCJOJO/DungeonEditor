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
#include "Interfaces/OnlineSessionInterface.h"
#include "Interfaces/OnlineTitleFileInterface.h"
#include "Kismet/GameplayStatics.h"
#include <DungeonEditor/Public/DungeonCustomGameInstance.h>

#include "OnlineSessionSettings.h"
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
		

		Friends->OnFriendsChangeDelegates->Clear();
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


bool UEOSLibrary::CreateLobby(int32 localUserNum, FName SessionName, bool bIsLAN, bool bIsPresence, int32 MaxNumPlayers)
{
	IOnlineSubsystem* OSS = IOnlineSubsystem::Get();
	if(OSS)
	{
		IOnlineSessionPtr Sessions = OSS->GetSessionInterface();

		if(Sessions.IsValid())
		{
			//FOnlineSessionSettings* NewSettings = FOnlineSessionSettings(4, 4, true, false, false, false, true, true, true, true, true, false, true, false, 0);

			TSharedPtr<class FOnlineSessionSettings> SessionSettings = MakeShareable(new FOnlineSessionSettings());
			
			SessionSettings->bIsLANMatch = bIsLAN;
			SessionSettings->bUsesPresence = bIsPresence;
            SessionSettings->NumPublicConnections = MaxNumPlayers;
            SessionSettings->NumPrivateConnections = 0;
            SessionSettings->bAllowInvites = true;
            SessionSettings->bAllowJoinInProgress = false;
            SessionSettings->bShouldAdvertise = true;
            SessionSettings->bAllowJoinViaPresence = true;
            SessionSettings->bAllowJoinViaPresenceFriendsOnly = true;

			if (GEngine->GetWorld() != nullptr && GEngine->GetWorld()->GetGameInstance() != nullptr)
			{
				UDungeonCustomGameInstance* gameInstance = Cast<UDungeonCustomGameInstance>(GEngine->GetWorld()->GetGameInstance());
				//gameInstance->BindOnCreateSessionCompleteDelegateHandle(Sessions);
				Sessions->OnCreateSessionCompleteDelegates.AddLambda([&](FName Name, bool bIsSuccessful)
				{
					DISPLAY_LOG("Tried to create session");
					if(bIsSuccessful){ DISPLAY_LOG("Created Session Succesfully"); }
					else { DISPLAY_LOG("Tried to create session but couldn't"); }
					gameInstance->HasCreatedSessionEvent(Name, bIsSuccessful);
				});
			}
			DISPLAY_LOG("Creating Session...");
			return Sessions->CreateSession(localUserNum, SessionName, *SessionSettings);
			//Sessions->CreateSession(localUserNum, SessionName, SessionSettings);
		}
		DISPLAY_LOG("Sessions Interface not valid");

		return false;
	}
	DISPLAY_LOG("Online Subsystem not valid");
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


/*void GetTitleFile(FName FileName)
{
	IOnlineSubsystem* OSS = IOnlineSubsystem::Get();
	if (OSS)
	{
		IOnlineTitleFilePtr TitleFiles = OSS->GetTitleFileInterface();
		if(TitleFiles.IsValid())
		{
			TitleFiles->EnumerateFiles();
		}
	}
}*/