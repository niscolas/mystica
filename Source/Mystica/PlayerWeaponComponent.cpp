#include "PlayerWeaponComponent.h"
#include "Components/ShapeComponent.h"
#include "Mystica/HelperMacros.h"

UPlayerWeaponComponent::UPlayerWeaponComponent() {
    PrimaryComponentTick.bCanEverTick = false;
}

void UPlayerWeaponComponent::BeginPlay() {
    Super::BeginPlay();

    if (CollisionComponent) {
        CollisionComponent->OnComponentBeginOverlap.AddDynamic(
            this, &ThisClass::OnCollisionComponentBeginOverlap);

        CollisionComponent->OnComponentEndOverlap.AddDynamic(
            this, &ThisClass::OnCollisionComponentEndOverlap);
    }
}

UShapeComponent *UPlayerWeaponComponent::GetCollisionComponent() const {
    return CollisionComponent;
}

void UPlayerWeaponComponent::AssignGrantedAbilitiesSpecHandles(
    const TArray<FGameplayAbilitySpecHandle> &InSpecHandles) {
    GrantedAbilitySpecHandles = InSpecHandles;
}

void UPlayerWeaponComponent::OnCollisionComponentBeginOverlap(
    UPrimitiveComponent *OverlappedComponent,
    AActor *OtherActor,
    UPrimitiveComponent *OtherComp,
    int32 OtherBodyIndex,
    bool bFromSweep,
    const FHitResult &SweepResult) {
    APawn *OwningPawn = GetOwner()->GetInstigator<APawn>();
    MYSTICA_LOG_AND_RETURN_IF(
        !OwningPawn, LogTemp, Warning,
        TEXT("Will not continue OnCollisionComponentBeginOverlap logic, "
             "missing valid Instigator"));

    if (APawn *HitPawn = Cast<APawn>(OtherActor)) {
        if (OwningPawn != HitPawn) {
            UE_LOG(LogTemp, Warning, TEXT("Weapon properly hit another Pawn"));
        } else {
            UE_LOG(LogTemp, Warning, TEXT("Weapon hit OwningPawn"));
        }
    }
}

void UPlayerWeaponComponent::OnCollisionComponentEndOverlap(
    UPrimitiveComponent *OverlappedComponent,
    AActor *OtherActor,
    UPrimitiveComponent *OtherComp,
    int32 OtherBodyIndex) {
}
