#include "IdUserWidget.h"

#include "Components/TextBlock.h"

void UIdUserWidget::SetPlayerId(const FString& NewPlayerId)
{
	IDText->SetText(FText::FromString(NewPlayerId));
}
