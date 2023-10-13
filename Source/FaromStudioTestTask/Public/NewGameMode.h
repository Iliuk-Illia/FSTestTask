// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "NewGameMode.generated.h"

/**
 * 
 */
UCLASS()
class FAROMSTUDIOTESTTASK_API ANewGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:

	void BeginPlay() override;
	
	UPROPERTY(BlueprintReadWrite)
	int Player1Score;
	
	UPROPERTY(BlueprintReadWrite)
	int Player2Score;
};
