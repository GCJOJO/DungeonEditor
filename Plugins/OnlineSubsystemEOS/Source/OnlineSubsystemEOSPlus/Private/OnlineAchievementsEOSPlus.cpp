// Copyright Epic Games, Inc. All Rights Reserved.

#include "OnlineAchievementsEOSPlus.h"
#include "OnlineSubsystem.h"
#include "OnlineSubsystemEOSPlus.h"
#include "EOSSettings.h"

FOnAchievementsWrittenDelegate Ignored;

FOnlineAchievementsEOSPlus::FOnlineAchievementsEOSPlus(FOnlineSubsystemEOSPlus* InSubsystem)
	: EOSPlus(InSubsystem)
{
	BaseAchievementsInterface = EOSPlus->BaseOSS->GetAchievementsInterface();
	check(BaseAchievementsInterface.IsValid());
	EosAchievementsInterface = EOSPlus->EosOSS->GetAchievementsInterface();
	check(EosAchievementsInterface.IsValid());

	BaseAchievementsInterface->AddOnAchievementUnlockedDelegate_Handle(FOnAchievementUnlockedDelegate::CreateRaw(this, &FOnlineAchievementsEOSPlus::OnAchievementUnlocked));
}

FOnlineAchievementsEOSPlus::~FOnlineAchievementsEOSPlus()
{
	BaseAchievementsInterface->ClearOnAchievementUnlockedDelegates(this);
}

void FOnlineAchievementsEOSPlus::OnAchievementUnlocked(const FUniqueNetId& PlayerId, const FString& AchievementId)
{
	TriggerOnAchievementUnlockedDelegates(PlayerId, AchievementId);
}

TSharedPtr<FUniqueNetIdEOSPlus> FOnlineAchievementsEOSPlus::GetNetIdPlus(const FString& SourceId)
{
	return EOSPlus->UserInterfacePtr->GetNetIdPlus(SourceId);
}

void FOnlineAchievementsEOSPlus::WriteAchievements(const FUniqueNetId& PlayerId, FOnlineAchievementsWriteRef& WriteObject, const FOnAchievementsWrittenDelegate& Delegate)
{
	TSharedPtr<FUniqueNetIdEOSPlus> NetIdPlus = GetNetIdPlus(PlayerId.ToString());
	if (!NetIdPlus.IsValid())
	{
		UE_LOG_ONLINE(Warning, TEXT("FOnlineAchievementsEOSPlus::WriteAchievements() failed due to unknown user (%s)"), *PlayerId.ToString());
		return;
	}

	if (NetIdPlus->GetBaseNetId().IsValid())
	{
		BaseAchievementsInterface->WriteAchievements(*NetIdPlus->GetBaseNetId(), WriteObject, Delegate);
	}
	if (GetDefault<UEOSSettings>()->bMirrorAchievementsToEOS)
	{
		if (NetIdPlus->GetEOSNetId().IsValid())
		{
			// Mirror the achievement data to EOS
			EosAchievementsInterface->WriteAchievements(*NetIdPlus->GetEOSNetId(), WriteObject, Ignored);
		}
	}
}

void FOnlineAchievementsEOSPlus::QueryAchievements(const FUniqueNetId& PlayerId, const FOnQueryAchievementsCompleteDelegate& Delegate)
{
	TSharedPtr<FUniqueNetIdEOSPlus> NetIdPlus = GetNetIdPlus(PlayerId.ToString());
	if (!NetIdPlus.IsValid() || !NetIdPlus->GetBaseNetId().IsValid())
	{
		UE_LOG_ONLINE(Warning, TEXT("FOnlineAchievementsEOSPlus::QueryAchievements() failed due to unknown user (%s)"), *PlayerId.ToString());
		return;
	}

	BaseAchievementsInterface->QueryAchievements(*NetIdPlus->GetBaseNetId(), Delegate);
}

void FOnlineAchievementsEOSPlus::QueryAchievementDescriptions(const FUniqueNetId& PlayerId, const FOnQueryAchievementsCompleteDelegate& Delegate)
{
	TSharedPtr<FUniqueNetIdEOSPlus> NetIdPlus = GetNetIdPlus(PlayerId.ToString());
	if (!NetIdPlus.IsValid() || !NetIdPlus->GetBaseNetId().IsValid())
	{
		UE_LOG_ONLINE(Warning, TEXT("FOnlineAchievementsEOSPlus::QueryAchievementDescriptions() failed due to unknown user (%s)"), *PlayerId.ToString());
		return;
	}

	BaseAchievementsInterface->QueryAchievementDescriptions(*NetIdPlus->GetBaseNetId(), Delegate);
}

EOnlineCachedResult::Type FOnlineAchievementsEOSPlus::GetCachedAchievement(const FUniqueNetId& PlayerId, const FString& AchievementId, FOnlineAchievement& OutAchievement)
{
	TSharedPtr<FUniqueNetIdEOSPlus> NetIdPlus = GetNetIdPlus(PlayerId.ToString());
	if (!NetIdPlus.IsValid() || !NetIdPlus->GetBaseNetId().IsValid())
	{
		UE_LOG_ONLINE(Warning, TEXT("FOnlineAchievementsEOSPlus::GetCachedAchievement() failed due to unknown user (%s)"), *PlayerId.ToString());
		return EOnlineCachedResult::NotFound;
	}

	return BaseAchievementsInterface->GetCachedAchievement(*NetIdPlus->GetBaseNetId(), AchievementId, OutAchievement);
}

EOnlineCachedResult::Type FOnlineAchievementsEOSPlus::GetCachedAchievements(const FUniqueNetId& PlayerId, TArray<FOnlineAchievement>& OutAchievements)
{
	TSharedPtr<FUniqueNetIdEOSPlus> NetIdPlus = GetNetIdPlus(PlayerId.ToString());
	if (!NetIdPlus.IsValid() || !NetIdPlus->GetBaseNetId().IsValid())
	{
		UE_LOG_ONLINE(Warning, TEXT("FOnlineAchievementsEOSPlus::GetCachedAchievements() failed due to unknown user (%s)"), *PlayerId.ToString());
		return EOnlineCachedResult::NotFound;
	}

	return BaseAchievementsInterface->GetCachedAchievements(*NetIdPlus->GetBaseNetId(), OutAchievements);
}

EOnlineCachedResult::Type FOnlineAchievementsEOSPlus::GetCachedAchievementDescription(const FString& AchievementId, FOnlineAchievementDesc& OutAchievementDesc)
{
	return BaseAchievementsInterface->GetCachedAchievementDescription(AchievementId, OutAchievementDesc);
}

#if !UE_BUILD_SHIPPING
bool FOnlineAchievementsEOSPlus::ResetAchievements(const FUniqueNetId& PlayerId)
{
	return BaseAchievementsInterface->ResetAchievements(PlayerId);
}
#endif
