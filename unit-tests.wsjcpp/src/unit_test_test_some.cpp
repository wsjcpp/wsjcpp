#include "unit_test_test_some.h"
#include <vector>
#include <wsjcpp_core.h>

REGISTRY_WSJCPP_UNIT_TEST(UnitTestTestSome)

UnitTestTestSome::UnitTestTestSome()
    : UnitTestBase("UnitTestTestSome") {
}

// ---------------------------------------------------------------------

void UnitTestTestSome::init() {
    // nothing
}

// ---------------------------------------------------------------------

bool UnitTestTestSome::run() {
    bool bTestSuccess = true;
    compareB(bTestSuccess, "Not implemented", true, false);
    return bTestSuccess;
}

