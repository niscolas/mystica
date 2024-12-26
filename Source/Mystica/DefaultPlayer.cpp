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
#include "MysticaEnhancedInputComponent.h"
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
}

void ADefaultPlayer::BeginPlay() {
    Super::BeginPlay();
}

void ADefaultPlayer::SetupPlayerInputComponent(
    UInputComponent *PlayerInputComponent) {
    MYSTICA_IF_NULL_LOG_AND_RETURN(LogTemp, Error, InputConfigDataAsset);

    APlayerController *PlayerController =
        Cast<APlayerController>(GetController());
    MYSTICA_IF_NULL_LOG_AND_RETURN(LogTemp, Error, PlayerController);

    UEnhancedInputLocalPlayerSubsystem *Subsystem =
        ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(
            PlayerController->GetLocalPlayer());
    MYSTICA_IF_NULL_LOG_AND_RETURN(LogTemp, Error, Subsystem);

    Subsystem->AddMappingContext(InputConfigDataAsset->MappingContext, 0);
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
