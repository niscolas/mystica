#include "PlayerCombatComponent.h"
#include "Components/ShapeComponent.h"
#include "HelperMacros.h"
#include "Mystica/DefaultWeaponInventory.h"
#include "PlayerWeaponComponent.h"
#include "WeaponComponent.h"

UPlayerCombatComponent::UPlayerCombatComponent() {
    PrimaryComponentTick.bCanEverTick = false;
}

void UPlayerCombatComponent::BeginPlay() {
    Super::BeginPlay();
}

void UPlayerCombatComponent::RegisterWeapon_Implementation(
    FGameplayTag InTag,
    const TScriptInterface<IWeaponComponent> &InWeaponComponent,
    bool ShouldEquip) {
    WeaponInventory.RegisterWeapon(InTag, InWeaponComponent, ShouldEquip);
}

void UPlayerCombatComponent::EquipWeapon_Implementation(FGameplayTag InTag) {
    WeaponInventory.EquipWeapon(InTag);
}

TScriptInterface<IWeaponComponent>
UPlayerCombatComponent::GetWeaponByTag_Implementation(
    FGameplayTag InTag) const {
    return WeaponInventory.GetWeaponByTag(InTag);
}

UPlayerWeaponComponent *UPlayerCombatComponent::GetPlayerWeaponComponentByTag(
    FGameplayTag InTag) const {
    TScriptInterface<IWeaponComponent> FoundWeapon =
        GetWeaponByTag_Implementation(InTag);
    MYSTICA_IF_NULL_LOG_AND_RETURN_VALUE(LogTemp, Error, FoundWeapon, nullptr);

    return Cast<UPlayerWeaponComponent>(FoundWeapon.GetInterface());
}

TScriptInterface<IWeaponComponent>
UPlayerCombatComponent::GetEquippedWeapon_Implementation() const {
    return WeaponInventory.GetEquippedWeapon();
}

FGameplayTag
UPlayerCombatComponent::GetEquippedWeaponTag_Implementation() const {
    return WeaponInventory.GetEquippedWeaponTag();
}

void UPlayerCombatComponent::SetWeaponCollisionState_Implementation(
    bool SetActive) {
    UPlayerWeaponComponent *FoundWeapon =
        GetPlayerWeaponComponentByTag(GetEquippedWeaponTag_Implementation());
    MYSTICA_IF_NULL_LOG_AND_RETURN(LogTemp, Warning, FoundWeapon);

    UShapeComponent *CollisionComponent = FoundWeapon->GetCollisionComponent();
    MYSTICA_IF_NULL_LOG_AND_RETURN(LogTemp, Warning, CollisionComponent);

    CollisionComponent->SetCollisionEnabled(
        SetActive ? ECollisionEnabled::QueryOnly
                  : ECollisionEnabled::NoCollision);
}
