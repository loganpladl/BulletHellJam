// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySpawner.h"
#include "EnemyPawn.h"
#include "BulletHellGameStateBase.h"
#include "Engine/World.h"
#include "BaseEnemyMovement.h"
#include "UObject/UObjectGlobals.h"

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
void UEnemySpawner::SpawnEnemyAtX(TSubclassOf<AEnemyPawn> EnemyClass, TSubclassOf<UBaseEnemyMovement> MovementClass, float x) {
	ABulletHellGameStateBase* GameState = Cast<ABulletHellGameStateBase>(GetWorld()->GetGameState());
	float XWorld = GameState->HorizontalFracToWorld(x);
	float YWorld = GameState->GetPlayAreaPlanePosition();
	float ZWorld = GameState->VerticalFracToWorld(DefaultSpawnYFrac);

	AEnemyPawn* Enemy = GetWorld()->SpawnActor<AEnemyPawn>(EnemyClass, {XWorld, YWorld, ZWorld}, { 0,0,0 });
	Enemy->SetOwner(this->GetOwner());


	UBaseEnemyMovement* MovementComponent = NewObject<UBaseEnemyMovement>(Enemy, MovementClass, TEXT("MovementComponent"));
	if (MovementComponent) {
		MovementComponent->RegisterComponent();
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Could not create movement component."));
	}
	

	UE_LOG(LogTemp, Warning, TEXT("Event called successfully."));
}