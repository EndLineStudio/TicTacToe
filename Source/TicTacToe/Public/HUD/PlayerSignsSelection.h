// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerSignsSelection.generated.h"

class UButton;
/**
 * 
 */
UCLASS()
class TICTACTOE_API UPlayerSignsSelection : public UUserWidget
{
	GENERATED_BODY()

protected:

	//Function.
	virtual void NativeOnInitialized() override;

	//Variables.
	UPROPERTY(meta = (BindWidget))
	UButton* Cross;
	
	UPROPERTY(meta = (BindWidget))
	UButton* Circle;

	class ABaseGameplayGameMode* BaseGameMode;

private:

	void SetObjectRef();
	void BindingButtonEvent();
	void DeActiveThisWidget();

	UFUNCTION()
	void SetCrossSign();
	UFUNCTION()
	void SetCircleSign();
	
};
