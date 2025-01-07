#include "DefaultWeaponInventory.h"
#include "GenericPlatform/GenericPlatformMisc.h"
#include "HelperMacros.h"
#include "Logging/LogVerbosity.h"

void UDefaultWeaponInventory::RegisterWeapon(FGameplayTag InTag,
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

void UDefaultWeaponInventory::EquipWeapon(FGameplayTag InTag) {
    EquippedWeaponTag = InTag;
}

AActor *UDefaultWeaponInventory::GetWeaponByTag(FGameplayTag InTag) const {
    AActor *const *FoundWeapon = WeaponsMap.Find(InTag);
    MYSTICA_IF_NULL_LOG_AND_RETURN_VALUE(LogTemp, Error, FoundWeapon, nullptr);

    return *FoundWeapon;
}

AActor *UDefaultWeaponInventory::GetEquippedWeapon() const {
    MYSTICA_RETURN_VALUE_IF(!EquippedWeaponTag.IsValid(), nullptr);

    return GetWeaponByTag(EquippedWeaponTag);
}

FGameplayTag UDefaultWeaponInventory::GetEquippedWeaponTag() const {
    return EquippedWeaponTag;
}
