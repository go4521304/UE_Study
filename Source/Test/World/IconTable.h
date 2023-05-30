// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "IconTable.generated.h"

/**
 * 
 */
USTRUCT()
struct FIconTable : public FTableRowBase
{
	GENERATED_BODY()

public:
	FIconTable() : Icon(nullptr) {}

	UPROPERTY(EditAnywhere)
	TSoftObjectPtr<class UTexture2D> Icon;
};
