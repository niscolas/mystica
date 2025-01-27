#pragma once

#include "BehaviorTree/BTService.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "CoreMinimal.h"
#include "BTService_OrientToTargetActor.generated.h"

UCLASS()

class MYSTICA_API UBTService_OrientToTargetActor : public UBTService {
    GENERATED_BODY()

    UBTService_OrientToTargetActor();

    UPROPERTY(EditAnywhere,
              BlueprintReadWrite,
              Category = "Target",
              meta = (AllowPrivateAccess))
    FBlackboardKeySelector InTargetActorKey;

    UPROPERTY(EditAnywhere,
              BlueprintReadWrite,
              Category = "Target",
              meta = (AllowPrivateAccess))
    float RotationInterpolationSpeed = 5.f;

    virtual void InitializeFromAsset(UBehaviorTree &Asset) override;
    virtual FString GetStaticDescription() const override;
    virtual void TickNode(UBehaviorTreeComponent &OwnerComp,
                          uint8 *NodeMemory,
                          float DeltaSeconds) override;
};
