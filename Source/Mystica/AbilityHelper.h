#pragma once

#include "Abilities/GameplayAbility.h"
#include "AbilitySystemComponent.h"
#include "GameplayAbilitySpec.h"
#include "GameplayTagContainer.h"
#include "GenericPlatform/GenericPlatformMisc.h"
#include "HelperMacros.h"
#include "Logging/LogVerbosity.h"
#include "Templates/UnrealTemplate.h"

namespace AbilityHelper {
static void
GiveCommonAbilitiesTo(UAbilitySystemComponent *InAbilitySystemComponent,
                      TArray<TSubclassOf<UGameplayAbility>> InAbilities,
                      int8 ApplyLevel) {
    MYSTICA_LOG_AND_RETURN_IF(
        !InAbilitySystemComponent || InAbilities.IsEmpty(), LogTemp, Error,
        TEXT("Invalid inputs, will not give abilities"));

    for (TSubclassOf<UGameplayAbility> Ability : InAbilities) {
        MYSTICA_CONTINUE_IF(!Ability);

        FGameplayAbilitySpec Spec(Ability);
        Spec.SourceObject = InAbilitySystemComponent->GetAvatarActor();
        Spec.Level = ApplyLevel;

        InAbilitySystemComponent->GiveAbility(Spec);
    }
}

static bool GiveGameplayTagBasedAbilityTo(
    UAbilitySystemComponent *InAbilitySystemComponent,
    FGameplayTag InTag,
    TSubclassOf<UGameplayAbility> InAbility,
    int8 ApplyLevel = 1,
    FGameplayAbilitySpecHandle *OutSpecHandle = nullptr) {
    MYSTICA_LOG_AND_RETURN_VALUE_IF(
        !InTag.IsValid() || !InAbility || !InAbilitySystemComponent, LogTemp,
        Error, false, TEXT("Invalid inputs, will not give ability"))

    FGameplayAbilitySpec Spec(InAbility);
    Spec.SourceObject = InAbilitySystemComponent->GetAvatarActor();
    Spec.Level = ApplyLevel;
    Spec.DynamicAbilityTags.AddTag(InTag);

    *OutSpecHandle = InAbilitySystemComponent->GiveAbility(Spec);
    return true;
}

static void GiveGameplayTagBasedAbilitiesTo(
    UAbilitySystemComponent *InAbilitySystemComponent,
    TMap<FGameplayTag, TSubclassOf<UGameplayAbility>> InAbilities,
    int8 ApplyLevel,
    TArray<FGameplayAbilitySpecHandle> &OutSpecHandles) {
    for (TTuple<FGameplayTag, TSubclassOf<UGameplayAbility>> AbilityKvp :
         InAbilities) {
        FGameplayAbilitySpecHandle *OutSpecHandle = nullptr;
        GiveGameplayTagBasedAbilityTo(InAbilitySystemComponent, AbilityKvp.Key,
                                      AbilityKvp.Value, ApplyLevel,
                                      OutSpecHandle);

        OutSpecHandles.AddUnique(*OutSpecHandle);
    }
}
} // namespace AbilityHelper
