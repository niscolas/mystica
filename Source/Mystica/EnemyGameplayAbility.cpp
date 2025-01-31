#include "EnemyGameplayAbility.h"
#include "AbilitySystemComponent.h"
#include "EnemyCombatComponent.h"
#include "HelperMacros.h"
#include "MysticaGameplayTags.h"
#include "UObject/WeakObjectPtrTemplates.h"

UEnemyCombatComponent *
UEnemyGameplayAbility::GetCombatComponentFromActorInfo() const {
    if (!CachedCombatComponent.IsValid()) {
        GetAvatarActorFromActorInfo()
            ->FindComponentByClass<UEnemyCombatComponent>();
    }

    return CachedCombatComponent.IsValid() ? CachedCombatComponent.Get()
                                           : nullptr;
}

FGameplayEffectSpecHandle UEnemyGameplayAbility::MakeDamageEffectSpecHandle(
    TSubclassOf<UGameplayEffect> InEffectClass,
    const FScalableFloat &InDamage) const {
    MYSTICA_LOG_AND_RETURN_VALUE_IF(
        !InEffectClass, LogTemp, Warning, FGameplayEffectSpecHandle(),
        TEXT("Will not MakeDamageEffectSpecHandle, invalid inputs"));

    UAbilitySystemComponent *AbilitySystemComponent =
        GetAbilitySystemComponentFromActorInfo();

    FGameplayEffectContextHandle ContextHandle =
        AbilitySystemComponent->MakeEffectContext();
    ContextHandle.SetAbility(this);
    ContextHandle.AddSourceObject(GetAvatarActorFromActorInfo());
    ContextHandle.AddInstigator(GetAvatarActorFromActorInfo(),
                                GetAvatarActorFromActorInfo());

    FGameplayEffectSpecHandle SpecHandle =
        GetAbilitySystemComponentFromActorInfo()->MakeOutgoingSpec(
            InEffectClass, GetAbilityLevel(), ContextHandle);
    SpecHandle.Data->SetSetByCallerMagnitude(
        MysticaGameplayTags::Shared_SetByCaller_BaseDamage,
        InDamage.GetValueAtLevel(GetAbilityLevel()));

    return SpecHandle;
}
