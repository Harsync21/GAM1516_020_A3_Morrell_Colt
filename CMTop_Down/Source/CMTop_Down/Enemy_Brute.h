// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Enemy_Brute.generated.h"

UCLASS()
class CMTOP_DOWN_API AEnemy_Brute : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemy_Brute();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Components")
		class UCapsuleComponent* CapsuleComponent;

	UPROPERTY(EditAnywhere, Category = "Components")
		class UPaperSpriteComponent* EnemySpriteComponent;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditInstanceOnly,
		Category = "AI",
		meta = (EditCondition = "Target"))
		AActor* Target;

    UFUNCTION()
        void OnBomberHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit);
};
