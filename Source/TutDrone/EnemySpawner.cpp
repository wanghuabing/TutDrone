// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySpawner.h"
#include "Components/BoxComponent.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AEnemySpawner::AEnemySpawner()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpawnArea = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnArea"));
	RootComponent = SpawnArea;
	SpawnArea->SetBoxExtent(FVector(2000.0f, 2000.0f, 100.0f));
}

// Called when the game starts or when spawned
void AEnemySpawner::BeginPlay()
{
	Super::BeginPlay();
	this->GetWorld()->GetTimerManager().SetTimer(SpawnHandle, this, &AEnemySpawner::SpawnEnemy, InRate, true);
}

// Called every frame
void AEnemySpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEnemySpawner::SpawnEnemy()
{
	FVector original;
	FVector extends;
	this->GetActorBounds(false, original, extends);
	FVector spawnPoint = UKismetMathLibrary::RandomPointInBoundingBox(original, extends);
	this->GetWorld()->SpawnActor<AEnemy>(EnemyType, spawnPoint, FRotator::ZeroRotator);
}

