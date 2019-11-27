// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerController.generated.h"

class APlayerPawn;
/**
 * 
 */
UCLASS()
class CMTOP_DOWN_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	AMyPlayerController();
protected:
	APlayerPawn* myPawn;

protected:
	void SetupInputComponent() override;
	void MoveRight(float amount);
	void MoveForward(float amount);
    void Turn(float amount);
	void Shoot();
	void Respawn();
};
