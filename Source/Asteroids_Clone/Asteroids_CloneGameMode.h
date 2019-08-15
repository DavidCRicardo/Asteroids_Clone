// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MyAsteroid.h"
#include "Runtime/Engine/Public/TimerManager.h"
#include "math.h"
#include "Asteroids_CloneGameMode.generated.h"

UCLASS(MinimalAPI)
class AAsteroids_CloneGameMode : public AGameModeBase
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	AAsteroids_CloneGameMode();

	UPROPERTY(EditAnywhere, Category = MyAsteroid)
	FRotator StartRotation;

	virtual void Tick(float DeltaSeconds) override;

	void SpawnAsteroid();

	FTimerHandle MemberTimerHandle;

	int32 randomLocation;
};