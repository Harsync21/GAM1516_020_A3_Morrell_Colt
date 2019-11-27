// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"
#include "PlayerPawn.h"

AMyPlayerController::AMyPlayerController()
{

}

void AMyPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();

	//Bind Axis
    if (InputComponent != nullptr)
    {
        InputComponent->BindAxis("MoveRight", this, &AMyPlayerController::MoveRight);
        InputComponent->BindAxis("MoveForward", this, &AMyPlayerController::MoveForward);

        InputComponent->BindAxis("Turn", this, &AMyPlayerController::Turn);
        //Bind Action
        InputComponent->BindAction("Shoot", IE_Pressed, this, &AMyPlayerController::Shoot);
        InputComponent->BindAction("Respawn", IE_Pressed, this, &AMyPlayerController::Respawn);
    }
}

void AMyPlayerController::MoveRight(float amount)
{
	APlayerPawn* pawn = Cast<APlayerPawn>(GetPawn());
	if (pawn != nullptr)
	{
		pawn->MoveRight(amount);
	}
}

void AMyPlayerController::MoveForward(float amount)
{
	APlayerPawn* pawn = Cast<APlayerPawn>(GetPawn());
	if (pawn != nullptr)
	{
		pawn->MoveForward(amount);
	}
}

void AMyPlayerController::Turn(float amount)
{
    APlayerPawn* pawn = Cast<APlayerPawn>(GetPawn());
    if (pawn != nullptr)
    {
        pawn->Turn(amount);
    }
}

void AMyPlayerController::Shoot()
{
	APlayerPawn* pawn = Cast<APlayerPawn>(GetPawn());
	if (pawn != nullptr)
	{
		pawn->Shoot();
	}
}

void AMyPlayerController::Respawn()
{
	APlayerPawn* pawn = Cast<APlayerPawn>(GetPawn());
	if (pawn != nullptr)
	{
		pawn->Respawn();
	}
}
