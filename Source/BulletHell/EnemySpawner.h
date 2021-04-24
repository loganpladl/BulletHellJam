// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EnemySpawner.generated.h"

class AEnemyPawn;
class UBaseEnemyMovement;
class UBaseBulletPattern;


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BULLETHELL_API UEnemySpawner : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UEnemySpawner();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = "LevelEvents")
	void SpawnEnemyAtX(TSubclassOf<AEnemyPawn> EnemyClass, TSubclassOf<UBaseEnemyMovement> MovementClass, TSubclassOf<UBaseBulletPattern> BulletPattern, float x);

	UFUNCTION(BlueprintCallable, Category = "LevelEvents")
	void SpawnEnemyLeftAtY(TSubclassOf<AEnemyPawn> EnemyClass, TSubclassOf<UBaseEnemyMovement> MovementClass, TSubclassOf<UBaseBulletPattern> BulletPattern, float y);

	UFUNCTION(BlueprintCallable, Category = "LevelEvents")
	void SpawnEnemyRightAtY(TSubclassOf<AEnemyPawn> EnemyClass, TSubclassOf<UBaseEnemyMovement> MovementClass, TSubclassOf<UBaseBulletPattern> BulletPattern, float y);

	// R correlates to Frac as in below variables
	UFUNCTION(BlueprintCallable, Category = "LevelEvents")
	void SpawnNEnemiesAtXWithinR(TSubclassOf<AEnemyPawn> EnemyClass, TSubclassOf<UBaseEnemyMovement> MovementClass, TSubclassOf<UBaseBulletPattern> BulletPattern, float N, float X, float R);

	UFUNCTION(BlueprintCallable, Category = "LevelEvents")
	void SpawnBoss(TSubclassOf<AEnemyPawn> EnemyClass, TSubclassOf<UBaseEnemyMovement> MovementClass, TSubclassOf<UBaseBulletPattern> BulletPattern);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	// Default Vertical spawn position where 1 represents the top of the play area
	UPROPERTY(category = "Spawn", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float DefaultSpawnYFrac = 1.1f;
	
	// Default horiontal left spawn position where -1 represents the left of the play area
	UPROPERTY(category = "Spawn", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float DefaultSpawnLeftXFrac = -1.1f;

	// Default horizontal right spawn position where 1 represents the right of the play area
	UPROPERTY(category = "Spawn", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float DefaultSpawnRightXFrac = 1.1f;
};
