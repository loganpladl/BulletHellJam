// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Math/Vector.h"
#include "BulletHellGameStateBase.h"
#include "BaseBullet.generated.h"

class UCapsuleComponent;
class UPaperFlipbookComponent;

UCLASS()
class BULLETHELL_API ABaseBullet : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseBullet();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Disable();
	void Enable();

	void SetVelocity(FVector NewVelocity);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void Move(float DeltaTime);

private:
	UPROPERTY(Category = "Components", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UCapsuleComponent* CapsuleComponent;

	UPROPERTY(Category = "Components", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UPaperFlipbookComponent* FlipbookComponent;

	FVector CurrentVelocity = { 0,0,0 };

	void CheckBounds();

	ABulletHellGameStateBase* GameState;

	UFUNCTION()
	void OnHit;
};
