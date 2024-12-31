#include "PlayerCombatComponent.h"
#include "HelperMacros.h"

UPlayerCombatComponent::UPlayerCombatComponent() {
    PrimaryComponentTick.bCanEverTick = false;
}

void UPlayerCombatComponent::BeginPlay() {
    Super::BeginPlay();
}

void UPlayerCombatComponent::RegisterWeapon_Implementation(FGameplayTag InTag,
                                                           AActor *InActor,
                                                           bool ShouldEquip) {
    MYSTICA_IF_NULL_LOG_AND_RETURN(LogTemp, Error, InActor);
    MYSTICA_LOG_AND_RETURN_IF(WeaponsMap.Contains(InTag), LogTemp, Error,
                              TEXT("Not registering Weapon twice"));

    WeaponsMap.Emplace(InTag, InActor);
    if (ShouldEquip) {
        EquippedWeaponTag = InTag;
    }
}

AActor *UPlayerCombatComponent::GetWeaponByTag_Implementation(
    FGameplayTag InTag) const {
    AActor *const *FoundWeapon = WeaponsMap.Find(InTag);
    MYSTICA_IF_NULL_LOG_AND_RETURN_VALUE(LogTemp, Error, FoundWeapon, nullptr);

    return *FoundWeapon;
}

AActor *UPlayerCombatComponent::GetEquippedWeapon() const {
    MYSTICA_RETURN_VALUE_IF(!EquippedWeaponTag.IsValid(), nullptr);

    return GetWeaponByTag_Implementation(EquippedWeaponTag);
}
