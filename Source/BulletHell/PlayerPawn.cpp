// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPawn.h"
#include "Math/Vector.h"

APlayerPawn::APlayerPawn() {

}

// Called when the game starts or when spawned
void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void APlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Move(DeltaTime);
}

// Called to bind functionality to input
void APlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("Vertical", this, &APlayerPawn::InputMoveVertical);
	PlayerInputComponent->BindAxis("Horizontal", this, &APlayerPawn::InputMoveHorizontal);
	PlayerInputComponent->BindAction("Shoot", IE_Pressed, this, &APlayerPawn::InputShootPressed);
	PlayerInputComponent->BindAction("Shoot", IE_Released, this, &APlayerPawn::InputShootReleased);
	PlayerInputComponent->BindAction("Focus", IE_Pressed, this, &APlayerPawn::InputFocusPressed);
	PlayerInputComponent->BindAction("Focus", IE_Released, this, &APlayerPawn::InputFocusReleased);
}

void APlayerPawn::InputMoveVertical(float Value) {
	MoveDirection.Z = Value;
}

void APlayerPawn::InputMoveHorizontal(float Value) {
	MoveDirection.X = Value;
}

void APlayerPawn::InputShootPressed() {
	IsShooting = true;
}

void APlayerPawn::InputShootReleased() {
	IsShooting = false;
}

void APlayerPawn::InputFocusPressed() {
	IsMovingSlow = true;
}

void APlayerPawn::InputFocusReleased() {
	IsMovingSlow = false;
}

void APlayerPawn::Move(float DeltaTime) {
	float speed;
	if (IsMovingSlow) {
		speed = MoveSpeedSlow;
	}
	else {
		speed = MoveSpeedNormal;
	}

	AddActorLocalOffset(MoveDirection * speed * DeltaTime, true);
}