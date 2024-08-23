// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameMode/BaseGameplayGameMode.h"
#include "GM_P2P.generated.h"

/**
 *
 */
UCLASS()
class TICTACTOE_API AGM_P2P : public ABaseGameplayGameMode
{
	GENERATED_BODY()

protected:
	virtual void CheckGameState() override;
	virtual void BeginPlay() override;
	void TurnSwitch();

};
