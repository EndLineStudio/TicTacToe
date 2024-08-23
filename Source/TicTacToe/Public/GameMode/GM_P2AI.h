// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameMode/BaseGameplayGameMode.h"
#include "GM_P2AI.generated.h"

/**
 *
 */
UCLASS()
class TICTACTOE_API AGM_P2AI : public ABaseGameplayGameMode
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	virtual void CheckGameState() override;
	virtual void GameStart() override;
	void TurnSwitch();

private:
	void PlayAIMove();
	void CheckFirstMove();
	bool CheckAIWinMove();
	bool CheckPlayerWin();
	bool CheckWinMoveSigns(ESignsState State);
	void AIRandomMove();


	//Variables.
	FTimerHandle TimerHandler;

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	float AIMoveTimer = 1.f;



};
