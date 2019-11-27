// Fill out your copyright notice in the Description page of Project Settings.


#include "WaveTimer.h"
#include "GameFramework/Actor.h"
#include "Components/TextRenderComponent.h"

// Sets default values
AWaveTimer::AWaveTimer()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    CountdownText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("WaveTimer"));

    CountdownText->SetHorizontalAlignment(EHTA_Center);

    CountdownText->SetWorldSize(150.f);

    RootComponent = CountdownText;

    WaveTimer = 60;

}

// Called when the game starts or when spawned
void AWaveTimer::BeginPlay()
{
	Super::BeginPlay();
	
    UpdateTimerDisplay();

    GetWorldTimerManager().SetTimer(WaveTimerHandle, this, &AWaveTimer::AdvanceTimer, 1.0f, true);
}

// Called every frame
void AWaveTimer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWaveTimer::UpdateTimerDisplay()
{
    CountdownText->SetText(FString::FromInt(FMath::Max(WaveTimer,0)));
}

void AWaveTimer::AdvanceTimer()
{
    --WaveTimer;

    UpdateTimerDisplay();

    if (WaveTimer < 1)
    {
        GetWorldTimerManager().ClearTimer(WaveTimerHandle);
        CountdownHasFinished();
    }


}

void AWaveTimer::CountdownHasFinished_Implementation()
{
    CountdownText->SetText(TEXT("WAVE END"));
}

