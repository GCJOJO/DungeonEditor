// Fill out your copyright notice in the Description page of Project Settings.


#include "DungeonEditorLibrary.h"

void UDungeonEditorLibrary::ChangeLocalization(ELocalizationCulture culture)
{
	switch(culture)
	{
	case ELocalizationCulture::EN :
		FInternationalization::Get().SetCurrentCulture(TEXT("en"));
		break;
	case ELocalizationCulture::FR :
		FInternationalization::Get().SetCurrentCulture(TEXT("fr-FR"));
		break;
	}
}
