#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MyGameInstance.generated.h"

UCLASS()
class TEST_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()

		FString PlayerId;

public:
	void SetPlayerId(const FString& NewPlayerId) { PlayerId = NewPlayerId; }
	const FString& GetPlayerId() const { return PlayerId; }
};
