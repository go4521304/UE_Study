// Fill out your copyright notice in the Description page of Project Settings.


#include "OtakuWeapon.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"

// Sets default values
AOtakuWeapon::AOtakuWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	WeaponMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));
	SetRootComponent(WeaponMeshComponent);

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("WeaponHitArea"));
	CapsuleComponent->SetupAttachment(GetRootComponent());
}

bool AOtakuWeapon::CheckWeaponOverlapped(TSet<AActor*>& OutOverlapActors, TSubclassOf<AActor> InActorClass /*= nullptr*/)
{
	CapsuleComponent->GetOverlappingActors(OutOverlapActors, InActorClass);

	return OutOverlapActors.IsEmpty() == false;
}
