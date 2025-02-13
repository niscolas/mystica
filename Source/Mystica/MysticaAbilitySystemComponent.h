#pragma once

#include "AbilitySystemComponent.h"
#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "MysticaAbilitySystemComponent.generated.h"

struct FGameplayAbilitySpecHandle;
class UGameplayAbility;

UCLASS()

class MYSTICA_API UMysticaAbilitySystemComponent
    : public UAbilitySystemComponent {
    GENERATED_BODY()

public:
    void OnAbilityInputStarted(const FGameplayTag &InInputTag);
    void OnAbilityInputCompleted(const FGameplayTag &InInputTag);

    UFUNCTION(BlueprintCallable,
              Category = "Ability System",
              meta = (ApplyLevel = "1"))
    void GrantWeaponAbilities(
        const TMap<FGameplayTag, TSubclassOf<UGameplayAbility>> &InAbilities,
        int32 ApplyLevel,
        TArray<FGameplayAbilitySpecHandle> &OutSpecHandles);

    UFUNCTION(BlueprintCallable, Category = "Ability System")
    void RemoveWeaponAbilities(
        UPARAM(ref) TArray<FGameplayAbilitySpecHandle> &InSpecHandles);

    UFUNCTION(BlueprintCallable, Category = "Ability System")
    bool TryActivateAbilityByTag(FGameplayTag InTag);
};
