#include "WorldGameStateBase.h"

void AWorldGameStateBase::PostNetInit()
{
	Super::PostNetInit();

	UE_LOG(LogTemp, Error, TEXT("GameStatePostNet"));

}
