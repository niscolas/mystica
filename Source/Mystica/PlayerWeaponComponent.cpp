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

AActor *UPlayerWeaponComponent::GetActor_Implementation() const {
    return GetOwner();
}

UShapeComponent *UPlayerWeaponComponent::GetCollisionComponent() const {
    return CollisionComponent;
}

const FHitTarget &UPlayerWeaponComponent::GetBeginHitOtherPawnDelegate() const {
    return BeginHitOtherPawn;
}

const FHitTarget &UPlayerWeaponComponent::GetEndHitOtherPawnDelegate() const {
    return EndHitOtherPawn;
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
    APawn *InstigatorPawn = GetInstigator();

    if (APawn *HitPawn = Cast<APawn>(OtherActor)) {
        if (InstigatorPawn != HitPawn) {
            BeginHitOtherPawn.Broadcast(HitPawn);
        }
    }
}

void UPlayerWeaponComponent::OnCollisionComponentEndOverlap(
    UPrimitiveComponent *OverlappedComponent,
    AActor *OtherActor,
    UPrimitiveComponent *OtherComp,
    int32 OtherBodyIndex) {
    APawn *InstigatorPawn = GetInstigator();

    if (APawn *HitPawn = Cast<APawn>(OtherActor)) {
        if (InstigatorPawn != HitPawn) {
            EndHitOtherPawn.Broadcast(HitPawn);
        }
    }
}

APawn *UPlayerWeaponComponent::GetInstigator() const {
    APawn *InstigatorPawn = GetOwner()->GetInstigator<APawn>();
    MYSTICA_LOG_AND_RETURN_VALUE_IF(
        !InstigatorPawn, LogTemp, Warning, nullptr,
        TEXT("Will not continue OnCollisionComponentBeginOverlap logic, "
             "missing valid Instigator"));

    return InstigatorPawn;
}
