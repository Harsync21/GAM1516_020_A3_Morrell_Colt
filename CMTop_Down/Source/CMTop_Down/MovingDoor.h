// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MovingDoor.generated.h"

UCLASS()
class CMTOP_DOWN_API AMovingDoor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMovingDoor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

    UPROPERTY(EditAnywhere, Category = "Collision Box")
        class UBoxComponent* DoorBox;

    UPROPERTY(EditAnywhere, Category = "Actor Visual")
        class UStaticMeshComponent* DoorMesh;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

    void AdvanceTimer();

    UPROPERTY(EditAnywhere)
    int32 DoorTimer;

};
