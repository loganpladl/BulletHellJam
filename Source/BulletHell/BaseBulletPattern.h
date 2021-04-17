// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Math/Vector.h"
#include "Math/Rotator.h"
#include "BaseBulletPattern.generated.h"

class ABulletPool;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable )
class BULLETHELL_API UBaseBulletPattern : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBaseBulletPattern();

	void Fire();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:

	// Bullet pool to draw from. Dictates the type of bullets spawned.
	UPROPERTY(Category = "Bullet Pool", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<ABulletPool> BulletPoolType;

	// Pointer to instantiated bullet pool, retrieved in BeginPlay
	ABulletPool* BulletPool;

	UPROPERTY(Category = "Bullet Pool", EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	int32 BulletStreamsPerSection = 1;

	// Angle containing a stream
	UPROPERTY(Category = "Bullet Pool", EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float StreamAngle = 90; // in degrees

	UPROPERTY(Category = "Bullet Pool", EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	int32 BulletSections = 1;

	UPROPERTY(Category = "Bullet Pool", EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float AngleBetweenSections = 90.0f; // in degrees

	UPROPERTY(Category = "Bullet Pool", EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float MaxSpinSpeed = 30.0f;

	UPROPERTY(Category = "Bullet Pool", EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float SpinSpeedDelta = 0.0f;

	// Seconds per Shot
	UPROPERTY(Category = "Bullet Pool", EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float FireRate = .3f;

	UPROPERTY(Category = "Bullet Pool", EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float BulletSpeed = 100.0f;

	UPROPERTY(Category = "Bullet Pool", EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float InitialAngle = 270.0f;

	USceneComponent* SpawnPointComponent = nullptr;

	float ShotTimer;
	float CurrentAngle;
};
