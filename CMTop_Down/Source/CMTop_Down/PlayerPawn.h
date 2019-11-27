// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PlayerPawn.generated.h"

//UENUM
UENUM(BlueprintType)
enum class EAnimState : uint8
{
    Idle,
    Jumping,
    Walking,
    Shooting,
    Dying,
    Dead,
    Hit
};

UCLASS()
class CMTOP_DOWN_API APlayerPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerPawn();

    //Capsule Component
    UPROPERTY(EditAnywhere, Category = "Components")
        class UCapsuleComponent* CapsuleComponent;

    //Walking Animation
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Config", meta = (AllowPrivateAccess = "true"))
        class UPaperFlipbook* WalkFlipbook;

    //Idle Animation
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Config", meta = (AllowPrivateAccess = "true"))
        class UPaperFlipbook* IdleFlipbook;

    //Shooting Animation
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Config", meta = (AllowPrivateAccess = "true"))
        class UPaperFlipbook* ShootingFlipbook;

    //Current Animatation State
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Config", meta = (AllowPrivateAccess = "true"))
        EAnimState AnimState = EAnimState::Idle;

    //Axis 
	void MoveRight(float amount);
	void MoveForward(float amount);
    void Turn(float amount);

    //Action
	void Shoot();
	void Respawn();

private:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Custom", meta = (AllowPrivateAccess = "true"))
        class UPaperSpriteComponent* PlayerSpriteComponent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	class UFloatingPawnMovement* FloatingPawnMovement;

	UPROPERTY(EditAnywhere, Category = "Shooting")
		TSubclassOf<class ABullet> BulletClass;

    UPROPERTY(Category = Character, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
        class UPaperFlipbookComponent* AnimatedSpriteComponent;

    virtual void UpdateAnimation();

    /** sets character state to NewState  */
    UFUNCTION(BlueprintCallable, Category = "AAA")
       void SetState(EAnimState NewState) {AnimState = NewState;}

	//Player Camera
	UPROPERTY(EditAnywhere, Category = "Components")
		class UCameraComponent* Camera;
	//Player SpringArm
	UPROPERTY(EditAnywhere, Category = "Components")
		class USpringArmComponent* CameraArm;

    float TravelDirection;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    void OnEnemyHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit);

	UPROPERTY(EditDefaultsOnly,
		BlueprintReadOnly,
		Category = "Config",
		meta = (AllowPrivateAccess = "true"))
		TSubclassOf<class ABullet> BulletActorTemplate;

	//Arrow Component//
	UPROPERTY(VisibleAnywhere,
		BlueprintReadOnly,
		Category = "Components",
		meta = (AllowPrivateAccess = "true"))
		class UArrowComponent* BulletSpawnComponent;

	UPROPERTY(EditDefaultsOnly,
		BlueprintReadOnly,
		Category = "Config",
		meta = (AllowPrivateAccess = "true"))
		int32 SpawnCount = 0;

    void IncrementAmmoCount(int ammo);

    void IncrementHealth(int health);

    UFUNCTION(BlueprintCallable, Category = "Pickups")
    int GetAmmoCount();

    UFUNCTION(BlueprintCallable, Category = "Pickups")
    int GetHealthCount();

private:
	float Movement;
    float Rotation;

	int32 AmmoCount;
    int32 PlayerHealth;
};
