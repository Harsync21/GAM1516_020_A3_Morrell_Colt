// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WaveTimer.generated.h"

UCLASS()
class CMTOP_DOWN_API AWaveTimer : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWaveTimer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
    int32 WaveTimer;

    class UTextRenderComponent* CountdownText;

    void UpdateTimerDisplay();

    void AdvanceTimer();

	UFUNCTION(BlueprintNativeEvent)
    void CountdownHasFinished();
	virtual void CountdownHasFinished_Implementation();

    FTimerHandle WaveTimerHandle;

};
