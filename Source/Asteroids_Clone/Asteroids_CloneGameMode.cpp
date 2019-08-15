// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "Asteroids_CloneGameMode.h"
#include "Asteroids_ClonePawn.h"

AAsteroids_CloneGameMode::AAsteroids_CloneGameMode()
{
	PrimaryActorTick.bCanEverTick = true;


	// set default pawn class to our character class
	DefaultPawnClass = AAsteroids_ClonePawn::StaticClass();

	StartRotation = FRotator(0.0f, 0.0f, 0.0f);
}

void AAsteroids_CloneGameMode::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(MemberTimerHandle, this, &AAsteroids_CloneGameMode::SpawnAsteroid, 0.5f, true, 1.0f);
}

// Called every frame
void AAsteroids_CloneGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAsteroids_CloneGameMode::SpawnAsteroid() {
	
	FMath rand;

	randomLocation = rand.RandRange(0, 3);
	auto randomLocationX = rand.RandRange(-2000, 2000);
	auto randomLocationY = rand.RandRange(-2000, 2000);

	FActorSpawnParameters SpawnInfo;

	if (randomLocation == 0)//spawn from left
	{
		GetWorld()->SpawnActor<AMyAsteroid>(FVector(randomLocationX, -2000, 0.f), StartRotation, SpawnInfo);
	} 
	else if (randomLocation == 1)//spawn from bottom
	{
		GetWorld()->SpawnActor<AMyAsteroid>(FVector(-2000, randomLocationY, 0.f), StartRotation, SpawnInfo);
	}
	else if (randomLocation == 2)//spawn from right
	{
		GetWorld()->SpawnActor<AMyAsteroid>(FVector(randomLocationX, 2000, 0.f), StartRotation, SpawnInfo);
	}
	else if (randomLocation == 3)//spawn from top
	{
		GetWorld()->SpawnActor<AMyAsteroid>(FVector(2000, randomLocationY, 0.f), StartRotation, SpawnInfo);

	}

}