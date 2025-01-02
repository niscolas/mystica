#include "PlayerAbilitiesProfileDataAsset.h"
#include "AbilitySystemComponent.h"
#include "GameplayAbilitySpec.h"
#include "GameplayAbilitySpecHandle.h"
#include "HelperMacros.h"
#include "Mystica/AbilityHelper.h"

void UPlayerAbilitiesProfileDataAsset::GiveAllTo(
    UAbilitySystemComponent *InAbilitySystemComponent, int8 ApplyLevel) {
    MYSTICA_RETURN_IF(!InAbilitySystemComponent);

    AbilityHelper::GiveCommonAbilitiesTo(
        InAbilitySystemComponent,
        CommonAbilities[EAbilityActivationSituation::OnGiven].Content,
        ApplyLevel);

    TArray<FGameplayAbilitySpecHandle> SpecHandles;
    AbilityHelper::GiveGameplayTagBasedAbilitiesTo(InAbilitySystemComponent,
                                                   GameplayTagBasedAbilities,
                                                   ApplyLevel, SpecHandles);
}
