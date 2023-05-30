// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class TEST_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()

private:
	virtual void BeginPlay() override;

public:
	UFUNCTION(Client, Reliable)
	void ClientGetPlayerId();

	UFUNCTION(Server, Reliable)
	void ServerSetPlayerId(const FString& NewPlayerId);
};
