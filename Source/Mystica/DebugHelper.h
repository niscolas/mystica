#pragma once

#include "Engine/Engine.h"
#include "HAL/Platform.h"
#include "HelperMacros.h"
#include "Logging/LogVerbosity.h"
#include "Math/Color.h"

namespace MysticaDebug {
static constexpr FColor DefaultDebugColor = FColor(255, 255, 0);

static void Print(const FString &Message,
                  const FColor &Color = DefaultDebugColor,
                  float TimeToDisplay = 5.0f,
                  ELogVerbosity::Type Verbosity = ELogVerbosity::Warning,
                  int16 Key = -1) {
    MYSTICA_RETURN_IF(!GEngine);

    GEngine->AddOnScreenDebugMessage(Key, TimeToDisplay, Color, Message);
    UE_LOG(LogTemp, Verbosity, TEXT("%s"), *Message);
}
} // namespace MysticaDebug
