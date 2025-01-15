#include "EnemyCombatComponent.h"

UEnemyCombatComponent::UEnemyCombatComponent() {
    PrimaryComponentTick.bCanEverTick = false;
}

void UEnemyCombatComponent::BeginPlay() {
    Super::BeginPlay();
}

void UEnemyCombatComponent::RegisterWeapon_Implementation(
    FGameplayTag InTag,
    const TScriptInterface<IWeaponComponent> &InWeaponComponent,
    bool ShouldEquip) {
    WeaponInventory.RegisterWeapon(InTag, InWeaponComponent, ShouldEquip);
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
