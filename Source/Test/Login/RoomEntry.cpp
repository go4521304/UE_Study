#include "RoomEntry.h"
#include "SessionData.h"
#include "Components/TextBlock.h"

void URoomEntry::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	USessionData* SessionData = Cast<USessionData>(ListItemObject);
	RoomTitle->SetText(FText::FromString(SessionData->Session.OnlineResult.Session.OwningUserName));
}
