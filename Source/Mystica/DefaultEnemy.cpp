#include "DefaultEnemy.h"

ADefaultEnemy::ADefaultEnemy() {
    PrimaryActorTick.bCanEverTick = false;
}

void ADefaultEnemy::BeginPlay() {
    Super::BeginPlay();
}
