// Fill out your copyright notice in the Description page of Project Settings.


#include "PacManCharacter.h"
#include "TutDroneGameModeBase.h"
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
	//将实例转化了
	GameMode = Cast<ATutDroneGameModeBase>(UGameplayStatics::GetGameMode(this));
}

// Called every frame
void APacManCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APacManCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	//绑定
	//第三个参数传递是引用，所以要使用取指符
	PlayerInputComponent->BindAxis("PacManMoveX", this, &APacManCharacter::MoveX);
	PlayerInputComponent->BindAxis("PacManMoveY", this, &APacManCharacter::MoveY);

	PlayerInputComponent->BindAction("NewGame", IE_Pressed, this, &APacManCharacter::NewGame);
	PlayerInputComponent->BindAction("Restart", IE_Pressed, this, &APacManCharacter::Restart);
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
	if (GameMode->GetCurrentState == EGameState::EMenu)
	{
		GameMode->SetCurrentState(EGameState::EPlaying);
	}
}

void APacManCharacter::Pause()
{
	if (GameMode->GetCurrentState == EGameState::EPlaying)
	{
		GameMode->SetCurrentState(EGameState::EPause);
	}
	else if (GameMode->GetCurrentState == EGameState::EPlause)
	{
		GameMode->SetCurrentState(EGameState::EPlaying);
	}
}

//整理代码快捷键 Ctrl+K Ctrl+F