#pragma once

#include "Containers/Map.h"
#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"
#include "PlayerAbilitiesProfileDataAsset.generated.h"

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

class MYSTICA_API UPlayerAbilitiesProfileDataAsset : public UDataAsset {
    GENERATED_BODY()

public:
    void GiveAllTo(UAbilitySystemComponent *InAbilitySystemComponent,
                   int8 ApplyLevel = 1);

private:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess))
    TMap<EAbilityActivationSituation, FGameplayAbilitiesArray> CommonAbilities;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess))
    TMap<FGameplayTag, TSubclassOf<UGameplayAbility>> GameplayTagBasedAbilities;
};
