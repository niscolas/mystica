#include "DefaultEnemyAIController.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GenericTeamAgentInterface.h"
#include "HelperMacros.h"
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

    SetGenericTeamId(FGenericTeamId(1));
}

void ADefaultEnemyAIController::BeginPlay() {
    Super::BeginPlay();
    UCrowdFollowingComponent *CrowdFollowingComponent =
        Cast<UCrowdFollowingComponent>(GetPathFollowingComponent());

    MYSTICA_LOG_AND_RETURN_IF(!CrowdFollowingComponent, LogTemp, Warning,
                              TEXT("Will not proceed on BeginPlay, "
                                   "invalid CrowdFollowingComponent"));

    CrowdFollowingComponent->SetCrowdSimulationState(
        ShouldEnableDetourCrowdAvoidance ? ECrowdSimulationState::Enabled
                                         : ECrowdSimulationState::Disabled);

    ECrowdAvoidanceQuality::Type DetourCrowdAvoidanceQualityType;
    switch (DetourCrowdAvoidanceQuality) {
    case 1:
        DetourCrowdAvoidanceQualityType = ECrowdAvoidanceQuality::Low;
        break;
    case 2:
        DetourCrowdAvoidanceQualityType = ECrowdAvoidanceQuality::Medium;
        break;
    case 3:
        DetourCrowdAvoidanceQualityType = ECrowdAvoidanceQuality::Good;
        break;
    case 4:
        DetourCrowdAvoidanceQualityType = ECrowdAvoidanceQuality::High;
        break;
    }
    CrowdFollowingComponent->SetCrowdAvoidanceQuality(
        DetourCrowdAvoidanceQualityType);

    CrowdFollowingComponent->SetAvoidanceGroup(1);
    CrowdFollowingComponent->SetGroupsToAvoid(1);
    CrowdFollowingComponent->SetCrowdCollisionQueryRange(
        DetourCrowdAvoidanceQueryRange);
}

void ADefaultEnemyAIController::OnPerceptionUpdated(AActor *Actor,
                                                    FAIStimulus Stimulus) {
    MYSTICA_RETURN_IF(!Stimulus.WasSuccessfullySensed() || !Actor);

    UBlackboardComponent *BlackboardComponent = GetBlackboardComponent();
    MYSTICA_LOG_AND_RETURN_IF(
        !BlackboardComponent ||
            BlackboardComponent->GetValueAsObject(FName("TargetActor")),
        LogTemp, Warning,
        TEXT("Will not proceed on OnPerceptionUpdated, "
             "invalid BlackboardComponent or already has TargetActor set"));

    BlackboardComponent->SetValueAsObject(FName("TargetActor"), Actor);
}

ETeamAttitude::Type
ADefaultEnemyAIController::GetTeamAttitudeTowards(const AActor &Other) const {
    const APawn *OtherPawn = Cast<const APawn>(&Other);
    const IGenericTeamAgentInterface *OtherTeamAgent =
        Cast<const IGenericTeamAgentInterface>(OtherPawn->GetController());

    if (!OtherTeamAgent ||
        OtherTeamAgent->GetGenericTeamId() < GetGenericTeamId()) {
        return ETeamAttitude::Hostile;
    }

    return ETeamAttitude::Friendly;
}
