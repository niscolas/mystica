#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "GameplayTagContainer.h"
#include "InputConfigDataAsset.h"
#include "MysticaEnhancedInputComponent.generated.h"

UCLASS()

class MYSTICA_API UMysticaEnhancedInputComponent
    : public UEnhancedInputComponent {
    GENERATED_BODY()

public:
    template <class ContextObject, typename Callback>
    void BindInputAction(const UInputConfigDataAsset *InputConfig,
                         const FGameplayTag &Tag,
                         enum ETriggerEvent TriggerEvent,
                         ContextObject *Context,
                         Callback InCallback);
};

template <class ContextObject, typename Callback>
inline void UMysticaEnhancedInputComponent::BindInputAction(
    const UInputConfigDataAsset *InputConfig,
    const FGameplayTag &Tag,
    enum ETriggerEvent TriggerEvent,
    ContextObject *Context,
    Callback InCallback) {
    if (UInputAction *FoundAction = InputConfig->FindActionByTag(Tag)) {
        BindAction(FoundAction, TriggerEvent, Context, InCallback);
    }
}
