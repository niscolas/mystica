#pragma once

#include "CoreMinimal.h"
#include "FunctionalTest.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "MysticaFunctionalTestFunctionLibrary.generated.h"

UCLASS()

class MYSTICA_API UMysticaFunctionalTestFunctionLibrary
    : public UBlueprintFunctionLibrary {
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable,
              Category = "Functional Test|Mystica Function Library",
              meta = (DefaultToSelf = "InFunctionalTest"))
    static void AssertAndFinishTestOnFailure(AFunctionalTest *InFunctionalTest,
                                             bool Condition,
                                             const FString &Message);
};
