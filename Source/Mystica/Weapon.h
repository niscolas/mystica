#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Weapon.generated.h"

class IWeaponComponent;

UINTERFACE(MinimalAPI)

class UWeapon : public UInterface {
    GENERATED_BODY()
};

class MYSTICA_API IWeapon {
    GENERATED_BODY()

public:
    virtual TScriptInterface<IWeaponComponent> GetWeaponComponent() = 0;
};
