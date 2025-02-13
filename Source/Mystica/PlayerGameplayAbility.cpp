#include "PlayerGameplayAbility.h"
#include "AbilitySystemComponent.h"
#include "CombatComponent.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/PlayerController.h"
#include "GameplayEffectTypes.h"
#include "HelperMacros.h"
#include "Logging/LogMacros.h"
#include "Mystica/MysticaGameplayTags.h"
#include "Mystica/PawnUI.h"
#include "Mystica/PlayerCombatComponent.h"
#include "MysticaAbilitySystemComponent.h"
#include "PlayerUIComponent.h"

APlayerController *
UPlayerGameplayAbility::GetPlayerControllerFromActorInfo() const {
    APawn *OwningPawn = Cast<APawn>(GetAvatarActorFromActorInfo());
    return Cast<APlayerController>(OwningPawn->GetController());
}

UCombatComponent *
UPlayerGameplayAbility::GetCombatComponentFromActorInfo() const {
    return GetAvatarActorFromActorInfo()
        ->FindComponentByInterface<UCombatComponent>();
}

UMysticaAbilitySystemComponent *
UPlayerGameplayAbility::GetPlayerAbilitySystemComponentFromActorInfo() const {
    return GetAvatarActorFromActorInfo()
        ->FindComponentByClass<UMysticaAbilitySystemComponent>();
}

UPlayerCombatComponent *
UPlayerGameplayAbility::GetPlayerCombatComponentFromActorInfo() const {
    return GetAvatarActorFromActorInfo()
        ->FindComponentByClass<UPlayerCombatComponent>();
}

UPlayerUIComponent *
UPlayerGameplayAbility::GetPlayerUIComponentFromActorInfo() const {
    IPawnUI *PawnUI = Cast<IPawnUI>(GetAvatarActorFromActorInfo());
    AActor *TargetActor = GetAvatarActorFromActorInfo();

    MYSTICA_LOG_AND_RETURN_VALUE_IF(
        !PawnUI, LogTemp, Warning, nullptr,
        TEXT("Will not get PlayerUIComponent, Actor (%s) is not an IPawnUI"),
        *TargetActor->GetActorNameOrLabel());

    TScriptInterface<IPawnUIComponent> PawnUIComponent =
        PawnUI->GetUIComponent();

    MYSTICA_LOG_AND_RETURN_VALUE_IF(
        !PawnUIComponent.GetInterface(), LogTemp, Warning, nullptr,
        TEXT("Will not get PlayerUIComponent, invalid PawnUIComponent provided "
             "by %s"),
        *TargetActor->GetActorNameOrLabel());

    UPlayerUIComponent *Result =
        Cast<UPlayerUIComponent>(PawnUIComponent.GetInterface());

    MYSTICA_LOG_AND_RETURN_VALUE_IF(
        !Result, LogTemp, Warning, nullptr,
        TEXT("Will not get PlayerUIComponent, %s's PawnUIComponent is not an "
             "UPlayerUIComponent"),
        *TargetActor->GetActorNameOrLabel());

    return Result;
}

void UPlayerGameplayAbility::OnGiveAbility(
    const FGameplayAbilityActorInfo *ActorInfo,
    const FGameplayAbilitySpec &Spec) {
    Super::OnGiveAbility(ActorInfo, Spec);

    MYSTICA_RETURN_IF(ActivationPolicy != EAbilityActivationPolicy::OnGiven);
    MYSTICA_RETURN_IF(!ActorInfo || Spec.IsActive());

    ActorInfo->AbilitySystemComponent->TryActivateAbility(Spec.Handle);
}

void UPlayerGameplayAbility::EndAbility(
    const FGameplayAbilitySpecHandle Handle,
    const FGameplayAbilityActorInfo *ActorInfo,
    const FGameplayAbilityActivationInfo ActivationInfo,
    bool bReplicateEndAbility,
    bool bWasCancelled) {
    Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility,
                      bWasCancelled);

    MYSTICA_RETURN_IF(ActivationPolicy != EAbilityActivationPolicy::OnGiven);
    MYSTICA_RETURN_IF(!ActorInfo);

    ActorInfo->AbilitySystemComponent->ClearAbility(Handle);
}

FGameplayEffectSpecHandle UPlayerGameplayAbility::MakeDamageEffectSpecHandle(
    TSubclassOf<UGameplayEffect> InEffectClass,
    float InWeaponBaseDamage,
    FGameplayTag InAttackTypeTag,
    int32 InCurrentComboCount) const {
    MYSTICA_LOG_AND_RETURN_VALUE_IF(
        !InEffectClass, LogTemp, Warning, FGameplayEffectSpecHandle(),
        TEXT("Will not Make Damage Effect Spec Handle, invalid inputs"));

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
        MysticaGameplayTags::Shared_SetByCaller_BaseDamage, InWeaponBaseDamage);
    if (InAttackTypeTag.IsValid()) {
        SpecHandle.Data->SetSetByCallerMagnitude(InAttackTypeTag,
                                                 InCurrentComboCount);
    }

    return SpecHandle;
}
