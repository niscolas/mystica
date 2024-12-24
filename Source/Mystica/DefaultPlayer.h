#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "DefaultPlayer.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(config = Game)

class ADefaultPlayer : public ACharacter {
    GENERATED_BODY()

    UPROPERTY(VisibleAnywhere,
              BlueprintReadOnly,
              Category = Camera,
              meta = (AllowPrivateAccess = "true"))
    USpringArmComponent *CameraBoom;

    UPROPERTY(VisibleAnywhere,
              BlueprintReadOnly,
              Category = Camera,
              meta = (AllowPrivateAccess = "true"))
    UCameraComponent *FollowCamera;

    UPROPERTY(EditAnywhere,
              BlueprintReadOnly,
              Category = Input,
              meta = (AllowPrivateAccess = "true"))
    UInputMappingContext *DefaultMappingContext;

    UPROPERTY(EditAnywhere,
              BlueprintReadOnly,
              Category = Input,
              meta = (AllowPrivateAccess = "true"))
    UInputAction *JumpAction;

    UPROPERTY(EditAnywhere,
              BlueprintReadOnly,
              Category = Input,
              meta = (AllowPrivateAccess = "true"))
    UInputAction *MoveAction;

    UPROPERTY(EditAnywhere,
              BlueprintReadOnly,
              Category = Input,
              meta = (AllowPrivateAccess = "true"))
    UInputAction *LookAction;

public:
    ADefaultPlayer();

protected:
    void Move(const FInputActionValue &Value);
    void Look(const FInputActionValue &Value);

protected:
    virtual void SetupPlayerInputComponent(
        class UInputComponent *PlayerInputComponent) override;
    virtual void BeginPlay();

public:
    FORCEINLINE class USpringArmComponent *GetCameraBoom() const {
        return CameraBoom;
    }

    FORCEINLINE class UCameraComponent *GetFollowCamera() const {
        return FollowCamera;
    }
};
