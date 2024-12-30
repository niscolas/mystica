#include "MysticaGameplayAbility.h"
#include "AbilitySystemComponent.h"
#include "HelperMacros.h"

void UMysticaGameplayAbility::OnGiveAbility(
    const FGameplayAbilityActorInfo *ActorInfo,
    const FGameplayAbilitySpec &Spec) {
    Super::OnGiveAbility(ActorInfo, Spec);

    MYSTICA_RETURN_IF(ActivationPolicy != EAbilityActivationPolicy::OnGiven);
    MYSTICA_RETURN_IF(!ActorInfo || Spec.IsActive());

    ActorInfo->AbilitySystemComponent->TryActivateAbility(Spec.Handle);
}

void UMysticaGameplayAbility::EndAbility(
    const FGameplayAbilitySpecHandle Handle,
    const FGameplayAbilityActorInfo *ActorInfo,
    const FGameplayAbilityActivationInfo ActivationInfo,
    bool bReplicateEndAbility,
    bool bWasCancelled) {
    Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility,
                      bWasCancelled);

    MYSTICA_RETURN_IF(ActivationPolicy != EAbilityActivationPolicy::OnGiven);
    MYSTICA_RETURN_IF(!ActorInfo);

    ActorInfo->AbilitySystemComponent->ClearAbility(Handle);
}
