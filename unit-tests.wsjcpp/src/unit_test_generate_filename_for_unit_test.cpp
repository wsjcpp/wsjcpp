#include "unit_test_generate_filename_for_unit_test.h"
#include <vector>
#include <wsjcpp_core.h>
#include <wsjcpp_package_manager.h>

REGISTRY_UNIT_TEST(UnitTestgenerateFilenameForUnitTest)

UnitTestgenerateFilenameForUnitTest::UnitTestgenerateFilenameForUnitTest()
    : WSJCppUnitTestBase("UnitTestgenerateFilenameForUnitTest") {
}

// ---------------------------------------------------------------------

void UnitTestgenerateFilenameForUnitTest::init() {
    // nothing
}

// ---------------------------------------------------------------------
bool UnitTestgenerateFilenameForUnitTest::run() {
    bool bTestSuccess = true;
    
    WSJCppPackageManager pkg(".");
    std::vector<std::pair<std::string, std::string>> tests;
    tests.push_back(std::pair<std::string, std::string>("SomeTest1", "unit_test_some_test1"));
    tests.push_back(std::pair<std::string, std::string>("Some2IpV4", "unit_test_some2_ip_v4"));
    for (int i = 0; i < tests.size(); i++) {
        std::string sName = pkg.normalizeUnitTestName(tests[i].first, true);
        std::string sGotBaseName = pkg.generateFilenameForUnitTest(sName);
        std::string sExpectedBaseName = tests[i].second;
        compareS(bTestSuccess, sName, sGotBaseName, sExpectedBaseName);
        std::string sData;
        
    }
    return bTestSuccess;
}

