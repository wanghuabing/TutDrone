// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/StaticMeshComponent.h"
#include "PacManEnemy.generated.h"

UCLASS()
class TUTDRONE_API APacManEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APacManEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	UPROPERTY(VisibleAnyWhere, Category = body)
		UStaticMeshComponent* EnemyBody;


	bool bIsDead;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	class UMaterialInterface* DefaultMaterial;
	class UMaterialInterface* VulnerableMaterial;
	FTimerHandle TimeVulnerable;
	
	bool bIsVulnerable;
	


	void SetVulnerable();

	void SetInVulnerable();

	void SetMove(bool bMoveIt); 

	void Killed();

	void ReArm();

	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
