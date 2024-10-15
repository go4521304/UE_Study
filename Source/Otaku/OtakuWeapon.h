// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "OtakuWeapon.generated.h"

class USkeletalMeshComponent;
class UCapsuleComponent;

UCLASS()
class OTAKU_API AOtakuWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AOtakuWeapon();

	UPROPERTY(Category=Weapon, VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<USkeletalMeshComponent> WeaponMeshComponent;

	UPROPERTY(Category=Weapon, VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UCapsuleComponent> CapsuleComponent;
public:
	// Return True, if actors overlapped.
	bool CheckWeaponOverlapped(TSet<AActor*>& OutOverlapActors, TSubclassOf<AActor> InActorClass = nullptr);

};
