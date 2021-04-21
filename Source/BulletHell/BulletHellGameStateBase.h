// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "Math/Vector.h"
#include "Containers/UnrealString.h"
#include "BulletHellGameStateBase.generated.h"


class APlayerPawn;
class APickup;

enum class PlayerRank {
	Health, Damage, Speed, BulletSpread, FireRate
};
enum class EnemyRank {
	Health, Damage, Speed, BulletSpeed, FireRate
};

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
	UFUNCTION(BlueprintCallable)
	int GetPlayerHealthRank() { return PlayerHealthRank; }
	UFUNCTION(BlueprintCallable)
	int GetPlayerDamageRank() { return PlayerDamageRank; }
	UFUNCTION(BlueprintCallable)
	int GetPlayerSpeedRank() { return PlayerSpeedRank; }
	UFUNCTION(BlueprintCallable)
	int GetPlayerBulletSpreadRank() { return PlayerBulletSpreadRank; }
	UFUNCTION(BlueprintCallable)
	int GetPlayerFireRateRank() { return PlayerFireRateRank; }

	UFUNCTION(BlueprintCallable)
	int GetEnemyHealthRank() { return EnemyHealthRank; }
	UFUNCTION(BlueprintCallable)
	int GetEnemyDamageRank() { return EnemyDamageRank; }
	UFUNCTION(BlueprintCallable)
	int GetEnemySpeedRank() { return EnemySpeedRank; }
	UFUNCTION(BlueprintCallable)
	int GetEnemyBulletSpeedRank() { return EnemyBulletSpeedRank; }
	UFUNCTION(BlueprintCallable)
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
	UFUNCTION(BlueprintCallable)
	int GetCurrentPlayerHealth() { return CurrentPlayerHealth; }

	UFUNCTION(BlueprintCallable)
	int GetCurrentPlayerMaxHealth() { return PlayerHealthRank + 3; }

	UFUNCTION(BlueprintCallable)
	int GetCurrentPlayerLives() { return CurrentPlayerLives; }

	void DecrementPlayerHealth();
	void DecrementPlayerLives();

	// Formatted like 9.99
	UFUNCTION(BlueprintCallable)
	FString CountdownTimerToString();

	PlayerRank GetValidRandomPlayerRank();
	EnemyRank GetValidRandomEnemyRank();

	// Converts integers 0 to 4 to corresponding Player Ranks
	PlayerRank NumToPlayerRank(int32 Num);
	// Returns true if this rank can be upgraded (not at rank 5)
	bool IsValidPlayerUpgrade(PlayerRank Rank);

	EnemyRank NumToEnemyRank(int32 Num);
	bool IsValidEnemyUpgrade(EnemyRank Rank);

	void StartGameTransition();
	UFUNCTION(BlueprintCallable)
	void StartGame();

	UFUNCTION(BlueprintCallable)
	bool IsGameStarted() { return GameStarted; }
	UFUNCTION(BlueprintCallable)
	bool IsGameStartTransitioning() { return GameStartTransitioning; }

	UFUNCTION(BlueprintCallable)
	bool IsGameRestartTransitioning() { return GameRestartTransitioning; }
	UFUNCTION(BlueprintCallable)
	void RestartGame();

	void RestartGameTransition();

	UFUNCTION(BlueprintCallable)
	bool IsGameOver() { return GameOver; }

	void ClearBuffPickups();

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

	UPROPERTY(Category = "Buffs", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<APickup> PickupClass;

	FVector Buff1SpawnPosition;
	APickup* CurrentBuff1Pickup;

	FVector Buff2SpawnPosition;
	APickup* CurrentBuff2Pickup;

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
	const float PlayerRespawnDuration = 2.0f;
	bool PlayerDead = false;

	APlayerPawn* PlayerPawn;

	bool PlayerInvulnerable = false;
	const float PlayerInvulnerableDuration = 2.0f;
	float PlayerInvulnerableTimer;

	float CountdownTimer;
	float CountdownDuration = 9.9f;

	bool GameStarted = false;
	bool GameStartTransitioning = false;
	bool GameRestartTransitioning = false;

	bool GameOver = false;
};
