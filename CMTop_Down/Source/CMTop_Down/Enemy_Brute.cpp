// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy_Brute.h"
#include "Bomber.h"

#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"

#include "ConstructorHelpers.h"

#include "Classes/PaperSpriteComponent.h"

#include "PaperCharacter.h"

#include "GameFramework/Character.h"


// Sets default values
AEnemy_Brute::AEnemy_Brute()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Capsule Component
	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(ACharacter::CapsuleComponentName);
	//CapsuleComponent->InitCapsuleSize(50.f,50.f);
	CapsuleComponent->SetCollisionProfileName("BlockAll");
    CapsuleComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	CapsuleComponent->SetNotifyRigidBodyCollision(true);
	SetRootComponent(CapsuleComponent);

	//Sprite Component
	EnemySpriteComponent = CreateDefaultSubobject<UPaperSpriteComponent>("Enemy Sprite Component");
	EnemySpriteComponent->SetCollisionProfileName("BlockAll");
	EnemySpriteComponent->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AEnemy_Brute::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemy_Brute::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Target != nullptr)
	{
		FVector targetLocation = FMath::VInterpConstantTo(GetActorLocation(), Target->GetActorLocation(), DeltaTime, 200.0f);
		SetActorLocation(targetLocation);
	}
}

void AEnemy_Brute::OnBomberHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit)
{
    if (OtherActor)
    {
        ABomber* Bomber = Cast<ABomber>(OtherActor);
        if (Bomber)
        {
            Bomber->DecrementHealth(10);
        }
    }
}

