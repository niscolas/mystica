#include "InputConfigDataAsset.h"
#include "HelperMacros.h"
#include "InputAction.h"
#include "Templates/SharedPointer.h"

UInputAction *UInputConfigDataAsset::FindCommonInputActionByTag(
    const FGameplayTag &InTag) const {
    for (const FInputActionConfig &CommonInputActionConfig :
         CommonInputActionConfigs) {
        MYSTICA_CONTINUE_IF(CommonInputActionConfig.Tag != InTag ||
                            !CommonInputActionConfig.Action);

        return CommonInputActionConfig.Action;
    }

    return nullptr;
}
