// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "Math/Vector.h"
#include "BulletHellGameStateBase.generated.h"

/**
 * 
 */
UCLASS()
class BULLETHELL_API ABulletHellGameStateBase : public AGameStateBase
{
	GENERATED_BODY()
	

public:
	// Returns play area edges as out parameters
	void GetPlayAreaBorders(float& MinX, float& MaxX, float& MinZ, float& MaxZ);

	// Given a position from -1 to 1 from the left side of the play area to the right, return x in world coords
	float HorizontalFracToWorld(float x);

	// Given a position from -1 to 1 from the bottom of the play area to the top, return y in world coords
	float VerticalFracToWorld(float y);

	// Given a world position, convert to fraction -1 to 1
	float WorldToVerticalFrac(float y);
	float WorldToHorizontalFrac(float x);

	float GetPlayAreaPlanePosition() { return PlayAreaPlanePosition; }

	// Return player horizontal position from -1 to 1 where -1 is the left side of the play area and 1 is the right side
	float GetPlayerHorizontalFrac();
	float GetPlayerVerticalFrac();

	bool IsOutOfBounds(FVector Position);

protected:
	UPROPERTY(Category = "Play Area", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float PlayAreaWidth = 720.0f;

	UPROPERTY(Category = "Play Area", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float PlayAreaHeight = 1080.0f;

	UPROPERTY(Category = "Play Area", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float PlayAreaBorder = 32.0f;

	UPROPERTY(Category = "Play Area", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float PlayAreaPlanePosition = -550.0f;

	// How far outside play area is considered out of bounds in terms of the above "Frac" functions
	UPROPERTY(Category = "Play Area", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float OutOfBoundsMargin = 1.1f;
};
