// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseEnemyMovement.h"
#include "Math/Vector.h"
#include "MovementChasePlayer.generated.h"

/**
 * 
 */
UCLASS()
class BULLETHELL_API UMovementChasePlayer : public UBaseEnemyMovement
{
	GENERATED_BODY()

public:
	virtual void Move(float DeltaTime) override;

	UPROPERTY(category = "Movement", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float PlayerTrackingSpeed = 10.0f;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
private:
	// Target player position, acquire by lerping with player position for delayed targeting
	FVector TargetPosition;
};
