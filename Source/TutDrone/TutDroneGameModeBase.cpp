// Copyright Epic Games, Inc. All Rights Reserved.


#include "TutDroneGameModeBase.h"

void ATutDroneGameModeBase::SetCurrentState(EGameState value)
{
	currentState = value;
}

void ATutDroneGameModeBase::BeginPlay()
{
	SetCurrentState(EGameState::EPlaying);
}
