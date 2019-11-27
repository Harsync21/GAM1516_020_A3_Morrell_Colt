// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthPickUp.h"
#include "PlayerPawn.h"

#include "Classes/PaperSpriteComponent.h"
#include "Components/BoxComponent.h"

// Sets default values
AHealthPickUp::AHealthPickUp()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

#pragma region Collision Component
    UBoxComponent* HealthBox = CreateDefaultSubobject<UBoxComponent>(TEXT("RootComponent"));
    HealthBox->SetWorldScale3D(FVector(1.0));
    HealthBox->SetBoxExtent(FVector(10.f, 10.f, 10.f));
    SetRootComponent(RootComponent);
    HealthBox->SetCollisionProfileName("OnOverlay");
   

	HealthKit = CreateDefaultSubobject<UPaperSpriteComponent>("Health Kit Visual");
	HealthKit->SetCollisionProfileName("OnOverlay");
	HealthKit->SetupAttachment(RootComponent);

    HealthBox->OnComponentBeginOverlap.AddDynamic(this, &AHealthPickUp::OnOverlapBegin);
}

// Called when the game starts or when spawned
void AHealthPickUp::BeginPlay()
{
	Super::BeginPlay();
	
}

void AHealthPickUp::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (OtherActor)
    {
        APlayerPawn* pawn = Cast<APlayerPawn>(OtherActor);
        if (pawn)
        {
            pawn->IncrementHealth(25);
            Destroy();
        }
    }
}

// Called every frame
void AHealthPickUp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

