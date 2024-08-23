// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/BaseGameplayGameMode.h"
#include "Blueprint/UserWidget.h"
#include "Components/GridPanel.h"
#include "Components/GridSlot.h"
#include "HUD/BaseBoardGrid.h"
#include "HUD/PlayerSignsSelection.h"
#include "HUD/IteamBox.h"
#include "HUD/GameOver.h"


void ABaseGameplayGameMode::BeginPlay()
{
	Super::BeginPlay();
	CreateBoxGridWidget();
	CreatePlayerSignSelectWidget();
}

void ABaseGameplayGameMode::CheckAI(bool IsAI)
{
	IsAIMode = IsAI;
}

void ABaseGameplayGameMode::CreateBoxGridWidget()
{
	if (BoxGird_ref)
	{
		BoxGird = CreateWidget<UBaseBoardGrid>(GetWorld(), BoxGird_ref);
		if (BoxGird)
		{
			BoxGird->AddToViewport();
			AddChildToGridWidget();
		}
	}
}

void ABaseGameplayGameMode::CreatePlayerSignSelectWidget()
{
	if (PlayerSignSelection_Ref)
	{
		UPlayerSignsSelection* PlayerSignSelection = CreateWidget<UPlayerSignsSelection>(GetWorld(), PlayerSignSelection_Ref);

		if (PlayerSignSelection)
			PlayerSignSelection->AddToViewport();
	}
}

void ABaseGameplayGameMode::AddChildToGridWidget()
{
	if (IteamBox_ref)
	{
		for (int32 i = 0; i < GridXSize; i++)
		{
			TArray<UIteamBox*> LocalStates;

			for (int32 j = 0; j < GridYSize; j++)
			{
				UIteamBox* IteamBox = CreateWidget<UIteamBox>(GetWorld(), IteamBox_ref);

				if (IteamBox && BoxGird->BoardGrid)
				{
					//Add Number of Iteam to Local Array.
					LocalStates.Add(IteamBox);

					BoxGird->GridSlots = BoxGird->BoardGrid->AddChildToGrid(IteamBox);
					BoxGird->GridSlots->SetRow(i);
					BoxGird->GridSlots->SetColumn(j);
				}
			}
			NumberOfBoxs.Add(LocalStates);
		}
	}
}

void ABaseGameplayGameMode::CreateGameOverWidget(FString massage)
{
	GameOverWidget = CreateWidget<UGameOver>(GetWorld(), GameOver_ref);
	if (GameOverWidget) {
		GameOverWidget->SetGameOverMessage(massage);
		if (GetWorld())
		{
			GetWorld()->GetTimerManager().SetTimer(GameOverHandler, this, &ABaseGameplayGameMode::ShowGameOverWidget, GameOverPopTime, false);
		}
	}
}

void ABaseGameplayGameMode::ShowGameOverWidget()
{
	if (GameOverWidget)
		GameOverWidget->AddToViewport();
}

void ABaseGameplayGameMode::SetPlayerSigns(bool IsCross)
{
	if (IsCross)
		SetSignsState(ESignsState::ECS_Cross);
	else
		SetSignsState(ESignsState::ECS_Circle);
}

void ABaseGameplayGameMode::SetSignsState(ESignsState SignsState)
{
	switch (SignsState)
	{
	case ESignsState::ECS_None:
		break;
	case ESignsState::ECS_Cross:
		Player1Sign = ESignsState::ECS_Cross;
		Player2Sign = ESignsState::ECS_Circle;
		AISign = ESignsState::ECS_Circle;
		break;
	case ESignsState::ECS_Circle:
		Player1Sign = ESignsState::ECS_Circle;
		Player2Sign = ESignsState::ECS_Cross;
		AISign = ESignsState::ECS_Cross;
		break;
	default:
		break;
	}
	GameStart();
}

void ABaseGameplayGameMode::GameStart()
{
}

void ABaseGameplayGameMode::SetPlayerTrun(ETurnState PlayerTrun)
{
	switch (PlayerTrun)
	{
	case ETurnState::ECS_None:
		break;

	case ETurnState::ECS_Player1:
		TrunState = ETurnState::ECS_Player1;
		break;

	case ETurnState::ECS_Player2:
		TrunState = ETurnState::ECS_Player2;
		break;

	case ETurnState::ECS_AI:
		TrunState = ETurnState::ECS_AI;
		break;

	default:
		break;
	}
}

void ABaseGameplayGameMode::CheckGameState()
{
	if (CheckGameWin())
	{
		IsGameOver = true;
		switch (GetTurnState())
		{
		case ETurnState::ECS_None:
			break;
		case ETurnState::ECS_Player1:
			CreateGameOverWidget(FString::Printf(TEXT("Player 1 Wins The Game.")));
			break;
		case ETurnState::ECS_Player2:
			CreateGameOverWidget(FString::Printf(TEXT("Player 2 Wins The Game.")));
			break;
		case ETurnState::ECS_AI:
			CreateGameOverWidget(FString::Printf(TEXT("AI Player Wins The Game.")));
			break;
		default:
			break;
		}
	}
	else if (CheckGameDraw())
	{
		//Draw The Game.
		IsGameOver = true;
		CreateGameOverWidget(FString::Printf(TEXT("Game Draw None are Win.")));
	}

}

bool ABaseGameplayGameMode::CheckGameWin()
{
	for (int32 i = 0; i < GridXSize; i++)
	{
		if (CheckColums(i) || CheckRow(i))
		{
			return true;
		}
	}

	if (CheckDiagonals())
		return true;

	return false;
}

bool ABaseGameplayGameMode::CheckGameDraw()
{
	for (int32 i = 0; i < GridXSize; i++)
	{
		for (int32 j = 0; j < GridYSize; j++)
		{
			if (NumberOfBoxs[i][j]->GetBoxState() == ESignsState::ECS_None)
				return false;
		}
	}
	return true;
}

bool ABaseGameplayGameMode::CheckColums(int32 Index)
{
	if (NumberOfBoxs[0][Index]->GetBoxState() == NumberOfBoxs[1][Index]->GetBoxState() && NumberOfBoxs[0][Index]->GetBoxState() == NumberOfBoxs[2][Index]->GetBoxState() && NumberOfBoxs[0][Index]->GetBoxState() != ESignsState::ECS_None)
	{
		return true;
	}

	return false;
}

bool ABaseGameplayGameMode::CheckRow(int32 Index)
{
	if (NumberOfBoxs[Index][0]->GetBoxState() == NumberOfBoxs[Index][1]->GetBoxState() && NumberOfBoxs[Index][0]->GetBoxState() == NumberOfBoxs[Index][2]->GetBoxState() && NumberOfBoxs[Index][0]->GetBoxState() != ESignsState::ECS_None)
	{
		return true;
	}

	return false;
}

bool ABaseGameplayGameMode::CheckDiagonals()
{
	if (NumberOfBoxs[0][0]->GetBoxState() == NumberOfBoxs[1][1]->GetBoxState() && NumberOfBoxs[0][0]->GetBoxState() == NumberOfBoxs[2][2]->GetBoxState() && NumberOfBoxs[0][0]->GetBoxState() != ESignsState::ECS_None)
	{
		return true;
	}
	if (NumberOfBoxs[0][2]->GetBoxState() == NumberOfBoxs[1][1]->GetBoxState() && NumberOfBoxs[0][2]->GetBoxState() == NumberOfBoxs[2][0]->GetBoxState() && NumberOfBoxs[0][2]->GetBoxState() != ESignsState::ECS_None)
	{
		return true;
	}
	return false;
}

