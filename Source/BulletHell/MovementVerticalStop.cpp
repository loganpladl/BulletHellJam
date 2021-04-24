// Fill out your copyright notice in the Description page of Project Settings.


#include "MovementVerticalStop.h"
#include "Math/Vector.h"
#include "BulletHellGameStateBase.h"

void UMovementVerticalStop::Move(float DeltaTime) {
	FVector location = GetOwner()->GetActorLocation();
	float CurrentZ = location.Z;

	if (GameState->WorldToVerticalFrac(CurrentZ) > EndYPosition) {
		GetOwner()->SetActorLocation({ location.X, location.Y, CurrentZ - AdjustedMoveSpeed * DeltaTime });
	}
}