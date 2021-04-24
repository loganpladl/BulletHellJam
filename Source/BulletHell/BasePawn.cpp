// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePawn.h"
#include "Components/CapsuleComponent.h"
#include "Components/SceneComponent.h"

// Sets default values
ABasePawn::ABasePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
	RootComponent = CapsuleComponent;

	FlipbookComponent = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("Base Flipbook"));
	FlipbookComponent->SetupAttachment(CapsuleComponent);

	BulletSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Bullet Spawn Point"));
	BulletSpawnPoint->SetupAttachment(CapsuleComponent);

	FireAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("Fire Audio"));
	FireAudioComponent->SetupAttachment(CapsuleComponent);

	DamagedAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("Damaged Audio"));
	DamagedAudioComponent->SetupAttachment(CapsuleComponent);

	DeathAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("Death Audio"));
	DeathAudioComponent->SetupAttachment(CapsuleComponent);
}