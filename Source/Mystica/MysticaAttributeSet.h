#pragma once

#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "CoreMinimal.h"
#include "HelperMacros.h"
#include "MysticaAttributeSet.generated.h"

UCLASS()

class MYSTICA_API UMysticaAttributeSet : public UAttributeSet {
    GENERATED_BODY()

public:
    UMysticaAttributeSet();

    UPROPERTY(BlueprintReadOnly, Category = "Health")
    FGameplayAttributeData CurrentHealth;
    ATTRIBUTE_ACCESSORS(UMysticaAttributeSet, CurrentHealth)

    UPROPERTY(BlueprintReadOnly, Category = "Health")
    FGameplayAttributeData MaxHealth;
    ATTRIBUTE_ACCESSORS(UMysticaAttributeSet, MaxHealth)

    UPROPERTY(BlueprintReadOnly, Category = "Combat|Rage")
    FGameplayAttributeData CurrentRage;
    ATTRIBUTE_ACCESSORS(UMysticaAttributeSet, CurrentRage)

    UPROPERTY(BlueprintReadOnly, Category = "Combat|Rage")
    FGameplayAttributeData MaxRage;
    ATTRIBUTE_ACCESSORS(UMysticaAttributeSet, MaxRage)

    UPROPERTY(BlueprintReadOnly, Category = "Combat|Damage")
    FGameplayAttributeData AttackBaseDamage;
    ATTRIBUTE_ACCESSORS(UMysticaAttributeSet, AttackBaseDamage)

    UPROPERTY(BlueprintReadOnly, Category = "Combat|Damage")
    FGameplayAttributeData Defense;
    ATTRIBUTE_ACCESSORS(UMysticaAttributeSet, Defense)

    UPROPERTY(BlueprintReadOnly, Category = "Combat|Combo")
    FGameplayAttributeData LightComboCount;
    ATTRIBUTE_ACCESSORS(UMysticaAttributeSet, LightComboCount)

    UPROPERTY(BlueprintReadOnly, Category = "Combat|Combo")
    FGameplayAttributeData HeavyComboCount;
    ATTRIBUTE_ACCESSORS(UMysticaAttributeSet, HeavyComboCount)

    UPROPERTY(BlueprintReadOnly, Category = "Combat|Damage")
    FGameplayAttributeData DamageTaken;
    ATTRIBUTE_ACCESSORS(UMysticaAttributeSet, DamageTaken)
};
