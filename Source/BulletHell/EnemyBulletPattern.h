// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseBulletPattern.h"
#include "EnemyBulletPattern.generated.h"

/**
 * 
 */
UCLASS()
class BULLETHELL_API UEnemyBulletPattern : public UBaseBulletPattern
{
	GENERATED_BODY()
	
public:
	void PlayFireSound() override;
};
