// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseEnemyMovement.h"
#include "PlayerPawn.h"
#include "Engine/World.h"
#include "BulletHellGameStateBase.h"

// Sets default values for this component's properties
UBaseEnemyMovement::UBaseEnemyMovement()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UBaseEnemyMovement::BeginPlay()
{
	Super::BeginPlay();

	PlayerPawn = Cast<APlayerPawn>(GetWorld()->GetFirstPlayerController()->GetPawn());
	GameState = Cast<ABulletHellGameStateBase>(GetWorld()->GetGameState());
}


// Called every frame
void UBaseEnemyMovement::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	MoveSpeedMultiplier = GameState->GetEnemySpeedMultiplier();
	AdjustedMoveSpeed = MoveSpeed * MoveSpeedMultiplier;

	Move(DeltaTime);
}

// To be overriden by derived classes
void UBaseEnemyMovement::Move(float DeltaTime) {

}

