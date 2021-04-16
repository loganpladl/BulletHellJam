// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BasePawn.generated.h"

class UCapsuleComponent;
class UPaperFlipbookComponent;

UCLASS()
class BULLETHELL_API ABasePawn : public APawn
{
	GENERATED_BODY()

private:
	UPROPERTY(Category = "Components", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UCapsuleComponent* CapsuleComponent;

	UPROPERTY(Category = Components, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UPaperFlipbookComponent* FlipbookComponent;

public:
	// Sets default values for this pawn's properties
	ABasePawn();

protected:
	virtual void BeginPlay();
};
