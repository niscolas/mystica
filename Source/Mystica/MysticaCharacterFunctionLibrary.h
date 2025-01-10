#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "MysticaCharacterFunctionLibrary.generated.h"

class UAnimInstance;

UCLASS()

class MYSTICA_API UMysticaCharacterFunctionLibrary
    : public UBlueprintFunctionLibrary {
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintPure,
              Category = "Character|Mystica Function Library",
              meta = (DefaultToSelf = "InCharacter"))
    static UAnimInstance *GetAnimInstance(ACharacter *InCharacter);
};
