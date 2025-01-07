#pragma once

#include "CombatComponent.h"
#include "Components/ActorComponent.h"
#include "CoreMinimal.h"
#include "Mystica/DefaultWeaponInventory.h"
#include "EnemyCombatComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))

class MYSTICA_API UEnemyCombatComponent : public UActorComponent,
                                          public ICombatComponent {
    GENERATED_BODY()

public:
    UEnemyCombatComponent();

    UFUNCTION(BlueprintCallable, Category = "Combat")
    virtual void RegisterWeapon_Implementation(FGameplayTag InTag,
                                               AActor *InActor,
                                               bool ShouldEquip) override;

    UFUNCTION(BlueprintCallable, Category = "Combat")
    virtual void EquipWeapon_Implementation(FGameplayTag InTag) override;

    UFUNCTION(BlueprintPure, Category = "Combat")
    virtual AActor *
    GetWeaponByTag_Implementation(FGameplayTag InTag) const override;

    UFUNCTION(BlueprintPure, Category = "Combat")
    AActor *GetEquippedWeapon_Implementation() const override;

    UFUNCTION(BlueprintPure, Category = "Combat")
    virtual FGameplayTag GetEquippedWeaponTag_Implementation() const override;

private:
    UDefaultWeaponInventory WeaponInventory;

    virtual void BeginPlay() override;
};
