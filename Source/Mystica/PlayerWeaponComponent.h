#pragma once

#include "Components/ActorComponent.h"
#include "CoreMinimal.h"
#include "PlayerWeaponComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))

class MYSTICA_API UPlayerWeaponComponent : public UActorComponent {
    GENERATED_BODY()

public:
    UPlayerWeaponComponent();

private:
    UPROPERTY(EditDefaultsOnly,
              BlueprintReadWrite,
              Category = "Combat",
              meta = (AllowPrivateAccess))
    TSubclassOf<UAnimInstance> LinkedAnimLayer;

    virtual void BeginPlay() override;
};
