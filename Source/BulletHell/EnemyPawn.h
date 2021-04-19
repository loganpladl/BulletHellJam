// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Sound/SoundCue.h"
#include "Containers/Array.h"
#include "EnemyPawn.generated.h"

class UBaseEnemyMovement;

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

	void Die();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(category = "Movement", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int BaseHealth = 3;

	int CurrentHealth;

	UPROPERTY(Category = "Sound", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TArray<USoundCue*> DeathSounds;

	void PlayDeathSound();
};

