// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "PacManAIAIController.generated.h"

/**
 * 
 */
UCLASS()
class TUTDRONE_API APacManAIAIController : public AAIController
{
	GENERATED_BODY()

	
		
		
	virtual void OnPossess(APawn* InPawn) override;
		
	virtual void OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result);

	class APacManEnemy* Bot;

	FVector HomeLocation;

	class ATutDronGameModeBase* GameMode;

};
