#include "LobbyPlayerController.h"
#include "Engine/World.h"

void ALobbyPlayerController::ServerChangeLevel()
{
	GetWorld()->ServerTravel(NextLevel.GetLongPackageName());
}
