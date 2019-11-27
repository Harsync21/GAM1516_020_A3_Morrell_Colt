// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bullet.generated.h"

UCLASS()
class CMTOP_DOWN_API ABullet : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABullet();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

    //Bullet Sprite
    UPROPERTY(EditAnywhere, Category = "Components")
        class UStaticMeshComponent* BulletSprite;

    //Bullet Component
    UPROPERTY(EditAnywhere, Category = "Components")
        class USphereComponent* CapsuleComponent;

    //Bullet ProjectileMovement
    UPROPERTY(EditAnywhere, Category = "Components")
        class UProjectileMovementComponent* BulletMovement;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	class UPrimitiveComponent* GetPhysicsComponent();

    UFUNCTION()
        void OnBulletHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit);
};
