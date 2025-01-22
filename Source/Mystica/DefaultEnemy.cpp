#include "DefaultEnemy.h"
#include "Components/WidgetComponent.h"
#include "EnemyAbilitiesProfileDataAsset.h"
#include "EnemyCombatComponent.h"
#include "EnemyUIComponent.h"
#include "Engine/AssetManager.h"
#include "Engine/StreamableManager.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "HelperMacros.h"
#include "Mystica/EnemyUIWidget.h"
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

    UIComponent =
        CreateDefaultSubobject<UEnemyUIComponent>(TEXT("EnemyUIComponent"));

    HealthBarWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(
        TEXT("HealthBarWidgetComponent"));
    HealthBarWidgetComponent->SetupAttachment(GetMesh());
}

UCombatComponent *ADefaultEnemy::GetCombatComponent() const {
    return FindComponentByInterface<UCombatComponent>();
}

TScriptInterface<IPawnUIComponent> ADefaultEnemy::GetUIComponent() const {
    return UIComponent;
}

void ADefaultEnemy::BeginPlay() {
    Super::BeginPlay();

    UUserWidget *UserWidget = HealthBarWidgetComponent->GetUserWidgetObject();

    MYSTICA_LOG_AND_RETURN_IF(!UserWidget->Implements<UEnemyUIWidget>(),
                              LogTemp, Warning,
                              TEXT("Will not Initialize Health Bar (%s), it's "
                                   "not an IEnemyUIWidget"),
                              *UserWidget->GetName());

    IEnemyUIWidget::Execute_EnemyUIWidgetInitialize(UserWidget, UIComponent);
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
