#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "UObject/ScriptInterface.h"
#include "PawnUI.generated.h"

class IPawnUIComponent;

UINTERFACE(MinimalAPI)

class UPawnUI : public UInterface {
    GENERATED_BODY()
};

class MYSTICA_API IPawnUI {
    GENERATED_BODY()

public:
    virtual TScriptInterface<IPawnUIComponent> GetUIComponent() const = 0;
};
