// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyBulletPattern.h"
#include "BulletHellGameStateBase.h"
#include "EnemyPawn.h"

void UEnemyBulletPattern::PlayFireSound() {
	AEnemyPawn* Enemy = Cast<AEnemyPawn>(this->GetOwner());
	Enemy->PlayFireSound();
}

float UEnemyBulletPattern::GetSpeedMultiplier() {
	ABulletHellGameStateBase* GameState = Cast<ABulletHellGameStateBase>(GetWorld()->GetGameState());

	return GameState->GetEnemyBulletSpeedMultiplier();
}

float UEnemyBulletPattern::GetFireRateMultiplier() {
	ABulletHellGameStateBase* GameState = Cast<ABulletHellGameStateBase>(GetWorld()->GetGameState());

	return GameState->GetEnemyFireRateMultiplier();
}