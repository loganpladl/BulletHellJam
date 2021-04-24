// Fill out your copyright notice in the Description page of Project Settings.


#include "BulletHellGameStateBase.h"
#include "Engine/World.h"
#include "PlayerPawn.h"
#include "Math/UnrealMathUtility.h"
#include "Pickup.h"

ABulletHellGameStateBase::ABulletHellGameStateBase() {
	PlayerRespawnTimer = PlayerRespawnDuration;
	PlayerInvulnerableTimer = PlayerInvulnerableDuration;

	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PickupAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("Pickup Audio"));
	RootComponent = PickupAudioComponent;

	VictoryAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("Victory Audio"));
	VictoryAudioComponent->SetupAttachment(RootComponent);

	GameOverAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("Game Over Audio"));
	GameOverAudioComponent->SetupAttachment(RootComponent);

	GameOverScreenAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("Game Over Screen Audio"));
	GameOverScreenAudioComponent->SetupAttachment(RootComponent);

	WinScreenAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("Win Screen Audio"));
	WinScreenAudioComponent->SetupAttachment(RootComponent);
}

void ABulletHellGameStateBase::BeginPlay() {
	Super::BeginPlay();

	PlayerPawn = Cast<APlayerPawn>(GetWorld()->GetFirstPlayerController()->GetPawn());
	CountdownTimer = CountdownDuration;

	Buff1SpawnPosition = { HorizontalFracToWorld(-.5), PlayAreaPlanePosition, VerticalFracToWorld(1.1) };
	Buff2SpawnPosition = { HorizontalFracToWorld(.5), PlayAreaPlanePosition, VerticalFracToWorld(1.1) };

	PreventRestartTimer = PreventRestartDuration;
}

// Called every frame
void ABulletHellGameStateBase::Tick(float DeltaTime) {
	if (GameOver) {
		PreventRestartTimer -= DeltaTime;
	}
	if (GameStarted && !GameOver) {
		if (!BossSpawned) {
			CountdownTimer -= DeltaTime;
		}
		if (CountdownTimer <= 0 && !BossSpawned) {
			// Spawn Buffs
			PlayerRank PlayerRankForPickup1 = GetValidRandomPlayerRank();
			EnemyRank EnemyRankForPickup1 = GetValidRandomEnemyRank();

			PlayerRank PlayerRankForPickup2;
			// Get a different valid player rank for pickup 2
			do {
				PlayerRankForPickup2 = GetValidRandomPlayerRank();
			} while (PlayerRankForPickup1 == PlayerRankForPickup2);

			EnemyRank EnemyRankForPickup2;
			do {
				EnemyRankForPickup2 = GetValidRandomEnemyRank();
			} while (EnemyRankForPickup1 == EnemyRankForPickup2);

			// We have our two buffs. Now spawn two pickups.
			CurrentBuff1Pickup = GetWorld()->SpawnActor<APickup>(PickupClass, Buff1SpawnPosition, { 0,0,0 });
			CurrentBuff2Pickup = GetWorld()->SpawnActor<APickup>(PickupClass, Buff2SpawnPosition, { 0,0,0 });

			CurrentBuff1Pickup->Initialize(PlayerRankForPickup1, EnemyRankForPickup1);
			CurrentBuff2Pickup->Initialize(PlayerRankForPickup2, EnemyRankForPickup2);

			CountdownTimer = CountdownDuration;
		}

		if (PlayerDead && !GameStartTransitioning) {
			PlayerRespawnTimer -= DeltaTime;

			if (PlayerRespawnTimer <= 0) {
				PlayerPawn->PlayRespawnSound();
				// Respawn Player
				PlayerDead = false;

				// Reset health based on player health rank
				CurrentPlayerHealth = PlayerHealthRank + 3;

				// Make player invulnerable and setup timers
				PlayerPawn->MakeInvulnerable();
				PlayerInvulnerable = true;
				PlayerInvulnerableTimer = PlayerInvulnerableDuration;

				PlayerPawn->Enable();
				PlayerPawn->Respawn();
				PlayerPawn->PlayEngineSound();
			}
		}

		if (PlayerInvulnerable) {
			PlayerInvulnerableTimer -= DeltaTime;

			if (PlayerInvulnerableTimer <= 0) {
				// Make player vulnerable
				PlayerInvulnerable = false;

				PlayerPawn->MakeVulnerable();
			}
		}
	}
	else {

	}
}

void ABulletHellGameStateBase::ClearBuffPickups() {
	if (CurrentBuff1Pickup) {
		CurrentBuff1Pickup->Destroy();
	}
	if (CurrentBuff2Pickup) {
		CurrentBuff2Pickup->Destroy();
	}
}

void ABulletHellGameStateBase::GetPlayAreaBorders(float& MinX, float& MaxX, float& MinZ, float& MaxZ) {
	// Assume center of play area is (0, Y, 0) where Y is arbitrary
	float HalfWidth = PlayAreaWidth / 2;
	float HalfHeight = PlayAreaHeight / 2;

	MinX = -HalfWidth + PlayAreaBorder;
	MaxX = HalfWidth - PlayAreaBorder;
	MinZ = -HalfHeight + PlayAreaBorder;
	MaxZ = HalfHeight - PlayAreaBorder;
}

float ABulletHellGameStateBase::HorizontalFracToWorld(float x) {
	return x * (PlayAreaWidth / 2);
}

float ABulletHellGameStateBase::VerticalFracToWorld(float y) {
	return y * (PlayAreaHeight / 2);
}

float ABulletHellGameStateBase::WorldToVerticalFrac(float y) {
	return y / (PlayAreaHeight / 2);
}

float ABulletHellGameStateBase::WorldToHorizontalFrac(float x) {
	return x / (PlayAreaWidth / 2);
}

float ABulletHellGameStateBase::GetPlayerHorizontalFrac() {
	FVector MyCharacterPosition = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();
	return WorldToHorizontalFrac(MyCharacterPosition.X);
}

float ABulletHellGameStateBase::GetPlayerVerticalFrac() {
	FVector MyCharacterPosition = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();
	return WorldToVerticalFrac(MyCharacterPosition.Z);
}

bool ABulletHellGameStateBase::IsOutOfBounds(FVector Position) {
	float HorizontalFrac = WorldToHorizontalFrac(Position.X);
	float VerticalFrac = WorldToVerticalFrac(Position.Z);

	if (HorizontalFrac > OutOfBoundsMargin || HorizontalFrac < -OutOfBoundsMargin) {
		return true;
	}

	if (VerticalFrac > OutOfBoundsMargin || VerticalFrac < -OutOfBoundsMargin) {
		return true;
	}

	return false;
}

void ABulletHellGameStateBase::DecrementPlayerHealth() {
	CurrentPlayerHealth -= 1 + GetEnemyDamageRank();
	PlayerPawn->ResetDamageTimer();

	if (CurrentPlayerHealth <= 0) {
		// Kill player
		PlayerDead = true;
		PlayerRespawnTimer = PlayerRespawnDuration;

		PlayerPawn->Disable();
		PlayerPawn->StopEngineSound();
		PlayerPawn->PlayDeathSound();

		DecrementPlayerLives();
	}
	else {
		PlayerPawn->PlayDamagedSound();
	}
}

void ABulletHellGameStateBase::DecrementPlayerLives() {
	--CurrentPlayerLives;
	if (CurrentPlayerLives == 0) {
		PreventRestartTimer = PreventRestartDuration;
		GameOver = true;
		PlayGameOverAudio();
	}
}

FString ABulletHellGameStateBase::CountdownTimerToString() {
	FString String = FString::Printf(TEXT("%.1f"), CountdownTimer);
	return String;
}

PlayerRank ABulletHellGameStateBase::GetValidRandomPlayerRank() {
	int32 PlayerNum;
	do {
		PlayerNum = FMath::RandRange(0, 4);
	} while (!IsValidPlayerUpgrade(NumToPlayerRank(PlayerNum)));

	return NumToPlayerRank(PlayerNum);
}

EnemyRank ABulletHellGameStateBase::GetValidRandomEnemyRank() {
	int32 EnemyNum;
	do {
		EnemyNum = FMath::RandRange(0, 4);
	} while (!IsValidEnemyUpgrade(NumToEnemyRank(EnemyNum)));

	return NumToEnemyRank(EnemyNum);
}

PlayerRank ABulletHellGameStateBase::NumToPlayerRank(int32 Num) {
	switch (Num) {
	case 0:
		return PlayerRank::Health;
	case 1:
		return PlayerRank::Damage;
	case 2:
		return PlayerRank::Speed;
	case 3:
		return PlayerRank::BulletSpread;
	case 4:
		return PlayerRank::FireRate;
	default:
		return PlayerRank::Health;
	}
}

bool ABulletHellGameStateBase::IsValidPlayerUpgrade(PlayerRank Rank) {
	switch (Rank) {
	case PlayerRank::Health:
		if (PlayerHealthRank < 5) {
			return true;
		}
		else return false;
		break;
	case PlayerRank::Damage:
		if (PlayerDamageRank < 5) {
			return true;
		}
		else return false;
		break;
	case PlayerRank::Speed:
		if (PlayerSpeedRank < 5) {
			return true;
		}
		else return false;
		break;
	case PlayerRank::BulletSpread:
		if (PlayerBulletSpreadRank < 5) {
			return true;
		}
		else return false;
		break;
	case PlayerRank::FireRate:
		if (PlayerFireRateRank < 5) {
			return true;
		}
		else return false;
		break;
	default: 
		return false;
	}
}

EnemyRank ABulletHellGameStateBase::NumToEnemyRank(int32 Num) {
	switch (Num) {
	case 0:
		return EnemyRank::Health;
	case 1:
		return EnemyRank::Damage;
	case 2:
		return EnemyRank::Speed;
	case 3:
		return EnemyRank::BulletSpeed;
	case 4:
		return EnemyRank::FireRate;
	default:
		return EnemyRank::Health;
	}
}

bool ABulletHellGameStateBase::IsValidEnemyUpgrade(EnemyRank Rank) {
	switch (Rank) {
	case EnemyRank::Health:
		if (EnemyHealthRank < 5) {
			return true;
		}
		else return false;
		break;
	case EnemyRank::Damage:
		if (EnemyDamageRank < 5) {
			return true;
		}
		else return false;
		break;
	case EnemyRank::Speed:
		if (EnemySpeedRank < 5) {
			return true;
		}
		else return false;
		break;
	case EnemyRank::BulletSpeed:
		if (EnemyBulletSpeedRank < 5) {
			return true;
		}
		else return false;
		break;
	case EnemyRank::FireRate:
		if (EnemyFireRateRank < 5) {
			return true;
		}
		else return false;
		break;
	default:
		return false;
	}
}

void ABulletHellGameStateBase::StartGame() {
	GameStarted = true;
	GameStartTransitioning = false;
}

void ABulletHellGameStateBase::RestartGameTransition() {
	if (PreventRestartTimer < 0) {
		GameRestartTransitioning = true;

		StopGameOverScreenAudio();

		PlayerDead = false;
		PlayerPawn->Enable();
		// Avoid collisions with enemies that happen in a split second
		PlayerPawn->DisableCollision();

		CountdownTimer = CountdownDuration;

		PlayerHealthRank = 0;
		PlayerDamageRank = 0;
		PlayerSpeedRank = 0;
		PlayerBulletSpreadRank = 0;
		PlayerFireRateRank = 0;
		EnemyHealthRank = 0;
		EnemyDamageRank = 0;
		EnemySpeedRank = 0;
		EnemyBulletSpeedRank = 0;
		EnemyFireRateRank = 0;

		CurrentPlayerHealth = 3;
		CurrentPlayerLives = 3;

		PlayerRespawnTimer = PlayerRespawnDuration;
		PlayerInvulnerable = false;
	}
}

void ABulletHellGameStateBase::RestartGame() {
	// RESET EVERYTHING
	GameRestartTransitioning = false;
	GameStarted = false;
	GameOver = false;
	GameStartTransitioning = true;
	BossSpawned = false;

	PlayerPawn->PlayEngineSound();
	PlayerPawn->EnableCollision();
}

void ABulletHellGameStateBase::StartGameTransition() {
	GameStartTransitioning = true;
}

void ABulletHellGameStateBase::PlayPickupSound() {
	PickupAudioComponent->SetSound(PickupSound);
	PickupAudioComponent->Play();
}

void ABulletHellGameStateBase::PickedUpBuffs(PlayerRank P, EnemyRank E) {
	switch (P) {
	case PlayerRank::Health:
		UpgradePlayerHealthRank();
		break;
	case PlayerRank::Damage:
		UpgradePlayerDamageRank();
		break;
	case PlayerRank::Speed:
		UpgradePlayerSpeedRank();
		break;
	case PlayerRank::BulletSpread:
		UpgradePlayerBulletSpreadRank();
		break;
	case PlayerRank::FireRate:
		UpgradePlayerFireRateRank();
		break;
	default:
		UpgradePlayerHealthRank();
		break;
	}

	switch (E) {
	case EnemyRank::Health:
		UpgradeEnemyHealthRank();
		break;
	case EnemyRank::Damage:
		UpgradeEnemyDamageRank();
		break;
	case EnemyRank::Speed:
		UpgradeEnemySpeedRank();
		break;
	case EnemyRank::BulletSpeed:
		UpgradeEnemyBulletSpeedRank();
		break;
	case EnemyRank::FireRate:
		UpgradeEnemyFireRateRank();
		break;
	default:
		UpgradeEnemyHealthRank();
		break;
	}
}

void ABulletHellGameStateBase::KillBoss() {
	BossKilled = true;
	PlayVictoryAudio();
	PlayerPawn->StopEngineSound();
	// For safety
	PlayerPawn->MakeInvulnerable();
}