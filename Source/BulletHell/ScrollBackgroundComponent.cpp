// Fill out your copyright notice in the Description page of Project Settings.


#include "ScrollBackgroundComponent.h"
#include "BulletHellGameStateBase.h"
#include "Engine/World.h"
#include "Math/UnrealMathUtility.h"

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

	TargetPosition = StartingPosition;

	Owner = this->GetOwner();
}


// Called every frame
void UScrollBackgroundComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	ABulletHellGameStateBase* GameState = Cast<ABulletHellGameStateBase>(GetWorld()->GetGameState());
	if (GameState->IsGameStarted() && !GameState->IsGameOver()) {
		ScrollHorizontal();

		ScrollVertical(DeltaTime);


		FVector NewLocation = FMath::Lerp(Owner->GetActorLocation(), TargetPosition, ScrollSpeed * DeltaTime);
		Owner->SetActorLocation(NewLocation);

		if (RestartMoving) {
			RestartMoving = false;
		}
	}

	if (GameState->IsGameRestartTransitioning()) {
		if (!RestartMoving) {
			RestartMoving = true;
			RestartMoveStartTime = GetWorld()->GetTimeSeconds();
			CurrentLengthScrolled = 0.0f;
			CurrentVerticalHeight = StartingPosition.Z;
			RestartFromPosition = TargetPosition;
			TargetPosition = StartingPosition;
		}

		float SmoothStepParameter = (GetWorld()->GetTimeSeconds() - RestartMoveStartTime) / RestartTransitionDuration;

		float LerpParameter = FMath::SmoothStep(0, 1, SmoothStepParameter);

		Owner->SetActorLocation(FMath::Lerp(RestartFromPosition, StartingPosition, LerpParameter));
	}
}


void UScrollBackgroundComponent::ScrollHorizontal() {
	ABulletHellGameStateBase* GameState = Cast<ABulletHellGameStateBase>(GetWorld()->GetGameState());

	// Horizontal position from -1 to 1
	float PlayerFracPosition = GameState->GetPlayerHorizontalFrac();
	float NewX = StartingPosition.X - (PlayerFracPosition * HorizontalPadding);

	FVector NewBackgroundPosition = { NewX, TargetPosition.Y, TargetPosition.Z };
	TargetPosition = NewBackgroundPosition;
}

void UScrollBackgroundComponent::ScrollVertical(float DeltaTime) {
	float AmountToScroll = 0;

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

	FVector NewBackgroundPosition = { TargetPosition.X, TargetPosition.Y, NewZ };
	TargetPosition = NewBackgroundPosition;
}