#include "DefaultWeaponInventory.h"
#include "Components/ShapeComponent.h"
#include "GenericPlatform/GenericPlatformMisc.h"
#include "HelperMacros.h"
#include "Logging/LogVerbosity.h"
#include "Mystica/WeaponComponent.h"
#include "UObject/ScriptInterface.h"

FDefaultWeaponInventory::FDefaultWeaponInventory(AActor *InOwner) {
    Owner = InOwner;
}

void FDefaultWeaponInventory::RegisterWeapon(
    FGameplayTag InTag,
    const TScriptInterface<IWeaponComponent> &InWeaponComponent,
    bool ShouldEquip) {
    MYSTICA_IF_NULL_LOG_AND_RETURN(LogTemp, Warning, InWeaponComponent);
    MYSTICA_LOG_AND_RETURN_IF(WeaponsMap.Contains(InTag), LogTemp, Warning,
                              TEXT("Not registering Weapon twice"));

    WeaponsMap.Emplace(InTag, InWeaponComponent);
    if (ShouldEquip) {
        EquipWeapon(InTag);
    }
}

bool FDefaultWeaponInventory::EquipWeapon(FGameplayTag InTag) {
    MYSTICA_LOG_AND_RETURN_VALUE_IF(
        !InTag.IsValid(), LogTemp, Warning, false,
        TEXT("Will not equip weapon, invalid inputs"));

    MYSTICA_LOG_AND_RETURN_VALUE_IF(
        !CheckHasWeapon(InTag), LogTemp, Warning, false,
        TEXT("Will not equip weapon that's not registered"));

    EquippedWeaponTag = InTag;
    return true;
}

TScriptInterface<IWeaponComponent>
FDefaultWeaponInventory::GetWeaponByTag(FGameplayTag InTag) const {
    const TScriptInterface<IWeaponComponent> *FoundWeapon =
        WeaponsMap.Find(InTag);
    MYSTICA_IF_NULL_LOG_AND_RETURN_VALUE(LogTemp, Warning, FoundWeapon,
                                         TScriptInterface<IWeaponComponent>());

    return *FoundWeapon;
}

TScriptInterface<IWeaponComponent>
FDefaultWeaponInventory::GetEquippedWeapon() const {
    MYSTICA_RETURN_VALUE_IF(!EquippedWeaponTag.IsValid(), nullptr);

    return GetWeaponByTag(EquippedWeaponTag);
}

FGameplayTag FDefaultWeaponInventory::GetEquippedWeaponTag() const {
    return EquippedWeaponTag;
}

bool FDefaultWeaponInventory::CheckHasWeapon(FGameplayTag InTag) const {
    return GetWeaponByTag(InTag) != nullptr;
}

void FDefaultWeaponInventory::SetEquippedWeaponCollisionState(bool SetActive) {
    TScriptInterface<IWeaponComponent> FoundWeapon = GetEquippedWeapon();

    MYSTICA_IF_NULL_LOG_AND_RETURN(LogTemp, Warning, FoundWeapon);

    UShapeComponent *CollisionComponent = FoundWeapon->GetCollisionComponent();
    MYSTICA_IF_NULL_LOG_AND_RETURN(LogTemp, Warning, CollisionComponent);

    ECollisionEnabled::Type NewCollisionEnabledType;
    if (SetActive) {
        NewCollisionEnabledType = ECollisionEnabled::QueryOnly;
    } else {
        NewCollisionEnabledType = ECollisionEnabled::NoCollision;
    }

    CollisionComponent->SetCollisionEnabled(NewCollisionEnabledType);
    PawnsOverlappedByHit.Empty();
}

TArray<APawn *> FDefaultWeaponInventory::GetPawnsOverlappedByHit() const {
    return PawnsOverlappedByHit;
}

bool FDefaultWeaponInventory::CommonOnBeginHitOtherPawn(APawn *OtherPawn) {
    MYSTICA_RETURN_VALUE_IF(PawnsOverlappedByHit.Contains(OtherPawn), false);

    UE_LOG(LogTemp, Warning, TEXT("OnBeginHitOtherPawn: %s %s"),
           *Owner->GetActorNameOrLabel(), *OtherPawn->GetName());

    PawnsOverlappedByHit.AddUnique(OtherPawn);

    return true;
}
