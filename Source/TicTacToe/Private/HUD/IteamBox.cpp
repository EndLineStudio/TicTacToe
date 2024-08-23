// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/IteamBox.h"
#include "Components/Button.h"
#include "Components/Overlay.h"
#include "GameMode/BaseGameplayGameMode.h"


void UIteamBox::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (IteamBox)
		IteamBox->OnClicked.AddDynamic(this, &UIteamBox::OnClickIteamBtn);

	GetGameMode();

}

void UIteamBox::GetGameMode()
{
	if (GetWorld())
		BaseGameMode = Cast<ABaseGameplayGameMode>(GetWorld()->GetAuthGameMode());
}

void UIteamBox::OnClickIteamBtn()
{
	if (BaseGameMode && BaseGameMode->IsAICheck())
		if (BaseGameMode->GetTurnState() == ETurnState::ECS_AI)
			return;

	SetBoxState();
}

void UIteamBox::SetAIBoxState()
{
	SetBoxState();
}

void UIteamBox::SetBoxState()
{
	if (BoxState != ESignsState::ECS_None) return;

	if (BaseGameMode)
	{
		ETurnState CheckPlayerTurn = BaseGameMode->GetTurnState();

		switch (CheckPlayerTurn)
		{
		case ETurnState::ECS_None:
			BoxState = ESignsState::ECS_None;
			ShowBoxSigns();
			break;
		case ETurnState::ECS_Player1:
			BoxState = BaseGameMode->GetPlayer1State();
			ShowBoxSigns();
			break;
		case ETurnState::ECS_Player2:
			BoxState = BaseGameMode->GetPlayer2State();
			ShowBoxSigns();
			break;
		case ETurnState::ECS_AI:
			BoxState = BaseGameMode->GetAIState();
			ShowBoxSigns();
			break;
		default:
			break;
		}

		BaseGameMode->CheckGameState();
	}
}

void UIteamBox::ShowBoxSigns()
{
	if (SignContener)
	{
		TArray<UWidget*> Childs = SignContener->GetAllChildren();

		switch (BoxState)
		{
		case ESignsState::ECS_None:
			for (UWidget* Child : Childs)
			{
				Child->SetVisibility(ESlateVisibility::Collapsed);
			}
			break;
		case ESignsState::ECS_Cross:
			Childs[1]->SetVisibility(ESlateVisibility::Visible);
			break;
		case ESignsState::ECS_Circle:
			Childs[0]->SetVisibility(ESlateVisibility::Visible);
			break;
		default:
			break;
		}
	}
}

