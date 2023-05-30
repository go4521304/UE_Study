#include "WorldGameModeBase.h"
#include "MyPawn.h"
#include "MyPlayerController.h"

void AWorldGameModeBase::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	UE_LOG(LogTemp, Error, TEXT("PostLogin"));

	Cast<AMyPlayerController>(NewPlayer)->ClientGetPlayerId();
}
