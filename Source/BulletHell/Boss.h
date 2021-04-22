// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyPawn.h"
#include "Boss.generated.h"

/**
 * 
 */
UCLASS()
class BULLETHELL_API ABoss : public AEnemyPawn
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
public:
	void Die() override;
};
