#include "KenneyCharacterLinkedAnimLayer.h"
#include "Mystica/KenneyCharacterAnimInstance.h"

void UKenneyCharacterLinkedAnimLayer::NativeInitializeAnimation() {
    AnimInstance = Cast<UKenneyCharacterAnimInstance>(
        GetOwningComponent()->GetAnimInstance());
}
