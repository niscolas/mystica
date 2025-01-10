#include "MysticaCharacterFunctionLibrary.h"
#include "GameFramework/Character.h"

UAnimInstance *
UMysticaCharacterFunctionLibrary::GetAnimInstance(ACharacter *InCharacter) {
    return InCharacter->GetMesh()->GetAnimInstance();
}
