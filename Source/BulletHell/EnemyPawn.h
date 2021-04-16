// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "EnemyPawn.generated.h"

class UBaseEnemyMovement;

/**
 * 
 */
UCLASS()
class BULLETHELL_API AEnemyPawn : public ABasePawn
{
	GENERATED_BODY()

public:
	AEnemyPawn();

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement Type", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UBaseEnemyMovement> MovementClass;
};

