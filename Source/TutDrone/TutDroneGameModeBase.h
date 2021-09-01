// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TutDroneGameModeBase.generated.h"


enum class EGameState :short
{
	EMenu,
	EPlaying,
	EPause,
	EWin,
	EGameOver
};

/**
 *
 */
UCLASS()
class TUTDRONE_API ATutDroneGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

private:
	EGameState currentState;

public:

	EGameState GetCurrentState() const;//�����޸ĵ�ǰ��Ա������ʹ��const�ؼ���
	void SetCurrentState(EGameState value);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		int32 Point;//uint32 ������ͼ֧��
};

//ʹ������ ��ߺ�����ִ��Ч��
FORCEINLINE EGameState ATutDroneGameModeBase::GetCurrentState() const {
	return currentState;
}