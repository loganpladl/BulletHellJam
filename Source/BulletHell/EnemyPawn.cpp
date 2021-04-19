// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyPawn.h"
#include "BaseEnemyMovement.h"

AEnemyPawn::AEnemyPawn() {
	CurrentHealth = BaseHealth;
}

void AEnemyPawn::BeginPlay() {
	Super::BeginPlay();

	this->Tags.AddUnique(TEXT("Enemy"));
}

void AEnemyPawn::DecrementHealth() {
	--CurrentHealth;
	if (CurrentHealth <= 0) {
		Die();
	}

	
}

void AEnemyPawn::Die() {
	bool Result = this->Destroy();
	PlayDeathSound();

	UE_LOG(LogTemp, Warning, TEXT("Result: %d"), Result);
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