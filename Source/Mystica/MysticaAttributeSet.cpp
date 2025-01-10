#include "MysticaAttributeSet.h"

UMysticaAttributeSet::UMysticaAttributeSet() {
    InitCurrentHealth(1);
    InitMaxHealth(1);

    InitCurrentRage(1);
    InitMaxRage(1);

    InitAttackBaseDamage(1);
    InitDefense(1);

    InitLightComboCount(1);
    InitHeavyComboCount(1);
}
