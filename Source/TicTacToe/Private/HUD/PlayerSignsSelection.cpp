// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/PlayerSignsSelection.h"
#include "Components/Button.h"
#include "GameMode/BaseGameplayGameMode.h"

void UPlayerSignsSelection::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	SetObjectRef();
	BindingButtonEvent();
}


void UPlayerSignsSelection::SetObjectRef()
{
	if (GetWorld())
	{
		BaseGameMode = Cast<ABaseGameplayGameMode>(GetWorld()->GetAuthGameMode());
	}
}


void UPlayerSignsSelection::BindingButtonEvent()
{
	if (Cross && Circle)
	{
		Cross->OnClicked.AddDynamic(this, &UPlayerSignsSelection::SetCrossSign);

		Circle->OnClicked.AddDynamic(this, &UPlayerSignsSelection::SetCircleSign);
	}
}


void UPlayerSignsSelection::SetCrossSign()
{
	////Set Player Signs
	if (BaseGameMode)
		BaseGameMode->SetPlayerSigns(true);
	DeActiveThisWidget();
}

void UPlayerSignsSelection::SetCircleSign()
{
	//Set Player Signs
	if (BaseGameMode)
		BaseGameMode->SetPlayerSigns(false);
	DeActiveThisWidget();
}

void UPlayerSignsSelection::DeActiveThisWidget()
{
	this->SetVisibility(ESlateVisibility::Collapsed);
}