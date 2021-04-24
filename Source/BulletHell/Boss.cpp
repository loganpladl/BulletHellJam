// Fill out your copyright notice in the Description page of Project Settings.


#include "Boss.h"
#include "BulletHellGameStateBase.h"

void ABoss::BeginPlay() {
	Super::BeginPlay();

	GameState->BossSpawn();
}

void ABoss::Die() {
	GameState->KillBoss();

	bool Result = this->Destroy();
	PlayDeathSound();
}