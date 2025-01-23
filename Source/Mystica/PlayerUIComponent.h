#pragma once

#include "Components/ActorComponent.h"
#include "Containers/Map.h"
#include "CoreMinimal.h"
#include "PawnUI.h"
#include "PawnUIComponent.h"
#include "UObject/SoftObjectPtr.h"
#include "PlayerUIComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FEquippedWeaponChangedDelegate,
                                            TSoftObjectPtr<UTexture2D>,
                                            SoftIconTexture);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))

class MYSTICA_API UPlayerUIComponent : public UActorComponent,
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

    UPROPERTY(BlueprintCallable,
              BlueprintAssignable,
              Category = "UI",
              meta = (AllowPrivateAccess))
    FEquippedWeaponChangedDelegate EquippedWeaponChanged;
};
