// Fill out your copyright notice in the Description page of Project Settings.


#include "BulletPool.h"
#include "BaseBullet.h"
#include "GameFramework/Actor.h"
#include "Engine/EngineTypes.h"

// Sets default values
ABulletPool::ABulletPool()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Pool = TArray<ABaseBullet*>();
	ActiveBullets = TArray<ABaseBullet*>();
}

// Called when the game starts or when spawned
void ABulletPool::BeginPlay()
{
	Super::BeginPlay();
	
	for (int i = 0; i < Count; i++) {
		ABaseBullet* Bullet = GetWorld()->SpawnActor<ABaseBullet>(BulletType, { 0, 0, 0 }, { 0,0,0 });

		FAttachmentTransformRules rules(EAttachmentRule::KeepWorld, false);

		Bullet->AttachToActor(this, rules);
		Bullet->SetOwner(this);
		Bullet->Disable();

		Pool.Add(Bullet);
	}
}

// Called every frame
void ABulletPool::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//UE_LOG(LogTemp, Display, TEXT("NumBullets: %i"), ActiveBullets.Num()); // Display current number of active bullets for testing purposes
}

ABaseBullet* ABulletPool::Instantiate(FVector StartPos, FRotator Rotation, FVector StartVelocity) {
	if (Pool.Num() == 0) {
		UE_LOG(LogTemp, Error, TEXT("Bullet Pool empty."));
		return nullptr;
	}
	
	ABaseBullet* Bullet = Pool[0];
	Bullet->Enable();
	Bullet->SetActorLocation(StartPos, false);
	Bullet->SetActorRotation(Rotation);
	Bullet->SetVelocity(StartVelocity);	

	Pool.RemoveAt(0);
	ActiveBullets.Add(Bullet);

	return Bullet;
}

void ABulletPool::Disable(ABaseBullet* Bullet) {
	Bullet->Disable();
	Bullet->SetActorLocation({ 0,0,0 }, false); // Set actor to origin for organization
	
	ActiveBullets.RemoveSingle(Bullet);
	Pool.Add(Bullet);
}

void ABulletPool::DisableAllBullets() {
	for (ABaseBullet* Bullet : ActiveBullets) {
		Bullet->Disable();
		Bullet->SetActorLocation({ 0,0,0 }, false); // Set actor to origin for organization
		Pool.Add(Bullet);
	}

	ActiveBullets.Empty();
}