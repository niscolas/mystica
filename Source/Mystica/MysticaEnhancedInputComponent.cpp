#include "MysticaEnhancedInputComponent.h"

template <class ContextObject, typename Callback>
void UMysticaEnhancedInputComponent::BindInputAction(
    const UInputConfigDataAsset &InputConfig,
    const FGameplayTag &Tag,
    enum ETriggerEvent TriggerEvent,
    const ContextObject &Context,
    Callback InCallback) {
}
