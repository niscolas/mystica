#pragma once

#include "Components/ActorComponent.h"
#include "CoreMinimal.h"
#include "GameplayAbilitySpecHandle.h"
#include "GameplayTagContainer.h"
#include "PlayerWeaponComponent.generated.h"

class UGameplayAbility;
class UInputMappingContext;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))

class MYSTICA_API UPlayerWeaponComponent : public UActorComponent {
    GENERATED_BODY()

public:
    UPlayerWeaponComponent();

    UFUNCTION(BlueprintCallable, Category = "Combat")
    void AssignGrantedAbilitiesSpecHandles(
        const TArray<FGameplayAbilitySpecHandle> &InSpecHandles);

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

    UPROPERTY(VisibleAnywhere,
              BlueprintReadWrite,
              Category = "Combat",
              meta = (AllowPrivateAccess))
    TArray<FGameplayAbilitySpecHandle> GrantedAbilitySpecHandles;

    virtual void BeginPlay() override;
};
