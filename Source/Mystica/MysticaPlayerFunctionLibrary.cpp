#include "MysticaPlayerFunctionLibrary.h"
#include "DefaultPlayer.h"
#include "Kismet/GameplayStatics.h"

ADefaultPlayer *
UMysticaPlayerFunctionLibrary::GetDefaultPlayer(AActor *WorldContextActor,
                                                int32 PlayerIndex) {
    return Cast<ADefaultPlayer>(
        UGameplayStatics::GetPlayerCharacter(WorldContextActor, 0));
}
