// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bomber.generated.h"

UCLASS()
class CMTOP_DOWN_API ABomber : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABomber();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//Let's Bomber move (For setting up waves)
	UPROPERTY(EditInstanceOnly, Category = "AI")
		bool bPatrol;

	//Visual Representation
	UPROPERTY(EditAnywhere, Category = "Components")
		class UPaperSpriteComponent* BomberMesh;

	UPROPERTY(EditAnywhere, Category = "Component")
		class UBoxComponent* BomberBox;

	//Dust Effect
	UPROPERTY(EditAnywhere, Category = "Components")
		UParticleSystemComponent* OurParticleSystem;

	//Patrol Checkpoint One
	UPROPERTY(EditInstanceOnly, Category = "AI", meta = (EditCondition = "bPatrol"))
		AActor* FirstCheckpoint;
	//Patrol Checkpoint Two
	UPROPERTY(EditInstanceOnly, Category = "AI", meta = (EditCondition = "bPatrol"))
		AActor* SecondCheckpoint;
	//Current Position
	AActor* CurrentPatrolPoint;

	//Optimization
	UFUNCTION()
		void MoveToNextPatrolPoint();

private:
	FTimerHandle SpawnProjectileTimer;
    int32 BomberHealth;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	FVector pointLocation;

    UFUNCTION(BlueprintCallable, Category = "Pickups")
        int GetBomberHealth(); 

    void DecrementHealth(int Health);
};
