// Fill out your copyright notice in the Description page of Project Settings.


#include "BulletHellGameStateBase.h"
#include "Engine/World.h"
#include "PlayerPawn.h"

ABulletHellGameStateBase::ABulletHellGameStateBase() {
	PlayerRespawnTimer = PlayerRespawnDuration;

	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void ABulletHellGameStateBase::BeginPlay() {
	PlayerPawn = Cast<APlayerPawn>(GetWorld()->GetFirstPlayerController()->GetPawn());
}

// Called every frame
void ABulletHellGameStateBase::Tick(float DeltaTime) {
	if (PlayerDead) {
		PlayerRespawnTimer -= DeltaTime;

		if (PlayerRespawnTimer <= 0) {
			// Respawn Player
			PlayerDead = false;

			PlayerPawn->Enable();
		}
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

		DecrementPlayerLives();

		// Reset health based on player health rank
		// TODO: Might move this out of here
		CurrentPlayerHealth = PlayerHealthRank + 3;
	}
}

void ABulletHellGameStateBase::DecrementPlayerLives() {
	--CurrentPlayerLives;
	if (CurrentPlayerLives == 0) {
		// Game Over
	}
}