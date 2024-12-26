#include "Mystica/DebugHelper.h"
#include "HelperMacros.h"

namespace MysticaDebug {

void PrintToScreenAndConsole(const FString &Message,
                             const FColor &Color,
                             float TimeToDisplay,
                             int16 Key) {
    MYSTICA_RETURN_IF(!GEngine);

    GEngine->AddOnScreenDebugMessage(Key, TimeToDisplay, Color, Message);
    UE_LOG(LogTemp, Warning, TEXT("%s"), *Message);
}
} // namespace MysticaDebug
