#include "MysticaAbilitySystemComponent.h"
#include "GameplayTagContainer.h"
#include "HelperMacros.h"
#include "Internationalization/LocalizedTextSourceTypes.h"
#include "Mystica/MysticaGameplayTags.h"
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
    MYSTICA_RETURN_IF(!InInputTag.IsValid() ||
                      !InInputTag.MatchesTag(MysticaGameplayTags::Input_Hold));

    for (const FGameplayAbilitySpec &Spec : GetActivatableAbilities()) {
        MYSTICA_CONTINUE_IF(!Spec.DynamicAbilityTags.HasTagExact(InInputTag) ||
                            !Spec.IsActive());

        CancelAbilityHandle(Spec.Handle);
    }
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

bool UMysticaAbilitySystemComponent::TryActivateAbilityByTag(
    FGameplayTag InTag) {
    MYSTICA_LOG_AND_RETURN_VALUE_IF(
        !InTag.IsValid(), LogTemp, Error, false,
        TEXT("Will not try to Activate Ability, invalid InTag"));

    TArray<FGameplayAbilitySpec *> FoundAbilitySpecs;
    GetActivatableGameplayAbilitySpecsByAllMatchingTags(
        InTag.GetSingleTagContainer(), FoundAbilitySpecs);

    MYSTICA_LOG_AND_RETURN_VALUE_IF(
        FoundAbilitySpecs.IsEmpty(), LogTemp, Error, false,
        TEXT("Will not try to Activate Ability, no matching Ability Specs"));

    const int32 RandomAbilitySpecIndex =
        FMath::RandRange(0, FoundAbilitySpecs.Num() - 1);

    MYSTICA_LOG_AND_RETURN_VALUE_IF(
        !FoundAbilitySpecs[RandomAbilitySpecIndex] ||
            FoundAbilitySpecs[RandomAbilitySpecIndex]->IsActive(),
        LogTemp, Error, false,
        TEXT("Will not try to Activate Ability, given Spec is invalid or is "
             "already active"));

    return TryActivateAbility(
        FoundAbilitySpecs[RandomAbilitySpecIndex]->Handle);
}
