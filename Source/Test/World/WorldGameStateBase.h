#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "WorldGameStateBase.generated.h"

UCLASS()
class TEST_API AWorldGameStateBase : public AGameStateBase
{
	GENERATED_BODY()

	virtual void PostNetInit() override;
};
