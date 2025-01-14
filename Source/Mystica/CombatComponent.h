#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "UObject/Interface.h"
#include "CombatComponent.generated.h"

UINTERFACE(MinimalAPI)

class UCombatComponent : public UInterface {
    GENERATED_BODY()
};

class MYSTICA_API ICombatComponent {
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Combat")
    void RegisterWeapon(FGameplayTag InTag, AActor *InActor, bool ShouldEquip);

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Combat")
    void EquipWeapon(FGameplayTag InTag);

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Combat")
    AActor *GetWeaponByTag(FGameplayTag InTag) const;

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Combat")
    FGameplayTag GetEquippedWeaponTag() const;

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Combat")
    AActor *GetEquippedWeapon() const;

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Combat")
    void SetWeaponCollisionState(bool SetActive);
};
