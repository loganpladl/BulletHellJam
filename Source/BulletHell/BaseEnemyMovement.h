// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BaseEnemyMovement.generated.h"

class APlayerPawn;
class ABulletHellGameStateBase;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable)
class BULLETHELL_API UBaseEnemyMovement : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBaseEnemyMovement();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void Move(float DeltaTime);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(category = "Movement", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float MoveSpeed = 500.0f;
	float AdjustedMoveSpeed;
	float MoveSpeedMultiplier;

	APlayerPawn* PlayerPawn;
	ABulletHellGameStateBase* GameState;
};
