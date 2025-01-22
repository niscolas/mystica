#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PlayerUIWidget.generated.h"

class UPlayerUIComponent;

UINTERFACE(MinimalAPI)

class UPlayerUIWidget : public UInterface {
    GENERATED_BODY()
};

class MYSTICA_API IPlayerUIWidget {
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
    void PlayerUIWidgetInitialize(UPlayerUIComponent *OwningPlayerUIComponent);
};
