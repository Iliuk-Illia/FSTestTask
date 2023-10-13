// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "Ball.generated.h"

UCLASS()
class FAROMSTUDIOTESTTASK_API ABall : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABall();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadOnly, Category = Replicate)
	FVector ActorLocation;
	
	UPROPERTY(EditDefaultsOnly)
	float Speed = 250.f;
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AActor> ActorSpawnClass;
	
	UPROPERTY(EditDefaultsOnly)
	UBoxComponent* Box;
	
	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* StaticMesh;
	
	UPROPERTY(VisibleAnywhere)
	FVector Velocity;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp,
						AActor* OtherActor,
						UPrimitiveComponent* OtherComp,
						int OtherBodyIndex,
						bool FromSweep,
						const FHitResult& SweepResult);
	
	UFUNCTION()
	void SetRandomVelocity();
	
	UFUNCTION()
	void SpawmActor();
};
