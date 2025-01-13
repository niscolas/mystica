#pragma once

#include "Containers/Map.h"
#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"
#include "MiscTypes.h"
#include "PlayerAbilitiesProfileDataAsset.generated.h"

class UGameplayEffect;
class UGameplayAbility;
class UAbilitySystemComponent;

UCLASS()

class MYSTICA_API UPlayerAbilitiesProfileDataAsset : public UDataAsset {
    GENERATED_BODY()

public:
    void GiveAllTo(UAbilitySystemComponent *InAbilitySystemComponent,
                   int8 ApplyLevel = 1);

private:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess))
    TArray<TSubclassOf<UGameplayEffect>> StartUpEffects;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess))
    TMap<EAbilityActivationSituation, FGameplayAbilitiesArray> CommonAbilities;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess))
    TMap<FGameplayTag, TSubclassOf<UGameplayAbility>> GameplayTagBasedAbilities;
};
