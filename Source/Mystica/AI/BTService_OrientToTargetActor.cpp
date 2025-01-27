#include "BTService_OrientToTargetActor.h"
#include "AIController.h"
#include "BehaviorTree/BTService.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/KismetMathLibrary.h"

UBTService_OrientToTargetActor::UBTService_OrientToTargetActor() {
    NodeName = TEXT("Native Orient To Target Actor");

    INIT_SERVICE_NODE_NOTIFY_FLAGS();

    Interval = 0.f;
    RandomDeviation = 0.f;

    InTargetActorKey.AddObjectFilter(
        this, GET_MEMBER_NAME_CHECKED(ThisClass, InTargetActorKey),
        AActor::StaticClass());
}

void UBTService_OrientToTargetActor::InitializeFromAsset(UBehaviorTree &Asset) {
    Super::InitializeFromAsset(Asset);

    UBlackboardData *BlackboardAsset = GetBlackboardAsset();
    if (BlackboardAsset) {
        InTargetActorKey.ResolveSelectedKey(*BlackboardAsset);
    }
}

FString UBTService_OrientToTargetActor::GetStaticDescription() const {
    const FString Result =
        FString::Printf(TEXT("Orient rotation to %s Key %s"),
                        *InTargetActorKey.SelectedKeyName.ToString(),
                        *GetStaticServiceDescription());

    return Result;
}

void UBTService_OrientToTargetActor::TickNode(UBehaviorTreeComponent &OwnerComp,
                                              uint8 *NodeMemory,
                                              float DeltaSeconds) {
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

    AActor *TargetActor =
        Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(
            InTargetActorKey.SelectedKeyName));
    APawn *OwningPawn = OwnerComp.GetAIOwner()->GetPawn();
    if (OwningPawn && TargetActor) {
        const FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(
            OwningPawn->GetActorLocation(), TargetActor->GetActorLocation());

        const FRotator TargetRotation =
            FMath::RInterpTo(OwningPawn->GetActorRotation(), LookAtRotation,
                             DeltaSeconds, RotationInterpolationSpeed);

        OwningPawn->SetActorRotation(TargetRotation);
    }
}
