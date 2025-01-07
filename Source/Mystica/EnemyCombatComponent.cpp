#include "EnemyCombatComponent.h"

UEnemyCombatComponent::UEnemyCombatComponent() {
    PrimaryComponentTick.bCanEverTick = false;
}

void UEnemyCombatComponent::BeginPlay() {
    Super::BeginPlay();
}

void UEnemyCombatComponent::RegisterWeapon_Implementation(FGameplayTag InTag,
                                                          AActor *InActor,
                                                          bool ShouldEquip) {
    WeaponInventory.RegisterWeapon(InTag, InActor, ShouldEquip);
}

void UEnemyCombatComponent::EquipWeapon_Implementation(FGameplayTag InTag) {
    WeaponInventory.EquipWeapon(InTag);
}

AActor *
UEnemyCombatComponent::GetWeaponByTag_Implementation(FGameplayTag InTag) const {
    return WeaponInventory.GetWeaponByTag(InTag);
}

AActor *UEnemyCombatComponent::GetEquippedWeapon_Implementation() const {
    return WeaponInventory.GetEquippedWeapon();
}

FGameplayTag
UEnemyCombatComponent::GetEquippedWeaponTag_Implementation() const {
    return WeaponInventory.GetEquippedWeaponTag();
}
