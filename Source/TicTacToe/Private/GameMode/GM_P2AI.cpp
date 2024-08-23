// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/GM_P2AI.h"
#include "HUD/IteamBox.h"


void AGM_P2AI::BeginPlay()
{
	Super::BeginPlay();

	const int32 RandomTurn = FMath::RandRange(0, 1);
	UE_LOG(LogTemp, Warning, TEXT("Check Value :%d "), RandomTurn);
	if (RandomTurn == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Inside Player trun"));
		SetPlayerTrun(ETurnState::ECS_Player1);
	}
	else{
		UE_LOG(LogTemp, Warning, TEXT("Inside AI trun"));
		SetPlayerTrun(ETurnState::ECS_AI);
	}

	CheckAI(true);
}

void AGM_P2AI::GameStart()
{
	Super::GameStart();
	if (GetTurnState() == ETurnState::ECS_AI)
		PlayAIMove();
}

void AGM_P2AI::CheckGameState()
{
	Super::CheckGameState();
	if (!CheckGameWin() && !CheckGameDraw())
	{
		TurnSwitch();
	}
}

void AGM_P2AI::TurnSwitch()
{
	switch (GetTurnState())
	{
	case ETurnState::ECS_None:
		break;
	case ETurnState::ECS_Player1:
		SetPlayerTrun(ETurnState::ECS_AI);
		//Set Function For AI.
		if (GetWorld())
		{
			GetWorld()->GetTimerManager().SetTimer(TimerHandler, this, &AGM_P2AI::PlayAIMove, AIMoveTimer, false);
		}
		break;
	case ETurnState::ECS_Player2:
		break;
	case ETurnState::ECS_AI:
		SetPlayerTrun(ETurnState::ECS_Player1);
		break;
	default:
		break;
	}
}

void AGM_P2AI::PlayAIMove()
{
	if (GetIsGameOver()) return;


	int32 FirstMoveCount = 0;

	for (int32 i = 0; i < GridXSize; i++)
	{
		for (int32 j = 0; j < GridYSize; j++)
		{
			if (NumberOfBoxs[i][j]->GetBoxState() == ESignsState::ECS_None)
				FirstMoveCount += 1;
		}
	}

	if (FirstMoveCount > 7)
	{
		CheckFirstMove();
		UE_LOG(LogTemp, Warning, TEXT("AI trun"));
	}
	else
	{
		if (!CheckAIWinMove()) //Check AI can Win or Not.
		{
			if (!CheckPlayerWin()) //Check Player is wining then play stop player win move.
			{
				AIRandomMove();
			}
		}

	}

}

void AGM_P2AI::CheckFirstMove()
{
	if (NumberOfBoxs[1][1]->GetBoxState() == ESignsState::ECS_None)
		NumberOfBoxs[1][1]->SetAIBoxState();
	else
	{
		const int32 RandomMove = FMath::RandRange(0, 3);
		int32 XMove = 0;
		int32 YMove = 0;

		if (RandomMove == 0)
		{
			XMove = 0;
			YMove = 0;
		}
		else if (RandomMove == 1)
		{
			XMove = 0;
			YMove = 2;
		}
		else if (RandomMove == 2)
		{
			XMove = 2;
			YMove = 0;
		}
		else if (RandomMove == 3)
		{
			XMove = 2;
			YMove = 2;
		}

		if (NumberOfBoxs[XMove][YMove]->GetBoxState() == ESignsState::ECS_None)
			NumberOfBoxs[XMove][YMove]->SetAIBoxState();
	}
}

bool AGM_P2AI::CheckAIWinMove()
{
	if (CheckWinMoveSigns(GetAIState()))
		return true;

	return false;
}

bool AGM_P2AI::CheckPlayerWin()
{
	if (CheckWinMoveSigns(GetPlayer1State()))
		return true;

	return false;
}

bool AGM_P2AI::CheckWinMoveSigns(ESignsState State)
{
	for (int32 i = 0; i < GridXSize; i++)
	{
		//Check Rows.
		if (NumberOfBoxs[i][0]->GetBoxState() == ESignsState::ECS_None &&
			NumberOfBoxs[i][1]->GetBoxState() == State &&
			NumberOfBoxs[i][2]->GetBoxState() == State)
		{
			NumberOfBoxs[i][0]->SetAIBoxState();
			return true;
		}
		if (NumberOfBoxs[i][0]->GetBoxState() == State &&
			NumberOfBoxs[i][1]->GetBoxState() == ESignsState::ECS_None &&
			NumberOfBoxs[i][2]->GetBoxState() == State)
		{
			NumberOfBoxs[i][1]->SetAIBoxState();
			return true;
		}
		if (NumberOfBoxs[i][0]->GetBoxState() == State &&
			NumberOfBoxs[i][1]->GetBoxState() == State &&
			NumberOfBoxs[i][2]->GetBoxState() == ESignsState::ECS_None)
		{
			NumberOfBoxs[i][2]->SetAIBoxState();
			return true;
		}

		//Check Colums.
		if (NumberOfBoxs[0][i]->GetBoxState() == ESignsState::ECS_None &&
			NumberOfBoxs[1][i]->GetBoxState() == State &&
			NumberOfBoxs[2][i]->GetBoxState() == State)
		{
			NumberOfBoxs[0][i]->SetAIBoxState();
			return true;
		}
		if (NumberOfBoxs[0][i]->GetBoxState() == State &&
			NumberOfBoxs[1][i]->GetBoxState() == ESignsState::ECS_None &&
			NumberOfBoxs[2][i]->GetBoxState() == State)
		{
			NumberOfBoxs[1][i]->SetAIBoxState();
			return true;
		}
		if (NumberOfBoxs[0][i]->GetBoxState() == State &&
			NumberOfBoxs[1][i]->GetBoxState() == State &&
			NumberOfBoxs[2][i]->GetBoxState() == ESignsState::ECS_None)
		{
			NumberOfBoxs[2][i]->SetAIBoxState();
			return true;
		}
	}

	//Check Diagonals.
	if (NumberOfBoxs[0][0]->GetBoxState() == ESignsState::ECS_None &&
		NumberOfBoxs[1][1]->GetBoxState() == State &&
		NumberOfBoxs[2][2]->GetBoxState() == State)
	{
		NumberOfBoxs[0][0]->SetAIBoxState();
		return true;
	}
	if (NumberOfBoxs[0][0]->GetBoxState() == State &&
		NumberOfBoxs[1][1]->GetBoxState() == ESignsState::ECS_None &&
		NumberOfBoxs[2][2]->GetBoxState() == State)
	{
		NumberOfBoxs[1][1]->SetAIBoxState();
		return true;
	}
	if (NumberOfBoxs[0][0]->GetBoxState() == State &&
		NumberOfBoxs[1][1]->GetBoxState() == State &&
		NumberOfBoxs[2][2]->GetBoxState() == ESignsState::ECS_None)
	{
		NumberOfBoxs[2][2]->SetAIBoxState();
		return true;
	}
	if (NumberOfBoxs[0][2]->GetBoxState() == ESignsState::ECS_None &&
		NumberOfBoxs[1][1]->GetBoxState() == State &&
		NumberOfBoxs[2][0]->GetBoxState() == State)
	{
		NumberOfBoxs[0][2]->SetAIBoxState();
		return true;
	}
	if (NumberOfBoxs[0][2]->GetBoxState() == State &&
		NumberOfBoxs[1][1]->GetBoxState() == ESignsState::ECS_None &&
		NumberOfBoxs[2][0]->GetBoxState() == State)
	{
		NumberOfBoxs[1][1]->SetAIBoxState();
		return true;
	}
	if (NumberOfBoxs[0][2]->GetBoxState() == State &&
		NumberOfBoxs[1][1]->GetBoxState() == State &&
		NumberOfBoxs[2][0]->GetBoxState() == ESignsState::ECS_None)
	{
		NumberOfBoxs[2][0]->SetAIBoxState();
		return true;
	}

	return false;
}

void AGM_P2AI::AIRandomMove()
{
	for (int32 i = 0; i < GridXSize; i++)
	{
		if (NumberOfBoxs[0][i]->GetBoxState() == GetAIState() &&
			NumberOfBoxs[1][i]->GetBoxState() == ESignsState::ECS_None &&
			NumberOfBoxs[2][i]->GetBoxState() == ESignsState::ECS_None)
		{
			NumberOfBoxs[2][i]->SetAIBoxState();
			return;
		}
		if (NumberOfBoxs[0][i]->GetBoxState() == ESignsState::ECS_None &&
			NumberOfBoxs[1][i]->GetBoxState() == ESignsState::ECS_None &&
			NumberOfBoxs[2][i]->GetBoxState() == GetAIState())
		{
			NumberOfBoxs[0][i]->SetAIBoxState();
			return;
		}

	}

	for (int32 i = 0; i < GridXSize; i++)
	{
		if (NumberOfBoxs[i][0]->GetBoxState() == GetPlayer1State() &&
			NumberOfBoxs[i][1]->GetBoxState() == ESignsState::ECS_None)
		{
			NumberOfBoxs[i][1]->SetAIBoxState();
			return;
		}
		if (NumberOfBoxs[i][1]->GetBoxState() == ESignsState::ECS_None &&
			NumberOfBoxs[i][2]->GetBoxState() == GetPlayer1State())
		{
			NumberOfBoxs[i][1]->SetAIBoxState();
			return;
		}
		if (NumberOfBoxs[i][0]->GetBoxState() == ESignsState::ECS_None &&
			NumberOfBoxs[i][1]->GetBoxState() == GetPlayer1State())
		{
			NumberOfBoxs[i][0]->SetAIBoxState();
			return;
		}
		if (NumberOfBoxs[i][2]->GetBoxState() == ESignsState::ECS_None &&
			NumberOfBoxs[i][1]->GetBoxState() == GetPlayer1State())
		{
			NumberOfBoxs[i][2]->SetAIBoxState();
			return;
		}
		if (NumberOfBoxs[0][i]->GetBoxState() == ESignsState::ECS_None &&
			NumberOfBoxs[1][i]->GetBoxState() == GetPlayer1State())
		{
			NumberOfBoxs[0][i]->SetAIBoxState();
			return;
		}
		if (NumberOfBoxs[2][i]->GetBoxState() == ESignsState::ECS_None &&
			NumberOfBoxs[1][i]->GetBoxState() == GetPlayer1State())
		{
			NumberOfBoxs[2][i]->SetAIBoxState();
			return;
		}
	}

	for (int32 i = 0; i < GridXSize; i++)
	{
		for (int32 j = 0; j < GridYSize; j++)
		{
			if (NumberOfBoxs[i][j]->GetBoxState() == ESignsState::ECS_None)
			{
				NumberOfBoxs[i][j]->SetAIBoxState();
				return;
			}
		}
	}

	const int32 RandomX = FMath::RandRange(0, 2);
	const int32 RandomY = FMath::RandRange(0, 2);
	if (NumberOfBoxs[RandomX][RandomY]->GetBoxState() == ESignsState::ECS_None)
	{
		NumberOfBoxs[RandomX][RandomY]->SetAIBoxState();
		return;
	}

}
