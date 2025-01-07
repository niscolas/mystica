#include "EnemyGameplayAbility.h"
#include "EnemyCombatComponent.h"
#include "UObject/WeakObjectPtrTemplates.h"

UEnemyCombatComponent *
UEnemyGameplayAbility::GetCombatComponentFromActorInfo() const {
    if (!CachedCombatComponent.IsValid()) {
        GetAvatarActorFromActorInfo()
            ->FindComponentByClass<UEnemyCombatComponent>();
    }

    return CachedCombatComponent.IsValid() ? CachedCombatComponent.Get()
                                           : nullptr;
}
