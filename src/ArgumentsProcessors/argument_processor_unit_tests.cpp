#include "argument_processor_unit_tests.h"
#include "wsjcpp_package_manager.h"
#include <wsjcpp_core.h>

ArgumentProcessorUnitTests::ArgumentProcessorUnitTests() 
: WSJCppArgumentProcessor("unit-tests", "manage unit-tests in package") {
    registryProcessor(new ArgumentProcessorUnitTestsCreate());
    registryProcessor(new ArgumentProcessorUnitTestsDelete());
    registryProcessor(new ArgumentProcessorUnitTestsList());
}

// ---------------------------------------------------------------------

ArgumentProcessorUnitTestsCreate::ArgumentProcessorUnitTestsCreate() 
: WSJCppArgumentProcessor("create", "create a new unit-test") {

}

// ---------------------------------------------------------------------

int ArgumentProcessorUnitTestsCreate::exec(const std::string &sProgramName, const std::vector<std::string> &vSubParams) {
    WSJCppPackageManager pkg("./");
    if (!pkg.load()) {
        return -1;
    }

    if (vSubParams.size() != 2) {
        WSJCppLog::err(TAG, "Usage: <Name> <Description>");
        return -1;
    }
    if (pkg.createUnitTest(vSubParams[0], vSubParams[1])) {
      pkg.save();
      return 0;
    }

    return -1;
}

// ---------------------------------------------------------------------

ArgumentProcessorUnitTestsDelete::ArgumentProcessorUnitTestsDelete() 
: WSJCppArgumentProcessor("delete", "Delete unit-test by name") {

}

// ---------------------------------------------------------------------

int ArgumentProcessorUnitTestsDelete::exec(const std::string &sProgramName, const std::vector<std::string> &vSubParams) {
    WSJCppPackageManager pkg("./");
    if (!pkg.load()) {
        return -1;
    }

    if (vSubParams.size() != 1) {
        WSJCppLog::err(TAG, "Usage: <Name>");
        return -1;
    }
    std::string sUnitTestName = vSubParams[0];
    std::vector<WSJCppPackageManagerUnitTest> vUnitTests = pkg.getListOfUnitTests();
    for (int i = 0; i < vUnitTests.size(); i++) {
        WSJCppPackageManagerUnitTest ut = vUnitTests[i];
        if (ut.getName() == sUnitTestName) {
            if (pkg.deleteUnitTest(vSubParams[0])) {
                pkg.save();
                WSJCppLog::ok(TAG, "Unit Test '" + sUnitTestName + "' removed successfully.");
                return 0;
            } else {
                WSJCppLog::err(TAG, "Could not delete unit-test with name '" + sUnitTestName + "'");
                return -1;
            }
        }
    }
    WSJCppLog::err(TAG, "Unit test with name '" + sUnitTestName + "' did not found");
    return -1;
}

// ---------------------------------------------------------------------

ArgumentProcessorUnitTestsList::ArgumentProcessorUnitTestsList() 
: WSJCppArgumentProcessor("list", "list of unit-test") {
}

// ---------------------------------------------------------------------

int ArgumentProcessorUnitTestsList::exec(const std::string &sProgramName, const std::vector<std::string> &vSubParams) {
    WSJCppPackageManager pkg("./");
    if (!pkg.load()) {
        return -1;
    }
    std::string sRes = "\nUnit Tests Cases:\n";
    std::vector<WSJCppPackageManagerUnitTest> vUnitTests = pkg.getListOfUnitTests();
    for (int i = 0; i < vUnitTests.size(); i++) {
      WSJCppPackageManagerUnitTest ut = vUnitTests[i];
      sRes += "* " + ut.getName() + " - " + ut.getDescription() + "\n";
    }
    WSJCppLog::info(TAG, sRes);
    return 0;
}

// ---------------------------------------------------------------------
