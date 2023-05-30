#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "LobbyPlayerController.generated.h"

UCLASS()
class TEST_API ALobbyPlayerController : public APlayerController
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	TSoftObjectPtr<class UWorld> NextLevel;

	UFUNCTION(BlueprintCallable)
	void ServerChangeLevel();
};
