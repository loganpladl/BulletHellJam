// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyPawn.h"
#include "BulletHellGameStateBase.h"
#include "BaseEnemyMovement.h"
#include "Components/CapsuleComponent.h"
#include "PlayerPawn.h"

AEnemyPawn::AEnemyPawn() {
	CurrentHealth = BaseHealth;
}

void AEnemyPawn::BeginPlay() {
	Super::BeginPlay();
	
	this->Tags.AddUnique(TEXT("Enemy"));

	GameState = Cast<ABulletHellGameStateBase>(GetWorld()->GetGameState());
	float HealthMultiplier = GameState->GetEnemyHealthMultiplier();

	CurrentHealth *= HealthMultiplier;

	/*
	// Add dynamic on hit binding
	CapsuleComponent->OnComponentBeginOverlap.AddDynamic(this, &AEnemyPawn::OnOverlapBegin);

	*/

	PlayerPawn = Cast<APlayerPawn>(GetWorld()->GetFirstPlayerController()->GetPawn());
}

void AEnemyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (this->IsOverlappingActor(PlayerPawn)) {
		if (PlayerPawn->IsVulnerable() && PlayerPawn->CanDamage()) {
			GameState->DecrementPlayerHealth();
		}
	}
}

void AEnemyPawn::DecrementHealth() {
	float PlayerDamageMultiplier = GameState->GetPlayerDamageMultiplier();
	CurrentHealth -= 1 * PlayerDamageMultiplier;
	if (CurrentHealth <= 0) {
		Die();
	}
	else {
		PlayDamagedSound();
	}
	
}

void AEnemyPawn::Die() {
	bool Result = this->Destroy();
	PlayDeathSound();
}

void AEnemyPawn::PlayFireSound() {
	FireAudioComponent->SetSound(FireSound);
	FireAudioComponent->Play();
}

void AEnemyPawn::PlayDamagedSound() {
	DamagedAudioComponent->SetSound(DamagedSound);
	DamagedAudioComponent->Play();
}

void AEnemyPawn::PlayDeathSound() {
	if (DeathSounds.Num() == 0) {
		UE_LOG(LogTemp, Warning, TEXT("No Death sounds added to enemy pawn."));
		return;
	}
	int32 Index = FMath::RandRange(0, DeathSounds.Num() - 1);
	DeathAudioComponent->SetSound(DeathSounds[Index]);
	DeathAudioComponent->Play();
}