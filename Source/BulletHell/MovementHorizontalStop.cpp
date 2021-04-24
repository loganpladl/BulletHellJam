// Fill out your copyright notice in the Description page of Project Settings.


#include "MovementHorizontalStop.h"
#include "Math/Vector.h"
#include "BulletHellGameStateBase.h"

void UMovementHorizontalStop::BeginPlay() {
	Super::BeginPlay();

	float SpawnX = GameState->WorldToHorizontalFrac(this->GetOwner()->GetActorLocation().X);
	if (SpawnX < EndXPosition) {
		MovingRight = true;
	}
	else {
		MovingRight = false;
	}
}

void UMovementHorizontalStop::Move(float DeltaTime) {
	FVector Location = GetOwner()->GetActorLocation();
	float CurrentX = Location.X;

	if (MovingRight) {
		if (GameState->WorldToHorizontalFrac(CurrentX) < EndXPosition) {
			GetOwner()->SetActorLocation({ CurrentX + AdjustedMoveSpeed * DeltaTime, Location.Y, Location.Z });
		}
	}
	else {
		if (GameState->WorldToHorizontalFrac(CurrentX) > EndXPosition) {
			GetOwner()->SetActorLocation({ CurrentX - AdjustedMoveSpeed * DeltaTime, Location.Y, Location.Z });
		}
	}
}