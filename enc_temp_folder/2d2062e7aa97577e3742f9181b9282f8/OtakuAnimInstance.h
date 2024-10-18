// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "OtakuAnimInstance.generated.h"

/**
 * 
 */

 class UAnimMontage;
 class UOtakuPrimaryDataAsset;

UCLASS()
class OTAKU_API UOtakuAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

private:
	void ComboActionBegin();
	void ComboActionEnd(UAnimMontage* TargetMontage, bool IsProperlyEnded);

	void SetComboActionTime();
	void CheckComboAction();

public:
	void InitAnimInstance(UOtakuPrimaryDataAsset* InPrimaryDataAsset);
	void ComboAttack();

	void HitLag();

	virtual void NativeUpdateAnimation(float DeltaSeconds);

private:
	UPROPERTY()
	TWeakObjectPtr<UOtakuPrimaryDataAsset> DataAsset;

	int32 CurrentCombo;
	bool HasNextComboCommand;

	bool bComboAttack;
	float ComboCheckTime;

	float HitStopTimeSpan;
};
