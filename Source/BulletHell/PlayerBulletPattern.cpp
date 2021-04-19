// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerBulletPattern.h"
#include "PlayerPawn.h"

void UPlayerBulletPattern::PlayFireSound() {
	APlayerPawn* Player = Cast<APlayerPawn>(this->GetOwner());
	Player->PlayFireSound();
}