#include "EnemyAbilitiesProfileDataAsset.h"
#include "AbilitySystemComponent.h"
#include "HelperMacros.h"
#include "MiscTypes.h"
#include "MysticaAbilitySystemFunctionLibrary.h"

void UEnemyAbilitiesProfileDataAsset::GiveAllTo(
    UAbilitySystemComponent *InAbilitySystemComponent, int8 ApplyLevel) {
    MYSTICA_RETURN_IF(!InAbilitySystemComponent);

    FGameplayAbilitiesArray *FoundOnGivenAbilities =
        CommonAbilities.Find(EAbilityActivationSituation::OnGiven);
    if (FoundOnGivenAbilities) {
        UMysticaAbilitySystemFunctionLibrary::GiveCommonAbilitiesTo(
            InAbilitySystemComponent, FoundOnGivenAbilities->Content,
            ApplyLevel);
    }

    FGameplayAbilitiesArray *FoundReactiveAbilities =
        CommonAbilities.Find(EAbilityActivationSituation::Reactive);
    if (FoundReactiveAbilities) {
        UMysticaAbilitySystemFunctionLibrary::GiveCommonAbilitiesTo(
            InAbilitySystemComponent, FoundReactiveAbilities->Content,
            ApplyLevel);
    }

    UMysticaAbilitySystemFunctionLibrary::GiveCommonAbilitiesTo(
        InAbilitySystemComponent, CombatAbilities, ApplyLevel);

    UMysticaAbilitySystemFunctionLibrary::ApplyEffectsToAbilitySystemComponent(
        InAbilitySystemComponent, StartUpEffects, ApplyLevel);
}
