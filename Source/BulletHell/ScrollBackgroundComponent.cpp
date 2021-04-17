// Fill out your copyright notice in the Description page of Project Settings.


#include "ScrollBackgroundComponent.h"
#include "BulletHellGameStateBase.h"
#include "Engine/World.h"

// Sets default values for this component's properties
UScrollBackgroundComponent::UScrollBackgroundComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UScrollBackgroundComponent::BeginPlay()
{
	Super::BeginPlay();

	StartingPosition = this->GetOwner()->GetActorLocation();
	CurrentVerticalHeight = StartingPosition.Z;

	
}


// Called every frame
void UScrollBackgroundComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	ScrollHorizontal();

	ScrollVertical(DeltaTime);
}


void UScrollBackgroundComponent::ScrollHorizontal() {
	AActor* Owner = this->GetOwner();
	FVector CurrentBackgroundPosition = Owner->GetActorLocation();

	ABulletHellGameStateBase* GameState = Cast<ABulletHellGameStateBase>(GetWorld()->GetGameState());

	// Horizontal position from -1 to 1
	float PlayerFracPosition = GameState->GetPlayerHorizontalFrac();
	float NewX = StartingPosition.X - (PlayerFracPosition * HorizontalPadding);

	FVector NewBackgroundPosition = { NewX, CurrentBackgroundPosition.Y, CurrentBackgroundPosition.Z };
	Owner->SetActorLocation(NewBackgroundPosition);
}

void UScrollBackgroundComponent::ScrollVertical(float DeltaTime) {
	float AmountToScroll = 0;

	AActor* Owner = this->GetOwner();
	FVector CurrentBackgroundPosition = Owner->GetActorLocation();

	// Scroll over time
	if (CurrentLengthScrolled < VerticalScrollLength) {
		AmountToScroll = VerticalScrollSpeed * DeltaTime;
		
		CurrentLengthScrolled += AmountToScroll;
	}
	float NewZ = CurrentVerticalHeight - AmountToScroll;
	CurrentVerticalHeight = NewZ;

	// Scroll depending on player position
	ABulletHellGameStateBase* GameState = Cast<ABulletHellGameStateBase>(GetWorld()->GetGameState());
	// Vertical position from -1 to 1
	float PlayerFracPosition = GameState->GetPlayerVerticalFrac();
	NewZ = CurrentVerticalHeight - (PlayerFracPosition * VerticalPadding);

	FVector NewBackgroundPosition = { CurrentBackgroundPosition.X, CurrentBackgroundPosition.Y, NewZ };
	Owner->SetActorLocation(NewBackgroundPosition);
}