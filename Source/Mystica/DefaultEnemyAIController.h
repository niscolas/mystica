#pragma once

#include "AIController.h"
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

private:
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
