// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "Enum/EnumTypes.h"
#include "BaseGameplayGameMode.generated.h"

class UBaseBoardGrid;
class UPlayerSignsSelection;
class UIteamBox;
class UGameOver;
/**
 *
 */
UCLASS()
class TICTACTOE_API ABaseGameplayGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	//Functions.
	void SetPlayerSigns(bool IsCross);
	virtual void CheckGameState();
	virtual void GameStart();

protected:
	//Functions.
	virtual void BeginPlay() override;
	void CheckAI(bool IsAI);
	bool GetIsGameOver() { return IsGameOver; }
	void SetSignsState(ESignsState SignsState);
	void SetPlayerTrun(ETurnState PlayerTrun);

	bool CheckGameWin();
	bool CheckGameDraw();

	//Variables.
	UPROPERTY()
	UBaseBoardGrid* BoxGird; // Instance of widget

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	int32 GridXSize = 3;

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	int32 GridYSize = 3;

	TArray<TArray<UIteamBox*>> NumberOfBoxs;


private:
	//Functions.
	void CreateBoxGridWidget();
	void CreatePlayerSignSelectWidget();
	void CreateGameOverWidget(FString massage);
	void ShowGameOverWidget();
	void AddChildToGridWidget();

	//Conditions.
	bool CheckColums(int32 Index);
	bool CheckRow(int32 Index);
	bool CheckDiagonals();

	//Variables.
	bool IsAIMode = false; //Check
	bool IsGameOver = false; //Check

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UBaseBoardGrid> BoxGird_ref; // This is the class ref of widget

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UPlayerSignsSelection> PlayerSignSelection_Ref;

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UIteamBox> IteamBox_ref; // This is the class ref of widget

	UPROPERTY(VisibleAnywhere)
	ETurnState TrunState = ETurnState::ECS_None;

	UPROPERTY(VisibleAnywhere)
	ESignsState Player1Sign = ESignsState::ECS_None;

	UPROPERTY(VisibleAnywhere)
	ESignsState Player2Sign = ESignsState::ECS_None;

	UPROPERTY(VisibleAnywhere)
	ESignsState AISign = ESignsState::ECS_None;

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UGameOver> GameOver_ref; // This is the class ref of widget

	UGameOver* GameOverWidget;

	//Variables.
	FTimerHandle GameOverHandler;

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	float GameOverPopTime = 1.f;

public:

	//Getter Functions.
	FORCEINLINE ETurnState GetTurnState() { return TrunState; }
	FORCEINLINE ESignsState GetPlayer1State() { return Player1Sign; }
	FORCEINLINE ESignsState GetPlayer2State() { return Player2Sign; }
	FORCEINLINE ESignsState GetAIState() { return AISign; }
	FORCEINLINE bool IsAICheck() { return IsAIMode; }

};
