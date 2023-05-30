// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UMG/Public/Blueprint/UserWidget.h"
#include "IdUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class TEST_API UIdUserWidget : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* IDText;

public:
	void SetPlayerId(const FString& NewPlayerId);
};
