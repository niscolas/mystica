#pragma once

#include "AbilitySystemInterface.h"
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameplayTagContainer.h"
#include "Logging/LogMacros.h"
#include "Mystica/CombatPawn.h"
#include "UObject/SoftObjectPtr.h"
#include "DefaultPlayer.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
class UInputConfigDataAsset;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(config = Game)

class ADefaultPlayer : public ACharacter,
                       public IAbilitySystemInterface,
                       public ICombatPawn {
    GENERATED_BODY()

public:
    ADefaultPlayer();

    FORCEINLINE class USpringArmComponent *GetCameraBoom() const {
        return CameraBoom;
    }

    FORCEINLINE class UCameraComponent *GetFollowCamera() const {
        return FollowCamera;
    }

    virtual UCombatComponent *GetCombatComponent() const override;

private:
    UPROPERTY(VisibleAnywhere,
              BlueprintReadOnly,
              Category = Camera,
              meta = (AllowPrivateAccess = "true"))
    USpringArmComponent *CameraBoom;

    UPROPERTY(VisibleAnywhere,
              BlueprintReadOnly,
              Category = Camera,
              meta = (AllowPrivateAccess = "true"))
    UCameraComponent *FollowCamera;

    UPROPERTY(EditDefaultsOnly,
              BlueprintReadOnly,
              Category = Input,
              meta = (AllowPrivateAccess = "true"))
    UInputConfigDataAsset *InputConfigDataAsset;

    UPROPERTY(EditDefaultsOnly,
              BlueprintReadOnly,
              Category = "Ability System",
              meta = (AllowPrivateAccess = "true"))
    TSoftObjectPtr<class UPlayerAbilitiesProfileDataAsset> AbilitiesDataAsset;

    UPROPERTY(VisibleAnywhere,
              BlueprintReadOnly,
              Category = "Ability System",
              meta = (AllowPrivateAccess))
    class UMysticaAbilitySystemComponent *AbilitySystemComponent;

    UPROPERTY(VisibleAnywhere,
              BlueprintReadOnly,
              Category = "Ability System",
              meta = (AllowPrivateAccess))
    class UMysticaAttributeSet *AttributeSet;

    UPROPERTY(VisibleAnywhere,
              BlueprintReadOnly,
              Category = "Combat",
              meta = (AllowPrivateAccess))
    class UPlayerCombatComponent *CombatComponent;

    virtual void SetupPlayerInputComponent(
        class UInputComponent *PlayerInputComponent) override;
    virtual void BeginPlay() override;
    virtual void PossessedBy(AController *NewController) override;
    virtual UAbilitySystemComponent *GetAbilitySystemComponent() const override;

    void Move(const FInputActionValue &Value);
    void Look(const FInputActionValue &Value);
    void OnAbilityInputStarted(FGameplayTag InInputTag);
    void OnAbilityInputCompleted(FGameplayTag InInputTag);
};
