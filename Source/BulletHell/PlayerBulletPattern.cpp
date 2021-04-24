// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerBulletPattern.h"
#include "BulletHellGameStateBase.h"
#include "PlayerPawn.h"

void UPlayerBulletPattern::PlayFireSound() {
	APlayerPawn* Player = Cast<APlayerPawn>(this->GetOwner());
	Player->PlayFireSound();
}

float UPlayerBulletPattern::GetSpeedMultiplier() {
	return 1;
}

float UPlayerBulletPattern::GetFireRateMultiplier() {
	ABulletHellGameStateBase* GameState = Cast<ABulletHellGameStateBase>(GetWorld()->GetGameState());

	return GameState->GetPlayerFireRateMultiplier();
}