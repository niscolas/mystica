#pragma once

#include "GameplayTagContainer.h"
#include "Mystica/WeaponComponent.h"
#include "UObject/ScriptInterface.h"

class UWeaponComponent;

class MYSTICA_API FDefaultWeaponInventory {
public:
    void
    RegisterWeapon(FGameplayTag InTag,
                   const TScriptInterface<IWeaponComponent> &InWeaponComponent,
                   bool ShouldEquip);
    bool EquipWeapon(FGameplayTag InTag);
    TScriptInterface<IWeaponComponent> GetWeaponByTag(FGameplayTag InTag) const;
    TScriptInterface<IWeaponComponent> GetEquippedWeapon() const;
    FGameplayTag GetEquippedWeaponTag() const;
    bool CheckHasWeapon(FGameplayTag InTag) const;

private:
    FGameplayTag EquippedWeaponTag;
    TMap<FGameplayTag, TScriptInterface<IWeaponComponent>> WeaponsMap;
};
