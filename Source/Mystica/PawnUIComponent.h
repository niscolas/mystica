#pragma once

#include "CoreMinimal.h"
#include "PawnUIComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPercentageChanged,
                                            float,
                                            NewPercentage);

UINTERFACE(MinimalAPI)

class UPawnUIComponent : public UInterface {
    GENERATED_BODY()
};

class MYSTICA_API IPawnUIComponent {
    GENERATED_BODY()

public:
    virtual FPercentageChanged &GetHealthPercentageChangedDelegate() = 0;

    virtual FPercentageChanged &GetRagePercentageChangedDelegate() = 0;
};
