#include "EnemyWeaponComponent.h"
#include "Components/ShapeComponent.h"
#include "Mystica/HelperMacros.h"
#include "Mystica/MysticaMiscFunctionLibrary.h"

UEnemyWeaponComponent::UEnemyWeaponComponent() {
    PrimaryComponentTick.bCanEverTick = false;
}

void UEnemyWeaponComponent::BeginPlay() {
    Super::BeginPlay();

    if (CollisionComponent) {
        CollisionComponent->OnComponentBeginOverlap.AddDynamic(
            this, &ThisClass::OnCollisionComponentBeginOverlap);

        CollisionComponent->OnComponentEndOverlap.AddDynamic(
            this, &ThisClass::OnCollisionComponentEndOverlap);
    }
}

AActor *UEnemyWeaponComponent::GetActor_Implementation() const {
    return GetOwner();
}

UShapeComponent *UEnemyWeaponComponent::GetCollisionComponent() const {
    return CollisionComponent;
}

FHitTarget &UEnemyWeaponComponent::GetBeginHitOtherPawnDelegate() {
    return BeginHitOtherPawn;
}

FHitTarget &UEnemyWeaponComponent::GetEndHitOtherPawnDelegate() {
    return EndHitOtherPawn;
}

float UEnemyWeaponComponent::GetDamageAtLevel(float InLevel) const {
    return BaseDamage.GetValueAtLevel(InLevel);
}

void UEnemyWeaponComponent::OnCollisionComponentBeginOverlap(
    UPrimitiveComponent *OverlappedComponent,
    AActor *OtherActor,
    UPrimitiveComponent *OtherComp,
    int32 OtherBodyIndex,
    bool bFromSweep,
    const FHitResult &SweepResult) {
    APawn *InstigatorPawn = GetInstigator();
    MYSTICA_LOG_AND_RETURN_IF(
        !InstigatorPawn, LogTemp, Warning,
        TEXT("Will not continue OnCollisionComponentBeginOverlap logic, "
             "missing valid Instigator"));

    if (APawn *HitPawn = Cast<APawn>(OtherActor)) {
        if (UMysticaMiscFunctionLibrary::CheckIsPawnHostile(InstigatorPawn,
                                                            HitPawn)) {
            BeginHitOtherPawn.Broadcast(HitPawn);
        }
    }
}

void UEnemyWeaponComponent::OnCollisionComponentEndOverlap(
    UPrimitiveComponent *OverlappedComponent,
    AActor *OtherActor,
    UPrimitiveComponent *OtherComp,
    int32 OtherBodyIndex) {
    APawn *InstigatorPawn = GetInstigator();
    MYSTICA_LOG_AND_RETURN_IF(
        !InstigatorPawn, LogTemp, Warning,
        TEXT("Will not continue OnCollisionComponentEndOverlap logic, "
             "missing valid Instigator"));

    if (APawn *HitPawn = Cast<APawn>(OtherActor)) {
        if (UMysticaMiscFunctionLibrary::CheckIsPawnHostile(InstigatorPawn,
                                                            HitPawn)) {
            EndHitOtherPawn.Broadcast(HitPawn);
        }
    }
}

APawn *UEnemyWeaponComponent::GetInstigator() const {
    APawn *InstigatorPawn = GetOwner()->GetInstigator<APawn>();
    return InstigatorPawn;
}
