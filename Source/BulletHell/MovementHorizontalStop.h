// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseEnemyMovement.h"
#include "MovementHorizontalStop.generated.h"

/**
 * 
 */
UCLASS()
class BULLETHELL_API UMovementHorizontalStop : public UBaseEnemyMovement
{
	GENERATED_BODY()
	
public:
	virtual void Move(float DeltaTime) override;

	// Called when the game starts
	virtual void BeginPlay() override;

private:
	UPROPERTY(category = "Movement", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float EndXPosition = .75f;

	bool MovingRight;
};
