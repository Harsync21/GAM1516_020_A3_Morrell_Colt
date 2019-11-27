// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHUD.h"
#include "Blueprint/UserWidget.h"
#include "ConstructorHelpers.h"

APlayerHUD::APlayerHUD()
{
    static ConstructorHelpers::FClassFinder<UUserWidget> playerHud(TEXT("/Game/Blueprints/PlayerGUI"));
    if (playerHud.Succeeded())
        PlayerGuiclass = playerHud.Class;
}

void APlayerHUD::BeginPlay()
{
    PlayerGui = CreateWidget<UUserWidget>(GetGameInstance(),PlayerGuiclass);
    PlayerGui->AddToViewport();
}
