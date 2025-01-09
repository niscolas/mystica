#include "DefaultWeaponInventory.h"
#include "GenericPlatform/GenericPlatformMisc.h"
#include "HelperMacros.h"
#include "Logging/LogVerbosity.h"

void FDefaultWeaponInventory::RegisterWeapon(FGameplayTag InTag,
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

void FDefaultWeaponInventory::EquipWeapon(FGameplayTag InTag) {
    EquippedWeaponTag = InTag;
}

AActor *FDefaultWeaponInventory::GetWeaponByTag(FGameplayTag InTag) const {
    AActor *const *FoundWeapon = WeaponsMap.Find(InTag);
    MYSTICA_IF_NULL_LOG_AND_RETURN_VALUE(LogTemp, Error, FoundWeapon, nullptr);

    return *FoundWeapon;
}

AActor *FDefaultWeaponInventory::GetEquippedWeapon() const {
    MYSTICA_RETURN_VALUE_IF(!EquippedWeaponTag.IsValid(), nullptr);

    return GetWeaponByTag(EquippedWeaponTag);
}

FGameplayTag FDefaultWeaponInventory::GetEquippedWeaponTag() const {
    return EquippedWeaponTag;
}
