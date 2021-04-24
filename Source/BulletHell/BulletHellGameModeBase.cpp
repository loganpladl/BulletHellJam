// Copyright Epic Games, Inc. All Rights Reserved.


#include "BulletHellGameModeBase.h"

ABulletHellGameModeBase::ABulletHellGameModeBase() {
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void ABulletHellGameModeBase::BeginPlay() {
	Super::BeginPlay();

	HandleGameStart(); // initialization
}

void ABulletHellGameModeBase::PlayerDied() {

}

void ABulletHellGameModeBase::HandleGameStart() {
	GameStart();
}

void ABulletHellGameModeBase::HandleGameOver() {
	GameOver();
}