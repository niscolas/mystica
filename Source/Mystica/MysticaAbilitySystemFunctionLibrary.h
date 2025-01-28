#pragma once

#include "GameplayAbilitySpec.h"
#include "GameplayAbilitySpecHandle.h"
#include "GameplayTagContainer.h"
#include "GenericPlatform/GenericPlatformMisc.h"
#include "HelperMacros.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Templates/SubclassOf.h"
#include "Templates/UnrealTemplate.h"
#include "MysticaAbilitySystemFunctionLibrary.generated.h"

class UGameplayAbility;
class UGameplayEffect;
class UAbilitySystemComponent;

UCLASS()

class UMysticaAbilitySystemFunctionLibrary : public UBlueprintFunctionLibrary {
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable,
              Category = "Ability System|Mystica Function Library")
    static void AddGameplayTagToActor(AActor *InActor, FGameplayTag InTag);

    UFUNCTION(BlueprintCallable,
              Category = "Ability System|Mystica Function Library")
    static void RemoveGameplayTagFromActor(AActor *InActor, FGameplayTag InTag);

    UFUNCTION(BlueprintCallable,
              Category = "Ability System|Mystica Function Library",
              meta = (ExpandBoolAsExecs = "ReturnValue"))
    static bool BranchOnDoesActorHaveTag(AActor *InActor, FGameplayTag InTag);

    UFUNCTION(BlueprintCallable,
              Category = "Ability System|Mystica Function Library")
    static bool CheckDoesHaveGivenActivatableAbilityClass(
        UAbilitySystemComponent *InAbilitySystemComponent,
        TSubclassOf<UGameplayAbility> InAbilityClass);

    UFUNCTION(BlueprintCallable,
              Category = "Ability System|Mystica Function Library",
              meta = (ExpandBoolAsExecs = "ReturnValue"))
    static bool BranchOnDoesHaveGivenActivatableAbilityClass(
        UAbilitySystemComponent *InAbilitySystemComponent,
        TSubclassOf<UGameplayAbility> InAbilityClass);

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

    static bool NativeCheckDoesActorHaveTag(AActor *InActor,
                                            FGameplayTag InTag);

    static UAbilitySystemComponent *
    NativeGetAbilitySystemComponentFromActor(AActor *InActor);

    static void ApplyEffectsToAbilitySystemComponent(
        UAbilitySystemComponent *InAbilitySystemComponent,
        TArray<TSubclassOf<UGameplayEffect>> InEffects,
        int32 ApplyLevel);
};
