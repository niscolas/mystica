#pragma once

#include "CombatComponent.h"
#include "Components/ActorComponent.h"
#include "Containers/Map.h"
#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "PlayerCombatComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))

class MYSTICA_API UPlayerCombatComponent : public UActorComponent,
                                           public ICombatComponent {
    GENERATED_BODY()

public:
    UPlayerCombatComponent();

    UFUNCTION(BlueprintCallable, Category = "Combat")
    virtual void RegisterWeapon_Implementation(FGameplayTag InTag,
                                               AActor *InActor,
                                               bool ShouldEquip) override;

    UFUNCTION(BlueprintPure, Category = "Combat")
    AActor *GetWeaponByTag(FGameplayTag InTag) const;

    UFUNCTION(BlueprintPure, Category = "Combat")
    AActor *GetEquippedWeapon() const;

private:
    UPROPERTY(VisibleAnywhere,
              BlueprintReadWrite,
              Category = "Combat",
              meta = (AllowPrivateAccess))
    FGameplayTag EquippedWeaponTag;

    UPROPERTY(VisibleAnywhere,
              BlueprintReadOnly,
              Category = "Combat",
              meta = (AllowPrivateAccess))
    TMap<FGameplayTag, AActor *> WeaponsMap;

    virtual void BeginPlay() override;
};
