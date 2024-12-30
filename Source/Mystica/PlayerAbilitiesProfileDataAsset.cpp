#include "PlayerAbilitiesProfileDataAsset.h"
#include "AbilitySystemComponent.h"
#include "GameplayAbilitySpec.h"
#include "HelperMacros.h"

void UPlayerAbilitiesProfileDataAsset::GiveAllTo(
    UAbilitySystemComponent *TargetAbilitySystemComponent, int8 ApplyLevel) {
    MYSTICA_RETURN_IF(!TargetAbilitySystemComponent);

    GiveTo(Content[EAbilityActivationSituation::OnGiven].Content,
           TargetAbilitySystemComponent, ApplyLevel);
}

void UPlayerAbilitiesProfileDataAsset::GiveTo(
    TArray<TSubclassOf<UGameplayAbility>> Abilities,
    UAbilitySystemComponent *TargetAbilitySystemComponent,
    int8 ApplyLevel) {
    MYSTICA_RETURN_IF(!TargetAbilitySystemComponent || Abilities.IsEmpty());

    for (TSubclassOf<UGameplayAbility> Ability : Abilities) {
        MYSTICA_CONTINUE_IF(!Ability);

        FGameplayAbilitySpec Spec(Ability);
        Spec.SourceObject = TargetAbilitySystemComponent->GetAvatarActor();
        Spec.Level = ApplyLevel;

        TargetAbilitySystemComponent->GiveAbility(Spec);
    }
}
