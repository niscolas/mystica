#include "EnemyUIComponent.h"

FPercentageChanged &UEnemyUIComponent::GetHealthPercentageChangedDelegate() {
    return HealthPercentageChanged;
}

FPercentageChanged &UEnemyUIComponent::GetRagePercentageChangedDelegate() {
    return RagePercentageChanged;
}
