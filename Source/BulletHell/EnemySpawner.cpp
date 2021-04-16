// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySpawner.h"
#include "EnemyPawn.h"
#include "BulletHellGameStateBase.h"
#include "Engine/World.h"

// Sets default values for this component's properties
UEnemySpawner::UEnemySpawner()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UEnemySpawner::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UEnemySpawner::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

// Input x from 0 to 1 where 0 is left side of play area and 1 is right side
void UEnemySpawner::SpawnEnemyAtX(TSubclassOf<AEnemyPawn> EnemyClass, float x) {
	ABulletHellGameStateBase* GameState = Cast<ABulletHellGameStateBase>(GetWorld()->GetGameState());
	float xWorld = GameState->HorizontalFracToWorld(x);
	float yWorld = GameState->GetPlayAreaPlanePosition();
	float zWorld = GameState->VerticalFracToWorld(DefaultSpawnYFrac);

	AEnemyPawn* enemy = GetWorld()->SpawnActor<AEnemyPawn>(EnemyClass, {xWorld, yWorld, zWorld}, { 0,0,0 });
	enemy->SetOwner(this->GetOwner());

	UE_LOG(LogTemp, Warning, TEXT("Event called successfully."));
}

