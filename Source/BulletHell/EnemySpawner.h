// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EnemySpawner.generated.h"

class AEnemyPawn;


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
	void SpawnEnemyAtX(TSubclassOf<AEnemyPawn> EnemyClass, float x);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	// Default Vertical spawn position where 1 represents the top of the play area
	UPROPERTY(category = "Spawn", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float DefaultSpawnYFrac = 1.1f;
	
};
