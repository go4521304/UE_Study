// Fill out your copyright notice in the Description page of Project Settings.


#include "OtakuAnimInstance.h"
#include "OtakuCharacter.h"
#include "OtakuPrimaryDataAsset.h"


void UOtakuAnimInstance::InitAnimInstance(UOtakuPrimaryDataAsset* InPrimaryDataAsset)
{
	if (IsValid(InPrimaryDataAsset))
	{
		DataAsset = InPrimaryDataAsset;
	}
	else
	{
		ensureAlwaysMsgf(false, TEXT("Invalid OtakuPrimaryDataAsset"));
	}

	CurrentCombo = 0;
	HasNextComboCommand = false;

	bComboAttack = false;
	ComboCheckTime = 0.0f;

	HitStopTimeSpan = 0.0f;
}

void UOtakuAnimInstance::ComboAttack()
{
	if (CurrentCombo == 0)
	{
		ComboActionBegin();
		return;
	}

	// �Է� Ÿ�̹��� ����� ���� �Է��� ���� ���
	if (bComboAttack && ComboCheckTime >= 0.0f)
	{
		HasNextComboCommand = true;
	}
}

void UOtakuAnimInstance::HitLag()
{
	HitStopTimeSpan = 0.1f;

	Montage_Pause(DataAsset->ComboActionMontage.Get());
}

void UOtakuAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (bComboAttack)
	{
		if (ComboCheckTime <= Montage_GetPosition(DataAsset->ComboActionMontage.Get()))
		{
			CheckComboAction();
		}

		if (HitStopTimeSpan <= 0.0f)
		{
			Montage_Resume(DataAsset->ComboActionMontage.Get());
		}
		else
		{
			HitStopTimeSpan -= DeltaSeconds;
		}
	}
}

void UOtakuAnimInstance::ComboActionBegin()
{
	bComboAttack = true;

	CurrentCombo = 1;
	const float AttackSpeedRate = 1.0f;
	Montage_Play(DataAsset->ComboActionMontage.Get(), AttackSpeedRate);

	FOnMontageEnded EndedDelegate;
	EndedDelegate.BindUObject(this, &ThisClass::ComboActionEnd);
	Montage_SetEndDelegate(EndedDelegate, DataAsset->ComboActionMontage.Get());

	UE_LOG(LogTemp, Warning, TEXT("ComboActionBegin"));

	SetComboActionTime();
}

void UOtakuAnimInstance::ComboActionEnd(UAnimMontage* TargetMontage, bool IsProperlyEnded)
{
	ensureAlways(CurrentCombo != 0);

	CurrentCombo = 0;
	HasNextComboCommand = false;
	bComboAttack = false;
	ComboCheckTime = 0.0f;
	
	UE_LOG(LogTemp, Warning, TEXT("ComboActionEnd"));
}

// �ð����� �����ϸ� ���������� �ִϸ��̼��� �� ��� ����� �� ������ ����
// ������ �ش� �������� �ִϸ��̼��� ��� �������� �̸� ����صΰ� Montage_GetPosition �� ���� ���ؼ� ����
void UOtakuAnimInstance::SetComboActionTime()
{
	const float AttackSpeedRate = DataAsset->ComboActionMontage->RateScale;
	ComboCheckTime = (DataAsset->ComboActionData.EffectiveFrameCount[CurrentCombo - 1] / DataAsset->ComboActionData.FrameRate) / AttackSpeedRate;
}

void UOtakuAnimInstance::CheckComboAction()
{
	if (HasNextComboCommand)
	{
		CurrentCombo = FMath::Clamp(CurrentCombo + 1, 1, DataAsset->ComboActionData.MaxComboCount);
		FName CurrentSection = Montage_GetCurrentSection(DataAsset->ComboActionMontage.Get());
		FName NextSection = *FString::Printf(TEXT("%s%d"), *DataAsset->ComboActionData.MontageSectionNamePrefix, CurrentCombo);
		Montage_SetNextSection(CurrentSection, NextSection, DataAsset->ComboActionMontage.Get());

		HasNextComboCommand = false;

		SetComboActionTime();
	}
}
