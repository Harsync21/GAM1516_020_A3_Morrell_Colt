// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AmmoPickUp.generated.h"

UCLASS()
class CMTOP_DOWN_API AAmmoPickUp : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAmmoPickUp();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Collision Box")
		class UBoxComponent* AmmoBox;

	UPROPERTY(EditAnywhere, Category = "Actor Visual")
		class UPaperSpriteComponent* AmmoKit;
    
    UFUNCTION()
        void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent,
            AActor* OtherActor,
            UPrimitiveComponent* OtherComp,
            int32 OtherBodyIndex,
            bool bFromSweep,
            const FHitResult& SweepResult);
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	bool bImRotation = true;

};
