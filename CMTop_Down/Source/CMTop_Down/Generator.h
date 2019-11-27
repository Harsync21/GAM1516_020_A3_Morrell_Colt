// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Generator.generated.h"

UCLASS()
class CMTOP_DOWN_API AGenerator : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGenerator();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//CollisionComponent
	UPROPERTY(EditAnywhere, Category = "Components")
		class UBoxComponent* GeneratorMesh;
	//Visual Representation
	UPROPERTY(EditAnywhere, Category = "Components")
        UStaticMeshComponent* GeneratorVisual;
	//Particle System
	UPROPERTY(EditAnywhere, Category = "Components")
	    UParticleSystemComponent* OurParticleSystem;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
