// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Enum/EnumTypes.h"
#include "IteamBox.generated.h"

/**
 *
 */
UCLASS()
class TICTACTOE_API UIteamBox : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetAIBoxState();


protected:
	//Function.
	virtual void NativeOnInitialized() override;

	//Variables.
	UPROPERTY(meta = (BindWidget))
	class UButton* IteamBox;

	UPROPERTY(meta = (BindWidget))
	class UOverlay* SignContener;
	
	class ABaseGameplayGameMode* BaseGameMode;


private:

	UFUNCTION()
	void OnClickIteamBtn();
	void SetBoxState();
	void ShowBoxSigns();
	void GetGameMode();

	//Variables.
	UPROPERTY(VisibleAnywhere)
	ESignsState BoxState = ESignsState::ECS_None;


public:
	FORCEINLINE TEnumAsByte<ESignsState> GetBoxState() { return BoxState; }

};
