#include "MyPlayerController.h"
#include "WorldGameStateBase.h"
#include "MyPawn.h"
#include "Test/Game/MyGameInstance.h"


void AMyPlayerController::BeginPlay()
{
	Super::BeginPlay();
}

void AMyPlayerController::ServerSetPlayerId_Implementation(const FString& NewPlayerId)
{
	if (!IsValid(GetPawn()))
	{
		return;
	}
	AMyPawn* NewPlayerPawn = GetPawn<AMyPawn>();
	NewPlayerPawn->SetPlayerId(NewPlayerId);
}

void AMyPlayerController::ClientGetPlayerId_Implementation()
{
	UMyGameInstance* GameInst = GetGameInstance<UMyGameInstance>();
	if (!IsValid(GameInst))
	{
		return;
	}
	ServerSetPlayerId(GameInst->GetPlayerId());
}
