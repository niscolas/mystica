#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "DamageDealtEffectCalculation.generated.h"

UCLASS()

class MYSTICA_API UDamageDealtEffectCalculation
    : public UGameplayEffectExecutionCalculation {
    GENERATED_BODY()

public:
    UDamageDealtEffectCalculation();

    virtual void Execute_Implementation(
        const FGameplayEffectCustomExecutionParameters &ExecutionParams,
        FGameplayEffectCustomExecutionOutput &OutExecutionOutput)
        const override;
};
