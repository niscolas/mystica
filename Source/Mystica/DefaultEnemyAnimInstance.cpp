#include "DefaultEnemyAnimInstance.h"
#include "GameFramework/Character.h"
#include "HelperMacros.h"
#include "KenneyCharacterAnimInstance.h"
#include "KismetAnimationLibrary.h"
#include "Mystica/MysticaAbilitySystemFunctionLibrary.h"

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
    LocomotionDirection = UKismetAnimationLibrary::CalculateDirection(
        OwningCharacter->GetVelocity(), OwningCharacter->GetActorRotation());
}

bool UDefaultEnemyAnimInstance::CheckDoesOwnerHaveTag(
    FGameplayTag InTag) const {
    APawn *OwningPawn = TryGetPawnOwner();
    MYSTICA_RETURN_VALUE_IF(!OwningPawn, false);

    return UMysticaAbilitySystemFunctionLibrary::NativeCheckDoesActorHaveTag(
        OwningPawn, InTag);
}
