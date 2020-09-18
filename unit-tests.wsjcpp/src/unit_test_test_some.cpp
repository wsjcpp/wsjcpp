#include <wsjcpp_unit_tests.h>
#include <vector>

// ---------------------------------------------------------------------
// UnitTestTestSome

class UnitTestTestSome : public UnitTestBase {
    public:
        UnitTestTestSome();
        virtual bool doBeforeTest() override;
        virtual void executeTest() override;
        virtual bool doAfterTest() override;
};

REGISTRY_WSJCPP_UNIT_TEST(UnitTestTestSome)

UnitTestTestSome::UnitTestTestSome()
    : UnitTestBase("UnitTestTestSome") {
}

// ---------------------------------------------------------------------

bool UnitTestTestSome::doBeforeTest() {
    // nothing
    return true;
}

// ---------------------------------------------------------------------

void UnitTestTestSome::executeTest() {
    compare("Not implemented", true, false);
}

// ---------------------------------------------------------------------

bool UnitTestTestSome::doAfterTest() {
    // nothing
    return true;
}