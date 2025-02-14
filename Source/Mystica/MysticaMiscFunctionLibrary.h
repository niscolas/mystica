#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "UObject/ScriptInterface.h"
#include "MysticaMiscFunctionLibrary.generated.h"

class IWeaponComponent;
class UCombatComponent;

UCLASS()

class MYSTICA_API UMysticaMiscFunctionLibrary
    : public UBlueprintFunctionLibrary {
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintPure, Category = "Combat|Function Library")
    static UCombatComponent *GetCombatComponentFromActor(AActor *InActor);

    UFUNCTION(BlueprintPure, Category = "Combat|Function Library")
    static TScriptInterface<IWeaponComponent>
    GetWeaponComponentFromActor(AActor *InWeaponActor);

    UFUNCTION(BlueprintPure, Category = "Combat|Function Library")
    static bool CheckIsPawnHostile(APawn *SourcePawn, APawn *TargetPawn);

    UFUNCTION(BlueprintPure, Category = "Math|Function Library")
    static float ComputeAngleDifference(AActor *OriginActor,
                                        AActor *TargetActor);

    static bool CheckIsValidBlock(AActor *InAttacker, AActor *InDefender);
};
