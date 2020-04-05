#include "argument_processor_run.h"
#include "wsjcpp_package_manager.h"

ArgumentProcessorRun::ArgumentProcessorRun() 
  : WsjcppArgumentProcessor({"run"}, "run clean/build/unit-tests scripts") {
      registryProcessor(new ArgumentProcessorRunUnitTests());
      registryProcessor(new ArgumentProcessorRunClean());
      registryProcessor(new ArgumentProcessorRunBuild());
}

// ---------------------------------------------------------------------

ArgumentProcessorRunUnitTests::ArgumentProcessorRunUnitTests() 
  : WsjcppArgumentProcessor({"unit-tests"}, "do build and run unit-tests") {

}

// ---------------------------------------------------------------------

int ArgumentProcessorRunUnitTests::exec(const std::string &sProgramName, const std::vector<std::string> &vSubParams) {
    return -1;
}

// ---------------------------------------------------------------------

ArgumentProcessorRunClean::ArgumentProcessorRunClean() 
  : WsjcppArgumentProcessor({"clean"}, "do run clean.sh script") {

}

// ---------------------------------------------------------------------

int ArgumentProcessorRunClean::exec(const std::string &sProgramName, const std::vector<std::string> &vSubParams) {
    return -1;
}

// ---------------------------------------------------------------------

ArgumentProcessorRunBuild::ArgumentProcessorRunBuild() 
  : WsjcppArgumentProcessor({"build"}, "do run 'build_simple.sh' script") {

}

// ---------------------------------------------------------------------

int ArgumentProcessorRunBuild::exec(const std::string &sProgramName, const std::vector<std::string> &vSubParams) {
    return -1;
}

// ---------------------------------------------------------------------