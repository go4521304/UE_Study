// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UMG/Public/Blueprint/UserWidget.h"
#include "MyUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class TEST_API UMyUserWidget : public UUserWidget
{
	GENERATED_BODY()

private:
	UPROPERTY(meta = (BindWidget))
		class UEditableTextBox* TextBox1;
	UPROPERTY(meta = (BindWidget))
		class UEditableTextBox* TextBox2;
	UPROPERTY(meta = (BindWidget))
		class UEditableTextBox* TextBox3;
	UPROPERTY(meta = (BindWidget))
		class UEditableTextBox* TextBox4;
	UPROPERTY(meta = (BindWidget))
		class UEditableTextBox* TextBox5;

	virtual void NativeOnInitialized() override;
};
