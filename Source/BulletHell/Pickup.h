// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/CapsuleComponent.h"
#include "PaperFlipbookComponent.h"
#include "PaperFlipbook.h"
#include "Pickup.generated.h"

class ABulletHellGameStateBase;
enum class PlayerRank;
enum class EnemyRank;


UCLASS()
class BULLETHELL_API APickup : public AActor
{
	GENERATED_BODY()
	
public:	
	APickup();

	void Initialize(PlayerRank PRank, EnemyRank ERank);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(Category = "Components", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UCapsuleComponent* CapsuleComponent;

	UPROPERTY(Category = "Components", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UPaperFlipbookComponent* FlipbookComponent;

	UPROPERTY(Category = "Components", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UPaperFlipbookComponent* Buff1FlipbookComponent;

	UPROPERTY(Category = "Components", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UPaperFlipbookComponent* Buff2FlipbookComponent;

	UPROPERTY(Category = "Flipbooks", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UPaperFlipbook* HealthFlipbookPlayer;
	UPROPERTY(Category = "Flipbooks", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UPaperFlipbook* DamageFlipbookPlayer;
	UPROPERTY(Category = "Flipbooks", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UPaperFlipbook* SpeedFlipbookPlayer;
	UPROPERTY(Category = "Flipbooks", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UPaperFlipbook* BulletSpreadFlipbookPlayer;
	UPROPERTY(Category = "Flipbooks", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UPaperFlipbook* FireRateFlipbookPlayer;

	UPROPERTY(Category = "Flipbooks", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UPaperFlipbook* HealthFlipbookEnemy;
	UPROPERTY(Category = "Flipbooks", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UPaperFlipbook* DamageFlipbookEnemy;
	UPROPERTY(Category = "Flipbooks", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UPaperFlipbook* SpeedFlipbookEnemy;
	UPROPERTY(Category = "Flipbooks", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UPaperFlipbook* FireRateFlipbookEnemy;
	UPROPERTY(Category = "Flipbooks", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UPaperFlipbook* BulletSpeedFlipbookEnemy;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Move();

	bool IsOffScreenBottom();

	UFUNCTION()
	virtual void OnOverlapBegin(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:
	ABulletHellGameStateBase* GameState;

	UPROPERTY(Category = "Movement", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float MoveSpeed = 200.0f;

	// Increment corresponding ranks in gamestate
	void IncrementCorrespondingRanks();
};
