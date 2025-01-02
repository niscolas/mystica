#include "PlayerWeaponComponent.h"

UPlayerWeaponComponent::UPlayerWeaponComponent() {
    PrimaryComponentTick.bCanEverTick = false;
}

void UPlayerWeaponComponent::BeginPlay() {
    Super::BeginPlay();
}

void UPlayerWeaponComponent::AssignGrantedAbilitiesSpecHandles(
    const TArray<FGameplayAbilitySpecHandle> &InSpecHandles) {
    GrantedAbilitySpecHandles = InSpecHandles;
}
