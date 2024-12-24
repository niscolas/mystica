#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"
#include "InputConfigDataAsset.generated.h"

class UInputAction;

USTRUCT(BlueprintType)

struct FInputActionConfig {
    GENERATED_BODY()

    UPROPERTY(EditDefaultsOnly,
              BlueprintReadOnly,
              meta = (Categories = "Input"))
    FGameplayTag Tag;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    UInputAction *Action;
};

UCLASS()

class MYSTICA_API UInputConfigDataAsset : public UDataAsset {
    GENERATED_BODY()

public:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    class UInputMappingContext *MappingContext;

    UPROPERTY(EditDefaultsOnly,
              BlueprintReadOnly,
              meta = (TitleProperty = "Tag"))
    TArray<FInputActionConfig> ActionMapping;

    class TSharedPtr<UInputAction>
    FindActionByTag(const FGameplayTag &InTag) const;
};
