#pragma once

#include "Abilities/GameplayAbility.h"
#include "GameplayAbilitySpec.h"
#include "GameplayAbilitySpecHandle.h"
#include "GameplayTagContainer.h"
#include "GenericPlatform/GenericPlatformMisc.h"
#include "HelperMacros.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Logging/LogVerbosity.h"
#include "Templates/UnrealTemplate.h"
#include "MysticaAbilitySystemFunctionLibrary.generated.h"

class UAbilitySystemComponent;

UCLASS()

class UMysticaAbilitySystemFunctionLibrary : public UBlueprintFunctionLibrary {
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "Ability System|Function Library")
    static void AddGameplayTagToActor(AActor *InActor, FGameplayTag InTag);

    UFUNCTION(BlueprintCallable, Category = "Ability System|Function Library")
    static void RemoveGameplayTagFromActor(AActor *InActor, FGameplayTag InTag);

    UFUNCTION(BlueprintCallable,
              Category = "Ability System|Function Library",
              meta = (ExpandBoolAsExecs = "ReturnValue"))
    static bool BranchOnDoesActorHaveTag(AActor *InActor, FGameplayTag InTag);

    static void
    GiveCommonAbilitiesTo(UAbilitySystemComponent *InAbilitySystemComponent,
                          TArray<TSubclassOf<UGameplayAbility>> InAbilities,
                          int8 ApplyLevel);

    static bool GiveGameplayTagBasedAbilityTo(
        UAbilitySystemComponent *InAbilitySystemComponent,
        FGameplayTag InTag,
        TSubclassOf<UGameplayAbility> InAbility,
        int8 ApplyLevel,
        FGameplayAbilitySpecHandle &OutSpecHandle);

    static void GiveGameplayTagBasedAbilitiesTo(
        UAbilitySystemComponent *InAbilitySystemComponent,
        TMap<FGameplayTag, TSubclassOf<UGameplayAbility>> InAbilities,
        int8 ApplyLevel,
        TArray<FGameplayAbilitySpecHandle> &OutSpecHandles);

    static UAbilitySystemComponent *
    NativeGetAbilitySystemComponentFromActor(AActor *InActor);
};
