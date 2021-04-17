// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseBulletPattern.h"
#include "BulletPool.h"
#include "Components/SceneComponent.h"
#include "Math/UnrealMathUtility.h"
#include "EngineUtils.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UBaseBulletPattern::UBaseBulletPattern()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
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
	
	ShotTimer = FireRate;
	CurrentAngle = InitialAngle;
}


// Called every frame
void UBaseBulletPattern::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	ShotTimer -= DeltaTime;
	if (ShotTimer <= 0) {
		Fire();
		ShotTimer = FireRate;
	}

	
}

void UBaseBulletPattern::Fire() {
	if (BulletPool && SpawnPointComponent) {

		FVector SpawnPosition = SpawnPointComponent->GetComponentLocation();

		float AngleBetweenStreams = StreamAngle / BulletStreamsPerSection;

		float Angle;
		// Spawn each section
		for (int i = 0; i < BulletSections; i++) {
			Angle = CurrentAngle + AngleBetweenSections * i;

			// Spawn each stream
			for (int j = 0; j < BulletStreamsPerSection; j++) {
				float Cos, Sin;

				FMath::SinCos(&Sin, &Cos, FMath::DegreesToRadians(Angle));

				FVector Velocity = { Cos * BulletSpeed, 0, Sin * BulletSpeed };
				FRotator Rotation = Velocity.Rotation();

				BulletPool->Instantiate(SpawnPosition, Rotation, Velocity);

				Angle += AngleBetweenStreams;
			}
		}
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("No bullet pool assigned to bullet pattern."));
	}
}

