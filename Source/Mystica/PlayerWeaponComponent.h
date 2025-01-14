#pragma once

#include "Components/ActorComponent.h"
#include "CoreMinimal.h"
#include "GameplayAbilitySpecHandle.h"
#include "GameplayTagContainer.h"
#include "Mystica/WeaponComponent.h"
#include "PlayerWeaponComponent.generated.h"

class UShapeComponent;
class UGameplayAbility;
class UInputMappingContext;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))

class MYSTICA_API UPlayerWeaponComponent : public UActorComponent,
                                           public IWeaponComponent {
    GENERATED_BODY()

public:
    UPlayerWeaponComponent();

    UFUNCTION(BlueprintCallable, Category = "Combat")
    void AssignGrantedAbilitiesSpecHandles(
        const TArray<FGameplayAbilitySpecHandle> &InSpecHandles);

    virtual UShapeComponent *GetCollisionComponent() const override;

private:
    UPROPERTY(EditDefaultsOnly,
              BlueprintReadWrite,
              Category = "Combat",
              meta = (AllowPrivateAccess))
    UShapeComponent *CollisionComponent;

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

    UFUNCTION()
    void
    OnCollisionComponentBeginOverlap(UPrimitiveComponent *OverlappedComponent,
                                     AActor *OtherActor,
                                     UPrimitiveComponent *OtherComp,
                                     int32 OtherBodyIndex,
                                     bool bFromSweep,
                                     const FHitResult &SweepResult);

    UFUNCTION()
    void
    OnCollisionComponentEndOverlap(UPrimitiveComponent *OverlappedComponent,
                                   AActor *OtherActor,
                                   UPrimitiveComponent *OtherComp,
                                   int32 OtherBodyIndex);

    virtual void BeginPlay() override;
};
