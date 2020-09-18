#include <wsjcpp_unit_tests.h>
#include <vector>
#include <wsjcpp_package_manager.h>

// ---------------------------------------------------------------------
// UnitTestgenerateFilenameForUnitTest

class UnitTestgenerateFilenameForUnitTest : public WsjcppUnitTestBase {
    public:
        UnitTestgenerateFilenameForUnitTest();
        virtual bool doBeforeTest() override;
        virtual void executeTest() override;
        virtual bool doAfterTest() override;
};

REGISTRY_WSJCPP_UNIT_TEST(UnitTestgenerateFilenameForUnitTest)

UnitTestgenerateFilenameForUnitTest::UnitTestgenerateFilenameForUnitTest()
    : WsjcppUnitTestBase("UnitTestgenerateFilenameForUnitTest") {
}

// ---------------------------------------------------------------------

bool UnitTestgenerateFilenameForUnitTest::doBeforeTest() {
    // nothing
    return true;
}

// ---------------------------------------------------------------------
void UnitTestgenerateFilenameForUnitTest::executeTest() {
    bool bTestSuccess = true;
    
    WsjcppPackageManager pkg(".");
    std::vector<std::pair<std::string, std::string>> tests;
    tests.push_back(std::pair<std::string, std::string>("SomeTest1", "unit_test_some_test1"));
    tests.push_back(std::pair<std::string, std::string>("Some2IpV4", "unit_test_some2_ip_v4"));
    for (int i = 0; i < tests.size(); i++) {
        std::string sName = pkg.normalizeUnitTestName(tests[i].first, true);
        std::string sGotBaseName = pkg.generateFilenameForUnitTest(sName);
        std::string sExpectedBaseName = tests[i].second;
        compare(sName, sGotBaseName, sExpectedBaseName);
        std::string sData;
        
    }
}

// ---------------------------------------------------------------------

bool UnitTestgenerateFilenameForUnitTest::doAfterTest() {
    // nothing
    return true;
}