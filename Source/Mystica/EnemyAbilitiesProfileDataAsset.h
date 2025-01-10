#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "EnemyAbilitiesProfileDataAsset.generated.h"

class UAbilitySystemComponent;
class UGameplayAbility;

UCLASS()

class MYSTICA_API UEnemyAbilitiesProfileDataAsset : public UDataAsset {
    GENERATED_BODY()

public:
    void GiveAllTo(UAbilitySystemComponent *InAbilitySystemComponent,
                   int8 ApplyLevel = 1);

private:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess))
    TArray<TSubclassOf<UGameplayAbility>> CombatAbilities;
};
