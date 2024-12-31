#pragma once

#include "AbilitySystemComponent.h"
#include "CoreMinimal.h"
#include "MysticaAbilitySystemComponent.generated.h"

UCLASS()

class MYSTICA_API UMysticaAbilitySystemComponent
    : public UAbilitySystemComponent {
    GENERATED_BODY()

public:
    void OnAbilityInputStarted(const FGameplayTag &InInputTag);
    void OnAbilityInputCompleted(const FGameplayTag &InInputTag);
};
