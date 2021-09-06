// Fill out your copyright notice in the Description page of Project Settings.

#include "PacManCharacter.h"
#include "../TutDroneGameModeBase.h"
#include "Collectables.h"
#include "Components/CapsuleComponent.h"
#include "EngineUtils.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APacManCharacter::APacManCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void APacManCharacter::BeginPlay()
{
	Super::BeginPlay();

	Lives = 3;
	StartPoint = GetActorLocation();
	//打印 向量转化为字符串
	UE_LOG(LogTemp, Warning, TEXT("Start Point is %s"), *StartPoint.ToString());
	//将实例转化了
	GameMode = Cast<ATutDroneGameModeBase>(UGameplayStatics::GetGameMode(this));
	// FComponentBeginOverlapSignature, UPrimitiveComponent, OnComponentBeginOverlap,
	//
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &APacManCharacter::OnBeginOverlap);

	//迭代器	统计world里面一共有多少个Collectable
	for (TActorIterator<ACollectables> CollectableItr(GetWorld()); CollectableItr; ++CollectableItr)
	{
		CollectablesToEat++;
	}
	UE_LOG(LogTemp, Warning, TEXT("Total Collectable is %d"), CollectablesToEat);
}

// Called every frame
void APacManCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void APacManCharacter::SetupPlayerInputComponent(UInputComponent *PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	//绑定
	//第三个参数传递是引用，所以要使用取指符
	PlayerInputComponent->BindAxis("PacManMoveX", this, &APacManCharacter::MoveX);
	PlayerInputComponent->BindAxis("PacManMoveY", this, &APacManCharacter::MoveY);

	PlayerInputComponent->BindAction("NewGame", IE_Pressed, this, &APacManCharacter::NewGame);
	PlayerInputComponent->BindAction("ReStart", IE_Pressed, this, &APacManCharacter::ReStart);
	PlayerInputComponent->BindAction("Pause", IE_Pressed, this, &APacManCharacter::Pause);
}

void APacManCharacter::MoveX(float Value)
{
	CurrentVelocity.X = Value;
	AddMovementInput(CurrentVelocity);
}

void APacManCharacter::MoveY(float Value)
{
	CurrentVelocity.Y = Value;
	AddMovementInput(CurrentVelocity);
}

void APacManCharacter::ReStart()
{
	GetWorld()->GetFirstPlayerController()->ConsoleCommand(TEXT("RestartLevel"));
}

void APacManCharacter::NewGame()
{
	if (GameMode->GetCurrentState() == EGameState::EMenu)
	{
		GameMode->SetCurrentState(EGameState::EPlaying);
	}
}

void APacManCharacter::Pause()
{
	if (GameMode->GetCurrentState() == EGameState::EPlaying)
	{
		GameMode->SetCurrentState(EGameState::EPause);
	}
	else if (GameMode->GetCurrentState() == EGameState::EPause)
	{
		GameMode->SetCurrentState(EGameState::EPlaying);
	}
}

void APacManCharacter::Killed()
{
	if (--Lives == 0)
	{
		GameMode->SetCurrentState(EGameState::EGameOver);
	}else
	{
		SetActorLocation(StartPoint);
	}
}

void APacManCharacter::OnBeginOverlap(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
	if (GameMode->GetCurrentState() == EGameState::EPlaying)
	{
		if (OtherActor->IsA(ACollectables::StaticClass()))
		{
			OtherActor->Destroy();
			if (CollectablesToEat > 0)
			{
				CollectablesToEat--;
			}
			UE_LOG(LogTemp, Warning, TEXT("Remain Collectable is %d"), CollectablesToEat);
		}
	}
}

//整理代码快捷键 Ctrl+K Ctrl+F