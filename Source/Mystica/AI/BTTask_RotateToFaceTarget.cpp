#include "BTTask_RotateToFaceTarget.h"
#include "AIController.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BlackboardData.h"
#include "Kismet/KismetMathLibrary.h"
#include "Mystica/MysticaMiscFunctionLibrary.h"

UBTTask_RotateToFaceTarget::UBTTask_RotateToFaceTarget() {
    NodeName = TEXT("Native Rotate To Face Target Actor");

    bNotifyTick = true;
    bNotifyTaskFinished = true;
    bCreateNodeInstance = false;

    INIT_TASK_NODE_NOTIFY_FLAGS();
    InTargetToFaceKey.AddObjectFilter(
        this, GET_MEMBER_NAME_CHECKED(ThisClass, InTargetToFaceKey),
        AActor::StaticClass());
}

void UBTTask_RotateToFaceTarget::InitializeFromAsset(UBehaviorTree &InAsset) {
    Super::InitializeFromAsset(InAsset);

    if (UBlackboardData *BlackboardAsset = GetBlackboardAsset()) {
        InTargetToFaceKey.ResolveSelectedKey(*BlackboardAsset);
    }
}

uint16 UBTTask_RotateToFaceTarget::GetInstanceMemorySize() const {
    return sizeof(FRotateToFaceTargetTaskMemory);
}

FString UBTTask_RotateToFaceTarget::GetStaticDescription() const {
    const FString KeyDescription = InTargetToFaceKey.SelectedKeyName.ToString();
    return FString::Printf(TEXT("Smoothly rotates to face %s Key until the "
                                "AnglePrecision: %s is reached"),
                           *KeyDescription,
                           *FString::SanitizeFloat(AnglePrecision));
}

EBTNodeResult::Type
UBTTask_RotateToFaceTarget::ExecuteTask(UBehaviorTreeComponent &OwnerComp,
                                        uint8 *NodeMemory) {
    AActor *TargetActor =
        Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(
            InTargetToFaceKey.SelectedKeyName));

    APawn *OwningPawn = OwnerComp.GetAIOwner()->GetPawn();
    FRotateToFaceTargetTaskMemory *Memory =
        CastInstanceNodeMemory<FRotateToFaceTargetTaskMemory>(NodeMemory);

    Memory->OwningPawn = OwningPawn;
    Memory->TargetActor = TargetActor;
    if (!Memory->IsValid()) {
        return EBTNodeResult::Failed;
    }

    if (HasReachedAnglePrecision(OwningPawn, TargetActor)) {
        Memory->Reset();
        return EBTNodeResult::Succeeded;
    }

    return EBTNodeResult::InProgress;
}

void UBTTask_RotateToFaceTarget::TickTask(UBehaviorTreeComponent &OwnerComp,
                                          uint8 *NodeMemory,
                                          float DeltaSeconds) {
    FRotateToFaceTargetTaskMemory *Memory =
        CastInstanceNodeMemory<FRotateToFaceTargetTaskMemory>(NodeMemory);

    if (!Memory->IsValid()) {
        FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
    }

    if (HasReachedAnglePrecision(Memory->OwningPawn.Get(),
                                 Memory->TargetActor.Get())) {
        Memory->Reset();
        FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
    } else {
        const FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(
            Memory->OwningPawn->GetActorLocation(),
            Memory->TargetActor->GetActorLocation());
        const FRotator TargetRotation = FMath::RInterpTo(
            Memory->OwningPawn->GetActorRotation(), LookAtRotation,
            DeltaSeconds, RotationInterpolationSpeed);

        Memory->OwningPawn->SetActorRotation(TargetRotation);
    }
}

bool UBTTask_RotateToFaceTarget::HasReachedAnglePrecision(
    APawn *QueryPawn, AActor *TargetActor) const {
    const float AngleDifference =
        UMysticaMiscFunctionLibrary::ComputeAngleDifference(QueryPawn,
                                                            TargetActor);

    return AngleDifference <= AnglePrecision;
}
