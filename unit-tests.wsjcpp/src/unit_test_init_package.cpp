#include <wsjcpp_unit_tests.h>
#include <vector>

// ---------------------------------------------------------------------
// UnitTestInitPackage

class UnitTestInitPackage : public WsjcppUnitTestBase {
    public:
        UnitTestInitPackage();
        virtual bool doBeforeTest() override;
        virtual void executeTest() override;
        virtual bool doAfterTest() override;
};

REGISTRY_WSJCPP_UNIT_TEST(UnitTestInitPackage)

UnitTestInitPackage::UnitTestInitPackage()
    : WsjcppUnitTestBase("UnitTestInitPackage") {
}

// ---------------------------------------------------------------------

bool UnitTestInitPackage::doBeforeTest() {
    // nothing
    return true;
}

// ---------------------------------------------------------------------

bool UnitTestInitPackage::run() {
    bool bTestSuccess = true;
    compare("Not implemented", true, false);
    return bTestSuccess;
}

