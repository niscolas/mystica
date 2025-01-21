#pragma once

#include "CoreMinimal.h"
#include "Mystica/PlayerUIComponent.h"
#include "UObject/Interface.h"
#include "PawnUIWidget.generated.h"

class IPawnUIComponent;

UINTERFACE(MinimalAPI)

class UPawnUIWidget : public UInterface {
    GENERATED_BODY()
};

class MYSTICA_API IPawnUIWidget {
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
    void PawnUIWidgetInitialize(UPlayerUIComponent *OwningPlayerUIComponent);
};
