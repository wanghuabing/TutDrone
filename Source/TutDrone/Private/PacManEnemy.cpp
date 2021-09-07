// Fill out your copyright notice in the Description page of Project Settings.


#include "PacManEnemy.h"
#include "Components/CapsuleComponent.h"
#include "UObject/ConstructorHelpers.h"

// Sets default values
APacManEnemy::APacManEnemy()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	EnemyBody = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> CylinderObj(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Cylinder.Shape_Cylinder'"));

	if (CylinderObj.Succeeded())
	{
		EnemyBody->SetStaticMesh(CylinderObj.Object);
	}
	EnemyBody->SetRelativeScale3D(FVector(0.75f, 0.75f, 1));
	EnemyBody->SetupAttachment(RootComponent);
	EnemyBody->SetRelativeLocation(FVector(0, 0, -50));
	GetCapsuleComponent()->SetCapsuleRadius(40.0f);
	GetCapsuleComponent()->SetCapsuleHalfHeight(50.0f);
}

// Called when the game starts or when spawned
void APacManEnemy::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void APacManEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APacManEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

