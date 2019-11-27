// Fill out your copyright notice in the Description page of Project Settings.


#include "Bullet.h"
#include "Enemy_Brute.h"

#include "Components/StaticMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"

#include "Classes/GameFramework/ProjectileMovementComponent.h"


#include "UObject/ConstructorHelpers.h"

// Sets default values
ABullet::ABullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


#pragma region Collision Component
	CapsuleComponent = CreateDefaultSubobject<USphereComponent>("CapsuleComponent");
	CapsuleComponent->SetCollisionProfileName("BlockAll");
    CapsuleComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	SetRootComponent(CapsuleComponent);

#pragma region Sprite Component
		UStaticMeshComponent* BulletSprite = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Visual Representation"));
		BulletSprite->SetupAttachment(RootComponent);
		static ConstructorHelpers::FObjectFinder<UStaticMesh> BulletSpriteVisualAsset(TEXT("/Game/StarterContent/Shapes/Shape_NarrowCapsule.Shape_NarrowCapsule"));
		if (BulletSpriteVisualAsset.Succeeded())
		{
			BulletSprite->SetStaticMesh(BulletSpriteVisualAsset.Object);
			//BulletSprite->SetRelativeLocation(FVector(0.0f, 0.0f, 0.f));
			//BulletSprite->SetRelativeRotation(FRotator(0.f, 0.f, 0.f));
			//BulletSprite->SetWorldScale3D(FVector(1.0f));
            BulletSprite->SetCollisionProfileName("BlockAll");
		}

#pragma region Projectile Component
	BulletMovement = CreateDefaultSubobject<UProjectileMovementComponent>("BulletMovement");
	BulletMovement->ProjectileGravityScale = 0.f;
	BulletMovement->bShouldBounce = false;
	BulletMovement->InitialSpeed = 500.f;
	BulletMovement->MaxSpeed = 500.f;

    InitialLifeSpan = 5.f;

    OnActorHit.AddDynamic(this, &ABullet::OnBulletHit);

	
}

// Called when the game starts or when spawned
void ABullet::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

UPrimitiveComponent* ABullet::GetPhysicsComponent()
{
	return Cast<UPrimitiveComponent>(RootComponent);
}

void ABullet::OnBulletHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit)
{
    if (OtherActor)
    {
        AEnemy_Brute* EB = Cast<AEnemy_Brute>(OtherActor);
        if (EB)
        {
            EB->Destroy();
            Destroy();
        }
    }
}

