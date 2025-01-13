#include "MysticaAbilitySystemFunctionLibrary.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "GameplayEffect.h"
#include "HelperMacros.h"

void UMysticaAbilitySystemFunctionLibrary::GiveCommonAbilitiesTo(
    UAbilitySystemComponent *InAbilitySystemComponent,
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

bool UMysticaAbilitySystemFunctionLibrary::GiveGameplayTagBasedAbilityTo(
    UAbilitySystemComponent *InAbilitySystemComponent,
    FGameplayTag InTag,
    TSubclassOf<UGameplayAbility> InAbility,
    int8 ApplyLevel,
    FGameplayAbilitySpecHandle &OutSpecHandle) {
    MYSTICA_LOG_AND_RETURN_VALUE_IF(
        !InTag.IsValid() || !InAbility || !InAbilitySystemComponent, LogTemp,
        Error, false, TEXT("Invalid inputs, will not give ability"))

    FGameplayAbilitySpec Spec(InAbility);
    Spec.SourceObject = InAbilitySystemComponent->GetAvatarActor();
    Spec.Level = ApplyLevel;
    Spec.DynamicAbilityTags.AddTag(InTag);

    OutSpecHandle = InAbilitySystemComponent->GiveAbility(Spec);
    return true;
}

void UMysticaAbilitySystemFunctionLibrary::GiveGameplayTagBasedAbilitiesTo(
    UAbilitySystemComponent *InAbilitySystemComponent,
    TMap<FGameplayTag, TSubclassOf<UGameplayAbility>> InAbilities,
    int8 ApplyLevel,
    TArray<FGameplayAbilitySpecHandle> &OutSpecHandles) {
    for (TTuple<FGameplayTag, TSubclassOf<UGameplayAbility>> AbilityKvp :
         InAbilities) {
        FGameplayAbilitySpecHandle OutSpecHandle;
        GiveGameplayTagBasedAbilityTo(InAbilitySystemComponent, AbilityKvp.Key,
                                      AbilityKvp.Value, ApplyLevel,
                                      OutSpecHandle);

        OutSpecHandles.AddUnique(OutSpecHandle);
    }
}

UAbilitySystemComponent *
UMysticaAbilitySystemFunctionLibrary::NativeGetAbilitySystemComponentFromActor(
    AActor *InActor) {
    MYSTICA_LOG_AND_RETURN_VALUE_IF(
        !InActor, LogTemp, Error, nullptr,
        TEXT("Will not get Ability System Component, invalid inputs"));

    return UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(InActor);
}

void UMysticaAbilitySystemFunctionLibrary::AddGameplayTagToActor(
    AActor *InActor, FGameplayTag InTag) {
    UAbilitySystemComponent *AbilitySystemComponent =
        NativeGetAbilitySystemComponentFromActor(InActor);

    MYSTICA_LOG_AND_RETURN_IF(
        AbilitySystemComponent->HasMatchingGameplayTag(InTag), LogTemp, Error,
        TEXT("Will not add Tag, Actor already has it"));

    AbilitySystemComponent->AddLooseGameplayTag(InTag);
}

void UMysticaAbilitySystemFunctionLibrary::RemoveGameplayTagFromActor(
    AActor *InActor, FGameplayTag InTag) {
    UAbilitySystemComponent *AbilitySystemComponent =
        NativeGetAbilitySystemComponentFromActor(InActor);

    MYSTICA_LOG_AND_RETURN_IF(
        !AbilitySystemComponent->HasMatchingGameplayTag(InTag), LogTemp, Error,
        TEXT("Will not remove Tag, Actor doesn't have it"));

    AbilitySystemComponent->RemoveLooseGameplayTag(InTag);
}

bool UMysticaAbilitySystemFunctionLibrary::BranchOnDoesActorHaveTag(
    AActor *InActor, FGameplayTag InTag) {
    UAbilitySystemComponent *AbilitySystemComponent =
        NativeGetAbilitySystemComponentFromActor(InActor);

    return AbilitySystemComponent->HasMatchingGameplayTag(InTag);
}

bool UMysticaAbilitySystemFunctionLibrary::
    CheckDoesHaveGivenActivatableAbilityClass(
        UAbilitySystemComponent *InAbilitySystemComponent,
        TSubclassOf<UGameplayAbility> InAbilityClass) {
    MYSTICA_LOG_AND_RETURN_VALUE_IF(
        !InAbilitySystemComponent, LogTemp, Error, false,
        TEXT("Will not check if Ability System Component has given ability, "
             "invalid inputs"));

    for (const FGameplayAbilitySpec &Spec :
         InAbilitySystemComponent->GetActivatableAbilities()) {
        MYSTICA_CONTINUE_IF(Spec.Ability->GetClass() != InAbilityClass);
        return true;
    }

    return false;
}

bool UMysticaAbilitySystemFunctionLibrary::
    BranchOnDoesHaveGivenActivatableAbilityClass(
        UAbilitySystemComponent *InAbilitySystemComponent,
        TSubclassOf<UGameplayAbility> InAbilityClass) {
    return CheckDoesHaveGivenActivatableAbilityClass(InAbilitySystemComponent,
                                                     InAbilityClass);
}

void UMysticaAbilitySystemFunctionLibrary::ApplyEffectsToAbilitySystemComponent(
    UAbilitySystemComponent *InAbilitySystemComponent,
    TArray<TSubclassOf<UGameplayEffect>> InEffects,
    int32 ApplyLevel) {
    MYSTICA_LOG_AND_RETURN_IF(!InAbilitySystemComponent || InEffects.IsEmpty(),
                              LogTemp, Error,
                              TEXT("Will not apply Effects, invalid inputs"));

    for (TSubclassOf<UGameplayEffect> EffectClass : InEffects) {
        MYSTICA_CONTINUE_IF(!EffectClass);

        UGameplayEffect *Effect =
            EffectClass->GetDefaultObject<UGameplayEffect>();
        InAbilitySystemComponent->ApplyGameplayEffectToSelf(
            Effect, ApplyLevel, InAbilitySystemComponent->MakeEffectContext());
    }
}
