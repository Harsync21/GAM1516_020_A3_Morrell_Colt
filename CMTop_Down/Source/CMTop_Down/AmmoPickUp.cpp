// Fill out your copyright notice in the Description page of Project Settings.


#include "AmmoPickUp.h"
#include "PlayerPawn.h"

#include "Components/StaticMeshComponent.h"
#include "Classes/PaperSpriteComponent.h"
#include "Components/BoxComponent.h"

#include "UObject/ConstructorHelpers.h"



// Sets default values
AAmmoPickUp::AAmmoPickUp()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//Create Player Object
	UBoxComponent* AmmoBox = CreateDefaultSubobject<UBoxComponent>(TEXT("RootComponent"));
	AmmoBox->SetWorldScale3D(FVector(1.0));
	AmmoBox->SetBoxExtent(FVector(10.f,10.f, 10.f));
	SetRootComponent(AmmoBox);
	AmmoBox->SetCollisionProfileName("OverlapAllDynamic");
    AmmoBox->OnComponentBeginOverlap.AddDynamic(this,&AAmmoPickUp::OnOverlapBegin);

#pragma region StaticMesh Component
	AmmoKit = CreateDefaultSubobject<UPaperSpriteComponent>("Enemy Sprite Component");
	AmmoKit->SetCollisionProfileName("NoCollision");
	AmmoKit->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AAmmoPickUp::BeginPlay()
{
	Super::BeginPlay();
	
}

void AAmmoPickUp::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (OtherActor)
    {
        APlayerPawn* pawn = Cast<APlayerPawn>(OtherActor);
        if (pawn)
        {
            pawn->IncrementAmmoCount(10);
            Destroy();
        }
    }

}

// Called every frame
void AAmmoPickUp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
 	FVector NewLocation = GetActorLocation();

	FRotator NewRotation = GetActorRotation();

	float RunningTime = GetGameTimeSinceCreation();

	float DeltaHeight = (FMath::Sin(RunningTime + DeltaTime) - FMath::Sin(RunningTime));

	//Scales Height by 20
	NewLocation.Y += DeltaHeight * 20.f;

	//Rotates Object by 20
	float DeltaRotation = DeltaTime * 20.f;

	NewRotation.Pitch += DeltaRotation;

	SetActorLocationAndRotation(NewLocation, NewRotation);
}

