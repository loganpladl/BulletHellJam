// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
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

protected:
	UPROPERTY(Category = "Play Area", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float PlayAreaWidth = 1920.0f;

	UPROPERTY(Category = "Play Area", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float PlayAreaHeight = 1080.0f;

	UPROPERTY(Category = "Play Area", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float PlayAreaBorder = 48.0f;
};
