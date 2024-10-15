// Fill out your copyright notice in the Description page of Project Settings.


#include "AttackNotifyState.h"
#include "AnimAttackInterface.h"


void UAttackNotifyState::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);

	if (IsValid(MeshComp) && MeshComp->GetOwner()->Implements<UAnimAttackInterface>())
	{
		TScriptInterface<IAnimAttackInterface> AnimPawn {MeshComp->GetOwner()};
		if (AnimPawn)
		{
			AnimPawn->AttackHitCheck();
		}
	}
}
