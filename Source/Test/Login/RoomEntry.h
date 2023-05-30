// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "Blueprint/UserWidget.h"
#include "RoomEntry.generated.h"

/**
 * 
 */
UCLASS()
class TEST_API URoomEntry : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()

private:
	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* RoomTitle;

		
};
