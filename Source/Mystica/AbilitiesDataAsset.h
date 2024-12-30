#pragma once

#include "Containers/Map.h"
#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "AbilitiesDataAsset.generated.h"

class UGameplayAbility;
class UAbilitySystemComponent;

UENUM(BlueprintType)
enum class EAbilityActivationSituation : uint8 { OnGiven };

USTRUCT(BlueprintType)

struct FGameplayAbilitiesArray {
    GENERATED_BODY()

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess))
    TArray<TSubclassOf<UGameplayAbility>> Content;
};

UCLASS()

class MYSTICA_API UAbilitiesDataAsset : public UDataAsset {
    GENERATED_BODY()

public:
    void GiveAllTo(UAbilitySystemComponent *TargetAbilitySystemComponent,
                   int8 ApplyLevel = 1);

private:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess))
    TMap<EAbilityActivationSituation, FGameplayAbilitiesArray> Content;

    void GiveTo(TArray<TSubclassOf<UGameplayAbility>> Abilities,
                UAbilitySystemComponent *TargetAbilitySystemComponent,
                int8 ApplyLevel = 1);
};
