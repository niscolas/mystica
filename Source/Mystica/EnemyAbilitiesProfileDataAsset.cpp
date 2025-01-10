#include "EnemyAbilitiesProfileDataAsset.h"
#include "AbilitySystemComponent.h"
#include "HelperMacros.h"
#include "MysticaAbilitySystemFunctionLibrary.h"

void UEnemyAbilitiesProfileDataAsset::GiveAllTo(
    UAbilitySystemComponent *InAbilitySystemComponent, int8 ApplyLevel) {
    MYSTICA_RETURN_IF(!InAbilitySystemComponent);

    UMysticaAbilitySystemFunctionLibrary::GiveCommonAbilitiesTo(
        InAbilitySystemComponent, CombatAbilities, ApplyLevel);
}
