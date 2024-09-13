// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "OtakuAnimInstance.generated.h"

/**
 * 
 */

 class UAnimMontage;

UCLASS()
class OTAKU_API UOtakuAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	void BeginAttackCheck(const FName& InNextSectionName);
	void EndAttackCheck();

	void InputAttackAction();

	void PlayAttackAnim();
	bool IsPlayingAttackAnim();

private:
	UPROPERTY(EditAnywhere, Category="AttackAnim")
	UAnimMontage* AttackMontage;

	bool bWaitingComboAttack;
	bool bContinueToNextCombo;

	FName NextAttackSectionName;

	float AttackDelay;
	
};
