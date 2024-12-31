#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "GameplayTagContainer.h"
#include "InputConfigDataAsset.h"
#include "Mystica/HelperMacros.h"
#include "MysticaEnhancedInputComponent.generated.h"

UCLASS()

class MYSTICA_API UMysticaEnhancedInputComponent
    : public UEnhancedInputComponent {
    GENERATED_BODY()

public:
    template <class ContextObject, typename Callback>
    void BindCommonInputAction(const UInputConfigDataAsset *InputConfig,
                               const FGameplayTag &Tag,
                               enum ETriggerEvent TriggerEvent,
                               ContextObject *Context,
                               Callback InCallback);

    template <class ContextObject, typename CallbackFunc>
    void BindAbilityInputAction(const UInputConfigDataAsset *InputConfig,
                                enum ETriggerEvent TriggerEvent,
                                ContextObject *Context,
                                CallbackFunc InCallback);
};

template <class ContextObject, typename Callback>
inline void UMysticaEnhancedInputComponent::BindCommonInputAction(
    const UInputConfigDataAsset *InputConfig,
    const FGameplayTag &Tag,
    enum ETriggerEvent TriggerEvent,
    ContextObject *Context,
    Callback InCallback) {
    MYSTICA_LOG_AND_RETURN_IF(
        !InputConfig || !Tag.IsValid() || !Context || !InCallback, LogTemp,
        Error, TEXT("Not proceeding with Input Binding, invalid inputs"));

    if (UInputAction *FoundAction =
            InputConfig->FindCommonInputActionByTag(Tag)) {
        BindAction(FoundAction, TriggerEvent, Context, InCallback);
    }
}

template <class ContextObject, typename CallbackFunc>
inline void UMysticaEnhancedInputComponent::BindAbilityInputAction(
    const UInputConfigDataAsset *InputConfig,
    enum ETriggerEvent TriggerEvent,
    ContextObject *Context,
    CallbackFunc InCallback) {
    MYSTICA_LOG_AND_RETURN_IF(
        !InputConfig || !Context || !InCallback, LogTemp, Error,
        TEXT("Not proceeding with Input Binding, invalid inputs"));

    for (const FInputActionConfig &AbilityInputActionConfig :
         InputConfig->AbilityInputActionConfigs) {
        MYSTICA_LOG_AND_CONTINUE_IF(
            !AbilityInputActionConfig.CheckIsValid(), LogTemp, Error,
            TEXT("Skipping Input Binding, invalid config"));

        BindAction(AbilityInputActionConfig.Action, TriggerEvent, Context,
                   InCallback, AbilityInputActionConfig.Tag);
    }
}
