// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "OtakuPrimaryDataAsset.generated.h"

USTRUCT()
struct FComboAction
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = ComboData)
	FString MontageSectionNamePrefix;

	UPROPERTY(EditAnywhere, Category = ComboData)
	uint8 MaxComboCount;

	UPROPERTY(EditAnywhere, Category = ComboData)
	float FrameRate;

	UPROPERTY(EditAnywhere, Category = ComboData)
	TArray<float> EffectiveFrameCount;
};

/**
 * 
 */
UCLASS()
class OTAKU_API UOtakuPrimaryDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, Category = Weapon, meta = (AssetBundles = "Visible"))
	TSoftClassPtr<class AOtakuWeapon> OtakuWeapon;
	
	UPROPERTY(EditDefaultsOnly, Category = Animation)
	FComboAction ComboActionData;

	UPROPERTY(EditDefaultsOnly, Category = Animation, meta = (AssetBundles = "Visible"))
	TSoftObjectPtr<class UAnimMontage> ComboActionMontage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = HitLag, meta = (AllowPrivateAccess = "true"))
	float HitLagTime;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = HitLag, meta = (AllowPrivateAccess = "true"))
	float HitLagCoolTime;

	UPROPERTY(EditDefaultsOnly, Category = Camera, meta = (AssetBundles = "Visible"))
	TSoftClassPtr<class UCameraShakeBase> CameraShakeAsset;
};
