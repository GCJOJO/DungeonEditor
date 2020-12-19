// Fill out your copyright notice in the Description page of Project Settings.


#include "DiscordLibrary.h"
#include "Discord/discord.h"

discord::Core* core{};

bool UDiscordLibrary::InitDiscord(){
    auto result = discord::Core::Create(783767259713110046, DiscordCreateFlags_Default, &core);
    return true;
}

bool UDiscordLibrary::UpdateDiscord() {
    //::core->RunCallbacks();
    return true;
}


bool UDiscordLibrary::SetDiscordActivity(FString State, FString Details) 
{
    const char* CState = TCHAR_TO_ANSI(*State);
    const char* CDetails = TCHAR_TO_ANSI(*Details);

    discord::Activity activity{};
    activity.SetState(CState);
    activity.SetDetails(CDetails);
    core->ActivityManager().UpdateActivity(activity, [](discord::Result result) {});
    return true;
}