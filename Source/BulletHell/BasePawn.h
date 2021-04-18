// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PaperFlipbookComponent.h"
#include "BasePawn.generated.h"

class UCapsuleComponent;
class UPaperFlipbookComponent;
class USceneComponent;

UCLASS()
class BULLETHELL_API ABasePawn : public APawn
{
	GENERATED_BODY()

protected:
	UPROPERTY(Category = "Components", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UCapsuleComponent* CapsuleComponent;

	UPROPERTY(Category = "Components", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UPaperFlipbookComponent* FlipbookComponent;

	UPROPERTY(Category = "Components", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	USceneComponent* BulletSpawnPoint;

public:
	// Sets default values for this pawn's properties
	ABasePawn();
};
