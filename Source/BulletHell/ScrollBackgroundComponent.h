// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Math/Vector.h"
#include "ScrollBackgroundComponent.generated.h"

// Used for a single background scroll, no repetition
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BULLETHELL_API UScrollBackgroundComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UScrollBackgroundComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	// The extra space on each side of the background
	UPROPERTY(Category = "Background Scrolling", EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	int32 HorizontalPadding = 90;

	UPROPERTY(Category = "Background Scrolling", EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	int32 VerticalPadding = 135;

	// Vertical Scroll in pixels per second
	UPROPERTY(Category = "Background Scrolling", EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float VerticalScrollSpeed = 25.0f;

	// Total length to scroll vertically before stopping
	// Can calculate by subtracting 1080 from sprite height
	UPROPERTY(Category = "Background Scrolling", EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	int VerticalScrollLength = 3770;

	// Vertical height before panning from movement
	float CurrentVerticalHeight = 0.0f;

	FVector StartingPosition;
	float CurrentLengthScrolled = 0.0f;

	void ScrollHorizontal();

	void ScrollVertical(float DeltaTime);

	// Location to lerp to
	FVector TargetPosition;

	FVector RestartFromPosition;

	UPROPERTY(Category = "Background Scrolling", EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float ScrollSpeed = 1.25f;

	AActor* Owner;

	float RestartTransitionDuration = 3.0f;

	bool RestartMoving = false;

	float RestartMoveStartTime;
};
