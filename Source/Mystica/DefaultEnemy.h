#pragma once

#include "AbilitySystemInterface.h"
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "Mystica/CombatPawn.h"
#include "PawnUI.h"
#include "UObject/SoftObjectPtr.h"
#include "DefaultEnemy.generated.h"

class UMysticaAttributeSet;
class UEnemyAbilitiesProfileDataAsset;
class UEnemyCombatComponent;
class UMysticaAbilitySystemComponent;
class IPawnUIComponent;
class UEnemyUIComponent;

UCLASS()

class ADefaultEnemy : public ACharacter,
                      public IAbilitySystemInterface,
                      public ICombatPawn,
                      public IPawnUI {
    GENERATED_BODY()

public:
    ADefaultEnemy();

    virtual UCombatComponent *GetCombatComponent() const override;
    virtual TScriptInterface<IPawnUIComponent> GetUIComponent() const override;

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
    UMysticaAttributeSet *AttributeSet;

    UPROPERTY(VisibleAnywhere,
              BlueprintReadOnly,
              Category = "Combat",
              meta = (AllowPrivateAccess))
    UEnemyCombatComponent *CombatComponent;

    UPROPERTY(VisibleAnywhere,
              BlueprintReadOnly,
              Category = "UI",
              meta = (AllowPrivateAccess))
    UEnemyUIComponent *UIComponent;
};
