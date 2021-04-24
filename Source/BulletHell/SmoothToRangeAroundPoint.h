// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseEnemyMovement.h"
#include "Math/Vector.h"
#include "SmoothToRangeAroundPoint.generated.h"

/**
 *
 */
UCLASS()
class BULLETHELL_API USmoothToRangeAroundPoint : public UBaseEnemyMovement
{
	GENERATED_BODY()

public:
	virtual void Move(float DeltaTime) override;

	virtual void BeginPlay() override;

private:
	UPROPERTY(category = "Movement", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		float TargetXFrac;

	UPROPERTY(category = "Movement", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		float TargetYFrac;

	UPROPERTY(category = "Movement", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		float TargetRange;

	UPROPERTY(category = "Movement", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		float BaseDuration;

	float AdjustedDuration;

	bool StartedMoving = false;
	float StartMoveTime = 0.0f;

	FVector SpawnPosition;
	FVector TargetPosition;
};
