// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "PlayerHUD.generated.h"

/**
 * 
 */
UCLASS()
class CMTOP_DOWN_API APlayerHUD : public AHUD
{
	GENERATED_BODY()
	
public:
    APlayerHUD();

    UPROPERTY(EditAnywhere, Category = "Player HUD")
        TSubclassOf<class UUserWidget> PlayerGuiclass;
    UPROPERTY()
        class UUserWidget* PlayerGui;

protected:
    virtual void BeginPlay() override;
};
