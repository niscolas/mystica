#include "DefaultPlayerController.h"

ADefaultPlayerController::ADefaultPlayerController() {
    TeamId = FGenericTeamId(0);
}

FGenericTeamId ADefaultPlayerController::GetGenericTeamId() const {
    return TeamId;
}
