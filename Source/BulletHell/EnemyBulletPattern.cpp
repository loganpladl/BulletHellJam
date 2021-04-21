// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyBulletPattern.h"
#include "EnemyPawn.h"

void UEnemyBulletPattern::PlayFireSound() {
	AEnemyPawn* Enemy = Cast<AEnemyPawn>(this->GetOwner());
	Enemy->PlayFireSound();
}