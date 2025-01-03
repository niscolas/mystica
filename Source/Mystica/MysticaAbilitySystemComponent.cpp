#include "MysticaAbilitySystemComponent.h"
#include "GameplayTagContainer.h"
#include "HelperMacros.h"
#include "MysticaAbilitySystemFunctionLibrary.h"

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

void UMysticaAbilitySystemComponent::GrantWeaponAbilities(
    const TMap<FGameplayTag, TSubclassOf<UGameplayAbility>> &InAbilities,
    int32 ApplyLevel,
    TArray<FGameplayAbilitySpecHandle> &OutSpecHandles) {
    UMysticaAbilitySystemFunctionLibrary::GiveGameplayTagBasedAbilitiesTo(
        this, InAbilities, ApplyLevel, OutSpecHandles);
}

void UMysticaAbilitySystemComponent::RemoveWeaponAbilities(
    UPARAM(ref) TArray<FGameplayAbilitySpecHandle> &InSpecHandles) {
    MYSTICA_LOG_AND_RETURN_IF(
        InSpecHandles.IsEmpty(), LogTemp, Error,
        TEXT("Will not remove abilities, invalid inputs"));

    for (const FGameplayAbilitySpecHandle &SpecHandle : InSpecHandles) {
        MYSTICA_LOG_AND_CONTINUE_IF(
            !SpecHandle.IsValid(), LogTemp, Error,
            TEXT("Will not remove current ability, invalid input"));
        ClearAbility(SpecHandle);
    }

    InSpecHandles.Empty();
}
