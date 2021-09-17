// Fill out your copyright notice in the Description page of Project Settings.

#include "PacManEnemy.h"
#include "Kismet/GameplayStatics.h"
#include "PacManAIAIController.h"

void APacManAIAIController::OnPossess(APawn* InPawn)
{
	Super::Possess(InPawn);
	Bot = Cast<APacManEnemy>(InPawn);
	HomeLocation = Bot->GetActorLocation();
	GameMode = Cast<ATutDronGameModeBase>(UGameplayStatics::GetGameMode(this));
}

void APacManAIAIController::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
	if (!Bot.bIsDead && GameMode ->GetCurrentState() != EGameState::EPause)
	{

	}
}
