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

	EGameState GetCurrentState() const;//不能修改当前成员，所以使用const关键字
	void SetCurrentState(EGameState value);

	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		int32 Point;//uint32 不被蓝图支持
};

//使用内联 提高函数的执行效率
FORCEINLINE EGameState ATutDroneGameModeBase::GetCurrentState() const {
	return currentState;
}