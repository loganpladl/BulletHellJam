// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Sound/SoundCue.h"
#include "Containers/Array.h"
#include "EnemyPawn.generated.h"

class UBaseEnemyMovement;
class APlayerPawn;
class ABulletHellGameStateBase;

/**
 * 
 */
UCLASS()
class BULLETHELL_API AEnemyPawn : public ABasePawn
{
	GENERATED_BODY()

public:
	AEnemyPawn();

	void DecrementHealth();

	virtual void Die();

	void PlayFireSound();
	void PlayDamagedSound();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void PlayDeathSound();

	UPROPERTY(category = "Movement", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float BaseHealth = 3;

	float CurrentHealth;

	UPROPERTY(Category = "Sound", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	USoundCue* FireSound;

	UPROPERTY(Category = "Sound", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	USoundCue* DamagedSound;

	UPROPERTY(Category = "Sound", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TArray<USoundCue*> DeathSounds;

	APlayerPawn* PlayerPawn;
	ABulletHellGameStateBase* GameState;
	
};

