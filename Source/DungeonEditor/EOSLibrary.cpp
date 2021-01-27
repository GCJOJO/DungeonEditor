

#include "EOSLibrary.h"
#include <OnlineSubsystem.h>
#include <Interfaces\OnlineIdentityInterface.h>

void UEOSLibrary::Login(int32 userNum)
{
	FOnlineAccountCredentials Credentials;
	Credentials.Id = TEXT("");
	Credentials.Token = TEXT("");
	Credentials.Type = TEXT("web");

	IOnlineSubsystem* OSS = IOnlineSubsystem::Get();
	if (OSS)
	{
		IOnlineIdentityPtr Identity = OSS->GetIdentityInterface();
		if (Identity.IsValid())
		{
			Identity->Login(userNum, Credentials);
		}
	}
}

void UEOSLibrary::Logout(int32 userNum)
{
	IOnlineSubsystem* OSS = IOnlineSubsystem::Get();
	if (OSS)
	{
		IOnlineIdentityPtr Identity = OSS->GetIdentityInterface();
		if (Identity.IsValid())
		{
			Identity->Logout(userNum);
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