#pragma once

#include "AIController.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "CoreMinimal.h"
#include "DefaultEnemyAIController.generated.h"

class UAIPerceptionComponent;
struct FAIStimulus;
class UAISenseConfig_Sight;

UCLASS()

class MYSTICA_API ADefaultEnemyAIController : public AAIController {
    GENERATED_BODY()

public:
    ADefaultEnemyAIController(const FObjectInitializer &ObjectInitializer);

    virtual ETeamAttitude::Type
    GetTeamAttitudeTowards(const AActor &Other) const override;

private:
    virtual void BeginPlay() override;

    UPROPERTY(EditDefaultsOnly,
              BlueprintReadWrite,
              Category = "AI",
              meta = (AllowPrivateAccess))
    bool ShouldEnableDetourCrowdAvoidance = true;

    UPROPERTY(EditDefaultsOnly,
              BlueprintReadWrite,
              Category = "AI",
              meta = (AllowPrivateAccess,
                      EditCondition = "ShouldEnableDetourCrowdAvoidance",
                      UIMin = "1",
                      UIMax = "1"))
    int32 DetourCrowdAvoidanceQuality = 4;

    UPROPERTY(EditDefaultsOnly,
              BlueprintReadWrite,
              Category = "AI",
              meta = (AllowPrivateAccess,
                      EditCondition = "ShouldEnableDetourCrowdAvoidance"))
    float DetourCrowdAvoidanceQueryRange = 600.f;

    UPROPERTY(VisibleAnywhere,
              BlueprintReadOnly,
              Category = "AI",
              meta = (AllowPrivateAccess))
    UAISenseConfig_Sight *SightSense;

    UPROPERTY(VisibleAnywhere,
              BlueprintReadOnly,
              Category = "AI",
              meta = (AllowPrivateAccess))
    UAIPerceptionComponent *EnemyPerceptionComponent;

    UFUNCTION()
    void OnPerceptionUpdated(AActor *Actor, FAIStimulus Stimulus);
};
