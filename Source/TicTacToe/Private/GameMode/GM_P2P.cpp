// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/GM_P2P.h"



void AGM_P2P::BeginPlay()
{
	Super::BeginPlay();
	SetPlayerTrun(ETurnState::ECS_Player1);
	CheckAI(false);
}

void AGM_P2P::CheckGameState()
{
	Super::CheckGameState();
	if (!CheckGameWin() && !CheckGameDraw())
	{
		TurnSwitch();
	}
}

void AGM_P2P::TurnSwitch()
{
	switch (GetTurnState())
	{
	case ETurnState::ECS_None:
		break;
	case ETurnState::ECS_Player1:
			SetPlayerTrun(ETurnState::ECS_Player2);
		break;
	case ETurnState::ECS_Player2:
		SetPlayerTrun(ETurnState::ECS_Player1);
		break;
	case ETurnState::ECS_AI:
		break;
	default:
		break;
	}
}
