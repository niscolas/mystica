#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "MysticaEnhancedInputComponent.generated.h"

UCLASS()

class MYSTICA_API UMysticaEnhancedInputComponent
    : public UEnhancedInputComponent {
    GENERATED_BODY()

public:
    template <class ContextObject, typename Callback>
    void BindInputAction(const class UInputConfigDataAsset &InputConfig,
                         const struct FGameplayTag &Tag,
                         enum ETriggerEvent TriggerEvent,
                         const ContextObject &Context,
                         Callback InCallback);
};
