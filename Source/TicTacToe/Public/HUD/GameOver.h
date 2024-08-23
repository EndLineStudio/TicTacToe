// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameOver.generated.h"

/**
 * 
 */
UCLASS()
class TICTACTOE_API UGameOver : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetGameOverMessage(FString message);

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Message;
	
};
