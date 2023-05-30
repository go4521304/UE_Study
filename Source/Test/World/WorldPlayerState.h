// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "WorldPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class TEST_API AWorldPlayerState : public APlayerState
{
	GENERATED_BODY()
		
	virtual void ClientInitialize(AController* C) override;

	virtual void PostNetInit() override;
};
