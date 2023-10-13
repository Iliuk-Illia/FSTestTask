// Fill out your copyright notice in the Description page of Project Settings.


#include "NewPlayerController.h"

#include "Net/UnrealNetwork.h"

void ANewPlayerController::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME(ANewPlayerController, RightInputValue);
	DOREPLIFETIME(ANewPlayerController, PawnLocation);

}

void ANewPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	InputComponent->BindAxis(TEXT("MoveRight"), this, &ANewPlayerController::MoveRight_Server);
	InputComponent->BindAxis(TEXT("LookUp"), this, &ANewPlayerController::LookUp);
}


void ANewPlayerController::MoveRight_Server_Implementation(float Value)
{
	if(Value != 0.0f)
	{
		APawn* ControlledPawn = GetPawn();
		if (ControlledPawn)
		{
			FVector RightDirection = ControlledPawn->GetActorRightVector() * Speed;
			ControlledPawn->SetActorLocation(ControlledPawn->GetActorLocation() + RightDirection * Value * GetWorld()->GetDeltaSeconds());
			PawnLocation = ControlledPawn->GetActorLocation();
		}
		MoveRight_Client(Value);
	}
}

void ANewPlayerController::MoveRight_Client_Implementation(float Value)
{
	RightInputValue = Value;
}

void ANewPlayerController::LookUp(float Value)
{
	if(Value != 0.f)
	{
		AddPitchInput(Value * TurnRate * GetWorld()->GetDeltaSeconds());
	}
}

void ANewPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (PawnLocation.Y > 225)
	{
		APawn* ControlledPawn = GetPawn();
		if (ControlledPawn)
		{
			FVector location = ControlledPawn->GetActorLocation();
			location.Y=225;
			ControlledPawn->SetActorLocation(location);
		}
	}
	if (PawnLocation.Y < -225)
	{
		APawn* ControlledPawn = GetPawn();
		if (ControlledPawn)
		{
			FVector location = ControlledPawn->GetActorLocation();
			location.Y=-225;
			ControlledPawn->SetActorLocation(location);
		}
	}
}
