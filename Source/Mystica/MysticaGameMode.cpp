// Copyright Epic Games, Inc. All Rights Reserved.

#include "MysticaGameMode.h"
#include "MysticaCharacter.h"
#include "UObject/ConstructorHelpers.h"

AMysticaGameMode::AMysticaGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
