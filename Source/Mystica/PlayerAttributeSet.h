#pragma once

#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "CoreMinimal.h"
#include "HelperMacros.h"
#include "PlayerAttributeSet.generated.h"

UCLASS()

class MYSTICA_API UPlayerAttributeSet : public UAttributeSet {
    GENERATED_BODY()

public:
    UPlayerAttributeSet();
};
