// Fill out your copyright notice in the Description page of Project Settings.


#include "Bomber.h"

#include "UObject/ConstructorHelpers.h"

#include "Classes/PaperSpriteComponent.h"

#include "Particles/ParticleSystemComponent.h"

#include "Components/BoxComponent.h"

// Sets default values
ABomber::ABomber()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//CapsuleComponent->BodyInstance.bLockZRotation = false;
	Tags.Empty();
	Tags.Add("AIGuard");

#pragma region Box Collision Component
	UBoxComponent* BomberBox = CreateDefaultSubobject<UBoxComponent>(TEXT("RootComponent"));
    BomberBox->SetCollisionProfileName("BlockAll");
    BomberBox->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	BomberBox->SetWorldScale3D(FVector(1.0f));
	BomberBox->SetBoxExtent(FVector(80.f, 80.f, 80.f));
	SetRootComponent(BomberBox);
	

#pragma region Paper Mesh Component
	BomberMesh = CreateDefaultSubobject<UPaperSpriteComponent>("Bomber Sprite Component");
	BomberMesh->SetCollisionProfileName("BlockAll");
	BomberMesh->SetupAttachment(RootComponent);

#pragma region ParticleEffect
	OurParticleSystem = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("MovementParticles"));
	OurParticleSystem->SetupAttachment(RootComponent);
	OurParticleSystem->bAutoActivate = true;
	OurParticleSystem->SetRelativeLocation(FVector(0.0f, 10.0f, 0.0f));
	OurParticleSystem->SetWorldScale3D(FVector(3.0f));

	static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleAsset(TEXT("/Game/StarterContent/Particles/P_Smoke.P_Smoke"));
	if (ParticleAsset.Succeeded())
	{
		OurParticleSystem->SetTemplate(ParticleAsset.Object);
		OurParticleSystem->ToggleActive();
	}

    BomberMesh->GetBodyInstance()->bLockXRotation = true;
    BomberMesh->GetBodyInstance()->bLockYRotation = true;
    BomberMesh->GetBodyInstance()->bLockZRotation = true;
    BomberMesh->GetBodyInstance()->bLockYTranslation = true;

    BomberHealth = 1000;
}

// Called when the game starts or when spawned
void ABomber::BeginPlay()
{
	Super::BeginPlay();

    if (bPatrol)
    {
        MoveToNextPatrolPoint();
    }
}

void ABomber::MoveToNextPatrolPoint()
{
    if (CurrentPatrolPoint == nullptr || CurrentPatrolPoint == SecondCheckpoint)
    {
        CurrentPatrolPoint = FirstCheckpoint;

    }
    else
    {
        CurrentPatrolPoint = SecondCheckpoint;
    }

    FVector Direction = GetActorLocation() - CurrentPatrolPoint->GetActorLocation();
    Direction.Normalize();

    FRotator NewLookAt = FRotationMatrix::MakeFromX(Direction).Rotator();
    NewLookAt.Pitch = 0.0f;
    NewLookAt.Roll = 0.0f;
    NewLookAt.Yaw += -180.0f;
    SetActorRotation(NewLookAt);
}

// Called every frame
void ABomber::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    if (CurrentPatrolPoint)
    {
        FVector Delta = GetActorLocation() - CurrentPatrolPoint->GetActorLocation();
        float DistanceToGoal = Delta.Size();

        if (DistanceToGoal < 100)
        {
            MoveToNextPatrolPoint();
        }
        SetActorLocation(FMath::VInterpConstantTo(GetActorLocation(), CurrentPatrolPoint->GetActorLocation(), DeltaTime, 600.f));
    }
}

int ABomber::GetBomberHealth()
{
    return BomberHealth;
}

void ABomber::DecrementHealth(int Health)
{
    BomberHealth -= Health;
}

