// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyBullet.h"
#include "Components/CapsuleComponent.h"
#include "PlayerPawn.h"

// Called when the game starts or when spawned
void AEnemyBullet::BeginPlay()
{
	Super::BeginPlay();

	// Add dynamic on hit binding
	CapsuleComponent->OnComponentBeginOverlap.AddDynamic(this, &AEnemyBullet::OnOverlapBegin);
}

void AEnemyBullet::OnOverlapBegin(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Check if the other actor is the player
	if (OtherActor && OtherActor->ActorHasTag(FName(TEXT("Player")))) {
		APlayerPawn* Player = Cast<APlayerPawn>(OtherActor);
		if (Player->IsVulnerable()) {
			GameState->DecrementPlayerHealth();
			// TODO: Spawn particle effect and play sound effect

			DisableFromPool();
		}
	}
}