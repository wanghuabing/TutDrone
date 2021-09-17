// Fill out your copyright notice in the Description page of Project Settings.


#include "PacManEnemy.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "TimerManager.h"
#include "PacManCharacter.h"
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

	static ConstructorHelpers::FObjectFinder<UMaterial> VulnerMat(TEXT("Material'/Game/Materials/M_Vulnerable.M_Vulnerable'"));

	if (VulnerMat.Succeeded())
	{
		VulnerableMaterial = VulnerMat.Object;
	}

	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &APacManEnemy::OnBeginOverlap);
}

// Called when the game starts or when spawned
void APacManEnemy::BeginPlay()
{
	Super::BeginPlay();
	DefaultMaterial = EnemyBody->GetMaterial(0);

	bIsVulnerable = false;
	SetVulnerable();
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

void APacManEnemy::SetVulnerable()
{
	GetWorldTimerManager().SetTimer(TimeVulnerable, this, &APacManEnemy::SetInVulnerable, 10, false);

	if (bIsVulnerable)
	{
		return;
	}
	bIsVulnerable = true;
	EnemyBody->SetMaterial(0, VulnerableMaterial);
	GetCharacterMovement()->MaxWalkSpeed = 50.0f;
}

void APacManEnemy::SetInVulnerable()
{
	GetWorldTimerManager().ClearTimer(TimeVulnerable);
	bIsVulnerable = false;
	EnemyBody->SetMaterial(0, DefaultMaterial);
	GetCharacterMovement()->MaxWalkSpeed = 150.0f;
}

void APacManEnemy::SetMove(bool bMoveIt)
{
}

void APacManEnemy::Killed()
{
	if (bIsDead)
	{
		return;
	}
	bIsDead = true;

	GetCharacterMovement()->MaxWalkSpeed = 300;
}

void APacManEnemy::ReArm()
{
	bIsDead = false;
	GetCharacterMovement()->MaxWalkSpeed = 150.0f;

	if (bIsVulnerable)
	{
		SetInVulnerable();
	}
}

void APacManEnemy::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA(APacManCharacter::StaticClass()))
	{
		if (bIsVulnerable)
		{
			this->Killed();
		}
		else
		{
			APacManCharacter* PacManCharacter = Cast<APacManCharacter>(OtherActor);
			PacManCharacter->Killed();
		}
	}
}
