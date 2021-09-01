// Fill out your copyright notice in the Description page of Project Settings.


#include "PacManCharacter.h"

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
	//��
	//�������������������ã�����Ҫʹ��ȡָ��
	PlayerInputComponent->BindAxis("PacManMoveX", this, &APacManCharacter::MoveX);
	PlayerInputComponent->BindAxis("PacManMoveY", this, &APacManCharacter::MoveY);
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
}

void APacManCharacter::NewGame()
{
}

void APacManCharacter::Pause()
{
}

//��������ݼ� Ctrl+K Ctrl+F