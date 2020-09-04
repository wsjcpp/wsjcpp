#include "argument_processor_run.h"
#include "wsjcpp_package_manager.h"

ArgumentProcessorRun::ArgumentProcessorRun() 
  : WsjcppArgumentProcessor({"run"}, "Run basic scripts", "run clean/build/unit-tests scripts") {
      registryProcessor(new ArgumentProcessorRunUnitTests());
      registryProcessor(new ArgumentProcessorRunClean());
      registryProcessor(new ArgumentProcessorRunBuild());
}

// ---------------------------------------------------------------------

ArgumentProcessorRunUnitTests::ArgumentProcessorRunUnitTests() 
  : WsjcppArgumentProcessor({"unit-tests"}, "Build and run unit-tests", "Build and run unit-tests") {

}

// ---------------------------------------------------------------------

int ArgumentProcessorRunUnitTests::exec(const std::vector<std::string> &vRoutes, const std::vector<std::string> &vSubParams) {
    return -1;
}

// ---------------------------------------------------------------------

ArgumentProcessorRunClean::ArgumentProcessorRunClean() 
  : WsjcppArgumentProcessor({"clean"}, "Run clean script", "do run clean.sh script") {

}

// ---------------------------------------------------------------------

int ArgumentProcessorRunClean::exec(const std::vector<std::string> &vRoutes, const std::vector<std::string> &vSubParams) {
    return -1;
}

// ---------------------------------------------------------------------

ArgumentProcessorRunBuild::ArgumentProcessorRunBuild() 
  : WsjcppArgumentProcessor({"build"}, "run build.sh script", "do run 'build_simple.sh' script") {

}

// ---------------------------------------------------------------------

int ArgumentProcessorRunBuild::exec(const std::vector<std::string> &vRoutes, const std::vector<std::string> &vSubParams) {
    return -1;
}

// ---------------------------------------------------------------------