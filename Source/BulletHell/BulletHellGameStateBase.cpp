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
	PickupAudioComponent->SetupAttachment(RootComponent);
}

void ABulletHellGameStateBase::BeginPlay() {
	Super::BeginPlay();

	PlayerPawn = Cast<APlayerPawn>(GetWorld()->GetFirstPlayerController()->GetPawn());
	CountdownTimer = CountdownDuration;

	Buff1SpawnPosition = { HorizontalFracToWorld(-.5), PlayAreaPlanePosition, VerticalFracToWorld(1.1) };
	Buff2SpawnPosition = { HorizontalFracToWorld(.5), PlayAreaPlanePosition, VerticalFracToWorld(1.1) };
}

// Called every frame
void ABulletHellGameStateBase::Tick(float DeltaTime) {
	if (GameStarted && !GameOver) {
		CountdownTimer -= DeltaTime;
		if (CountdownTimer <= 0) {
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
	--CurrentPlayerHealth;
	if (CurrentPlayerHealth == 0) {
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
		GameOver = true;
		
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
	GameRestartTransitioning = true;

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

void ABulletHellGameStateBase::RestartGame() {
	// RESET EVERYTHING
	GameRestartTransitioning = false;
	GameStarted = false;
	GameOver = false;
	GameStartTransitioning = true;

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