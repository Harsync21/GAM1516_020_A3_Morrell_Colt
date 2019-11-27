// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPawn.h"
#include "Bullet.h"
#include "Top_Down_GameStateBase.h"

#include "Classes/Camera/CameraComponent.h"
#include "Classes/GameFramework/SpringArmComponent.h"
#include "Classes/PaperSpriteComponent.h"
#include "Classes/Components/InputComponent.h"
#include "Classes/GameFramework/FloatingPawnMovement.h"

#include "PaperFlipbookComponent.h"
#include "PaperCharacter.h"
#include "PaperFlipbook.h"

#include "UObject/ConstructorHelpers.h"

#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/ArrowComponent.h"

// Sets default values
APlayerPawn::APlayerPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

#pragma region Movement Component

	FloatingPawnMovement = CreateDefaultSubobject<UFloatingPawnMovement>("PawnMovement");

#pragma region Collision Component
    //Collision Component
    CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>("CapsuleComponent");
    CapsuleComponent->SetCollisionProfileName("BlockAll");
    CapsuleComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    CapsuleComponent->SetWorldScale3D(FVector(0.5f));
    CapsuleComponent->SetRelativeRotation(FRotator(0.f,90.f,0.f));
    SetRootComponent(CapsuleComponent);

#pragma region Bullet Spawn Component
	BulletSpawnComponent = CreateDefaultSubobject<UArrowComponent>(TEXT("BulletSpawnPoint"));
	BulletSpawnComponent->SetupAttachment(RootComponent);
	BulletSpawnComponent->ArrowSize = 2.5f;

#pragma region Animated Sprite Component
    UPaperSpriteComponent* comp = Cast<UPaperSpriteComponent>(GetComponentByClass(UPaperSpriteComponent::StaticClass()));

    if (comp)
    {
        comp->DestroyComponent();
        comp->SetActive(false);
    }

    AnimatedSpriteComponent = CreateOptionalDefaultSubobject<UPaperFlipbookComponent>(APaperCharacter::SpriteComponentName);

    if (AnimatedSpriteComponent)
    {
        AnimatedSpriteComponent->SetupAttachment(RootComponent);

        AnimatedSpriteComponent->SetCollisionProfileName("NoCollision");

        AnimatedSpriteComponent->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));

        AnimatedSpriteComponent->SetGenerateOverlapEvents(false);
    }

#pragma region Camera Component
    //Camera Spring Arm
    CameraArm = CreateDefaultSubobject<USpringArmComponent>("CameraSpringArm");
    CameraArm->SetupAttachment(RootComponent);
    CameraArm->SetRelativeRotation(FRotator(0.f, -180.f, 0.f));
    CameraArm->TargetArmLength = 250.f;

    //Camera Component
    Camera = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
    Camera->SetProjectionMode(ECameraProjectionMode::Orthographic);
    Camera->SetOrthoWidth(2500.f);
    Camera->SetupAttachment(CameraArm);

#pragma region Default States
	//Automatically Possesses Player
	AutoPossessPlayer = EAutoReceiveInput::Player0;
    //Default State
    SetState(EAnimState::Idle);
	//Finds Rotation
	bUseControllerRotationRoll = true;

	AmmoCount = 20;
    PlayerHealth = 100;
}

void APlayerPawn::MoveRight(float amount)
{
    SetState(EAnimState::Walking);

	FloatingPawnMovement->AddInputVector(GetActorRightVector()* amount);
}

void APlayerPawn::MoveForward(float amount)
{
    SetState(EAnimState::Walking);

	FloatingPawnMovement->AddInputVector(GetActorUpVector()* amount);
}

void APlayerPawn::Turn(float amount)
{
	AddControllerRollInput(amount);
}

void APlayerPawn::Shoot()
{
	if (AmmoCount != 0)
	{
		SetState(EAnimState::Shooting);

		if (BulletClass != nullptr)
		{
			UWorld* World = GetWorld();

			if (World)
			{
				FActorSpawnParameters SpawnParams;

				SpawnParams.Owner = this;
				SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

				FTransform SpawnTransform = BulletSpawnComponent->GetComponentTransform();
				ABullet* Bullet = World->SpawnActor<ABullet>(BulletActorTemplate, SpawnTransform, SpawnParams);

				if (Bullet)
				{
					FVector direction = FRotationMatrix(SpawnTransform.Rotator()).GetScaledAxis(EAxis::X);
					UPrimitiveComponent* physicsComponent = Bullet->GetPhysicsComponent();
				}
			}
		}
		AmmoCount--;
	}
}

void APlayerPawn::Respawn()
{


}

// Called when the game starts or when spawned
void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();
	
    if (AnimatedSpriteComponent != nullptr)
        AnimatedSpriteComponent->Stop();
}

void APlayerPawn::UpdateAnimation()
{
    float velocity = GetVelocity().Size();

    if (velocity > 0)
    {
        if (AnimState == EAnimState::Walking)
        {

            AnimatedSpriteComponent->SetFlipbook(WalkFlipbook);

            AnimatedSpriteComponent->SetLooping(true);

            AnimatedSpriteComponent->Play();
        }
  
    }
    else 
    {

        AnimatedSpriteComponent->Stop();

        AnimatedSpriteComponent->SetFlipbook(IdleFlipbook);

        AnimatedSpriteComponent->SetLooping(true);

        AnimatedSpriteComponent->Play();
    }


    //Update WALKING Animation
    if (AnimState == EAnimState::Walking)
    {

        AnimatedSpriteComponent->SetFlipbook(WalkFlipbook);

        AnimatedSpriteComponent->SetLooping(true);

        AnimatedSpriteComponent->Play();
    }

    //Update IDLE Animation
    if (AnimState == EAnimState::Idle)
    {
        AnimatedSpriteComponent->SetFlipbook(IdleFlipbook);

        AnimatedSpriteComponent->SetLooping(true);

        AnimatedSpriteComponent->Play();
    }
    if (AnimState == EAnimState::Shooting)
    {
        AnimatedSpriteComponent->SetFlipbook(ShootingFlipbook);

        AnimatedSpriteComponent->SetLooping(true);

        AnimatedSpriteComponent->Play();
    }
}

// Called every frame
void APlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    UpdateAnimation();
}

// Called to bind functionality to input
void APlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &APlayerPawn::Shoot);

	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerPawn::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerPawn::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &APlayerPawn::Turn);

}

void APlayerPawn::OnEnemyHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit)
{


}

void APlayerPawn::IncrementAmmoCount(int ammo)
{
    AmmoCount += ammo;
    
}

void APlayerPawn::IncrementHealth(int health)
{
    PlayerHealth += health;
}

int APlayerPawn::GetAmmoCount()
{
    return AmmoCount;
}

int APlayerPawn::GetHealthCount()
{
    return PlayerHealth;
}



