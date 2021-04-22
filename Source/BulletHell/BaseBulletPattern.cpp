// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseBulletPattern.h"
#include "BulletPool.h"
#include "Components/SceneComponent.h"
#include "Math/UnrealMathUtility.h"
#include "EngineUtils.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "BulletHellGameStateBase.h"

// Sets default values for this component's properties
UBaseBulletPattern::UBaseBulletPattern()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	AdjustedFireRate = FireRate;
}


// Called when the game starts
void UBaseBulletPattern::BeginPlay()
{
	Super::BeginPlay();

	// Get instantiated Bullet Pool based on input type
	TArray<AActor*> OutActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), BulletPoolType, OutActors);

	BulletPool = Cast<ABulletPool>(OutActors[0]);


	AActor* Owner = this->GetOwner();

	TArray<UActorComponent*> Components;
	Owner->GetComponents(Components);
	for (UActorComponent* c : Components) {
		if (c->GetName() == "Bullet Spawn Point") {
			SpawnPointComponent = Cast<USceneComponent>(c);
		}
	}

	if (!SpawnPointComponent) {
		UE_LOG(LogTemp, Error, TEXT("Could not find bullet spawn point."));
		return;
	}
	
	ShotTimer = AdjustedFireRate;
	CurrentAngle = InitialAngle;

	Enabled = !StartDisabled;
}


// Called every frame
void UBaseBulletPattern::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	ShotTimer -= DeltaTime;


	if (!ReverseSpin) {
		CurrentSpinSpeed += SpinSpeedDelta * DeltaTime;
		if (CurrentSpinSpeed >= MaxSpinSpeed) {
			ReverseSpin = true;
		}
	}
	else {
		CurrentSpinSpeed += SpinSpeedDelta * DeltaTime;
		if (CurrentSpinSpeed <= -MaxSpinSpeed) {
			ReverseSpin = false;
		}
	}

	if (ShotTimer <= 0 && Enabled) {
		Fire();
		PlayFireSound();

		ABulletHellGameStateBase* GameState = Cast<ABulletHellGameStateBase>(GetWorld()->GetGameState());
		AdjustedFireRate = FireRate * (1 / GetFireRateMultiplier());
		ShotTimer = AdjustedFireRate;
	}

	
}

void UBaseBulletPattern::Fire() {
	if (BulletPool && SpawnPointComponent) {
		FVector SpawnPosition = SpawnPointComponent->GetComponentLocation();

		float AngleBetweenStreams;

		// Special case for circular angle to avoid double bullet stream at initial angle
		if (StreamAngle == 360) {
			AngleBetweenStreams = StreamAngle / BulletStreamsPerSection;
		}
		else {
			AngleBetweenStreams = StreamAngle / (BulletStreamsPerSection - 1);
		}

		
		// Rotate shots according to parent's orientation. Used for enemies that rotate.
		FRotator ParentRotation = this->GetOwner()->GetActorRotation();

		float Pitch = ParentRotation.Pitch;
		FVector ParentVector = ParentRotation.Vector();
		FVector Forward = this->GetOwner()->GetActorUpVector();

		if (ParentVector.X < 0) {
			if (Forward.Z < 0) {
				Pitch = 180 - Pitch;
			}
			else {
				Pitch = -Pitch;
			}
		}
		else {
			if (Forward.Z < 0) {
				Pitch = -180 + Pitch;
			}
		}

		CurrentAngle = InitialAngle + Pitch;

		float Angle;
		// Spawn each section
		for (int i = 0; i < BulletSections; i++) {
			Angle = CurrentAngle + AngleBetweenSections * i;

			// Spawn each stream
			for (int j = 0; j < BulletStreamsPerSection; j++) {
				float Cos, Sin;

				float RelativeAngle = Angle;

				FMath::SinCos(&Sin, &Cos, FMath::DegreesToRadians(RelativeAngle));

				float FinalSpeed = BulletSpeed * GetSpeedMultiplier();

				FVector Velocity = { Cos * FinalSpeed, 0, Sin * FinalSpeed };
				
				// Get rotation. Sprites are all oriented downwards, but we want to treat 0 degrees as facing rightward like in unit circle.
				// TODO: Definitely not the best way to do this, but capsule component is root component of bullets so I can't rotate that.
				FMath::SinCos(&Sin, &Cos, FMath::DegreesToRadians(RelativeAngle + 90));
				FVector Rotation = { Cos, 0, Sin };

				BulletPool->Instantiate(SpawnPosition, Rotation.Rotation(), Velocity);

				Angle += AngleBetweenStreams;
			}
		}
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("No bullet pool assigned to bullet pattern."));
	}
}

void UBaseBulletPattern::SetFireRateMultiplier() {

}

void UBaseBulletPattern::SetTargetAngle() {

}

void UBaseBulletPattern::SetBulletSpeedMultiplier() {

}

void UBaseBulletPattern::Enable() {
	Enabled = true;
}

void UBaseBulletPattern::Disable() {
	Enabled = false;
}

void UBaseBulletPattern::PlayFireSound() {

}

float UBaseBulletPattern::GetSpeedMultiplier() {
	return 1;
}

float UBaseBulletPattern::GetFireRateMultiplier() {
	return 1;
}