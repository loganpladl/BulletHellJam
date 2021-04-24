// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Containers/Array.h"
#include "Math/Rotator.h"
#include "Math/Vector.h"
#include "BulletPool.generated.h"

class ABaseBullet;

UCLASS()
class BULLETHELL_API ABulletPool : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABulletPool();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	ABaseBullet* Instantiate(FVector StartPos, FRotator Rotation, FVector StartVelocity);

	void Disable(ABaseBullet* Bullet);

	UFUNCTION(BlueprintCallable)
	void DisableAllBullets();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// How many bullets to store in a pool.
	UPROPERTY(Category = "Bullets", EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	int Count;

private:
	UPROPERTY(Category = "Bullets", EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<ABaseBullet> BulletType;

	TArray<ABaseBullet*> Pool;
	TArray<ABaseBullet*> ActiveBullets;


};
