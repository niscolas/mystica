#include "EnemyCombatComponent.h"
#include "Abilities/GameplayAbilityTypes.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "Mystica/MysticaGameplayTags.h"
#include "Mystica/MysticaMiscFunctionLibrary.h"
#include "MysticaAbilitySystemFunctionLibrary.h"

UEnemyCombatComponent::UEnemyCombatComponent() {
    PrimaryComponentTick.bCanEverTick = false;
    WeaponInventory = FDefaultWeaponInventory(GetOwner());
}

void UEnemyCombatComponent::BeginPlay() {
    Super::BeginPlay();
}

void UEnemyCombatComponent::RegisterWeapon_Implementation(
    FGameplayTag InTag,
    const TScriptInterface<IWeaponComponent> &InWeaponComponent,
    bool ShouldEquip) {
    WeaponInventory.RegisterWeapon(InTag, InWeaponComponent, ShouldEquip);

    InWeaponComponent->GetBeginHitOtherPawnDelegate().AddUObject(
        this, &ThisClass::OnBeginHitOtherPawn);
    InWeaponComponent->GetEndHitOtherPawnDelegate().AddUObject(
        this, &ThisClass::OnEndHitOtherPawn);
}

void UEnemyCombatComponent::EquipWeapon_Implementation(FGameplayTag InTag) {
    WeaponInventory.EquipWeapon(InTag);
}

TScriptInterface<IWeaponComponent>
UEnemyCombatComponent::GetWeaponByTag_Implementation(FGameplayTag InTag) const {
    return WeaponInventory.GetWeaponByTag(InTag);
}

TScriptInterface<IWeaponComponent>
UEnemyCombatComponent::GetEquippedWeapon_Implementation() const {
    return WeaponInventory.GetEquippedWeapon();
}

FGameplayTag
UEnemyCombatComponent::GetEquippedWeaponTag_Implementation() const {
    return WeaponInventory.GetEquippedWeaponTag();
}

void UEnemyCombatComponent::SetWeaponCollisionState_Implementation(
    bool SetActive) {
    WeaponInventory.SetEquippedWeaponCollisionState(SetActive);
}

void UEnemyCombatComponent::OnBeginHitOtherPawn(APawn *OtherPawn) {
    if (!WeaponInventory.CommonOnBeginHitOtherPawn(OtherPawn)) {
        return;
    }

    bool IsValidBlock = false;
    const bool IsPlayerBlocking =
        UMysticaAbilitySystemFunctionLibrary::NativeCheckDoesActorHaveTag(
            OtherPawn, MysticaGameplayTags::Player_Status_Blocking);
    const bool IsMyAttackUnblockable = false;

    if (IsPlayerBlocking && !IsMyAttackUnblockable) {
        IsValidBlock = UMysticaMiscFunctionLibrary::CheckIsValidBlock(
            GetOwner(), OtherPawn);
    }

    FGameplayEventData EventData;
    EventData.Instigator = GetOwner();
    EventData.Target = OtherPawn;

    if (IsValidBlock) {
        UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
            OtherPawn, MysticaGameplayTags::Player_Event_SuccessfulBlock,
            EventData);
    } else {
        UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
            GetOwner(), MysticaGameplayTags::Shared_Event_MeleeHit, EventData);
    }
}

void UEnemyCombatComponent::OnEndHitOtherPawn(APawn *OtherPawn) {
}
