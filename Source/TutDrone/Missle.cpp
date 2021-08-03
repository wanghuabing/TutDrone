// Fill out your copyright notice in the Description page of Project Settings.


#include "Missle.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Enemy.h"
#include "TutDroneGameModeBase.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AMissle::AMissle()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;
	Mesh->SetGenerateOverlapEvents(true);
	Mesh->OnComponentBeginOverlap.AddDynamic(this, &AMissle::OnComponentBeginOverlap);

	MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("MovementComponent"));
	MovementComponent->InitialSpeed = Speed;

	//auto t = FString::Printf(TEXT("%f"), Speed);
	//GEngine->AddOnScreenDebugMessage(0, 10, FColor::Red, t);

}

// Called when the game starts or when spawned
void AMissle::BeginPlay()
{
	Super::BeginPlay();
	this->SetLifeSpan(8.0f);
	UGameplayStatics::PlaySound2D(this, FireSound);
}

// Called every frame
void AMissle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMissle::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA<AEnemy>())
	{
		OtherActor->Destroy();
		this->Destroy();
		UWorld* world = this->GetWorld();
		ATutDroneGameModeBase* gamemode = Cast<ATutDroneGameModeBase>(world->GetAuthGameMode());
		if (gamemode != nullptr)
		{
			gamemode->Point++;
		}
	}
}

