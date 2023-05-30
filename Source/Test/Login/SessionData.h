// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FindSessionsCallbackProxy.h"
#include "SessionData.generated.h"

/**
 * 
 */
UCLASS()
class TEST_API USessionData : public UObject
{
	GENERATED_BODY()

public:
	FBlueprintSessionResult Session;
};
