#include "DamageDealtEffectCalculation.h"
#include "Engine/TextureDefines.h"
#include "GameplayEffectAggregator.h"
#include "GameplayEffectAttributeCaptureDefinition.h"
#include "GameplayEffectExecutionCalculation.h"
#include "GameplayEffectTypes.h"
#include "GameplayTagContainer.h"
#include "Misc/AssertionMacros.h"
#include "Mystica/MysticaAttributeSet.h"
#include "Mystica/MysticaGameplayTags.h"
#include "UObject/UnrealType.h"

struct FDamageDealtCapture {
    DECLARE_ATTRIBUTE_CAPTUREDEF(AttackBaseDamage);
    DECLARE_ATTRIBUTE_CAPTUREDEF(Defense);
    DECLARE_ATTRIBUTE_CAPTUREDEF(DamageTaken);

    FDamageDealtCapture() {
        DEFINE_ATTRIBUTE_CAPTUREDEF(UMysticaAttributeSet, AttackBaseDamage,
                                    Source, false);
        DEFINE_ATTRIBUTE_CAPTUREDEF(UMysticaAttributeSet, Defense, Target,
                                    false);
        DEFINE_ATTRIBUTE_CAPTUREDEF(UMysticaAttributeSet, DamageTaken, Target,
                                    false);
    }
};

static const FDamageDealtCapture &GetDamageDealtCapture() {
    static FDamageDealtCapture DamageDealtCapture;
    return DamageDealtCapture;
}

UDamageDealtEffectCalculation::UDamageDealtEffectCalculation() {
    RelevantAttributesToCapture.Add(
        GetDamageDealtCapture().AttackBaseDamageDef);
    RelevantAttributesToCapture.Add(GetDamageDealtCapture().DefenseDef);
    RelevantAttributesToCapture.Add(GetDamageDealtCapture().DamageTakenDef);
}

void UDamageDealtEffectCalculation::Execute_Implementation(
    const FGameplayEffectCustomExecutionParameters &ExecutionParams,
    FGameplayEffectCustomExecutionOutput &OutExecutionOutput) const {
    const FGameplayEffectSpec &EffectSpec = ExecutionParams.GetOwningSpec();

    FAggregatorEvaluateParameters EvaluateParameters;
    EvaluateParameters.SourceTags =
        EffectSpec.CapturedSourceTags.GetAggregatedTags();
    EvaluateParameters.TargetTags =
        EffectSpec.CapturedSourceTags.GetAggregatedTags();

    float SourceAttackBaseDamage = 0.f;
    ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(
        GetDamageDealtCapture().AttackBaseDamageDef, EvaluateParameters,
        SourceAttackBaseDamage);

    UE_LOG(LogTemp, Warning, TEXT("SourceAttackBaseDamage: %f"),
           SourceAttackBaseDamage);

    float FinalDamage = 0.f;
    int32 LightAttackComboCount = 0;
    int32 HeavyAttackComboCount = 0;
    for (const TPair<FGameplayTag, float> &TagMagnitude :
         EffectSpec.SetByCallerTagMagnitudes) {
        if (TagMagnitude.Key.MatchesTagExact(
                MysticaGameplayTags::Shared_SetByCaller_BaseDamage)) {
            FinalDamage = TagMagnitude.Value;

            UE_LOG(LogTemp, Warning, TEXT("FinalDamage 1: %f"), FinalDamage);
        } else if (TagMagnitude.Key.MatchesTagExact(
                       MysticaGameplayTags::
                           Player_SetByCaller_AttackType_Light)) {
            LightAttackComboCount = TagMagnitude.Value;

            UE_LOG(LogTemp, Warning, TEXT("LightAttackComboCount: %d"),
                   LightAttackComboCount);
        } else if (TagMagnitude.Key.MatchesTagExact(
                       MysticaGameplayTags::
                           Player_SetByCaller_AttackType_Heavy)) {
            HeavyAttackComboCount = TagMagnitude.Value;

            UE_LOG(LogTemp, Warning, TEXT("HeavyAttackComboCount: %d"),
                   HeavyAttackComboCount);
        }
    }

    float TargetDefense = 0.f;
    ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(
        GetDamageDealtCapture().DefenseDef, EvaluateParameters, TargetDefense);

    UE_LOG(LogTemp, Warning, TEXT("TargetDefense: %f"), TargetDefense);

    if (LightAttackComboCount != 0) {
        const float LightAttackDamageIncrease =
            (LightAttackComboCount - 1) * 0.05 + 1.f;
        FinalDamage *= LightAttackDamageIncrease;

        UE_LOG(LogTemp, Warning, TEXT("ScaledDamageByLightCombo: %f"),
               FinalDamage);
    }

    if (HeavyAttackComboCount != 0) {
        const float HeavyAttackDamageIncrease =
            HeavyAttackComboCount * 0.15 + 1.f;
        FinalDamage *= HeavyAttackDamageIncrease;

        UE_LOG(LogTemp, Warning, TEXT("ScaledDamageByHeavyCombo: %f"),
               FinalDamage);
    }

    FinalDamage = FinalDamage * SourceAttackBaseDamage / TargetDefense;

    UE_LOG(LogTemp, Warning, TEXT("RealFinalDamage: %f"), FinalDamage);
    if (FinalDamage > 0.f) {
        OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(
            GetDamageDealtCapture().DamageTakenProperty,
            EGameplayModOp::Override, FinalDamage));
    }
}
