#pragma once

#include "Animation/AnimInstance.h"
#include "CoreMinimal.h"
#include "KenneyCharacterAnimInstance.generated.h"

UCLASS()

class MYSTICA_API UKenneyCharacterAnimInstance : public UAnimInstance {
    GENERATED_BODY()

private:
    virtual void NativeInitializeAnimation() override;
    virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds) override;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess))
    ACharacter *OwningCharacter;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess))
    class UCharacterMovementComponent *CharacterMovementComponent;

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
