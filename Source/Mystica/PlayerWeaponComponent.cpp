#include "PlayerWeaponComponent.h"

UPlayerWeaponComponent::UPlayerWeaponComponent() {
    PrimaryComponentTick.bCanEverTick = false;
}

void UPlayerWeaponComponent::BeginPlay() {
    Super::BeginPlay();
}
