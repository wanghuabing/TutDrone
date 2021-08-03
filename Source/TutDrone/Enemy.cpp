// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AEnemy::AEnemy()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);
	Mesh->SetGenerateOverlapEvents(true);
	this->OnDestroyed.AddDynamic(this, &AEnemy::DestroyHandle);
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	this->AddActorWorldOffset(FVector(.0f, .0f, 1) * DeltaTime * Speed);
}

UFUNCTION()
void AEnemy::DestroyHandle(AActor* DestroyedActor)
{
	//GEngine->AddOnScreenDebugMessage(0, 10, FColor::Red, TEXT("DestroyHandle"));
	UGameplayStatics::SpawnEmitterAtLocation(this->GetWorld(), ExplosionParticle, this->GetActorTransform());
	UGameplayStatics::PlaySoundAtLocation(this, ExplosionSound, this->GetActorLocation(), 10.0f);
}

