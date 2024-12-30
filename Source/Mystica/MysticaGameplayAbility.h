#pragma once

#include "Abilities/GameplayAbility.h"
#include "CombatComponent.h"
#include "CoreMinimal.h"
#include "MysticaGameplayAbility.generated.h"

UENUM(BlueprintType)
enum class EAbilityActivationPolicy : uint8 { OnTriggered, OnGiven };

UCLASS()

class MYSTICA_API UMysticaGameplayAbility : public UGameplayAbility {
    GENERATED_BODY()

private:
    UPROPERTY(EditDefaultsOnly,
              BlueprintReadWrite,
              Category = "Ability System",
              meta = (AllowPrivateAccess))
    EAbilityActivationPolicy ActivationPolicy =
        EAbilityActivationPolicy::OnTriggered;

    UFUNCTION(BlueprintPure,
              Category = "Ability System",
              meta = (AllowPrivateAccess))
    UCombatComponent *GetCombatComponentFromActorInfo() const;

    virtual void OnGiveAbility(const FGameplayAbilityActorInfo *ActorInfo,
                               const FGameplayAbilitySpec &Spec) override;
    virtual void EndAbility(const FGameplayAbilitySpecHandle Handle,
                            const FGameplayAbilityActorInfo *ActorInfo,
                            const FGameplayAbilityActivationInfo ActivationInfo,
                            bool bReplicateEndAbility,
                            bool bWasCancelled) override;
};
