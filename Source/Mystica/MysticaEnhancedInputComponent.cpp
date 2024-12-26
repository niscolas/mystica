#include "MysticaEnhancedInputComponent.h"
#include "GameplayTagContainer.h"
#include "HelperMacros.h"
#include "InputTriggers.h"
#include "Mystica/InputConfigDataAsset.h"

template <class ContextObject, typename Callback>
void UMysticaEnhancedInputComponent::BindInputAction(
    const UInputConfigDataAsset &InputConfig,
    const FGameplayTag &Tag,
    enum ETriggerEvent TriggerEvent,
    const ContextObject &Context,
    Callback InCallback) {
    if (TSharedPtr<UInputAction> FoundAction =
            InputConfig.FindActionByTag(Tag)) {
        BindAction(FoundAction, TriggerEvent, Context, InCallback);
    }
}
