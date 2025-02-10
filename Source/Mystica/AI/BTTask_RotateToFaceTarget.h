#pragma once

#include "BehaviorTree/BTTaskNode.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "CoreMinimal.h"
#include "UObject/WeakObjectPtrTemplates.h"
#include "BTTask_RotateToFaceTarget.generated.h"

struct FRotateToFaceTargetTaskMemory {
    TWeakObjectPtr<APawn> OwningPawn;
    TWeakObjectPtr<AActor> TargetActor;

    bool IsValid() const {
        return OwningPawn.IsValid() && TargetActor.IsValid();
    }

    void Reset() {
        OwningPawn.Reset();
        TargetActor.Reset();
    }
};

UCLASS()

class MYSTICA_API UBTTask_RotateToFaceTarget : public UBTTaskNode {
    GENERATED_BODY()

    UBTTask_RotateToFaceTarget();

    UPROPERTY(EditAnywhere,
              BlueprintReadWrite,
              Category = "Face Target",
              meta = (AllowPrivateAccess))
    float AnglePrecision = 10.f;

    UPROPERTY(EditAnywhere,
              BlueprintReadWrite,
              Category = "Face Target",
              meta = (AllowPrivateAccess))
    float RotationInterpolationSpeed = 5.f;

    UPROPERTY(EditAnywhere,
              BlueprintReadWrite,
              Category = "Face Target",
              meta = (AllowPrivateAccess))
    FBlackboardKeySelector InTargetToFaceKey;

    virtual void InitializeFromAsset(UBehaviorTree &InAsset) override;
    virtual uint16 GetInstanceMemorySize() const override;
    virtual FString GetStaticDescription() const override;
    virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent &OwnerComp,
                                            uint8 *NodeMemory) override;
    virtual void TickTask(UBehaviorTreeComponent &OwnerComp,
                          uint8 *NodeMemory,
                          float DeltaSeconds) override;
    bool HasReachedAnglePrecision(APawn *QueryPawn, AActor *TargetActor) const;
};
