#include "DefaultWeapon.h"
#include "Mystica/WeaponComponent.h"
#include "UObject/ScriptInterface.h"

ADefaultWeapon::ADefaultWeapon() {
    PrimaryActorTick.bCanEverTick = false;
}

void ADefaultWeapon::BeginPlay() {
    Super::BeginPlay();
}

TScriptInterface<IWeaponComponent> ADefaultWeapon::GetWeaponComponent() {
    if (!WeaponComponent) {
        WeaponComponent = FindComponentByInterface<UWeaponComponent>();
    }

    return WeaponComponent;
}
