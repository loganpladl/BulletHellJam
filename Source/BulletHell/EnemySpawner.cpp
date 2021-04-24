// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySpawner.h"
#include "EnemyPawn.h"
#include "BulletHellGameStateBase.h"
#include "Engine/World.h"
#include "BaseEnemyMovement.h"
#include "UObject/UObjectGlobals.h"
#include "BaseBulletPattern.h"
#include "Math/UnrealMathUtility.h"
#include "Boss.h"

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
void UEnemySpawner::SpawnEnemyAtX(TSubclassOf<AEnemyPawn> EnemyClass, TSubclassOf<UBaseEnemyMovement> MovementClass, TSubclassOf<UBaseBulletPattern> BulletPattern, float x) {
	ABulletHellGameStateBase* GameState = Cast<ABulletHellGameStateBase>(GetWorld()->GetGameState());
	float XWorld = GameState->HorizontalFracToWorld(x);
	float YWorld = GameState->GetPlayAreaPlanePosition();
	float ZWorld = GameState->VerticalFracToWorld(DefaultSpawnYFrac);

	AEnemyPawn* Enemy = GetWorld()->SpawnActor<AEnemyPawn>(EnemyClass, {XWorld, YWorld, ZWorld}, { 0,0,0 });
	Enemy->SetOwner(this->GetOwner());

	if (!MovementClass) {
		UE_LOG(LogTemp, Warning, TEXT("No movement class set."));
		return;
	}

	UBaseEnemyMovement* MovementComponent = NewObject<UBaseEnemyMovement>(Enemy, MovementClass, TEXT("MovementComponent"));
	if (MovementComponent) {
		MovementComponent->RegisterComponent();
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Could not create movement component."));
	}


	if (!BulletPattern) {
		UE_LOG(LogTemp, Warning, TEXT("No bullet pattern set."));
		return;
	}

	UBaseBulletPattern* BulletPatternComponent = NewObject<UBaseBulletPattern>(Enemy, BulletPattern, TEXT("BulletPatternComponent"));
	if (BulletPatternComponent) {
		BulletPatternComponent->RegisterComponent();
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Could not create bullet pattern component."));
	}
}

void UEnemySpawner::SpawnEnemyLeftAtY(TSubclassOf<AEnemyPawn> EnemyClass, TSubclassOf<UBaseEnemyMovement> MovementClass, TSubclassOf<UBaseBulletPattern> BulletPattern, float y) {
	ABulletHellGameStateBase* GameState = Cast<ABulletHellGameStateBase>(GetWorld()->GetGameState());
	float XWorld = GameState->HorizontalFracToWorld(DefaultSpawnLeftXFrac);
	float YWorld = GameState->GetPlayAreaPlanePosition();
	float ZWorld = GameState->VerticalFracToWorld(y);

	AEnemyPawn* Enemy = GetWorld()->SpawnActor<AEnemyPawn>(EnemyClass, { XWorld, YWorld, ZWorld }, { 0,0,0 });
	Enemy->SetOwner(this->GetOwner());

	if (!MovementClass) {
		UE_LOG(LogTemp, Warning, TEXT("No movement class set."));
		return;
	}

	UBaseEnemyMovement* MovementComponent = NewObject<UBaseEnemyMovement>(Enemy, MovementClass, TEXT("MovementComponent"));
	if (MovementComponent) {
		MovementComponent->RegisterComponent();
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Could not create movement component."));
	}


	if (!BulletPattern) {
		UE_LOG(LogTemp, Warning, TEXT("No bullet pattern set."));
		return;
	}

	UBaseBulletPattern* BulletPatternComponent = NewObject<UBaseBulletPattern>(Enemy, BulletPattern, TEXT("BulletPatternComponent"));
	if (BulletPatternComponent) {
		BulletPatternComponent->RegisterComponent();
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Could not create bullet pattern component."));
	}
}

void UEnemySpawner::SpawnEnemyRightAtY(TSubclassOf<AEnemyPawn> EnemyClass, TSubclassOf<UBaseEnemyMovement> MovementClass, TSubclassOf<UBaseBulletPattern> BulletPattern, float y) {
	ABulletHellGameStateBase* GameState = Cast<ABulletHellGameStateBase>(GetWorld()->GetGameState());
	float XWorld = GameState->HorizontalFracToWorld(DefaultSpawnRightXFrac);
	float YWorld = GameState->GetPlayAreaPlanePosition();
	float ZWorld = GameState->VerticalFracToWorld(y);

	AEnemyPawn* Enemy = GetWorld()->SpawnActor<AEnemyPawn>(EnemyClass, { XWorld, YWorld, ZWorld }, { 0,0,0 });
	Enemy->SetOwner(this->GetOwner());

	if (!MovementClass) {
		UE_LOG(LogTemp, Warning, TEXT("No movement class set."));
		return;
	}

	UBaseEnemyMovement* MovementComponent = NewObject<UBaseEnemyMovement>(Enemy, MovementClass, TEXT("MovementComponent"));
	if (MovementComponent) {
		MovementComponent->RegisterComponent();
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Could not create movement component."));
	}


	if (!BulletPattern) {
		UE_LOG(LogTemp, Warning, TEXT("No bullet pattern set."));
		return;
	}

	UBaseBulletPattern* BulletPatternComponent = NewObject<UBaseBulletPattern>(Enemy, BulletPattern, TEXT("BulletPatternComponent"));
	if (BulletPatternComponent) {
		BulletPatternComponent->RegisterComponent();
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Could not create bullet pattern component."));
	}
}

void UEnemySpawner::SpawnNEnemiesAtXWithinR(TSubclassOf<AEnemyPawn> EnemyClass, TSubclassOf<UBaseEnemyMovement> MovementClass, TSubclassOf<UBaseBulletPattern> BulletPattern, float N, float X, float R) {
	for (int i = 0; i < N; i++) {
		float RandX = FMath::RandRange(0.0f - R, R);
		float RandY = FMath::RandRange(0.0f - R, R);
		ABulletHellGameStateBase* GameState = Cast<ABulletHellGameStateBase>(GetWorld()->GetGameState());
		float XWorld = GameState->HorizontalFracToWorld(X + RandX);
		float YWorld = GameState->GetPlayAreaPlanePosition();
		float ZWorld = GameState->VerticalFracToWorld(DefaultSpawnRightXFrac + RandY);

		AEnemyPawn* Enemy = GetWorld()->SpawnActor<AEnemyPawn>(EnemyClass, { XWorld, YWorld, ZWorld }, { 0,0,0 });
		Enemy->SetOwner(this->GetOwner());

		if (!MovementClass) {
			UE_LOG(LogTemp, Warning, TEXT("No movement class set."));
			return;
		}

		UBaseEnemyMovement* MovementComponent = NewObject<UBaseEnemyMovement>(Enemy, MovementClass, TEXT("MovementComponent"));
		if (MovementComponent) {
			MovementComponent->RegisterComponent();
		}
		else {
			UE_LOG(LogTemp, Warning, TEXT("Could not create movement component."));
		}


		if (!BulletPattern) {
			UE_LOG(LogTemp, Warning, TEXT("No bullet pattern set."));
			return;
		}

		UBaseBulletPattern* BulletPatternComponent = NewObject<UBaseBulletPattern>(Enemy, BulletPattern, TEXT("BulletPatternComponent"));
		if (BulletPatternComponent) {
			BulletPatternComponent->RegisterComponent();
		}
		else {
			UE_LOG(LogTemp, Warning, TEXT("Could not create bullet pattern component."));
		}
	}
}

void UEnemySpawner::SpawnBoss(TSubclassOf<AEnemyPawn> EnemyClass, TSubclassOf<UBaseEnemyMovement> MovementClass, TSubclassOf<UBaseBulletPattern> BulletPattern) {
	ABulletHellGameStateBase* GameState = Cast<ABulletHellGameStateBase>(GetWorld()->GetGameState());
	float XWorld = GameState->HorizontalFracToWorld(0);
	float YWorld = GameState->GetPlayAreaPlanePosition();
	float ZWorld = GameState->VerticalFracToWorld(DefaultSpawnRightXFrac + .3);

	AEnemyPawn* Enemy = GetWorld()->SpawnActor<AEnemyPawn>(EnemyClass, { XWorld, YWorld, ZWorld }, { 0,0,0 });
	Enemy->SetOwner(this->GetOwner());

	if (!MovementClass) {
		UE_LOG(LogTemp, Warning, TEXT("No movement class set."));
		return;
	}

	UBaseEnemyMovement* MovementComponent = NewObject<UBaseEnemyMovement>(Enemy, MovementClass, TEXT("MovementComponent"));
	if (MovementComponent) {
		MovementComponent->RegisterComponent();
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Could not create movement component."));
	}


	if (!BulletPattern) {
		UE_LOG(LogTemp, Warning, TEXT("No bullet pattern set."));
		return;
	}

	UBaseBulletPattern* BulletPatternComponent = NewObject<UBaseBulletPattern>(Enemy, BulletPattern, TEXT("BulletPatternComponent"));
	if (BulletPatternComponent) {
		BulletPatternComponent->RegisterComponent();
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Could not create bullet pattern component."));
	}
}