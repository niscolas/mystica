#include "MysticaMiscFunctionLibrary.h"
#include "GenericTeamAgentInterface.h"
#include "Kismet/KismetMathLibrary.h"
#include "Mystica/CombatComponent.h"
#include "Mystica/CombatPawn.h"
#include "Mystica/HelperMacros.h"
#include "Mystica/Weapon.h"

UCombatComponent *
UMysticaMiscFunctionLibrary::GetCombatComponentFromActor(AActor *InActor) {
    MYSTICA_LOG_AND_RETURN_VALUE_IF(
        !InActor, LogTemp, Warning, nullptr,
        TEXT("Will not get Combat Component, invalid inputs"));

    if (ICombatPawn *CombatPawn = Cast<ICombatPawn>(InActor)) {
        return CombatPawn->GetCombatComponent();
    }

    return nullptr;
}

TScriptInterface<IWeaponComponent>
UMysticaMiscFunctionLibrary::GetWeaponComponentFromActor(
    AActor *InWeaponActor) {
    MYSTICA_LOG_AND_RETURN_VALUE_IF(
        !InWeaponActor, LogTemp, Warning, nullptr,
        TEXT("Will not get Weapon Component, invalid inputs"));

    IWeapon *Weapon = Cast<IWeapon>(InWeaponActor);
    MYSTICA_LOG_AND_RETURN_VALUE_IF(
        !Weapon, LogTemp, Warning, nullptr,
        TEXT("InWeaponActor (%s) is not an IWeapon, returning nullptr"),
        *InWeaponActor->GetName());

    TScriptInterface<IWeaponComponent> Result = Weapon->GetWeaponComponent();
    MYSTICA_LOG_AND_RETURN_VALUE_IF(
        !Result, LogTemp, Warning, nullptr,
        TEXT("GetWeaponComponent() returned nullptr"));

    return Result;
}

bool UMysticaMiscFunctionLibrary::CheckIsPawnHostile(APawn *SourcePawn,
                                                     APawn *TargetPawn) {
    MYSTICA_LOG_AND_RETURN_VALUE_IF(
        !SourcePawn || !TargetPawn, LogTemp, Warning, false,
        TEXT("Will not proceed in CheckIsPawnHostile, invalid inputs"));

    IGenericTeamAgentInterface *SourceTeamAgent =
        Cast<IGenericTeamAgentInterface>(SourcePawn->GetController());
    IGenericTeamAgentInterface *TargetTeamAgent =
        Cast<IGenericTeamAgentInterface>(TargetPawn->GetController());

    MYSTICA_LOG_AND_RETURN_VALUE_IF(
        !SourceTeamAgent || !TargetTeamAgent, LogTemp, Warning, false,
        TEXT("Will not proceed in CheckIsPawnHostile, invalid Team Agents (%s "
             "or %s)"),
        *SourcePawn->GetName(), *TargetPawn->GetName());

    return SourceTeamAgent->GetGenericTeamId() !=
           TargetTeamAgent->GetGenericTeamId();
}

float UMysticaMiscFunctionLibrary::ComputeAngleDifference(AActor *OriginActor,
                                                          AActor *TargetActor) {
    const FVector OriginActorForward = OriginActor->GetActorForwardVector();
    const FVector OriginToTargetNormalized =
        (TargetActor->GetActorLocation() - OriginActor->GetActorLocation())
            .GetSafeNormal();

    const float DotResult =
        FVector::DotProduct(OriginActorForward, OriginToTargetNormalized);
    const float AngleDifference = UKismetMathLibrary::DegAcos(DotResult);

    return AngleDifference;
}

bool UMysticaMiscFunctionLibrary::CheckIsValidBlock(AActor *InAttacker,
                                                    AActor *InDefender) {
    MYSTICA_LOG_AND_RETURN_VALUE_IF(
        !InAttacker || !InDefender, LogTemp, Warning, false,
        TEXT("Invalid Inputs, will not CheckIsValidBlock"));

    const float DotResult =
        FVector::DotProduct(InAttacker->GetActorForwardVector(),
                            InDefender->GetActorForwardVector());

    return DotResult < -0.1f;
}
