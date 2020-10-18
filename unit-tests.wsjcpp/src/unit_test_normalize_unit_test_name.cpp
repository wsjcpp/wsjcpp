#include <wsjcpp_unit_tests.h>
#include <vector>
#include <wsjcpp_package_manager.h>


// ---------------------------------------------------------------------
// UnitTestNormalizeUnitTestName

class UnitTestNormalizeUnitTestName : public WsjcppUnitTestBase {
    public:
        UnitTestNormalizeUnitTestName();
        virtual bool doBeforeTest() override;
        virtual void executeTest() override;
        virtual bool doAfterTest() override;
};

REGISTRY_WSJCPP_UNIT_TEST(UnitTestNormalizeUnitTestName)

UnitTestNormalizeUnitTestName::UnitTestNormalizeUnitTestName()
    : WsjcppUnitTestBase("UnitTestNormalizeUnitTestName") {
}

// ---------------------------------------------------------------------

bool UnitTestNormalizeUnitTestName::doBeforeTest() {
    // nothing
    return true;
}

// ---------------------------------------------------------------------
void UnitTestNormalizeUnitTestName::executeTest() {
    
    WsjcppPackageManager pkg(".");
    std::vector<std::pair<std::string, std::string>> tests;
    tests.push_back(std::pair<std::string, std::string>("UnitTest1", "UnitTest1"));
    tests.push_back(std::pair<std::string, std::string>("UnitTest1%%%$", "UnitTest1"));
    tests.push_back(std::pair<std::string, std::string>("%%%%UnitT%&!±!#est1%%%$", "UnitTest1"));
    tests.push_back(std::pair<std::string, std::string>("%%%%UnitT%выафва#est1%%%$", "UnitTest1"));
    for (int i = 0; i < tests.size(); i++) {
        std::string sName = tests[i].first;
        std::string sExpectedName = tests[i].second;
        std::string sGotName = pkg.normalizeUnitTestName(sName, true);
        compare(sName, sGotName, sExpectedName);
        std::string sData;
    }
}

// ---------------------------------------------------------------------

bool UnitTestNormalizeUnitTestName::doAfterTest() {
    // nothing
    return true;
}