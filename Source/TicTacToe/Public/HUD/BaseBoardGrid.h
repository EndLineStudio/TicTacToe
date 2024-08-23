// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BaseBoardGrid.generated.h"

class UGridSlot;
class UGridPanel;
/**
 * 
 */
UCLASS()
class TICTACTOE_API UBaseBoardGrid : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(meta = (BindWidget))
	UGridPanel* BoardGrid;

	UPROPERTY()
	UGridSlot* GridSlots;

};
