#pragma once

#include "GameplayTagContainer.h"

class MYSTICA_API FDefaultWeaponInventory {
public:
    void RegisterWeapon(FGameplayTag InTag, AActor *InActor, bool ShouldEquip);
    bool EquipWeapon(FGameplayTag InTag);
    AActor *GetWeaponByTag(FGameplayTag InTag) const;
    AActor *GetEquippedWeapon() const;
    FGameplayTag GetEquippedWeaponTag() const;
    bool CheckHasWeapon(FGameplayTag InTag) const;

private:
    FGameplayTag EquippedWeaponTag;
    TMap<FGameplayTag, AActor *> WeaponsMap;
};
