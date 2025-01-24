#include "DefaultEnemyAIController.h"
#include "Navigation/CrowdFollowingComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"

ADefaultEnemyAIController::ADefaultEnemyAIController(
    const FObjectInitializer &ObjectInitializer)
    : Super(
          ObjectInitializer.SetDefaultSubobjectClass<UCrowdFollowingComponent>(
              "PathFollowingComponent")) {
    SightSense =
        CreateDefaultSubobject<UAISenseConfig_Sight>("AISenseConfig_Sight");
    SightSense->DetectionByAffiliation.bDetectEnemies = true;
    SightSense->DetectionByAffiliation.bDetectFriendlies = false;
    SightSense->DetectionByAffiliation.bDetectNeutrals = false;
    SightSense->SightRadius = 5000.f;
    SightSense->LoseSightRadius = 0.f;
    SightSense->PeripheralVisionAngleDegrees = 360.f;

    EnemyPerceptionComponent =
        CreateDefaultSubobject<UAIPerceptionComponent>("PerceptionComponent");
    SetPerceptionComponent(*EnemyPerceptionComponent);
    GetPerceptionComponent()->ConfigureSense(*SightSense);
    GetPerceptionComponent()->SetDominantSense(
        UAISenseConfig_Sight::StaticClass());
    GetPerceptionComponent()->OnTargetPerceptionUpdated.AddUniqueDynamic(
        this, &ThisClass::OnPerceptionUpdated);
}

void ADefaultEnemyAIController::OnPerceptionUpdated(AActor *Actor,
                                                    FAIStimulus Stimulus) {
}
