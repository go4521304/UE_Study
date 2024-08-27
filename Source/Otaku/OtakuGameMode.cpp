// Copyright Epic Games, Inc. All Rights Reserved.

#include "OtakuGameMode.h"
#include "OtakuCharacter.h"
#include "UObject/ConstructorHelpers.h"

AOtakuGameMode::AOtakuGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
