#pragma once

#include "Abilities/GameplayAbility.h"
#include "CoreMinimal.h"
#include "ScalableFloat.h"
#include "UObject/WeakObjectPtrTemplates.h"
#include "EnemyGameplayAbility.generated.h"

class UEnemyCombatComponent;

UCLASS()

class MYSTICA_API UEnemyGameplayAbility : public UGameplayAbility {
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintPure, Category = "Ability System")
    UEnemyCombatComponent *GetCombatComponentFromActorInfo() const;

    UFUNCTION(BlueprintPure,
              Category = "Ability System",
              meta = (AllowPrivateAccess))
    FGameplayEffectSpecHandle
    MakeDamageEffectSpecHandle(TSubclassOf<UGameplayEffect> InEffectClass,
                               const FScalableFloat &InDamage) const;

    TWeakObjectPtr<UEnemyCombatComponent> CachedCombatComponent;
};
