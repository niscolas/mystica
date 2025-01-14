#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "MysticaMiscFunctionLibrary.generated.h"

class UCombatComponent;

UCLASS()

class MYSTICA_API UMysticaMiscFunctionLibrary
    : public UBlueprintFunctionLibrary {
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintPure, Category = "Combat|Function Library")
    static UCombatComponent *GetCombatComponentFromActor(AActor *InActor);
};
