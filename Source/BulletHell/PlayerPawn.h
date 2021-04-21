// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "PaperFlipbook.h"
#include "Sound/SoundCue.h"
#include "Components/AudioComponent.h"
#include "Containers/Array.h"
#include "PlayerPawn.generated.h"

struct FVector;

class UPlayerBulletPattern;

/**
 * 
 */
UCLASS()
class BULLETHELL_API APlayerPawn : public ABasePawn
{
	GENERATED_BODY()


private:
	// Input Delegates
	void InputMoveVertical(float Value);
	void InputMoveHorizontal(float Value);
	void InputShootPressed();
	void InputShootReleased();
	void InputFocusPressed();
	void InputFocusReleased();

	void InputRestartPressed();
	void InputRestartReleased();
	void InputQuitPressed();
	void InputQuitReleased();

	FVector MoveDirection = { 0,0,0 };

	bool IsShooting = false;
	bool IsMovingSlow = false;

	UPROPERTY(Category = "Animation", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UPaperFlipbook* IdleFlipbook;

	UPROPERTY(Category = "Animation", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UPaperFlipbook* BankLeftFlipbook;

	UPROPERTY(Category = "Animation", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UPaperFlipbook* BankRightFlipbook;

	UPROPERTY(Category = "Sound", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UAudioComponent* EngineAudioComponent;

	UPROPERTY(Category = "Sound", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UAudioComponent* RespawnAudioComponent;

	UPROPERTY(Category = "Sound", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	USoundCue* FireSound;

	UPROPERTY(Category = "Sound", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TArray<USoundCue*> DamagedSounds;

	UPROPERTY(Category = "Sound", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	USoundCue* DeathSound;

	UPROPERTY(Category = "Sound", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	USoundCue* RespawnSound;

	UPROPERTY(category = "Movement", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float MoveSpeedNormal = 1000.0f;

	UPROPERTY(category = "Movement", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float IntroDuration = 3.0f;

	bool IntroMoving = false;
	float IntroMoveStartTime;

	bool RestartTransitioning = false;
	

	// More precision movement if the player is holding a given button
	UPROPERTY(category = "Movement", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float MoveSpeedSlow = 500.0f;

	UPROPERTY(Category = "Bullet Patterns", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UPlayerBulletPattern> BulletPatternRank0Type;

	UPROPERTY(Category = "Bullet Patterns", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UPlayerBulletPattern> BulletPatternRank1Type;

	UPROPERTY(Category = "Bullet Patterns", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UPlayerBulletPattern> BulletPatternRank2Type;

	UPROPERTY(Category = "Bullet Patterns", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UPlayerBulletPattern> BulletPatternRank3Type;

	UPROPERTY(Category = "Bullet Patterns", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UPlayerBulletPattern> BulletPatternRank4Type;

	UPROPERTY(Category = "Bullet Patterns", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UPlayerBulletPattern> BulletPatternRank5Type;

	UPlayerBulletPattern* BulletPatternRank0Component;
	UPlayerBulletPattern* BulletPatternRank1Component;
	UPlayerBulletPattern* BulletPatternRank2Component;
	UPlayerBulletPattern* BulletPatternRank3Component;
	UPlayerBulletPattern* BulletPatternRank4Component;
	UPlayerBulletPattern* BulletPatternRank5Component;

	int32 CurrentBulletPatternRank = 0;

	void Move(float DeltaTime);

	void Fire(float DeltaTime);

	float MinX, MaxX, MinZ, MaxZ;

	void ClampPosition();

	FVector RespawnPosition;
	FVector SpawnPosition;

	bool Invulnerable = false;

	void CreateBulletPatterns();

	bool Enabled = true;

	void MoveToStart(float DeltaTime);

public:
	APlayerPawn();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void Disable();
	void Enable();

	void Respawn();

	void MakeInvulnerable();
	void MakeVulnerable();

	bool IsVulnerable();

	void SetBulletPatternRank(int32 Rank) { CurrentBulletPatternRank = Rank; }

	UPlayerBulletPattern* GetCurrentBulletPatternComponent();

	void PlayDamagedSound();
	void PlayFireSound();
	void PlayDeathSound();
	void PlayRespawnSound();

	void PlayEngineSound();
	void StopEngineSound();

	void EnableCollision();
	void DisableCollision();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	
};
