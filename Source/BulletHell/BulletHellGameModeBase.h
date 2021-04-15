// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BulletHellGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class BULLETHELL_API ABulletHellGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

private:
	void HandleGameStart();
	void HandleGameOver();



public:
	void PlayerDied();

protected:
	virtual void BeginPlay();

	UFUNCTION(BlueprintImplementableEvent)
	void GameStart();
	UFUNCTION(BlueprintImplementableEvent)
	void GameOver();
};
