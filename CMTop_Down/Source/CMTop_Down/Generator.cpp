// Fill out your copyright notice in the Description page of Project Settings.


#include "Generator.h"

#include "Components/StaticMeshComponent.h"

#include "UObject/ConstructorHelpers.h"
#include "Particles/ParticleSystemComponent.h"

#include "Components/BoxComponent.h"

// Sets default values
AGenerator::AGenerator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Create Player Object
	UBoxComponent* GeneratorMesh = CreateDefaultSubobject<UBoxComponent>(TEXT("RootComponent"));
	GeneratorMesh->SetWorldScale3D(FVector(1.0f));
	GeneratorMesh->SetBoxExtent(FVector(10.f, 10.f, 10.f));
	SetRootComponent(GeneratorMesh);
	GeneratorMesh->SetCollisionProfileName("BlockAll");

	//Create and position a mesh component so we can see where our sphere is

#pragma region StaticMesh Component
    UStaticMeshComponent* GeneratorVisual = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Visual Representation"));
	GeneratorVisual->SetupAttachment(RootComponent);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> GeneratorVisualAsset(TEXT("/Game/StarterContent/Architecture/SM_AssetPlatform.SM_AssetPlatform"));
	if (GeneratorVisualAsset.Succeeded())
	{
		GeneratorVisual->SetStaticMesh(GeneratorVisualAsset.Object);
		GeneratorVisual->SetRelativeLocation(FVector(0.0f, 0.0f, 00.f));
		GeneratorVisual->SetRelativeRotation(FRotator(0.f,0.f,90.f));
        GeneratorVisual->SetWorldScale3D(FVector(0.6f));
	}


#pragma region ParticleEffect
	OurParticleSystem = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("MovementParticles"));
	OurParticleSystem->SetupAttachment(RootComponent);
	OurParticleSystem->bAutoActivate = true;
	OurParticleSystem->SetRelativeLocation(FVector(0.0f, 20.0f, 0.0f));
	OurParticleSystem->SetWorldScale3D(FVector(3.0f));

	static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleAsset(TEXT("/Game/StarterContent/Particles/P_Sparks.P_Sparks"));
	if (ParticleAsset.Succeeded())
	{
		OurParticleSystem->SetTemplate(ParticleAsset.Object);
		OurParticleSystem->ToggleActive();
	}
}

// Called when the game starts or when spawned
void AGenerator::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGenerator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

