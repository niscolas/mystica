#include "DefaultEnemy.h"
#include "EnemyAbilitiesProfileDataAsset.h"
#include "EnemyCombatComponent.h"
#include "Engine/AssetManager.h"
#include "Engine/StreamableManager.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "HelperMacros.h"
#include "Mystica/MysticaAbilitySystemComponent.h"
#include "MysticaAttributeSet.h"

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

    AbilitySystemComponent =
        CreateDefaultSubobject<UMysticaAbilitySystemComponent>(
            TEXT("MysticaAbilitySystemComponent"));
    AttributeSet =
        CreateDefaultSubobject<UMysticaAttributeSet>(TEXT("EnemyAttributeSet"));

    CombatComponent = CreateDefaultSubobject<UEnemyCombatComponent>(
        TEXT("EnemyCombatComponent"));
}

void ADefaultEnemy::BeginPlay() {
    Super::BeginPlay();
}

void ADefaultEnemy::PossessedBy(AController *NewController) {
    Super::PossessedBy(NewController);

    AbilitySystemComponent->InitAbilityActorInfo(this, this);

    MYSTICA_RETURN_IF_CANT_ENSURE_THAT(!AbilitiesDataAsset.IsNull());
    UAssetManager::GetStreamableManager().RequestAsyncLoad(
        AbilitiesDataAsset.ToSoftObjectPath(),
        FStreamableDelegate::CreateLambda([this]() {
            if (UEnemyAbilitiesProfileDataAsset *LoadedAbilitiesDataAsset =
                    AbilitiesDataAsset.Get()) {
                LoadedAbilitiesDataAsset->GiveAllTo(AbilitySystemComponent);
            }
        }));
}

UAbilitySystemComponent *ADefaultEnemy::GetAbilitySystemComponent() const {
    return AbilitySystemComponent;
}
