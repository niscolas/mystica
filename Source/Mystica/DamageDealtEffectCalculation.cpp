#include "DamageDealtEffectCalculation.h"
#include "GameplayEffectAttributeCaptureDefinition.h"
#include "GameplayEffectExecutionCalculation.h"
#include "Misc/AssertionMacros.h"
#include "Mystica/MysticaAttributeSet.h"
#include "UObject/UnrealType.h"

struct FDamageDealtCapture {
    DECLARE_ATTRIBUTE_CAPTUREDEF(AttackBaseDamage);
    DECLARE_ATTRIBUTE_CAPTUREDEF(Defense);

    FDamageDealtCapture() {
        DEFINE_ATTRIBUTE_CAPTUREDEF(UMysticaAttributeSet, AttackBaseDamage,
                                    Source, false);

        DEFINE_ATTRIBUTE_CAPTUREDEF(UMysticaAttributeSet, Defense, Target,
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
}
