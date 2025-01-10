#include "DefaultEnemyAnimInstance.h"
#include "GameFramework/Character.h"
#include "HelperMacros.h"
#include "KenneyCharacterAnimInstance.h"

void UDefaultEnemyAnimInstance::NativeInitializeAnimation() {
    Super::NativeInitializeAnimation();

    OwningCharacter = Cast<ACharacter>(TryGetPawnOwner());
    MYSTICA_RETURN_IF(!OwningCharacter);

    CharacterMovementComponent = OwningCharacter->GetCharacterMovement();
    CombatComponent =
        OwningCharacter->FindComponentByInterface<UCombatComponent>();
}

void UDefaultEnemyAnimInstance::NativeThreadSafeUpdateAnimation(
    float DeltaSeconds) {
    Super::NativeThreadSafeUpdateAnimation(DeltaSeconds);

    MYSTICA_RETURN_IF(!OwningCharacter || !CharacterMovementComponent);

    GroundSpeed = UKenneyCharacterAnimInstance::ComputeGroundSpeed(
        CharacterMovementComponent);
    HasAcceleration = UKenneyCharacterAnimInstance::CheckHasAcceleration(
        CharacterMovementComponent);
}
