#pragma once

#include "Animation/AnimInstance.h"
#include "CoreMinimal.h"
#include "Mystica/CombatComponent.h"
#include "KenneyCharacterAnimInstance.generated.h"

class UCharacterMovementComponent;
class UCombatComponent;

UCLASS()

class MYSTICA_API UKenneyCharacterAnimInstance : public UAnimInstance {
    GENERATED_BODY()

public:
    static float ComputeGroundSpeed(
        UCharacterMovementComponent *InCharacterMovementComponent);

    static bool CheckHasAcceleration(
        UCharacterMovementComponent *InCharacterMovementComponent);

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

    UPROPERTY(VisibleAnywhere,
              BlueprintReadOnly,
              Category = "Movement",
              meta = (AllowPrivateAccess))
    float LocomotionDirection;

    UPROPERTY(EditDefaultsOnly,
              BlueprintReadOnly,
              Category = "Deep Idle",
              meta = (AllowPrivateAccess))
    float EnterDeepIdleThreshold = 5.0f;

    UPROPERTY(VisibleAnywhere,
              BlueprintReadOnly,
              Category = "Deep Idle",
              meta = (AllowPrivateAccess))
    bool ShouldEnterDeepIdle;

    float IdleElapsedTime;
};
