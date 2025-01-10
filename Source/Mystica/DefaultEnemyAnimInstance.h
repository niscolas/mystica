#pragma once

#include "Animation/AnimInstance.h"
#include "CoreMinimal.h"
#include "DefaultEnemyAnimInstance.generated.h"

class UCharacterMovementComponent;
class UCombatComponent;

UCLASS()

class MYSTICA_API UDefaultEnemyAnimInstance : public UAnimInstance {
    GENERATED_BODY()

private:
    virtual void NativeInitializeAnimation() override;
    virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds) override;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess))
    ACharacter *OwningCharacter;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess))
    UCharacterMovementComponent *CharacterMovementComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess))
    TScriptInterface<UCombatComponent> CombatComponent;

    UPROPERTY(VisibleAnywhere,
              BlueprintReadOnly,
              Category = "Movement",
              meta = (AllowPrivateAccess))
    bool HasAcceleration;

    UPROPERTY(VisibleAnywhere,
              BlueprintReadOnly,
              Category = "Movement",
              meta = (AllowPrivateAccess))
    float GroundSpeed;
};
