// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPawn.h"
#include "Math/Vector.h"
#include "BulletHellGameStateBase.h"
#include "Engine/World.h"

APlayerPawn::APlayerPawn() {
	MinX = 0.0f;
	MaxX = 0.0f;
	MinZ = 0.0f;
	MaxZ = 0.0f;
}

// Called when the game starts or when spawned
void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();

	ABulletHellGameStateBase* GameState = Cast<ABulletHellGameStateBase>(GetWorld()->GetGameState());
	if (!GameState) {
		UE_LOG(LogTemp, Error, TEXT("Cannot find GameState."))
	}
	else {
		GameState->GetPlayAreaBorders(MinX, MaxX, MinZ, MaxZ);
	}

	// Add tag for bullets to check
	this->Tags.AddUnique(TEXT("Player"));

	RespawnPosition = GetActorLocation();
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

	ClampPosition();
}

void APlayerPawn::ClampPosition() {
	FVector location = GetActorLocation();
	if (location.X < MinX) {
		location.X = MinX;
		SetActorLocation({ location.X, location.Y, location.Z }, true);
	}
	else if (location.X > MaxX) {
		location.X = MaxX;
		SetActorLocation({ location.X, location.Y, location.Z }, true);
	}
	if (location.Z < MinZ) {
		location.Z = MinZ;
		SetActorLocation({ location.X, location.Y, location.Z }, true);
	}
	else if (location.Z > MaxZ) {
		location.Z = MaxZ;
		SetActorLocation({ location.X, location.Y, location.Z }, true);
	}
}

void APlayerPawn::Disable() {
	this->SetActorHiddenInGame(true);

	// Disables collision components
	this->SetActorEnableCollision(false);

	// Stops the Actor from ticking
	this->SetActorTickEnabled(false);
}

void APlayerPawn::Enable() {
	this->SetActorHiddenInGame(false);

	// Disables collision components
	this->SetActorEnableCollision(true);

	// Stops the Actor from ticking
	this->SetActorTickEnabled(true);
}

void APlayerPawn::Respawn() {
	SetActorLocation(RespawnPosition);
}