#pragma once

#include "Animation/AnimInstance.h"
#include "CoreMinimal.h"
#include "KenneyCharacterLinkedAnimLayer.generated.h"

class UKenneyCharacterAnimInstance;

UCLASS()

class MYSTICA_API UKenneyCharacterLinkedAnimLayer : public UAnimInstance {
    GENERATED_BODY()

private:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess))
    UKenneyCharacterAnimInstance *AnimInstance;

    virtual void NativeInitializeAnimation() override;
};
