#include "PlayerAbilitiesProfileDataAsset.h"
#include "AbilitySystemComponent.h"
#include "GameplayAbilitySpec.h"
#include "GameplayAbilitySpecHandle.h"
#include "HelperMacros.h"
#include "MiscTypes.h"
#include "MysticaAbilitySystemFunctionLibrary.h"

void UPlayerAbilitiesProfileDataAsset::GiveAllTo(
    UAbilitySystemComponent *InAbilitySystemComponent, int8 ApplyLevel) {
    MYSTICA_RETURN_IF(!InAbilitySystemComponent);

    UMysticaAbilitySystemFunctionLibrary::ApplyEffectsToAbilitySystemComponent(
        InAbilitySystemComponent, StartUpEffects, ApplyLevel);

    UMysticaAbilitySystemFunctionLibrary::GiveCommonAbilitiesTo(
        InAbilitySystemComponent,
        CommonAbilities[EAbilityActivationSituation::OnGiven].Content,
        ApplyLevel);

    TArray<FGameplayAbilitySpecHandle> SpecHandles;
    UMysticaAbilitySystemFunctionLibrary::GiveGameplayTagBasedAbilitiesTo(
        InAbilitySystemComponent, GameplayTagBasedAbilities, ApplyLevel,
        SpecHandles);
}
