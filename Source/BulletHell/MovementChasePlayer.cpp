// Fill out your copyright notice in the Description page of Project Settings.


#include "MovementChasePlayer.h"
#include "PlayerPawn.h"
#include "Math/UnrealMathVectorCommon.h"

// Called when the game starts
void UMovementChasePlayer::BeginPlay()
{
	Super::BeginPlay();

	TargetPosition = PlayerPawn->GetActorLocation();
}

void UMovementChasePlayer::Move(float DeltaTime) {
	FVector Location = GetOwner()->GetActorLocation();


	FVector PlayerLocation = PlayerPawn->GetActorLocation();
	TargetPosition = FMath::Lerp(TargetPosition, PlayerLocation, PlayerTrackingSpeed * DeltaTime);

	FVector Direction = TargetPosition - Location;
	Direction.Normalize();

	FVector MoveVector = Direction * MoveSpeed;

	GetOwner()->SetActorLocation(Location + MoveVector * DeltaTime);

	FRotator Rotation = MoveVector.Rotation();

	// Rotate since sprits are oriented downward
	Rotation = Rotation.Add(90, 0, 0);

	GetOwner()->SetActorRotation(Rotation);
}