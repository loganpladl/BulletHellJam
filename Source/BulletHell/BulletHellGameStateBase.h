// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "Math/Vector.h"
#include "BulletHellGameStateBase.generated.h"


class APlayerPawn;

/**
 * 
 */
UCLASS()
class BULLETHELL_API ABulletHellGameStateBase : public AGameStateBase
{
	GENERATED_BODY()


public:
	ABulletHellGameStateBase();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

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

	// Getters for rank system
	int GetPlayerHealthRank() { return PlayerHealthRank; }
	int GetPlayerDamageRank() { return PlayerDamageRank; }
	int GetPlayerSpeedRank() { return PlayerSpeedRank; }
	int GetPlayerBulletSpreadRank() { return PlayerBulletSpreadRank; }
	int GetPlayerFireRateRank() { return PlayerFireRateRank; }

	int GetEnemyHealthRank() { return EnemyHealthRank; }
	int GetEnemyDamageRank() { return EnemyDamageRank; }
	int GetEnemySpeedRank() { return EnemySpeedRank; }
	int GetEnemyBulletSpeedRank() { return EnemyBulletSpeedRank; }
	int GetEnemyFireRateRank() { return EnemyFireRateRank; }

	void UpgradePlayerHealthRank() { ++PlayerHealthRank; }
	void UpgradePlayerDamageRank() { ++PlayerDamageRank; }
	void UpgradePlayerSpeedRank() { ++PlayerSpeedRank; }
	void UpgradePlayerBulletSpreadRank() { ++PlayerBulletSpreadRank; }
	void UpgradePlayerFireRateRank() { ++PlayerFireRateRank; }

	void UpgradeEnemyHealthRank() { ++EnemyHealthRank; }
	void UpgradeEnemyDamageRank() { ++EnemyDamageRank; }
	void UpgradeEnemySpeedRank() { ++EnemySpeedRank; }
	void UpgradeEnemyBulletSpeedRank() { ++EnemyBulletSpeedRank; }
	void UpgradeEnemyFireRateRank() { ++EnemyFireRateRank; }

	// Player variables
	int GetCurrentPlayerHealth() { return CurrentPlayerHealth; }
	int GetCurrentPlayerLives() { return CurrentPlayerLives; }

	void DecrementPlayerHealth();
	void DecrementPlayerLives();

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

	virtual void BeginPlay() override;

private:
	// Rank System
	// Player
	int PlayerHealthRank = 0;
	int PlayerDamageRank = 0;
	int PlayerSpeedRank = 0;
	int PlayerBulletSpreadRank = 0;
	int PlayerFireRateRank = 0;

	// Enemy
	int EnemyHealthRank = 0;
	int EnemyDamageRank = 0;
	int EnemySpeedRank = 0;
	int EnemyBulletSpeedRank = 0;
	int EnemyFireRateRank = 0;

	int CurrentPlayerHealth = 3;
	int CurrentPlayerLives = 3;

	float PlayerRespawnTimer;
	const float PlayerRespawnDuration = 3.0f;
	bool PlayerDead = false;

	APlayerPawn* PlayerPawn;
};
