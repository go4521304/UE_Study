#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FindSessionsCallbackProxy.h"
#include "LoginList.generated.h"


UCLASS()
class TEST_API ULoginList : public UUserWidget
{
	GENERATED_BODY()
		
	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;

public:
	UFUNCTION(BlueprintImplementableEvent)
	void EventFindRoom();

	UFUNCTION(BlueprintImplementableEvent)
	void EventEnterRoom(FBlueprintSessionResult SessionResult);

	UFUNCTION(BlueprintImplementableEvent)
	void EventCreateRoom();

	UFUNCTION(BlueprintCallable)
	void AddRoom(TArray<FBlueprintSessionResult> SessionLResults);

private:
	UPROPERTY(meta=(BindWidget))
	class UListView* LobbyListView;

	UPROPERTY(meta = (BindWidget))
	class UEditableText* IDText;

	UPROPERTY(meta = (BindWidget))
	class UButton* FindButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* CreateButton;

	UFUNCTION()
	void OnFindSession();

	UFUNCTION()
	void OnCreateSession();

	UFUNCTION()
	void OnEnterSession(UObject* obj);


	void SetUserId();
};
