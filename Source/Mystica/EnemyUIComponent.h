#pragma once

#include "Components/ActorComponent.h"
#include "Containers/Map.h"
#include "CoreMinimal.h"
#include "PawnUI.h"
#include "PawnUIComponent.h"
#include "EnemyUIComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))

class MYSTICA_API UEnemyUIComponent : public UActorComponent,
                                      public IPawnUIComponent {
    GENERATED_BODY()

public:
    virtual FPercentageChanged &GetHealthPercentageChangedDelegate() override;
    virtual FPercentageChanged &GetRagePercentageChangedDelegate() override;

private:
    UPROPERTY(BlueprintAssignable, Category = "UI", meta = (AllowPrivateAccess))
    FPercentageChanged HealthPercentageChanged;

    UPROPERTY(BlueprintAssignable, Category = "UI", meta = (AllowPrivateAccess))
    FPercentageChanged RagePercentageChanged;
};
