#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "WeaponComponent.generated.h"

class UShapeComponent;

UINTERFACE(MinimalAPI)

class UWeaponComponent : public UInterface {
    GENERATED_BODY()
};

class MYSTICA_API IWeaponComponent {
    GENERATED_BODY()

public:
    virtual UShapeComponent *GetCollisionComponent() const = 0;
};
