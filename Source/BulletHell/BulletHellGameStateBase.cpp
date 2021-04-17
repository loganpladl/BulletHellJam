// Fill out your copyright notice in the Description page of Project Settings.


#include "BulletHellGameStateBase.h"
#include "Engine/World.h"


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