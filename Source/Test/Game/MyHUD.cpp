#include "MyHUD.h"
#include "Blueprint/UserWidget.h"

void AMyHUD::BeginPlay()
{
	Super::BeginPlay();

	if (!IsValid(Widget))
	{
		return;
	}

	CurWidget = CreateWidget<UUserWidget>(GetWorld(), Widget);
	CurWidget->AddToViewport();
}
