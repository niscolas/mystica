#include "PlayerCombatComponent.h"
#include "HelperMacros.h"
#include "Mystica/DefaultWeaponInventory.h"
#include "PlayerWeaponComponent.h"

UPlayerCombatComponent::UPlayerCombatComponent() {
    PrimaryComponentTick.bCanEverTick = false;
}

void UPlayerCombatComponent::BeginPlay() {
    Super::BeginPlay();
}

void UPlayerCombatComponent::RegisterWeapon_Implementation(FGameplayTag InTag,
                                                           AActor *InActor,
                                                           bool ShouldEquip) {
    WeaponInventory.RegisterWeapon(InTag, InActor, ShouldEquip);
}

void UPlayerCombatComponent::EquipWeapon_Implementation(FGameplayTag InTag) {
    WeaponInventory.EquipWeapon(InTag);
}

AActor *UPlayerCombatComponent::GetWeaponByTag_Implementation(
    FGameplayTag InTag) const {
    return WeaponInventory.GetWeaponByTag(InTag);
}

UPlayerWeaponComponent *UPlayerCombatComponent::GetPlayerWeaponComponentByTag(
    FGameplayTag InTag) const {
    const AActor *FoundWeapon = GetWeaponByTag_Implementation(InTag);
    MYSTICA_IF_NULL_LOG_AND_RETURN_VALUE(LogTemp, Error, FoundWeapon, nullptr);

    return FoundWeapon->GetComponentByClass<UPlayerWeaponComponent>();
}

AActor *UPlayerCombatComponent::GetEquippedWeapon_Implementation() const {
    return WeaponInventory.GetEquippedWeapon();
}

FGameplayTag
UPlayerCombatComponent::GetEquippedWeaponTag_Implementation() const {
    return WeaponInventory.GetEquippedWeaponTag();
}
