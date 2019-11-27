// Fill out your copyright notice in the Description page of Project Settings.


#include "CMWaveShooterGameMode.h"
#include "Top_Down_GameStateBase.h"
#include "Generator.h"
#include "PlayerPawn.h"
#include "UObject/ConstructorHelpers.h"

void ACMWaveShooterGameMode::OnGeneratorHit()
{
	//if (ATop_Down_GameStateBase * GH = Cast<ATop_Down_GameStateBase>(GameState))
	//{
	//	if (GH->GeneratorHealth > 0)
	//	{
	//		GH->GeneratorHealth--;
	//	}
	//	if (GH->GeneratorHealth == 0)
	//	{
	//		//AGenerator* Generator->Destroy();
	//	}
	//}
}

void ACMWaveShooterGameMode::OnPlayerHit()
{
	if (ATop_Down_GameStateBase * GH = Cast<ATop_Down_GameStateBase>(GameState))
	{
		if (GH->PlayerHealth != 0)
		{
			GH->PlayerHealth ++;
		}
	}
}

void ACMWaveShooterGameMode::OnPickUp()
{
	if (ATop_Down_GameStateBase * GH = Cast<ATop_Down_GameStateBase>(GameState))
	{
		GH->AmmoCount ++;
	}
}
