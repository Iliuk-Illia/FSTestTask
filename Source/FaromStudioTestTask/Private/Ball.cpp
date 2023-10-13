// Fill out your copyright notice in the Description page of Project Settings.


#include "Ball.h"
#include "PlayerPawn.h"
#include "Components/BoxComponent.h"
#include "Engine/StaticMeshActor.h"
#include "Kismet/KismetMathLibrary.h"
#include "Net/UnrealNetwork.h"

// Sets default values
ABall::ABall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(RootComponent);
	RootComponent = StaticMesh;

	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	Box->SetupAttachment(RootComponent);
	
}

// Called when the game starts or when spawned
void ABall::BeginPlay()
{
	Super::BeginPlay();

	Box->OnComponentBeginOverlap.AddDynamic(this,&ABall::OnOverlapBegin);
	
	SetRandomVelocity();
}

// Called every frame
void ABall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	FVector Direction = Velocity * Speed;
	SetActorLocation(GetActorLocation() + Direction * GetWorld()->GetDeltaSeconds());
	ActorLocation = GetActorLocation();
}

void ABall::SpawmActor()
{
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
	FVector Location = FVector(0,0,40);
	FRotator Rotator = FRotator();
	GetWorld()->SpawnActor<AActor>(ActorSpawnClass,Location, Rotator, SpawnParameters);
	SetRandomVelocity();
}

void ABall::SetRandomVelocity()
{
	if (UKismetMathLibrary::RandomBool())
	{
		Velocity.X = 1;
	}
	else
	{
		Velocity.X = -1;
	}
	if (UKismetMathLibrary::RandomBool())
	{
		Velocity.Y = 1;
	}
	else
	{
		Velocity.Y = -1;
	}
	Velocity.Z = 0;
}

void ABall::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int OtherBodyIndex, bool FromSweep, const FHitResult& SweepResult)
{
	if(Cast<APlayerPawn>(OtherActor))
	{
		Velocity.X=Velocity.X*-1;
		Speed*=1.2;
	}
	if(Cast<AStaticMeshActor>(OtherActor))
	{
		if (OtherComp->ComponentHasTag(FName("Goal")))
		{
			GetWorld()->DestroyActor(this);
			
			SpawmActor();
		}
		else
		{
			Velocity.Y=Velocity.Y*-1;
		}
	}
}

void ABall::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME(ABall, ActorLocation);
}
