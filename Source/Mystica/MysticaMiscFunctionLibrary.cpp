#include "MysticaMiscFunctionLibrary.h"
#include "Mystica/CombatComponent.h"
#include "Mystica/CombatPawn.h"
#include "Mystica/HelperMacros.h"

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
