#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "DefaultEnemy.generated.h"

class UEnemyCombatComponent;

UCLASS()

class MYSTICA_API ADefaultEnemy : public ACharacter {
    GENERATED_BODY()

public:
    ADefaultEnemy();

private:
    virtual void BeginPlay() override;

    UPROPERTY(VisibleAnywhere,
              BlueprintReadOnly,
              Category = "Combat",
              meta = (AllowPrivateAccess))
    UEnemyCombatComponent *CombatComponent;
};
