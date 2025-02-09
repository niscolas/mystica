#include "PlayerCombatComponent.h"
#include "Abilities/GameplayAbilityTypes.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "Components/ShapeComponent.h"
#include "Engine/EngineTypes.h"
#include "HelperMacros.h"
#include "Mystica/DefaultPlayer.h"
#include "Mystica/DefaultWeaponInventory.h"
#include "Mystica/MysticaGameplayTags.h"
#include "PlayerWeaponComponent.h"
#include "WeaponComponent.h"

UPlayerCombatComponent::UPlayerCombatComponent() {
    PrimaryComponentTick.bCanEverTick = false;
    WeaponInventory = FDefaultWeaponInventory(GetOwner());
}

void UPlayerCombatComponent::BeginPlay() {
    Super::BeginPlay();
}

void UPlayerCombatComponent::RegisterWeapon_Implementation(
    FGameplayTag InTag,
    const TScriptInterface<IWeaponComponent> &InWeaponComponent,
    bool ShouldEquip) {
    WeaponInventory.RegisterWeapon(InTag, InWeaponComponent, ShouldEquip);

    InWeaponComponent->GetBeginHitOtherPawnDelegate().AddUObject(
        this, &ThisClass::OnBeginHitOtherPawn);
    InWeaponComponent->GetEndHitOtherPawnDelegate().AddUObject(
        this, &ThisClass::OnEndHitOtherPawn);
}

void UPlayerCombatComponent::EquipWeapon_Implementation(FGameplayTag InTag) {
    WeaponInventory.EquipWeapon(InTag);
}

TScriptInterface<IWeaponComponent>
UPlayerCombatComponent::GetWeaponByTag_Implementation(
    FGameplayTag InTag) const {
    return WeaponInventory.GetWeaponByTag(InTag);
}

UPlayerWeaponComponent *UPlayerCombatComponent::GetPlayerWeaponComponentByTag(
    FGameplayTag InTag) const {
    TScriptInterface<IWeaponComponent> FoundWeapon =
        GetWeaponByTag_Implementation(InTag);
    MYSTICA_IF_NULL_LOG_AND_RETURN_VALUE(LogTemp, Error, FoundWeapon, nullptr);

    return Cast<UPlayerWeaponComponent>(FoundWeapon.GetInterface());
}

UPlayerWeaponComponent *
UPlayerCombatComponent::GetEquippedPlayerWeaponComponent() const {
    return GetPlayerWeaponComponentByTag(GetEquippedWeaponTag_Implementation());
}

TScriptInterface<IWeaponComponent>
UPlayerCombatComponent::GetEquippedWeapon_Implementation() const {
    return WeaponInventory.GetEquippedWeapon();
}

FGameplayTag
UPlayerCombatComponent::GetEquippedWeaponTag_Implementation() const {
    return WeaponInventory.GetEquippedWeaponTag();
}

void UPlayerCombatComponent::SetWeaponCollisionState_Implementation(
    bool SetActive) {
    WeaponInventory.SetEquippedWeaponCollisionState(SetActive);
}

void UPlayerCombatComponent::OnBeginHitOtherPawn(APawn *OtherPawn) {
    if (!WeaponInventory.CommonOnBeginHitOtherPawn(OtherPawn)) {
        return;
    }

    FGameplayEventData GameplayEventData;
    GameplayEventData.Instigator = GetOwner();
    GameplayEventData.Target = OtherPawn;

    UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
        GetOwner(), MysticaGameplayTags::Shared_Event_MeleeHit,
        GameplayEventData);

    UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
        GetOwner(), MysticaGameplayTags::Player_Event_HitPause,
        FGameplayEventData());
}

void UPlayerCombatComponent::OnEndHitOtherPawn(APawn *OtherPawn) {
    UE_LOG(LogTemp, Warning, TEXT("OnEndHitOtherPawn: %s"),
           *OtherPawn->GetName());

    UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
        GetOwner(), MysticaGameplayTags::Player_Event_HitPause,
        FGameplayEventData());
}
