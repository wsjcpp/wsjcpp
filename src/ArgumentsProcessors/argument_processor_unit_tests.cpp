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
    return -1;
}

// ---------------------------------------------------------------------

ArgumentProcessorUnitTestsDelete::ArgumentProcessorUnitTestsDelete() 
  : WSJCppArgumentProcessor("delete", "delete some unit-test") {

}

// ---------------------------------------------------------------------

int ArgumentProcessorUnitTestsDelete::exec(const std::string &sProgramName, const std::vector<std::string> &vSubParams) {
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
