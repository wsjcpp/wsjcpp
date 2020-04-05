#include "unit_test_read_package.h"
#include <vector>
#include <wsjcpp_core.h>
#include <wsjcpp_package_manager.h>

REGISTRY_UNIT_TEST(UnitTestReadPackage)

UnitTestReadPackage::UnitTestReadPackage()
    : WsjcppUnitTestBase("UnitTestReadPackage") {
}

// ---------------------------------------------------------------------

void UnitTestReadPackage::init() {
    // nothing
}

// ---------------------------------------------------------------------

bool UnitTestReadPackage::run() {
    
    std::string sFolder = "data/test-read-package";
    WsjcppPackageManager pkg(sFolder);
    if (!pkg.load()) {
        WsjcppLog::err(TAG, "Could not load from '" + sFolder + "'");
        return false;
    }
    bool bTestSuccess = true;
    compareS(bTestSuccess, "version", pkg.getVersion(), "v0.1.1a");
    compareS(bTestSuccess, "name", pkg.getName(), "wsjcpp-test-read-package");
    compareS(bTestSuccess, "wsjcpp_version", pkg.getWsjcppVersion(), "v0.0.1");
    compareS(bTestSuccess, "cmake_minimum_required", pkg.getCMakeMinimumRequired(), "3.0");
    compareS(bTestSuccess, "cmake_cxx_standard", pkg.getCMakeCxxStandard(), "11");
    compareS(bTestSuccess, "description", pkg.getDescription(), "C++. Test Read Package");
    compareS(bTestSuccess, "issues", pkg.getIssues(), "https://github.com/wsjcpp/wsjcpp/issues");

    std::vector<std::string> vKeywords = pkg.getListOfKeywords();
    compareN(bTestSuccess, "keywords size", vKeywords.size(), 2);
    if (vKeywords.size() == 2) {
        compareS(bTestSuccess, "keyword_0", vKeywords[0], "c++");
        compareS(bTestSuccess, "keyword_1", vKeywords[1], "test");
    }

    std::vector<WsjcppPackageManagerRepository> vReps = pkg.getListOfRepositories();
    compareN(bTestSuccess, "vReps size", vReps.size(), 1);
    if (vReps.size() == 1) {
        compareS(bTestSuccess, "repository_0_address", vReps[0].getUrl(), "https://github.com/wsjcpp/wsjcpp");
        compareS(bTestSuccess, "repository_0_type", vReps[0].getType(), "main");
    }

    std::vector<WsjcppPackageManagerUnitTest> vUnitTests = pkg.getListOfUnitTests();
    compareN(bTestSuccess, "vUnitTests size", vUnitTests.size(), 3);
    if (vUnitTests.size() == 3) {
        WsjcppPackageManagerUnitTest unitTest0 = vUnitTests[0];
        compareS(bTestSuccess, "unit_tests_0_name", unitTest0.getName(), "Test1");
        compareS(bTestSuccess, "unit_tests_0_description", unitTest0.getDescription(), "Test 1");
        compareB(bTestSuccess, "unit_tests_0_enabled", unitTest0.isEnabled(), true);

        WsjcppPackageManagerUnitTest unitTest1 = vUnitTests[1];
        compareS(bTestSuccess, "unit_tests_1_name", unitTest1.getName(), "Test2");
        compareS(bTestSuccess, "unit_tests_1_description", unitTest1.getDescription(), "Test 2");
        compareB(bTestSuccess, "unit_tests_1_enabled", unitTest1.isEnabled(), true);

        WsjcppPackageManagerUnitTest unitTest2 = vUnitTests[2];
        compareS(bTestSuccess, "unit_tests_2_name", unitTest2.getName(), "Test3");
        compareS(bTestSuccess, "unit_tests_2_description", unitTest2.getDescription(), "Test 3");
        compareB(bTestSuccess, "unit_tests_1_enabled", unitTest2.isEnabled(), false);
    }

    std::vector<WsjcppPackageManagerAuthor> vAuthors = pkg.getListOfAuthors();
    compareN(bTestSuccess, "vAuthors size", vAuthors.size(), 1);
    if (vAuthors.size() == 1) {
        WsjcppPackageManagerAuthor author0 = vAuthors[0];
        compareS(bTestSuccess, "author_0_email", author0.getEmail(), "author@test.test");
        compareS(bTestSuccess, "author_0_name", author0.getName(), "Unit Tests");
        compareS(bTestSuccess, "author_0_full_name", author0.getFullAuthor(), "Unit Tests <author@test.test>");
    }

/*
required-pkg-config:
  - CURL
*/  

    WsjcppLog::warn(TAG, "TODO check list of required-pkg-config");

    std::vector<WsjcppPackageManagerOrigin> vOrigins = pkg.getListOfOrigins();
    compareN(bTestSuccess, "vOrigins size", vOrigins.size(), 2);
    if (vOrigins.size() == 2) {
        compareS(bTestSuccess, "origins_0_address", vOrigins[0].getAddress(), "https://sea-kg.com/wsjcpp-package-registry/");
        compareS(bTestSuccess, "origins_0_type", vOrigins[0].getType(), "package-registry");
        compareS(bTestSuccess, "origins_1_address", vOrigins[1].getAddress(), "file:///usr/share/wsjcpp-package-registry");
        compareS(bTestSuccess, "origins_1_type", vOrigins[1].getType(), "local-file-system");
    }

    std::vector<WsjcppPackageManagerDistributionFile> vFiles = pkg.getListOfDistributionFiles();
    compareN(bTestSuccess, "vFiles size", vFiles.size(), 2);
    if (vFiles.size() == 2) {
        compareS(bTestSuccess, "distribution_0_source_file", vFiles[0].getSourceFile(), "src/test.cpp");
        compareS(bTestSuccess, "distribution_0_target_file", vFiles[0].getTargetFile(), "test.cpp");
        compareS(bTestSuccess, "distribution_0_type", vFiles[0].getType(), "source-code");
        compareS(bTestSuccess, "distribution_0_sha1", vFiles[0].getSha1(), "");
        
        compareS(bTestSuccess, "distribution_1_source_file", vFiles[1].getSourceFile(), "src/test.h");
        compareS(bTestSuccess, "distribution_1_target_file", vFiles[1].getTargetFile(), "test.h");
        compareS(bTestSuccess, "distribution_1_type", vFiles[1].getType(), "source-code");
        compareS(bTestSuccess, "distribution_1_sha1", vFiles[1].getSha1(), "");
    }

    return bTestSuccess;
}

