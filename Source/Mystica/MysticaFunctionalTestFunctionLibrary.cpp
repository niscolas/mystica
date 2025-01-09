#include "MysticaFunctionalTestFunctionLibrary.h"
#include "FunctionalTest.h"

void UMysticaFunctionalTestFunctionLibrary::AssertAndFinishTestOnFailure(
    AFunctionalTest *InFunctionalTest, bool Condition, const FString &Message) {
    if (!InFunctionalTest->AssertTrue(Condition, Message)) {
        InFunctionalTest->FinishTest(EFunctionalTestResult::Failed, Message);
    }
}
