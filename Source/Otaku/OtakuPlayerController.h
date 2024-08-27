// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "OtakuPlayerController.generated.h"

/**
 * 
 */

 class UInputAction;
 struct FInputActionValue;

UCLASS()
class OTAKU_API AOtakuPlayerController : public APlayerController
{
	GENERATED_BODY()

	AOtakuPlayerController();

protected:
	virtual void SetupInputComponent() override;

private:
	void FocusEnemy(const FInputActionValue& Value);

private:
	bool bFocusMode;
};
