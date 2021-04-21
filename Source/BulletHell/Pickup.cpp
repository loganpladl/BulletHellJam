// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickup.h"
#include "PlayerPawn.h"
#include "BulletHellGameStateBase.h"

// Sets default values. Need default constructor
APickup::APickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
	RootComponent = CapsuleComponent;

	FlipbookComponent = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("Base Flipbook"));
	FlipbookComponent->SetupAttachment(CapsuleComponent);

	Buff1FlipbookComponent = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("Buff 1"));
	Buff1FlipbookComponent->SetupAttachment(CapsuleComponent);

	Buff2FlipbookComponent = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("Buff 2"));
	Buff2FlipbookComponent->SetupAttachment(CapsuleComponent);
}


void APickup::Initialize(PlayerRank PRank, EnemyRank ERank)
{
	switch (PRank) {
	case PlayerRank::Health:
		Buff1FlipbookComponent->SetFlipbook(HealthFlipbookPlayer);
		break;
	case PlayerRank::Damage:
		Buff1FlipbookComponent->SetFlipbook(DamageFlipbookPlayer);
		break;
	case PlayerRank::Speed:
		Buff1FlipbookComponent->SetFlipbook(SpeedFlipbookPlayer);
		break;
	case PlayerRank::BulletSpread:
		Buff1FlipbookComponent->SetFlipbook(BulletSpreadFlipbookPlayer);
		break;
	case PlayerRank::FireRate:
		Buff1FlipbookComponent->SetFlipbook(FireRateFlipbookPlayer);
		break;
	}

	switch (ERank) {
	case EnemyRank::Health:
		Buff2FlipbookComponent->SetFlipbook(HealthFlipbookEnemy);
		break;
	case EnemyRank::Damage:
		Buff2FlipbookComponent->SetFlipbook(DamageFlipbookEnemy);
		break;
	case EnemyRank::Speed:
		Buff2FlipbookComponent->SetFlipbook(SpeedFlipbookEnemy);
		break;
	case EnemyRank::BulletSpeed:
		Buff2FlipbookComponent->SetFlipbook(BulletSpeedFlipbookEnemy);
		break;
	case EnemyRank::FireRate:
		Buff2FlipbookComponent->SetFlipbook(FireRateFlipbookEnemy);
		break;
	}
}

// Called when the game starts or when spawned
void APickup::BeginPlay()
{
	Super::BeginPlay();
	
	GameState = Cast<ABulletHellGameStateBase>(GetWorld()->GetGameState());

	// Add dynamic on hit binding
	CapsuleComponent->OnComponentBeginOverlap.AddDynamic(this, &APickup::OnOverlapBegin);
}

// Called every frame
void APickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector Location = this->GetActorLocation();

	this->SetActorLocation({ Location.X, Location.Y, Location.Z - MoveSpeed * DeltaTime });
}

void APickup::OnOverlapBegin(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Check if the other actor is the player
	if (OtherActor && OtherActor->ActorHasTag(FName(TEXT("Player")))) {
		APlayerPawn* Player = Cast<APlayerPawn>(OtherActor);
		// TODO: Increment corresponding rank in gamestate
		GameState = Cast<ABulletHellGameStateBase>(GetWorld()->GetGameState());

		GameState->ClearBuffPickups();
		
		// TODO: Spawn particle effect and play sound effect

		this->Destroy();
	}
}