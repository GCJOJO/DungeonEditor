// By G.C*JOJO
#include "EOSLibrary.h"

#include "OnlineSubsystem.h"
#include "Interfaces/OnlineIdentityInterface.h"
#include "Interfaces/OnlineFriendsInterface.h"
#include "Kismet/GameplayStatics.h"
#include "DungeonEditor/Public/DungeonCustomGameInstance.h"
#include "OnlineSessionSettings.h"
#include "DungeonEditor/DungeonEditor.h"

bool UEOSLibrary::Login(APlayerController* PlayerController, ELoginType loginType)
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
			Credentials.Token = TEXT(""); // Add Token from the Epic Games Launcher, so probably shouldn't use the 'Code' login type
			Credentials.Type = TEXT("exchangecode");

			break;
		default:
			Credentials.Id = TEXT("");
			Credentials.Token = TEXT("");
			Credentials.Type = TEXT("accountportal");
			break;
	}

	if(!PlayerController)
	{
		DISPLAY_LOG("Player Controller Not Valid !");
		return false;
	}
	
	ULocalPlayer* LocalPlayer = Cast<ULocalPlayer>(PlayerController->Player);
	int32 UserNum = LocalPlayer->GetControllerId();

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
					DISPLAY_LOG("Logged In !")
			});
			Identity->OnLoginChangedDelegates.Clear();
			Identity->OnLoginChangedDelegates.AddLambda([&](int32 LocalUserNum)
			{
				
				DISPLAY_LOG("User %i changed logged status now : %d!", LocalUserNum, Identity->GetLoginStatus(LocalUserNum));
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

bool UEOSLibrary::Logout(APlayerController* PlayerController)
{
	if(!PlayerController)
	{
		DISPLAY_LOG("Player Controller Not Valid !");
		return false;
	}
	
	ULocalPlayer* LocalPlayer = Cast<ULocalPlayer>(PlayerController->Player);
	int32 UserNum = LocalPlayer->GetControllerId();

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

bool UEOSLibrary::TryAutoLogin(APlayerController* PlayerController)
{
	if(!PlayerController)
	{
		DISPLAY_LOG("Player Controller Not Valid !");
		return false;
	}
	
	ULocalPlayer* LocalPlayer = Cast<ULocalPlayer>(PlayerController->Player);
	int32 UserNum = LocalPlayer->GetControllerId();

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

FString UEOSLibrary::GetPlayerNickname(APlayerController* PlayerController)
{
	FString playerName = TEXT("Null");

	if(!PlayerController)
	{
		DISPLAY_LOG("Player Controller Not Valid !");
		return playerName;
	}
	
	ULocalPlayer* LocalPlayer = Cast<ULocalPlayer>(PlayerController->Player);
	int32 UserNum = LocalPlayer->GetControllerId();

	DISPLAY_LOG("Getting Player Nickname for User Num : %i", UserNum);
	
	IOnlineSubsystem* OSS = IOnlineSubsystem::Get();
	if (OSS)
	{
		IOnlineIdentityPtr Identity = OSS->GetIdentityInterface();
		if (Identity.IsValid())
		{
			playerName = Identity->GetPlayerNickname(UserNum);
			return playerName;
		}
		return playerName;
	}
	return playerName;
}

void UEOSLibrary::GetPlayerFriends(APlayerController* PlayerController)
{
	if(!PlayerController)
	{
		DISPLAY_LOG("Player Controller Not Valid !");
		return;
	}
	
	ULocalPlayer* LocalPlayer = Cast<ULocalPlayer>(PlayerController->Player);
	int32 LocalUserNum = LocalPlayer->GetControllerId();
	
	IOnlineSubsystem* OSS = IOnlineSubsystem::Get();
	if (OSS)
	{
		IOnlineFriendsPtr Friends = OSS->GetFriendsInterface();
		Friends->ReadFriendsList(LocalUserNum, EFriendsLists::ToString((EFriendsLists::Default)));
		

		Friends->OnFriendsChangeDelegates->Clear();
		Friends->OnFriendsChangeDelegates->AddLambda([&] 
			{
				DISPLAY_LOG("Finished Retrieving Friends List");
				TArray<TSharedRef<FOnlineFriend>> OutFriends;
				Friends->GetFriendsList(LocalUserNum, EFriendsLists::ToString((EFriendsLists::Default)), OutFriends);
			});
		
	}
}

EUserLoginStatus UEOSLibrary::GetLoginStatus(APlayerController* PlayerController)
{
	if(!PlayerController)
	{
		DISPLAY_LOG("Player Controller Not Valid !");
		return EUserLoginStatus::NotLoggedIn;
	}
	
	ULocalPlayer* LocalPlayer = Cast<ULocalPlayer>(PlayerController->Player);
	int32 UserNum = LocalPlayer->GetControllerId();

	DISPLAY_LOG("Getting Status for User Num : %i", UserNum);
	
	IOnlineSubsystem* OSS = IOnlineSubsystem::Get();
	if (OSS)
	{
		IOnlineIdentityPtr Identity = OSS->GetIdentityInterface();
		if (Identity.IsValid())
		{
			EUserLoginStatus LoginStatus;
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
			return LoginStatus;
		}
		DISPLAY_LOG("Identity Interface not Valid !");
		return EUserLoginStatus::NotLoggedIn;
	}
	DISPLAY_LOG("OSS not Valid !");
	return EUserLoginStatus::NotLoggedIn;
}

bool UEOSLibrary::RetrieveAchievements(APlayerController *PlayerController)
{

	if (!PlayerController)
	{
		DISPLAY_LOG("Invalid Player Controller !");
		return false;
	}
	FUniqueNetIdPtr PlayerUniqueNetID = nullptr;
	
	if (APlayerState* PlayerState = (PlayerController != NULL) ? PlayerController->PlayerState : NULL)
	{
		PlayerUniqueNetID = PlayerState->GetUniqueId().GetUniqueNetId();
	}
	
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
				
			});*/
			// Achievements->QueryAchievements(*PlayerUniqueNetID, QueryComplete);
			Achievements->QueryAchievements(*PlayerUniqueNetID);
			return true;
		}
		return false;
	}
	return false;
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