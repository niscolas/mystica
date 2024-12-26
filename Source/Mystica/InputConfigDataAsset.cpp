#include "InputConfigDataAsset.h"
#include "HelperMacros.h"
#include "InputAction.h"
#include "Templates/SharedPointer.h"

UInputAction *
UInputConfigDataAsset::FindActionByTag(const FGameplayTag &InTag) const {
    for (const FInputActionConfig &ActionMappingEntry : ActionMapping) {
        MYSTICA_CONTINUE_IF(ActionMappingEntry.Tag != InTag ||
                            !ActionMappingEntry.Action);

        return ActionMappingEntry.Action;
    }

    return nullptr;
}
