// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingDoor.h"

#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"

#include "UObject/ConstructorHelpers.h"

// Sets default values
AMovingDoor::AMovingDoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

#pragma region Collision Component
    UBoxComponent* DoorBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision Component"));
    DoorBox->SetBoxExtent(FVector(10.f, 10.f, 10.f));
    DoorBox->SetCollisionProfileName("BlockAll");
    DoorBox->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
    SetRootComponent(DoorBox);
    RootComponent = DoorBox;

#pragma region Visual Component
    UStaticMeshComponent* DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Visual Component"));
    DoorMesh->SetupAttachment(RootComponent);

    DoorTimer = 10;
}

// Called when the game starts or when spawned
void AMovingDoor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMovingDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    if (DoorTimer >= 1)
    {
        FVector NewLocation = GetActorLocation();

        float RunningTime = GetGameTimeSinceCreation();

        float DeltaHeight = (FMath::Sin(RunningTime + DeltaTime) - FMath::Sin(RunningTime));

        //Scales Height by 20
        NewLocation.Y += DeltaHeight * 20.f;

        SetActorLocation(NewLocation);
    }
}

void AMovingDoor::AdvanceTimer()
{
    DoorTimer--;
}

