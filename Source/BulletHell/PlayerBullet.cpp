// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerBullet.h"
#include "Components/CapsuleComponent.h"
#include "EnemyPawn.h"

// Called when the game starts or when spawned
void APlayerBullet::BeginPlay()
{
	Super::BeginPlay();

	// Add dynamic on hit binding
	CapsuleComponent->OnComponentBeginOverlap.AddDynamic(this, &APlayerBullet::OnOverlapBegin);
}

void APlayerBullet::OnOverlapBegin(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Check if the other actor is an enemy
	if (OtherActor && OtherActor->ActorHasTag(FName(TEXT("Enemy")))) {
		AEnemyPawn* Enemy = Cast<AEnemyPawn>(OtherActor);
		// TODO: Spawn particle effect and play sound effect

		Enemy->DecrementHealth();

		DisableFromPool();
	}
}