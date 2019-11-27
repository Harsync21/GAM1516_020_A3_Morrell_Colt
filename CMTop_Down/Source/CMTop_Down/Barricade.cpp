// Fill out your copyright notice in the Description page of Project Settings.


#include "Barricade.h"

#include "Classes/PaperSpriteComponent.h"

#include "Components/BoxComponent.h"

// Sets default values
ABarricade::ABarricade()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

#pragma region Box Collision Component
	UBoxComponent* BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("RootComponent"));
	BoxComponent->SetWorldScale3D(FVector(1.0f));
	BoxComponent->SetBoxExtent(FVector(10.f, 50.f, 10.f));
	SetRootComponent(BoxComponent);
	BoxComponent->SetCollisionProfileName(TEXT("BlockAll"));
    BoxComponent->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);

#pragma region Paper Mesh Component
	barricadeSprite = CreateDefaultSubobject<UPaperSpriteComponent>("Bomber Sprite Component");
	barricadeSprite->SetCollisionProfileName(TEXT("BlockAll"));
    barricadeSprite->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	barricadeSprite->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ABarricade::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABarricade::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

