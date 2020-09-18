#include "unit_test_read_package.h"
#include <vector>
#include <wsjcpp_core.h>
#include <wsjcpp_package_manager.h>

#include <wsjcpp_unit_tests.h>

// ---------------------------------------------------------------------
// UnitTestReadPackage

class UnitTestReadPackage : public WsjcppUnitTestBase {
    public:
        UnitTestReadPackage();
        virtual bool doBeforeTest() override;
        virtual void executeTest() override;
        virtual bool doAfterTest() override;
};

REGISTRY_WSJCPP_UNIT_TEST(UnitTestReadPackage)

UnitTestReadPackage::UnitTestReadPackage()
    : WsjcppUnitTestBase("UnitTestReadPackage") {
}

// ---------------------------------------------------------------------

bool UnitTestReadPackage::doBeforeTest() {
    // do something before test
    return true;
}

// ---------------------------------------------------------------------

void UnitTestReadPackage::executeTest() {
    
    std::string sFolder = "data/test-read-package";
    WsjcppPackageManager pkg(sFolder);
    bool bPackageLoad = pkg.load();
    compare("Could not load from '" + sFolder + "'", bPackageLoad, true);
    if (!bPackageLoad) {
        return;
    }
    compare("version", pkg.getVersion(), "v0.1.1");
    compare("name", pkg.getName(), "wsjcpp-test-read-package");
    compare("wsjcpp_version", pkg.getWsjcppVersion(), "v0.0.1");
    compare("cmake_minimum_required", pkg.getCMakeMinimumRequired(), "3.0");
    compare("cmake_cxx_standard", pkg.getCMakeCxxStandard(), "11");
    compare("description", pkg.getDescription(), "C++. Test Read Package");
    compare("issues", pkg.getIssues(), "https://github.com/wsjcpp/wsjcpp/issues");

    std::vector<std::string> vKeywords = pkg.getListOfKeywords();
    compare("keywords size", vKeywords.size(), 2);
    if (vKeywords.size() == 2) {
        compare("keyword_0", vKeywords[0], "c++");
        compare("keyword_1", vKeywords[1], "test");
    }

    std::vector<WsjcppPackageManagerRepository> vReps = pkg.getListOfRepositories();
    compare("vReps size", vReps.size(), 1);
    if (vReps.size() == 1) {
        compare("repository_0_address", vReps[0].getUrl(), "https://github.com/wsjcpp/wsjcpp");
        compare("repository_0_type", vReps[0].getType(), "main");
    }

    std::vector<WsjcppPackageManagerUnitTest> vUnitTests = pkg.getListOfUnitTests();
    compare("vUnitTests size", vUnitTests.size(), 3);
    if (vUnitTests.size() == 3) {
        WsjcppPackageManagerUnitTest unitTest0 = vUnitTests[0];
        compare("unit_tests_0_name", unitTest0.getName(), "Test1");
        compare("unit_tests_0_description", unitTest0.getDescription(), "Test 1");
        compare("unit_tests_0_enabled", unitTest0.isEnabled(), true);

        WsjcppPackageManagerUnitTest unitTest1 = vUnitTests[1];
        compare("unit_tests_1_name", unitTest1.getName(), "Test2");
        compare("unit_tests_1_description", unitTest1.getDescription(), "Test 2");
        compare("unit_tests_1_enabled", unitTest1.isEnabled(), true);

        WsjcppPackageManagerUnitTest unitTest2 = vUnitTests[2];
        compare("unit_tests_2_name", unitTest2.getName(), "Test3");
        compare("unit_tests_2_description", unitTest2.getDescription(), "Test 3");
        compare("unit_tests_1_enabled", unitTest2.isEnabled(), false);
    }

    std::vector<WsjcppPackageManagerAuthor> vAuthors = pkg.getListOfAuthors();
    compare("vAuthors size", vAuthors.size(), 1);
    if (vAuthors.size() == 1) {
        WsjcppPackageManagerAuthor author0 = vAuthors[0];
        compare("author_0_email", author0.getEmail(), "author@test.test");
        compare("author_0_name", author0.getName(), "Unit Tests");
        compare("author_0_full_name", author0.getFullAuthor(), "Unit Tests <author@test.test>");
    }

/*
required-pkg-config:
  - CURL
*/  

    WsjcppLog::warn(TAG, "TODO check list of required-pkg-config");

    std::vector<WsjcppPackageManagerOrigin> vOrigins = pkg.getListOfOrigins();
    compare("vOrigins size", vOrigins.size(), 2);
    if (vOrigins.size() == 2) {
        compare("origins_0_address", vOrigins[0].getAddress(), "https://sea-kg.com/wsjcpp-package-registry/");
        compare("origins_0_type", vOrigins[0].getType(), "package-registry");
        compare("origins_1_address", vOrigins[1].getAddress(), "file:///usr/share/wsjcpp-package-registry");
        compare("origins_1_type", vOrigins[1].getType(), "local-file-system");
    }

    std::vector<WsjcppPackageManagerDistributionFile> vFiles = pkg.getListOfDistributionFiles();
    compare("vFiles size", vFiles.size(), 2);
    if (vFiles.size() == 2) {
        compare("distribution_0_source_file", vFiles[0].getSourceFile(), "src/test.cpp");
        compare("distribution_0_target_file", vFiles[0].getTargetFile(), "test.cpp");
        compare("distribution_0_type", vFiles[0].getType(), "source-code");
        compare("distribution_0_sha1", vFiles[0].getSha1(), "");
        
        compare("distribution_1_source_file", vFiles[1].getSourceFile(), "src/test.h");
        compare("distribution_1_target_file", vFiles[1].getTargetFile(), "test.h");
        compare("distribution_1_type", vFiles[1].getType(), "source-code");
        compare("distribution_1_sha1", vFiles[1].getSha1(), "");
    }
}

// ---------------------------------------------------------------------

bool UnitTestReadPackage::doAfterTest() {
    // do something after test
    return true;
}