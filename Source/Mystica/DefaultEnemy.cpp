#include "DefaultEnemy.h"
#include "EnemyCombatComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

ADefaultEnemy::ADefaultEnemy() {
    PrimaryActorTick.bCanEverTick = false;

    AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

    bUseControllerRotationPitch = false;
    bUseControllerRotationRoll = false;
    bUseControllerRotationYaw = false;

    GetCharacterMovement()->bUseControllerDesiredRotation = false;
    GetCharacterMovement()->bOrientRotationToMovement = true;
    GetCharacterMovement()->RotationRate = FRotator(0.f, 180.f, 0.f);
    GetCharacterMovement()->MaxWalkSpeed = 300.f;
    GetCharacterMovement()->BrakingDecelerationWalking = 1000.f;

    CombatComponent = CreateDefaultSubobject<UEnemyCombatComponent>(
        TEXT("EnemyCombatComponent"));
}

void ADefaultEnemy::BeginPlay() {
    Super::BeginPlay();
}
