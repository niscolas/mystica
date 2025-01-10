#include "KenneyCharacterAnimInstance.h"
#include "CombatComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "HelperMacros.h"

void UKenneyCharacterAnimInstance::NativeInitializeAnimation() {
    Super::NativeInitializeAnimation();

    OwningCharacter = Cast<ACharacter>(TryGetPawnOwner());
    MYSTICA_RETURN_IF(!OwningCharacter);

    CharacterMovementComponent = OwningCharacter->GetCharacterMovement();
    CombatComponent =
        OwningCharacter->FindComponentByInterface<UCombatComponent>();
}

void UKenneyCharacterAnimInstance::NativeThreadSafeUpdateAnimation(
    float DeltaSeconds) {
    Super::NativeThreadSafeUpdateAnimation(DeltaSeconds);

    MYSTICA_RETURN_IF(!OwningCharacter);
    MYSTICA_RETURN_IF(!CharacterMovementComponent);

    GroundSpeed = ComputeGroundSpeed(CharacterMovementComponent);
    HasAcceleration = CheckHasAcceleration(CharacterMovementComponent);

    if (HasAcceleration) {
        IdleElapsedTime = 0.0f;
        ShouldEnterDeepIdle = false;
    } else {
        IdleElapsedTime += DeltaSeconds;
        ShouldEnterDeepIdle = IdleElapsedTime >= EnterDeepIdleThreshold;
    }
}

float UKenneyCharacterAnimInstance::ComputeGroundSpeed(
    UCharacterMovementComponent *InCharacterMovementComponent) {
    return InCharacterMovementComponent->Velocity.Size2D();
}

bool UKenneyCharacterAnimInstance::CheckHasAcceleration(
    UCharacterMovementComponent *InCharacterMovementComponent) {
    return InCharacterMovementComponent->GetCurrentAcceleration()
               .SizeSquared2D() > 0;
}
