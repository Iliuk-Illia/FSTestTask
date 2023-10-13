// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "NewPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class FAROMSTUDIOTESTTASK_API ANewPlayerController : public APlayerController
{
	GENERATED_BODY()
	void Tick(float DeltaSeconds) override;
public:
	UPROPERTY(EditDefaultsOnly)
	float Speed = 500.f;

	UPROPERTY(EditDefaultsOnly)
	float TurnRate = 50.f;
	
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadOnly, Category = Replicate)
	float RightInputValue;

	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadOnly, Category = Replicate)
	FVector PawnLocation;
	
	virtual void SetupInputComponent() override;

	void LookUp(float Value);

	UFUNCTION(Server, Reliable)
	void MoveRight_Server(float Value);
	
	UFUNCTION(Client, Reliable)
	void MoveRight_Client(float Value);
};
