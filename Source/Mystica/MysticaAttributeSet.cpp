#include "MysticaAttributeSet.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AttributeSet.h"
#include "GameplayEffectExtension.h"
#include "Mystica/MysticaGameplayTags.h"
#include "MysticaGameplayTags.h"

UMysticaAttributeSet::UMysticaAttributeSet() {
    InitCurrentHealth(1);
    InitMaxHealth(1);

    InitCurrentRage(1);
    InitMaxRage(1);

    InitAttackBaseDamage(1);
    InitDefense(1);

    InitLightComboCount(1);
    InitHeavyComboCount(1);
}

void UMysticaAttributeSet::PostGameplayEffectExecute(
    const struct FGameplayEffectModCallbackData &Data) {
    if (Data.EvaluatedData.Attribute == GetCurrentHealthAttribute()) {
        SetCurrentHealth(FMath::Clamp(GetCurrentHealth(), 0.f, GetMaxHealth()));
    }

    if (Data.EvaluatedData.Attribute == GetCurrentRageAttribute()) {
        SetCurrentRage(FMath::Clamp(GetCurrentRage(), 0.f, GetMaxRage()));
    }

    if (Data.EvaluatedData.Attribute == GetDamageTakenAttribute()) {
        const float OldHealth = GetCurrentHealth();
        SetCurrentHealth(
            FMath::Clamp(OldHealth - GetDamageTaken(), 0.f, GetMaxHealth()));

        UE_LOG(LogTemp, Warning,
               TEXT("OldHealth: %f, DamageTaken: %f, NewCurrentHealth: %f"),
               OldHealth, GetDamageTaken(), GetCurrentHealth());

        if (GetCurrentHealth() <= 0) {
            UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
                GetOwningActor(), MysticaGameplayTags::Shared_Event_Death,
                FGameplayEventData());
        }
    }
}
