// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "EngineGlobals.h"
#include "Asteroids_ClonePawn.h"
#include "math.h"
#include "Asteroids_CloneGameMode.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "MyAsteroid.generated.h"

UCLASS()
class ASTEROIDS_CLONE_API AMyAsteroid : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyAsteroid();

	UPROPERTY(EditAnywhere, Category = MyAsteroid)
	uint16 Level_Asteroid;

	/*Location*/
	UPROPERTY(VisibleAnywhere, Category = MyMovementLocation)
	float Speed_X;
	UPROPERTY(VisibleAnywhere, Category = MyMovementLocation)
	float Speed_Y;
	UPROPERTY(VisibleAnywhere, Category = MyMovementLocation)
	float Speed_Z;

	/*Rotation*/
	UPROPERTY(EditAnywhere, Category = MyMovementRotation)
	float PitchValue;
	UPROPERTY(EditAnywhere, Category = MyMovementRotation)
	float YawValue;
	UPROPERTY(EditAnywhere, Category = MyMovementRotation)
	float RollValue;

private:
	FVector CurrentMeshLocation;
	FVector CurrentMeshRotation;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY()
	class USceneComponent* Root;

	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere)
	class UCapsuleComponent* CapsuleComponent;

	UPROPERTY(EditAnywhere)
	class AActor* PlayerRef = nullptr;

	class AAsteroids_ClonePawn* MyPawn = nullptr;	
	class AAsteroids_CloneGameMode* MyGM;

	UFUNCTION()
	void SpawnAgain(int32 NewLevel, FVector NewLocation);

	bool aux1 = false;
};
