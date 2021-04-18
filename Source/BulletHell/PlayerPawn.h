// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "PlayerPawn.generated.h"

struct FVector;

/**
 * 
 */
UCLASS()
class BULLETHELL_API APlayerPawn : public ABasePawn
{
	GENERATED_BODY()


private:
	// Input Delegates
	void InputMoveVertical(float Value);
	void InputMoveHorizontal(float Value);
	void InputShootPressed();
	void InputShootReleased();
	void InputFocusPressed();
	void InputFocusReleased();

	FVector MoveDirection = { 0,0,0 };

	bool IsShooting = false;
	bool IsMovingSlow = false;

	UPROPERTY(category = "Movement", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float MoveSpeedNormal = 1000.0f;

	// More precision movement if the player is holding a given button
	UPROPERTY(category = "Movement", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float MoveSpeedSlow = 500.0f;

	void Move(float DeltaTime);

	float MinX, MaxX, MinZ, MaxZ;

	void ClampPosition();

	FVector RespawnPosition;



public:
	APlayerPawn();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void Disable();
	void Enable();

	void Respawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
