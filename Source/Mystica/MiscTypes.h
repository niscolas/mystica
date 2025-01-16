#pragma once

#include "CoreMinimal.h"
#include "MiscTypes.generated.h"

class UGameplayAbility;

UENUM(BlueprintType)
enum class EAbilityActivationSituation : uint8 { OnGiven, Reactive };

USTRUCT(BlueprintType)

struct FGameplayAbilitiesArray {
    GENERATED_BODY()

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess))
    TArray<TSubclassOf<UGameplayAbility>> Content;
};
