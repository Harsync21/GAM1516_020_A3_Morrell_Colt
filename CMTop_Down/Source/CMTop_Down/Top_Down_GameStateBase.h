// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "Top_Down_GameStateBase.generated.h"

/**
 * 
 */
UCLASS()
class CMTOP_DOWN_API ATop_Down_GameStateBase : public AGameStateBase
{
	GENERATED_BODY()
public:
	ATop_Down_GameStateBase();

    void IncrementPlayerHealth(int health);
	//Affected by Enemy Collision
	int32 PlayerHealth;
	//Affected by Player Collision
	int32 AmmoCount;
};
