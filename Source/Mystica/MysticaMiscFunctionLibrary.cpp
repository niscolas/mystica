#include "MysticaMiscFunctionLibrary.h"
#include "Mystica/CombatComponent.h"
#include "Mystica/CombatPawn.h"
#include "Mystica/HelperMacros.h"
#include "Mystica/Weapon.h"

UCombatComponent *
UMysticaMiscFunctionLibrary::GetCombatComponentFromActor(AActor *InActor) {
    MYSTICA_LOG_AND_RETURN_VALUE_IF(
        !InActor, LogTemp, Warning, nullptr,
        TEXT("Will not get Combat Component, invalid inputs"));

    if (ICombatPawn *CombatPawn = Cast<ICombatPawn>(InActor)) {
        return CombatPawn->GetCombatComponent();
    }

    return nullptr;
}

TScriptInterface<IWeaponComponent>
UMysticaMiscFunctionLibrary::GetWeaponComponentFromActor(
    AActor *InWeaponActor) {
    MYSTICA_LOG_AND_RETURN_VALUE_IF(
        !InWeaponActor, LogTemp, Warning, nullptr,
        TEXT("Will not get Weapon Component, invalid inputs"));

    IWeapon *Weapon = Cast<IWeapon>(InWeaponActor);
    MYSTICA_LOG_AND_RETURN_VALUE_IF(
        !Weapon, LogTemp, Warning, nullptr,
        TEXT("InWeaponActor (%s) is not an IWeapon, returning nullptr"),
        *InWeaponActor->GetName());

    TScriptInterface<IWeaponComponent> Result = Weapon->GetWeaponComponent();
    MYSTICA_LOG_AND_RETURN_VALUE_IF(
        !Result, LogTemp, Warning, nullptr,
        TEXT("GetWeaponComponent() returned nullptr"));

    return Result;
}
