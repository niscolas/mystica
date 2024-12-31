#include "MysticaAbilitySystemComponent.h"
#include "GameplayTagContainer.h"
#include "HelperMacros.h"

void UMysticaAbilitySystemComponent::OnAbilityInputStarted(
    const FGameplayTag &InInputTag) {
    MYSTICA_LOG_AND_RETURN_IF(
        !InInputTag.IsValid(), LogTemp, Error,
        TEXT("Will not try to Activate Abilities, invalid inputs"));

    for (const FGameplayAbilitySpec &Spec : GetActivatableAbilities()) {
        MYSTICA_CONTINUE_IF(!Spec.DynamicAbilityTags.HasTagExact(InInputTag));

        TryActivateAbility(Spec.Handle);
    }
}

void UMysticaAbilitySystemComponent::OnAbilityInputCompleted(
    const FGameplayTag &InInputTag) {
}
