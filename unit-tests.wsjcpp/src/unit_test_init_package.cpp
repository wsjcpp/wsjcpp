#include "unit_test_init_package.h"
#include <vector>
#include <wsjcpp_core.h>

REGISTRY_WSJCPP_UNIT_TEST(UnitTestInitPackage)

UnitTestInitPackage::UnitTestInitPackage()
    : WsjcppUnitTestBase("UnitTestInitPackage") {
}

// ---------------------------------------------------------------------

void UnitTestInitPackage::init() {
    // nothing
}

// ---------------------------------------------------------------------

bool UnitTestInitPackage::run() {
    bool bTestSuccess = true;
    compareB(bTestSuccess, "Not implemented", true, false);
    return bTestSuccess;
}

