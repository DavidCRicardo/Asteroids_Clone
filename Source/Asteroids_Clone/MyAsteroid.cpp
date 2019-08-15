// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAsteroid.h"
#include "Components/StaticMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "ConstructorHelpers.h"

// Sets default values
AMyAsteroid::AMyAsteroid()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	Root->SetMobility(EComponentMobility::Movable);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));

	static ConstructorHelpers::FObjectFinder<UStaticMesh>RockAsset(TEXT("/Game/Asteroid/SM_Rock.SM_Rock"));
	if (RockAsset.Succeeded())
	{
		Mesh->SetStaticMesh(RockAsset.Object);
	}
	Mesh->AttachTo(Root);
	//Mesh->SetSimulatePhysics(true);

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Component"));
	CapsuleComponent->InitCapsuleSize(90, 150);
	CapsuleComponent->RelativeLocation = FVector(0.000000, 0.000000, 100.000000);
	CapsuleComponent->RelativeScale3D = FVector(1.5, 1, 1);
	CapsuleComponent->BodyInstance.SetCollisionProfileName("OverlapAll");
	CapsuleComponent->SetupAttachment(Mesh);
	CapsuleComponent->SetVisibility(true);

	Level_Asteroid = 1;
	

	/*Rotation*/ //Need to be random
	PitchValue = 0.f;
	//YawValue = 0.f;
	RollValue = 0.f;

	/*Location*/ //Need to be random
	//Speed_X = 0.f;
	//Speed_Y = 0.f;
	Speed_Z = 0.f;
}

// Called when the game starts or when spawned
void AMyAsteroid::BeginPlay()
{
	Super::BeginPlay();

	PlayerRef = GetWorld()->GetFirstPlayerController()->GetPawn();
	MyPawn = Cast<AAsteroids_ClonePawn>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	MyGM = (AAsteroids_CloneGameMode*) GetWorld()->GetAuthGameMode();

	aux1 = false;

	FMath rand;

	/*LevelAsteroid*/
	Level_Asteroid = rand.RandRange(1, 2);
	if (Level_Asteroid == 1)
	{
		Mesh->RelativeScale3D = FVector(1, 1, 1);
		CapsuleComponent->RelativeScale3D = FVector(1.5, 1, 1);

	}
	else if (Level_Asteroid == 2) {
		Mesh->RelativeScale3D = FVector(2, 2, 2);
		//CapsuleComponent->RelativeScale3D = FVector(3, 2, 2);
	}

	/*GetInitialLocation*/
	CurrentMeshLocation = this->GetActorLocation();

	int32 randomNumberX;
	int32 randomNumberY;

	if (MyGM->randomLocation == 0)//spawn from left
	{
		randomNumberX = rand.RandRange(0, 10); //don't move to left
		randomNumberY = rand.RandRange(-10, 10);
	}
	else if (MyGM->randomLocation == 1)//spawn from bottom
	{
		randomNumberX = rand.RandRange(-10, 10);
		randomNumberY = rand.RandRange(0, 10); //don't move to down
	}
	else if (MyGM->randomLocation == 2)//spawn from right
	{
		randomNumberX = rand.RandRange(-10, 0); //don't move to right
		randomNumberY = rand.RandRange(-10, 10);

	}
	else if (MyGM->randomLocation == 3)//spawn from top
	{
		randomNumberX = rand.RandRange(-10, 10);
		randomNumberY = rand.RandRange(-10, 0); //don't move to up
	}

	Speed_X = randomNumberX;
	Speed_Y = randomNumberY;

	/*Rotation*/
	auto randomNumberYaw = rand.RandRange(-10, 10);
	YawValue = randomNumberYaw;

}

// Called every frame
void AMyAsteroid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	/*Asteroid Hit Player*/
	if (CapsuleComponent->IsOverlappingActor(MyPawn) && aux1 == false)
	{
		aux1 = true;
		MyPawn->PlayerLife = MyPawn->PlayerLife - 1;
	}
	else if (!CapsuleComponent->IsOverlappingActor(MyPawn) && aux1 == true)
	{
		aux1 = false;
	}

	/*Location*/
	CurrentMeshLocation.X += Speed_X;
	CurrentMeshLocation.Y += Speed_Y;
	CurrentMeshLocation.Z += Speed_Z;
	SetActorLocation(CurrentMeshLocation);
	
	/*Rotation*/
	FQuat QuatRotation = FQuat(FRotator(PitchValue, YawValue, RollValue));
	AddActorLocalRotation(QuatRotation);

	/*Limits Asteroid*/
	if (CurrentMeshLocation.X < -2500 || CurrentMeshLocation.X > 2500)
	{
		this->Destroy();
	}
	if (CurrentMeshLocation.Y < -2500 || CurrentMeshLocation.Y > 2500)
	{
		this->Destroy();
	}

}

void AMyAsteroid::SpawnAgain(int32 NewLevel, FVector NewLocation)
{
	FActorSpawnParameters SpawnInfo;

	GetWorld()->SpawnActor<AMyAsteroid>(NewLocation, FRotator(0, 10, 0), SpawnInfo);
	GetWorld()->SpawnActor<AMyAsteroid>(NewLocation, FRotator(0, 10, 0), SpawnInfo);
	
}

