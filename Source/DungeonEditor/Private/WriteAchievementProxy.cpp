// Copyright Epic Games, Inc. All Rights Reserved.

#include "WriteAchievementProxy.h"

#include "AchievementWriteCallbackProxy.h"
#include "BlueprintDataDefinitions.h"
#include "EngineGlobals.h"
#include "Engine/Engine.h"
#include "OnlineSubsystem.h"
#include "DungeonEditor/DungeonEditor.h"
#include "Interfaces/OnlineAchievementsInterface.h"

UWriteAchievementProxy::UWriteAchievementProxy(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, WorldContextObject(nullptr)
{
}

UWriteAchievementProxy* UWriteAchievementProxy::WriteAchievementProgress(UObject* WorldContextObject, int32 localPlayerID, FName AchievementName, float Progress, int32 UserTag)
{
	UWriteAchievementProxy* Proxy = NewObject<UWriteAchievementProxy>();

	Proxy->WriteObject = MakeShareable(new FOnlineAchievementsWrite);
	Proxy->WriteObject->SetFloatStat(AchievementName, Progress);
	Proxy->localPlayerID = localPlayerID;
	Proxy->AchievementName = AchievementName;
	Proxy->AchievementProgress = Progress;
	Proxy->UserTag = UserTag;
	Proxy->WorldContextObject = WorldContextObject;

	return Proxy;
}

void UWriteAchievementProxy::Activate()
{
	IOnlineSubsystem* OSS = IOnlineSubsystem::Get();

	FBPUniqueNetId PlayerID;
	
	if (OSS)
	{
		IOnlineAchievementsPtr Achievements = OSS->GetAchievementsInterface();
		if (Achievements.IsValid())
		{
			PlayerID.SetUniqueNetId(OSS->GetIdentityInterface()->GetUniquePlayerId(localPlayerID));
			FOnlineAchievementsWriteRef WriteObjectRef = WriteObject.ToSharedRef();
			FOnAchievementsWrittenDelegate WriteFinishedDelegate = FOnAchievementsWrittenDelegate::CreateUObject(this, &ThisClass::OnAchievementWritten);
			Achievements->WriteAchievements(*PlayerID.GetUniqueNetId(), WriteObjectRef, WriteFinishedDelegate);
			
			return;
		}
	}

	// Fail immediately
	OnFailure.Broadcast(AchievementName, AchievementProgress, UserTag);
	WriteObject.Reset();
}

void UWriteAchievementProxy::OnAchievementWritten(const FUniqueNetId& UserID, bool bSuccess)
{
	if (bSuccess)
	{
		DISPLAY_LOG("Wrote to achievement %s with a progress of %f", *AchievementName.ToString(), AchievementProgress);
		OnSuccess.Broadcast(AchievementName, AchievementProgress, UserTag);
	}
	else
	{
		OnFailure.Broadcast(AchievementName, AchievementProgress, UserTag);
	}

	WriteObject.Reset();
}

void UWriteAchievementProxy::BeginDestroy()
{
	WriteObject.Reset();

	Super::BeginDestroy();
}
