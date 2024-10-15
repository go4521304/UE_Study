// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "AttackNotifyState.generated.h"

/**
 * 
 */
UCLASS()
class OTAKU_API UAttackNotifyState : public UAnimNotifyState
{
	GENERATED_BODY()
	
	
private:
	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference) override;
	
};
