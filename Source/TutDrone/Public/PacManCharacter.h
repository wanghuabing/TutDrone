﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "../TutDroneGameModeBase.h"
#include "PacManCharacter.generated.h"

UCLASS()
class TUTDRONE_API APacManCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APacManCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	// Character 继承 Pawn ; Pawn继承Actor
	// 这函数还Actor中不存在
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveX(float Value);

	void MoveY(float Value);

	void ReStart();

	void NewGame();

	void Pause();

	void Killed();

	int CollectablesToEat;

	int Lives;

	//因为监听这个函数使用了反射，所以要使用这个宏
	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
private:
	FVector CurrentVelocity;
	FVector StartPoint;
	ATutDroneGameModeBase* GameMode;

};
