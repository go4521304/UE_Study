#include "LoginList.h"
#include "Components/Button.h"
#include "Components/EditableText.h"
#include "SessionData.h"
#include "Components/ListView.h"
#include "Test/Game/MyGameInstance.h"

void ULoginList::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	FindButton->OnClicked.AddUniqueDynamic(this,  &ULoginList::OnFindSession);
	CreateButton->OnClicked.AddUniqueDynamic(this,  &ULoginList::OnCreateSession);
	LobbyListView->OnItemDoubleClicked().AddUObject(this, &ULoginList::OnEnterSession);
}

void ULoginList::NativeConstruct()
{
	Super::NativeConstruct();
	GetOwningPlayer()->SetShowMouseCursor(true);
}

void ULoginList::AddRoom(TArray<FBlueprintSessionResult> SessionLResults)
{
	for (FBlueprintSessionResult SessionIter: SessionLResults)
	{
		USessionData* NewSessionData = NewObject<USessionData>();
		NewSessionData->Session = SessionIter;
		LobbyListView->AddItem(NewSessionData);
	}
}

void ULoginList::OnFindSession()
{
	SetUserId();
	EventFindRoom();
}

void ULoginList::OnCreateSession()
{
	SetUserId();
	EventCreateRoom();
}

void ULoginList::OnEnterSession(UObject* obj)
{
	USessionData* Data = Cast<USessionData>(obj);
	EventEnterRoom(Data->Session);
}

void ULoginList::SetUserId()
{
	UMyGameInstance* GameInstance = GetGameInstance<UMyGameInstance>();
	GameInstance->SetPlayerId(IDText->GetText().ToString());
}
