#include "PlayerAbilitiesProfileDataAsset.h"
#include "AbilitySystemComponent.h"
#include "GameplayAbilitySpec.h"
#include "HelperMacros.h"

void UPlayerAbilitiesProfileDataAsset::GiveAllTo(
    UAbilitySystemComponent *TargetAbilitySystemComponent, int8 ApplyLevel) {
    MYSTICA_RETURN_IF(!TargetAbilitySystemComponent);

    GiveCommonAbilitiesTo(
        CommonAbilities[EAbilityActivationSituation::OnGiven].Content,
        TargetAbilitySystemComponent, ApplyLevel);

    for (TTuple<FGameplayTag, TSubclassOf<UGameplayAbility>>
             GameplayTagBasedAbilityKvp : GameplayTagBasedAbilities) {
        GiveGameplayTagBasedAbilitiesTo(
            GameplayTagBasedAbilityKvp.Key, GameplayTagBasedAbilityKvp.Value,
            TargetAbilitySystemComponent, ApplyLevel);
    }
}

void UPlayerAbilitiesProfileDataAsset::GiveCommonAbilitiesTo(
    TArray<TSubclassOf<UGameplayAbility>> InAbilities,
    UAbilitySystemComponent *TargetAbilitySystemComponent,
    int8 ApplyLevel) {
    MYSTICA_LOG_AND_RETURN_IF(
        !TargetAbilitySystemComponent || InAbilities.IsEmpty(), LogTemp, Error,
        TEXT("Invalid inputs, will not give abilities"));

    for (TSubclassOf<UGameplayAbility> Ability : InAbilities) {
        MYSTICA_CONTINUE_IF(!Ability);

        FGameplayAbilitySpec Spec(Ability);
        Spec.SourceObject = TargetAbilitySystemComponent->GetAvatarActor();
        Spec.Level = ApplyLevel;

        TargetAbilitySystemComponent->GiveAbility(Spec);
    }
}

void UPlayerAbilitiesProfileDataAsset::GiveGameplayTagBasedAbilitiesTo(
    FGameplayTag InTag,
    TSubclassOf<UGameplayAbility> InAbility,
    UAbilitySystemComponent *TargetAbilitySystemComponent,
    int8 ApplyLevel) {
    MYSTICA_LOG_AND_RETURN_IF(
        !InTag.IsValid() || !InAbility || !TargetAbilitySystemComponent,
        LogTemp, Error, TEXT("Invalid inputs, will not give ability"))

    FGameplayAbilitySpec Spec(InAbility);
    Spec.SourceObject = TargetAbilitySystemComponent->GetAvatarActor();
    Spec.Level = ApplyLevel;
    Spec.DynamicAbilityTags.AddTag(InTag);

    TargetAbilitySystemComponent->GiveAbility(Spec);
}
