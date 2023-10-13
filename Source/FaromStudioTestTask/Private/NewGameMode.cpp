// Fill out your copyright notice in the Description page of Project Settings.


#include "NewGameMode.h"

void ANewGameMode::BeginPlay()
{
	if (ENetMode::NM_ListenServer == GetNetMode())
	{
		if (GetNumPlayers()<2)
		{
			UE_LOG(LogTemp, Warning, TEXT("NumPlayers must be > 1"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Net Mode must be a ListenServer"));
	}
}