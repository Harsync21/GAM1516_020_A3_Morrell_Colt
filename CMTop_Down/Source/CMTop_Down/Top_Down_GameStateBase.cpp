// Fill out your copyright notice in the Description page of Project Settings.


#include "Top_Down_GameStateBase.h"
#include "UObject/ConstructorHelpers.h"

ATop_Down_GameStateBase::ATop_Down_GameStateBase()
{
	//OnPlayerHit
	PlayerHealth = 100;
	//PlayerPickUp
	AmmoCount = 25;
}

void ATop_Down_GameStateBase::IncrementPlayerHealth(int health)
{
    PlayerHealth += health;
}
