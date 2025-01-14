#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CombatPawn.generated.h"

class UCombatComponent;

UINTERFACE(MinimalAPI)

class UCombatPawn : public UInterface {
    GENERATED_BODY()
};

class MYSTICA_API ICombatPawn {
    GENERATED_BODY()

public:
    virtual UCombatComponent *GetCombatComponent() const = 0;
};
