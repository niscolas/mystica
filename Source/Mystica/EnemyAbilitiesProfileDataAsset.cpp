#include "EnemyAbilitiesProfileDataAsset.h"
#include "AbilitySystemComponent.h"
#include "HelperMacros.h"
#include "MiscTypes.h"
#include "MysticaAbilitySystemFunctionLibrary.h"

void UEnemyAbilitiesProfileDataAsset::GiveAllTo(
    UAbilitySystemComponent *InAbilitySystemComponent, int8 ApplyLevel) {
    MYSTICA_RETURN_IF(!InAbilitySystemComponent);

    UMysticaAbilitySystemFunctionLibrary::ApplyEffectsToAbilitySystemComponent(
        InAbilitySystemComponent, StartUpEffects, ApplyLevel);

    FGameplayAbilitiesArray *FoundOnGivenAbilities =
        CommonAbilities.Find(EAbilityActivationSituation::OnGiven);
    if (FoundOnGivenAbilities) {
        UMysticaAbilitySystemFunctionLibrary::GiveCommonAbilitiesTo(
            InAbilitySystemComponent, FoundOnGivenAbilities->Content,
            ApplyLevel);
    }

    UMysticaAbilitySystemFunctionLibrary::GiveCommonAbilitiesTo(
        InAbilitySystemComponent, CombatAbilities, ApplyLevel);
}
