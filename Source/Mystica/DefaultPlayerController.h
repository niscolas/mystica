#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GenericTeamAgentInterface.h"
#include "DefaultPlayerController.generated.h"

UCLASS()

class MYSTICA_API ADefaultPlayerController : public APlayerController,
                                             public IGenericTeamAgentInterface {
    GENERATED_BODY()

public:
    ADefaultPlayerController();
    virtual FGenericTeamId GetGenericTeamId() const override;

private:
    FGenericTeamId TeamId;
};
