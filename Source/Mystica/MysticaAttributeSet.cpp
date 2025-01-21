#include "MysticaAttributeSet.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AttributeSet.h"
#include "GameplayEffectExtension.h"
#include "HelperMacros.h"
#include "Mystica/HelperMacros.h"
#include "Mystica/MysticaGameplayTags.h"
#include "Mystica/PawnUI.h"
#include "Mystica/PawnUIComponent.h"
#include "MysticaGameplayTags.h"
#include "UObject/WeakInterfacePtr.h"

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
    if (!CachedPawnUI.IsValid()) {
        CachedPawnUI = TWeakInterfacePtr<IPawnUI>(Data.Target.GetAvatarActor());
    }

    MYSTICA_LOG_AND_RETURN_IF(
        !CachedPawnUI.IsValid(), LogTemp, Warning,
        TEXT("Will not proceed on PostGameplayEffectExecute, Actor (%s) does "
             "not implement IPawnUI"),
        *Data.Target.GetAvatarActor()->GetName());

    TScriptInterface<IPawnUIComponent> PawnUIComponent =
        CachedPawnUI->GetUIComponent();

    MYSTICA_LOG_AND_RETURN_IF(
        !PawnUIComponent.GetObject(), LogTemp, Warning,
        TEXT("Will not proceed on PostGameplayEffectExecute, (%s's) "
             "PawnUIComponent "
             "is not valid"),
        *Data.Target.GetAvatarActor()->GetActorNameOrLabel());

    if (Data.EvaluatedData.Attribute == GetCurrentHealthAttribute()) {
        SetCurrentHealth(FMath::Clamp(GetCurrentHealth(), 0.f, GetMaxHealth()));

        BroadcastHealthPercentageChanged(PawnUIComponent);
    }

    if (Data.EvaluatedData.Attribute == GetCurrentRageAttribute()) {
        SetCurrentRage(FMath::Clamp(GetCurrentRage(), 0.f, GetMaxRage()));

        PawnUIComponent->GetRagePercentageChangedDelegate().Broadcast(
            GetCurrentRage() / GetMaxRage());
    }

    if (Data.EvaluatedData.Attribute == GetDamageTakenAttribute()) {
        const float OldHealth = GetCurrentHealth();
        SetCurrentHealth(
            FMath::Clamp(OldHealth - GetDamageTaken(), 0.f, GetMaxHealth()));

        BroadcastHealthPercentageChanged(PawnUIComponent);

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

void UMysticaAttributeSet::BroadcastHealthPercentageChanged(
    TScriptInterface<IPawnUIComponent> &PawnUIComponent) {
    PawnUIComponent->GetHealthPercentageChangedDelegate().Broadcast(
        GetCurrentHealth() / GetMaxHealth());
}
