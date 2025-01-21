#include "PlayerUIComponent.h"

FPercentageChanged &UPlayerUIComponent::GetHealthPercentageChangedDelegate() {
    return HealthPercentageChanged;
}

FPercentageChanged &UPlayerUIComponent::GetRagePercentageChangedDelegate() {
    return RagePercentageChanged;
}
