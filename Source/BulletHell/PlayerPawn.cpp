// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPawn.h"
#include "Math/Vector.h"
#include "BulletHellGameStateBase.h"
#include "Engine/World.h"
#include "Math/Color.h"
#include "PlayerBulletPattern.h"
#include "Math/UnrealMathUtility.h"
#include "GenericPlatform/GenericPlatformMisc.h"
#include "Components/CapsuleComponent.h"

APlayerPawn::APlayerPawn() {
	MinX = 0.0f;
	MaxX = 0.0f;
	MinZ = 0.0f;
	MaxZ = 0.0f;

	EngineAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("Engine Audio"));
	EngineAudioComponent->SetupAttachment(CapsuleComponent);

	RespawnAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("Respawn Audio"));
	RespawnAudioComponent->SetupAttachment(CapsuleComponent);
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

	SpawnPosition = GetActorLocation();
	RespawnPosition = { 0.0f, -550.0f, 0.0f };

	CreateBulletPatterns();
}

// Called every frame
void APlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ABulletHellGameStateBase* GameState = Cast<ABulletHellGameStateBase>(GetWorld()->GetGameState());
	bool GameStarted = GameState->IsGameStarted();
	bool GameOver = GameState->IsGameOver();
	if (GameStarted && !GameOver) {
		Move(DeltaTime);

		UPlayerBulletPattern* BulletPattern = GetCurrentBulletPatternComponent();

		if (IsShooting && Enabled) {
			BulletPattern->Enable();
		}
		else {
			BulletPattern->Disable();
		}
	}
	else {
		if (IsShooting && !GameState->IsGameStartTransitioning()) {
			GameState->StartGameTransition();
		}
	}

	if (GameState->IsGameStartTransitioning() && !GameState->IsGameStarted()) {
		MoveToStart(DeltaTime);
		if (RestartTransitioning) {
			RestartTransitioning = false;
		}
	}

	if (GameState->IsGameRestartTransitioning()) {
		if (!RestartTransitioning) {
			RestartTransitioning = true;
			IntroMoving = false;
			this->SetActorLocation(SpawnPosition);
		}
	}
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

	PlayerInputComponent->BindAction("Restart", IE_Pressed, this, &APlayerPawn::InputRestartPressed);
	PlayerInputComponent->BindAction("Restart", IE_Released, this, &APlayerPawn::InputRestartReleased);
	PlayerInputComponent->BindAction("Quit", IE_Pressed, this, &APlayerPawn::InputQuitPressed);
	PlayerInputComponent->BindAction("Quit", IE_Released, this, &APlayerPawn::InputQuitReleased);
}

void APlayerPawn::InputMoveVertical(float Value) {
	MoveDirection.Z = Value;
}

void APlayerPawn::InputMoveHorizontal(float Value) {
	ABulletHellGameStateBase* GameState = Cast<ABulletHellGameStateBase>(GetWorld()->GetGameState());
	if (GameState->IsGameStarted()) {
		MoveDirection.X = Value;

		if (Value > 0) {
			if (BankLeftFlipbook) {
				FlipbookComponent->SetFlipbook(BankLeftFlipbook);
			}
		}
		else if (Value < 0) {
			if (BankRightFlipbook) {
				FlipbookComponent->SetFlipbook(BankRightFlipbook);
			}
		}
		else {
			if (IdleFlipbook) {
				FlipbookComponent->SetFlipbook(IdleFlipbook);
			}
		}
	}
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

void APlayerPawn::InputRestartPressed() {
	ABulletHellGameStateBase* GameState = Cast<ABulletHellGameStateBase>(GetWorld()->GetGameState());
	if (GameState->IsGameOver()) {
		GameState->RestartGameTransition();
	}
}

void APlayerPawn::InputRestartReleased() {

}

void APlayerPawn::InputQuitPressed() {
	FGenericPlatformMisc::RequestExit(false);
}

void APlayerPawn::InputQuitReleased() {
	FGenericPlatformMisc::RequestExit(false);
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

void APlayerPawn::Fire(float DeltaTime) {
	
}

void APlayerPawn::MoveToStart(float DeltaTime) {
	if (!IntroMoving) {
		IntroMoving = true;
		IntroMoveStartTime = GetWorld()->GetTimeSeconds();
	}

	float SmoothStepParameter = (GetWorld()->GetTimeSeconds() - IntroMoveStartTime) / IntroDuration;

	float LerpParameter = FMath::SmoothStep(0, 1, SmoothStepParameter);
	
	this->SetActorLocation(FMath::Lerp(SpawnPosition, RespawnPosition, LerpParameter));
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
	UPlayerBulletPattern* BulletPattern = GetCurrentBulletPatternComponent();
	BulletPattern->Disable();

	this->SetActorHiddenInGame(true);

	// Disables collision components
	this->SetActorEnableCollision(false);

	// Stops the Actor from ticking
	this->SetActorTickEnabled(false);

	Enabled = false;
}

void APlayerPawn::Enable() {
	this->SetActorHiddenInGame(false);

	// Disables collision components
	this->SetActorEnableCollision(true);

	// Stops the Actor from ticking
	this->SetActorTickEnabled(true);

	Enabled = true;
}

void APlayerPawn::EnableCollision() {
	this->SetActorEnableCollision(true);
}

void APlayerPawn::DisableCollision() {
	this->SetActorEnableCollision(false);
}

void APlayerPawn::Respawn() {
	SetActorLocation(RespawnPosition);
}

void APlayerPawn::MakeInvulnerable() {
	Invulnerable = true;
	FLinearColor Color = { 1.0f, 1.0f, 1.0f, 0.5f };
	FlipbookComponent->SetSpriteColor(Color);
}

void APlayerPawn::MakeVulnerable() {
	Invulnerable = false;
	FLinearColor Color = { 1.0f, 1.0f, 1.0f, 1.0f };
	FlipbookComponent->SetSpriteColor(Color);
}

bool APlayerPawn::IsVulnerable() {
	return !Invulnerable;
}

// Create all bullet patterns at the beginning of the game, only enable the corresponding rank
void APlayerPawn::CreateBulletPatterns() {
	if (BulletPatternRank0Type) {
		BulletPatternRank0Component = NewObject<UPlayerBulletPattern>(this, BulletPatternRank0Type, TEXT("BulletPatternRank0"));
		BulletPatternRank0Component->RegisterComponent();
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("No player bullet pattern type set."));
	}

	
	if (BulletPatternRank1Type) {
		BulletPatternRank1Component = NewObject<UPlayerBulletPattern>(this, BulletPatternRank1Type, TEXT("BulletPatternRank1"));
		BulletPatternRank1Component->RegisterComponent();
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("No player bullet pattern type set."));
	}


	if (BulletPatternRank2Type) {
		BulletPatternRank2Component = NewObject<UPlayerBulletPattern>(this, BulletPatternRank2Type, TEXT("BulletPatternRank2"));
		BulletPatternRank2Component->RegisterComponent();
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("No player bullet pattern type set."));
	}


	if (BulletPatternRank3Type) {
		BulletPatternRank3Component = NewObject<UPlayerBulletPattern>(this, BulletPatternRank3Type, TEXT("BulletPatternRank3"));
		BulletPatternRank3Component->RegisterComponent();
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("No player bullet pattern type set."));
	}


	if (BulletPatternRank4Type) {
		BulletPatternRank4Component = NewObject<UPlayerBulletPattern>(this, BulletPatternRank4Type, TEXT("BulletPatternRank4"));
		BulletPatternRank4Component->RegisterComponent();
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("No player bullet pattern type set."));
	}


	if (BulletPatternRank5Type) {
		BulletPatternRank5Component = NewObject<UPlayerBulletPattern>(this, BulletPatternRank5Type, TEXT("BulletPatternRank5"));
		BulletPatternRank5Component->RegisterComponent();
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("No player bullet pattern type set."));
	}
}

UPlayerBulletPattern* APlayerPawn::GetCurrentBulletPatternComponent() {
	switch (CurrentBulletPatternRank) {
	case 0:
		return BulletPatternRank0Component;
	case 1:
		return BulletPatternRank1Component;
	case 2:
		return BulletPatternRank2Component;
	case 3:
		return BulletPatternRank3Component;
	case 4:
		return BulletPatternRank4Component;
	case 5:
		return BulletPatternRank5Component;
	default:
		return BulletPatternRank0Component;
	}
}

void APlayerPawn::PlayDamagedSound() {
	if (DamagedSounds.Num() == 0) {
		UE_LOG(LogTemp, Warning, TEXT("No Damaged sounds added to player pawn."));
		return;
	}
	int32 Index = FMath::RandRange(0, DamagedSounds.Num() - 1);
	DamagedAudioComponent->SetSound(DamagedSounds[Index]);
	DamagedAudioComponent->Play();
}

// TODO: Check for null ptrs here and everywhere else I'm ignoring them
// TODO: Also should check if sounds are null (avoid crashing)

void APlayerPawn::PlayFireSound() {
	FireAudioComponent->SetSound(FireSound);
	FireAudioComponent->Play();
}

void APlayerPawn::PlayDeathSound() {
	DeathAudioComponent->SetSound(DeathSound);
	DeathAudioComponent->Play();
}

void APlayerPawn::PlayRespawnSound() {
	RespawnAudioComponent->SetSound(RespawnSound);
	RespawnAudioComponent->Play();
}

void APlayerPawn::PlayEngineSound() {
	EngineAudioComponent->Play();
}

void APlayerPawn::StopEngineSound() {
	EngineAudioComponent->Stop();
}