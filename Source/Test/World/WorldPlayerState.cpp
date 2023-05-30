#include "WorldPlayerState.h"
#include "Test/Game/MyGameInstance.h"
#include "MyPawn.h"

void AWorldPlayerState::ClientInitialize(AController* C)
{
	Super::ClientInitialize(C);
}

void AWorldPlayerState::PostNetInit()
{
	Super::PostNetInit();
}
