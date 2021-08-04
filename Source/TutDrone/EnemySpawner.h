// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Enemy.h"
#include "EnemySpawner.generated.h"

UCLASS()
class TUTDRONE_API AEnemySpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemySpawner();

	UPROPERTY(EditAnywhere)
		class UBoxComponent* SpawnArea;

	UPROPERTY(EditAnywhere)
		struct FTimerHandle SpawnHandle;

	UPROPERTY(EditAnywhere)
		TSubclassOf<AEnemy> EnemyType;

	UPROPERTY(EditAnywhere)
		float InRate = 2.0f;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UFUNCTION()
	void SpawnEnemy();

};
