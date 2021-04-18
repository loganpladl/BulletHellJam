// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "PlayerPawn.generated.h"

struct FVector;

class UPlayerBulletPattern;

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

	UPROPERTY(Category = "Bullet Patterns", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UPlayerBulletPattern> BulletPatternRank0Type;

	UPROPERTY(Category = "Bullet Patterns", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UPlayerBulletPattern> BulletPatternRank1Type;

	UPROPERTY(Category = "Bullet Patterns", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UPlayerBulletPattern> BulletPatternRank2Type;

	UPROPERTY(Category = "Bullet Patterns", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UPlayerBulletPattern> BulletPatternRank3Type;

	UPROPERTY(Category = "Bullet Patterns", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UPlayerBulletPattern> BulletPatternRank4Type;

	UPROPERTY(Category = "Bullet Patterns", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UPlayerBulletPattern> BulletPatternRank5Type;

	UPlayerBulletPattern* BulletPatternRank0Component;
	UPlayerBulletPattern* BulletPatternRank1Component;
	UPlayerBulletPattern* BulletPatternRank2Component;
	UPlayerBulletPattern* BulletPatternRank3Component;
	UPlayerBulletPattern* BulletPatternRank4Component;
	UPlayerBulletPattern* BulletPatternRank5Component;

	int32 CurrentBulletPatternRank = 0;

	void Move(float DeltaTime);

	void Fire(float DeltaTime);

	float MinX, MaxX, MinZ, MaxZ;

	void ClampPosition();

	FVector RespawnPosition;

	bool Invulnerable = false;

	void CreateBulletPatterns();

public:
	APlayerPawn();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void Disable();
	void Enable();

	void Respawn();

	void MakeInvulnerable();
	void MakeVulnerable();

	bool IsVulnerable();

	void SetBulletPatternRank(int32 Rank) { CurrentBulletPatternRank = Rank; }

	UPlayerBulletPattern* GetCurrentBulletPatternComponent();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
