#pragma once

#include "AbilitySystemInterface.h"
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "UObject/SoftObjectPtr.h"
#include "DefaultEnemy.generated.h"

class UEnemyAttributeSet;
class UEnemyAbilitiesProfileDataAsset;
class UEnemyCombatComponent;
class UMysticaAbilitySystemComponent;

UCLASS()

class ADefaultEnemy : public ACharacter, public IAbilitySystemInterface {
    GENERATED_BODY()

public:
    ADefaultEnemy();

private:
    virtual void BeginPlay() override;
    virtual void PossessedBy(AController *NewController) override;
    virtual UAbilitySystemComponent *GetAbilitySystemComponent() const override;

    UPROPERTY(EditDefaultsOnly,
              BlueprintReadOnly,
              Category = "Ability System",
              meta = (AllowPrivateAccess = "true"))
    TSoftObjectPtr<UEnemyAbilitiesProfileDataAsset> AbilitiesDataAsset;

    UPROPERTY(VisibleAnywhere,
              BlueprintReadOnly,
              Category = "Ability System",
              meta = (AllowPrivateAccess))
    UMysticaAbilitySystemComponent *AbilitySystemComponent;

    UPROPERTY(VisibleAnywhere,
              BlueprintReadOnly,
              Category = "Ability System",
              meta = (AllowPrivateAccess))
    UEnemyAttributeSet *AttributeSet;

    UPROPERTY(VisibleAnywhere,
              BlueprintReadOnly,
              Category = "Combat",
              meta = (AllowPrivateAccess))
    UEnemyCombatComponent *CombatComponent;
};
