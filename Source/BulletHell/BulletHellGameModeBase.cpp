// Copyright Epic Games, Inc. All Rights Reserved.


#include "BulletHellGameModeBase.h"

void ABulletHellGameModeBase::BeginPlay() {
	// Get references and win/lose conditions

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