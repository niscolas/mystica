#pragma once

namespace MysticaDebug {
constexpr FColor DefaultDebugColor = FColor(255, 255, 0);

void PrintToScreenAndConsole(const FString &Message,
                             const FColor &Color = DefaultDebugColor,
                             float TimeToDisplay = 5.0f,
                             int16 Key = -1);
} // namespace MysticaDebug
