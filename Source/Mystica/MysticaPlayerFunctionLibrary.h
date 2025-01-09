#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "MysticaPlayerFunctionLibrary.generated.h"

class ADefaultPlayer;

UCLASS()

class MYSTICA_API UMysticaPlayerFunctionLibrary
    : public UBlueprintFunctionLibrary {
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintPure,
              Category = "Player|Mystica Function Library",
              meta = (DefaultToSelf = "WorldContextActor"))
    static ADefaultPlayer *GetDefaultPlayer(AActor *WorldContextActor,
                                            int32 PlayerIndex = 0);
};
