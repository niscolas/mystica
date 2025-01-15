#pragma once

#include "CombatComponent.h"
#include "Components/ActorComponent.h"
#include "Containers/Map.h"
#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Mystica/DefaultWeaponInventory.h"
#include "Mystica/WeaponComponent.h"
#include "UObject/ScriptInterface.h"
#include "PlayerCombatComponent.generated.h"

class UPlayerWeaponComponent;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))

class MYSTICA_API UPlayerCombatComponent : public UActorComponent,
                                           public ICombatComponent {
    GENERATED_BODY()

public:
    UPlayerCombatComponent();

    UFUNCTION(BlueprintCallable, Category = "Combat")
    virtual void RegisterWeapon_Implementation(
        FGameplayTag InTag,
        const TScriptInterface<IWeaponComponent> &InWeaponComponent,
        bool ShouldEquip) override;

    UFUNCTION(BlueprintCallable, Category = "Combat")
    virtual void EquipWeapon_Implementation(FGameplayTag InTag) override;

    UFUNCTION(BlueprintPure, Category = "Combat")
    virtual TScriptInterface<IWeaponComponent>
    GetWeaponByTag_Implementation(FGameplayTag InTag) const override;

    UFUNCTION(BlueprintPure, Category = "Combat")
    UPlayerWeaponComponent *
    GetPlayerWeaponComponentByTag(FGameplayTag InTag) const;

    UFUNCTION(BlueprintPure, Category = "Combat")
    TScriptInterface<IWeaponComponent>
    GetEquippedWeapon_Implementation() const override;

    UFUNCTION(BlueprintPure, Category = "Combat")
    virtual FGameplayTag GetEquippedWeaponTag_Implementation() const override;

    UFUNCTION(BlueprintCallable, Category = "Combat")
    virtual void
    SetWeaponCollisionState_Implementation(bool SetActive) override;

private:
    FDefaultWeaponInventory WeaponInventory;

    virtual void BeginPlay() override;
};
