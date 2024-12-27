#include "KenneyCharacterAnimInstance.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "HelperMacros.h"

void UKenneyCharacterAnimInstance::NativeInitializeAnimation() {
    Super::NativeInitializeAnimation();

    OwningCharacter = Cast<ACharacter>(TryGetPawnOwner());
    MYSTICA_RETURN_IF(!OwningCharacter);

    CharacterMovementComponent = OwningCharacter->GetCharacterMovement();
}

void UKenneyCharacterAnimInstance::NativeThreadSafeUpdateAnimation(
    float DeltaSeconds) {
    Super::NativeThreadSafeUpdateAnimation(DeltaSeconds);

    MYSTICA_RETURN_IF(!OwningCharacter);
    MYSTICA_RETURN_IF(!CharacterMovementComponent);

    GroundSpeed = CharacterMovementComponent->Velocity.Size2D();
    HasAcceleration =
        CharacterMovementComponent->GetCurrentAcceleration().SizeSquared2D() >
        0;

    if (HasAcceleration) {
        IdleElapsedTime = 0.0f;
    } else {
        IdleElapsedTime += DeltaSeconds;
        ShouldEnterDeepIdle = IdleElapsedTime >= EnterDeepIdleThreshold;
    }
}
