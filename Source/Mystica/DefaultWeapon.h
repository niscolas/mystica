#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Mystica/Weapon.h"
#include "UObject/ScriptInterface.h"
#include "DefaultWeapon.generated.h"

class IWeaponComponent;

UCLASS()

class MYSTICA_API ADefaultWeapon : public AActor, public IWeapon {
    GENERATED_BODY()

public:
    ADefaultWeapon();

private:
    virtual void BeginPlay() override;

    UFUNCTION(BlueprintPure, Category = "Combat")
    virtual TScriptInterface<IWeaponComponent> GetWeaponComponent() override;

    TScriptInterface<IWeaponComponent> WeaponComponent;
};
