#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "EnemyUIWidget.generated.h"

class UEnemyUIComponent;

UINTERFACE(MinimalAPI)

class UEnemyUIWidget : public UInterface {
    GENERATED_BODY()
};

class MYSTICA_API IEnemyUIWidget {
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
    void EnemyUIWidgetInitialize(UEnemyUIComponent *OwningEnemyUIComponent);
};
