// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseBullet.h"
#include "Components/CapsuleComponent.h"
#include "PaperFlipbookComponent.h"
#include "BulletPool.h"

// Sets default values
ABaseBullet::ABaseBullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
	RootComponent = CapsuleComponent;

	FlipbookComponent = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("Base Flipbook"));
	FlipbookComponent->SetupAttachment(CapsuleComponent);

}

// Called when the game starts or when spawned
void ABaseBullet::BeginPlay()
{
	Super::BeginPlay();

	GameState = Cast<ABulletHellGameStateBase>(GetWorld()->GetGameState());
}

// Called every frame
void ABaseBullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Move(DeltaTime);

	CheckBounds();
}

void ABaseBullet::Disable() {
	this->SetActorHiddenInGame(true);

	// Disables collision components
	this->SetActorEnableCollision(false);

	// Stops the Actor from ticking
	this->SetActorTickEnabled(false);
}

void ABaseBullet::Enable() {
	this->SetActorHiddenInGame(false);

	// Disables collision components
	this->SetActorEnableCollision(true);

	// Stops the Actor from ticking
	this->SetActorTickEnabled(true);
}

void ABaseBullet::SetVelocity(FVector NewVelocity) {
	CurrentVelocity = NewVelocity;
}

void ABaseBullet::Move(float DeltaTime) {
	FVector CurrentLocation = this->GetActorLocation();
	this->SetActorLocation(CurrentLocation + (CurrentVelocity * DeltaTime), true);
}

void ABaseBullet::CheckBounds() {
	bool IsOutOfBounds = GameState->IsOutOfBounds(this->GetActorLocation());

	// Disable this bullet
	if (IsOutOfBounds) {
		DisableFromPool();
	}
}

void ABaseBullet::OnOverlapBegin(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}

void ABaseBullet::DisableFromPool() {
	AActor* PtrOwner = this->GetOwner();
	if (!PtrOwner) {
		UE_LOG(LogTemp, Warning, TEXT("Couldn't find owner."));
	}

	ABulletPool* Pool = Cast<ABulletPool>(PtrOwner);

	Pool->Disable(this);
}