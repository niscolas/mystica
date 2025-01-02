#pragma once

#include "Components/ActorComponent.h"
#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "PlayerWeaponComponent.generated.h"

class UGameplayAbility;
class UInputMappingContext;

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

    UPROPERTY(EditDefaultsOnly,
              BlueprintReadWrite,
              Category = "Combat",
              meta = (AllowPrivateAccess))
    UInputMappingContext *EquippedInputMappingContext;

    UPROPERTY(EditDefaultsOnly,
              BlueprintReadWrite,
              Category = "Combat",
              meta = (AllowPrivateAccess))
    TMap<FGameplayTag, TSubclassOf<UGameplayAbility>> DefaultAbilities;

    virtual void BeginPlay() override;
};
