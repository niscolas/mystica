#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "DefaultEnemy.generated.h"

UCLASS()

class MYSTICA_API ADefaultEnemy : public ACharacter {
    GENERATED_BODY()

public:
    ADefaultEnemy();

protected:
    virtual void BeginPlay() override;
}
