// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "CMWaveShooterGameMode.generated.h"

/**
 * 
 */
UCLASS()
class CMTOP_DOWN_API ACMWaveShooterGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
	void OnGeneratorHit();

	void OnPlayerHit();

	void OnPickUp();
public:
	UPROPERTY(EditAnywhere)
		TSubclassOf<class AGenerator> Generator;

};
