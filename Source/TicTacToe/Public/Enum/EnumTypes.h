
#pragma once

UENUM(BlueprintType)
enum class ESignsState : uint8
{
	ECS_None UMETA(DisplayName = "None"),
	ECS_Cross UMETA(DisplayName = "Cross"),
	ECS_Circle UMETA(DisplayName = "Circle")
};

UENUM(BlueprintType)
enum class ETurnState : uint8
{
	ECS_None UMETA(DisplayName = "None"),
	ECS_Player1 UMETA(DisplayName = "Player1"),
	ECS_Player2 UMETA(DisplayName = "Player2"),
	ECS_AI UMETA(DisplayName = "AI")
};