// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseEnemyMovement.h"
#include "MovementVerticalStop.generated.h"

/**
 * 
 */
UCLASS()
class BULLETHELL_API UMovementVerticalStop : public UBaseEnemyMovement
{
	GENERATED_BODY()

public:
	virtual void Move(float DeltaTime) override;
	
private:
	UPROPERTY(category = "Movement", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float EndYPosition = .75f;
};
