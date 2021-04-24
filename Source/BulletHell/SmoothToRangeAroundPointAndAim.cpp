// Fill out your copyright notice in the Description page of Project Settings.


#include "SmoothToRangeAroundPointAndAim.h"
#include "BulletHellGameStateBase.h"
#include "Engine/World.h"
#include "Math/UnrealMathUtility.h"
#include "PlayerPawn.h"


void USmoothToRangeAroundPointAndAim::BeginPlay() {
	Super::BeginPlay();

	AdjustedDuration = BaseDuration * (1 / GameState->GetEnemySpeedMultiplier());
	SpawnPosition = this->GetOwner()->GetActorLocation();
	float RandX = FMath::RandRange(0.0f - TargetRange, TargetRange);
	float RandY = FMath::RandRange(0.0f - TargetRange, TargetRange);
	TargetPosition = { GameState->HorizontalFracToWorld(TargetXFrac + RandX), GameState->GetPlayAreaPlanePosition(), GameState->VerticalFracToWorld(TargetYFrac + RandY) };
}

void USmoothToRangeAroundPointAndAim::Move(float DeltaTime) {
	if (!StartedMoving) {
		StartedMoving = true;
		StartMoveTime = GetWorld()->GetTimeSeconds();
	}

	// Move

	float SmoothStepParameter = (GetWorld()->GetTimeSeconds() - StartMoveTime) / AdjustedDuration;

	float LerpParameter = FMath::SmoothStep(0, 1, SmoothStepParameter);

	this->GetOwner()->SetActorLocation(FMath::Lerp(SpawnPosition, TargetPosition, LerpParameter));

	// Aim
	FVector CurrentLocation = this->GetOwner()->GetActorLocation();
	FVector Player = PlayerPawn->GetActorLocation();

	FVector Direction = Player - CurrentLocation;
	Direction.Normalize();

	FRotator Rotation = Direction.Rotation();

	// Rotate since sprites are oriented downward
	Rotation = Rotation.Add(90, 0, 0);

	GetOwner()->SetActorRotation(Rotation);
}