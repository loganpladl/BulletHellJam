// Fill out your copyright notice in the Description page of Project Settings.


#include "BulletHellGameStateBase.h"

void ABulletHellGameStateBase::GetPlayAreaBorders(float& MinX, float& MaxX, float& MinZ, float& MaxZ) {
	// Assume center of play area is (0, Y, 0) where Y is arbitrary
	float HalfWidth = PlayAreaWidth / 2;
	float HalfHeight = PlayAreaHeight / 2;

	MinX = -HalfWidth + PlayAreaBorder;
	MaxX = HalfWidth - PlayAreaBorder;
	MinZ = -HalfHeight + PlayAreaBorder;
	MaxZ = HalfHeight - PlayAreaBorder;
}

float ABulletHellGameStateBase::HorizontalFracToWorld(float x) {
	return x * (PlayAreaWidth / 2);
}

float ABulletHellGameStateBase::VerticalFracToWorld(float y) {
	return y * (PlayAreaHeight / 2);
}