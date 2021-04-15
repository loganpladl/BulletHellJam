// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePawn.h"
#include "Components/SphereComponent.h"
#include "PaperFlipbookComponent.h"

// Sets default values
ABasePawn::ABasePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Collider"));
	RootComponent = SphereComponent;

	FlipbookComponent = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("Base Flipbook"));
	FlipbookComponent->SetupAttachment(SphereComponent);
}

