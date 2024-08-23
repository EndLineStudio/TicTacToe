// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/GameOver.h"
#include "Components/TextBlock.h"


void UGameOver::SetGameOverMessage(FString message)
{
	const FText Text = FText::FromString(message);
	Message->SetText(Text);
}
