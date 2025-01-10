#include "DefaultPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Engine/LocalPlayer.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "HelperMacros.h"
#include "InputActionValue.h"
#include "InputConfigDataAsset.h"
#include "Mystica/MysticaGameplayTags.h"
#include "MysticaAbilitySystemComponent.h"
#include "MysticaEnhancedInputComponent.h"
#include "PlayerAbilitiesProfileDataAsset.h"
#include "PlayerAttributeSet.h"
#include "PlayerCombatComponent.h"
#include "Templates/Casts.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

ADefaultPlayer::ADefaultPlayer() {
    GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

    bUseControllerRotationPitch = false;
    bUseControllerRotationYaw = false;
    bUseControllerRotationRoll = false;

    GetCharacterMovement()->bOrientRotationToMovement = true;
    GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);

    GetCharacterMovement()->JumpZVelocity = 700.f;
    GetCharacterMovement()->AirControl = 0.35f;
    GetCharacterMovement()->MaxWalkSpeed = 500.f;
    GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
    GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
    GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

    CameraBoom =
        CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
    CameraBoom->SetupAttachment(RootComponent);
    CameraBoom->TargetArmLength = 400.0f;
    CameraBoom->bUsePawnControlRotation = true;

    FollowCamera =
        CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
    FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
    FollowCamera->bUsePawnControlRotation = false;

    AbilitySystemComponent =
        CreateDefaultSubobject<UMysticaAbilitySystemComponent>(
            TEXT("MysticaAbilitySystemComponent"));
    AttributeSet =
        CreateDefaultSubobject<UPlayerAttributeSet>(TEXT("PlayerAttributeSet"));

    CombatComponent = CreateDefaultSubobject<UPlayerCombatComponent>(
        TEXT("PlayerCombatComponent"));
}

void ADefaultPlayer::BeginPlay() {
    Super::BeginPlay();
}

void ADefaultPlayer::PossessedBy(AController *NewController) {
    Super::PossessedBy(NewController);

    AbilitySystemComponent->InitAbilityActorInfo(this, this);

    MYSTICA_RETURN_IF_CANT_ENSURE_THAT(!AbilitiesDataAsset.IsNull());
    UPlayerAbilitiesProfileDataAsset *LoadedAbilitiesDataAsset =
        AbilitiesDataAsset.LoadSynchronous();

    MYSTICA_RETURN_IF_CANT_ENSURE_THAT(LoadedAbilitiesDataAsset);
    LoadedAbilitiesDataAsset->GiveAllTo(AbilitySystemComponent);
}

UAbilitySystemComponent *ADefaultPlayer::GetAbilitySystemComponent() const {
    return AbilitySystemComponent;
}

void ADefaultPlayer::SetupPlayerInputComponent(
    UInputComponent *PlayerInputComponent) {
    MYSTICA_RETURN_IF_CANT_ENSURE_THAT(InputConfigDataAsset);

    APlayerController *PlayerController =
        Cast<APlayerController>(GetController());
    MYSTICA_RETURN_IF_CANT_ENSURE_THAT(PlayerController);

    UEnhancedInputLocalPlayerSubsystem *Subsystem =
        ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(
            PlayerController->GetLocalPlayer());
    MYSTICA_RETURN_IF_CANT_ENSURE_THAT(Subsystem);

    Subsystem->AddMappingContext(InputConfigDataAsset->MappingContext, 0);

    UMysticaEnhancedInputComponent *MysticaEnhancedInputComponent =
        CastChecked<UMysticaEnhancedInputComponent>(PlayerInputComponent);

    MysticaEnhancedInputComponent->BindCommonInputAction(
        InputConfigDataAsset, MysticaGameplayTags::Input_Look,
        ETriggerEvent::Triggered, this, &ThisClass::Look);

    MysticaEnhancedInputComponent->BindCommonInputAction(
        InputConfigDataAsset, MysticaGameplayTags::Input_Move,
        ETriggerEvent::Triggered, this, &ThisClass::Move);

    MysticaEnhancedInputComponent->BindAbilityInputAction(
        InputConfigDataAsset, ETriggerEvent::Started, this,
        &ThisClass::OnAbilityInputStarted);
    MysticaEnhancedInputComponent->BindAbilityInputAction(
        InputConfigDataAsset, ETriggerEvent::Completed, this,
        &ThisClass::OnAbilityInputCompleted);
}

void ADefaultPlayer::Move(const FInputActionValue &Value) {
    FVector2D MovementVector = Value.Get<FVector2D>();

    if (Controller != nullptr) {
        const FRotator Rotation = Controller->GetControlRotation();
        const FRotator YawRotation(0, Rotation.Yaw, 0);

        const FVector ForwardDirection =
            FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

        const FVector RightDirection =
            FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

        AddMovementInput(ForwardDirection, MovementVector.Y);
        AddMovementInput(RightDirection, MovementVector.X);
    }
}

void ADefaultPlayer::Look(const FInputActionValue &Value) {
    FVector2D LookAxisVector = Value.Get<FVector2D>();

    if (Controller != nullptr) {
        AddControllerYawInput(LookAxisVector.X);
        AddControllerPitchInput(LookAxisVector.Y);
    }
}

void ADefaultPlayer::OnAbilityInputStarted(FGameplayTag InInputTag) {
    AbilitySystemComponent->OnAbilityInputStarted(InInputTag);
}

void ADefaultPlayer::OnAbilityInputCompleted(FGameplayTag InInputTag) {
    AbilitySystemComponent->OnAbilityInputCompleted(InInputTag);
}
