#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "WeaponComponent.generated.h"

class UShapeComponent;

DECLARE_MULTICAST_DELEGATE_OneParam(FHitTarget, APawn *);

UINTERFACE(MinimalAPI)

class UWeaponComponent : public UInterface {
    GENERATED_BODY()
};

class MYSTICA_API IWeaponComponent {
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Combat")
    AActor *GetActor() const;

    virtual UShapeComponent *GetCollisionComponent() const = 0;
    virtual const FHitTarget &GetBeginHitOtherPawnDelegate() const = 0;
    virtual const FHitTarget &GetEndHitOtherPawnDelegate() const = 0;
};
