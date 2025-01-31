#pragma once

#include "GameplayTagContainer.h"
#include "Mystica/WeaponComponent.h"
#include "UObject/ScriptInterface.h"

class UWeaponComponent;

class MYSTICA_API FDefaultWeaponInventory {
public:
    FDefaultWeaponInventory() = default;
    FDefaultWeaponInventory(AActor *InOwner);

    void
    RegisterWeapon(FGameplayTag InTag,
                   const TScriptInterface<IWeaponComponent> &InWeaponComponent,
                   bool ShouldEquip);
    bool EquipWeapon(FGameplayTag InTag);
    TScriptInterface<IWeaponComponent> GetWeaponByTag(FGameplayTag InTag) const;
    TScriptInterface<IWeaponComponent> GetEquippedWeapon() const;
    FGameplayTag GetEquippedWeaponTag() const;
    bool CheckHasWeapon(FGameplayTag InTag) const;
    void SetEquippedWeaponCollisionState(bool SetActive);
    TArray<APawn *> GetPawnsOverlappedByHit() const;
    bool CommonOnBeginHitOtherPawn(APawn *OtherPawn);

private:
    FGameplayTag EquippedWeaponTag;
    TMap<FGameplayTag, TScriptInterface<IWeaponComponent>> WeaponsMap;
    TArray<APawn *> PawnsOverlappedByHit;
    AActor *Owner;
};
