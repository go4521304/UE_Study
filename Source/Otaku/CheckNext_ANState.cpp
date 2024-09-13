// Fill out your copyright notice in the Description page of Project Settings.


#include "CheckNext_ANState.h"
#include "OtakuAnimInstance.h"

void UCheckNext_ANState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

	UOtakuAnimInstance* AnimInst = Cast<UOtakuAnimInstance>(MeshComp->GetAnimInstance());
	if (IsValid(AnimInst))
	{
		AnimInst->BeginAttackCheck(NextMontageSection);
	}
}

void UCheckNext_ANState::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);
}

void UCheckNext_ANState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);

	UOtakuAnimInstance* AnimInst = Cast<UOtakuAnimInstance>(MeshComp->GetAnimInstance());
	if (IsValid(AnimInst))
	{
		AnimInst->EndAttackCheck();
	}
}
