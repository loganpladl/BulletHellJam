// Fill out your copyright notice in the Description page of Project Settings.


#include "SmoothToRangeAroundPoint.h"
#include "BulletHellGameStateBase.h"
#include "Engine/World.h"
#include "Math/UnrealMathUtility.h"
#include "PlayerPawn.h"


void USmoothToRangeAroundPoint::BeginPlay() {
	Super::BeginPlay();

	AdjustedDuration = BaseDuration * (1 / GameState->GetEnemySpeedMultiplier());
	SpawnPosition = this->GetOwner()->GetActorLocation();
	float RandX = FMath::RandRange(0.0f - TargetRange, TargetRange);
	float RandY = FMath::RandRange(0.0f - TargetRange, TargetRange);
	TargetPosition = { GameState->HorizontalFracToWorld(TargetXFrac + RandX), GameState->GetPlayAreaPlanePosition(), GameState->VerticalFracToWorld(TargetYFrac + RandY) };
}

void USmoothToRangeAroundPoint::Move(float DeltaTime) {
	if (!StartedMoving) {
		StartedMoving = true;
		StartMoveTime = GetWorld()->GetTimeSeconds();
	}

	// Move

	float SmoothStepParameter = (GetWorld()->GetTimeSeconds() - StartMoveTime) / AdjustedDuration;

	float LerpParameter = FMath::SmoothStep(0, 1, SmoothStepParameter);

	this->GetOwner()->SetActorLocation(FMath::Lerp(SpawnPosition, TargetPosition, LerpParameter));
}