// Fill out your copyright notice in the Description page of Project Settings.


#include "OtakuAnimInstance.h"
#include "OtakuCharacter.h"

void UOtakuAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	bWaitingComboAttack = false;
	bContinueToNextCombo = false;

	AttackDelay = 0.0f;
}

void UOtakuAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (Montage_IsActive(AttackMontage))
	{
		AttackDelay -= DeltaSeconds;
	}
}

void UOtakuAnimInstance::BeginAttackCheck(const FName& InNextSectionName)
{
	bWaitingComboAttack = true;
	bContinueToNextCombo = false;
	NextAttackSectionName = InNextSectionName;


	AttackDelay = 1.0f;
}

void UOtakuAnimInstance::EndAttackCheck()
{
	bWaitingComboAttack = false;
	bContinueToNextCombo = false;

	Montage_Pause(AttackMontage);
}

void UOtakuAnimInstance::InputAttackAction()
{
	if (bWaitingComboAttack && bContinueToNextCombo == false)
	{
		bContinueToNextCombo = true;

		Montage_SetNextSection(Montage_GetCurrentSection(AttackMontage), NextAttackSectionName, AttackMontage);
	}
}

void UOtakuAnimInstance::PlayAttackAnim()
{
	if (IsValid(AttackMontage) == false)
	{
		return;
	}

	if (AttackDelay > 0.0f)
	{
		return;
	}

	Montage_Play(AttackMontage);
}

bool UOtakuAnimInstance::IsPlayingAttackAnim()
{
	if (IsValid(AttackMontage) == false)
	{
		return false;
	}

	return Montage_IsPlaying(AttackMontage);
}
