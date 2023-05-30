#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MyHUD.generated.h"

UCLASS()
class TEST_API AMyHUD : public AHUD
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> Widget;

	UPROPERTY()
	class UUserWidget* CurWidget;

	virtual void BeginPlay() override;
};
