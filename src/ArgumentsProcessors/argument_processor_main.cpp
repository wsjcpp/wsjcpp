#include "argument_processor_main.h"
#include "argument_processor_unit_tests.h"
#include "argument_processor_run.h"
#include "argument_processor_templates.h"
#include "argument_processor_dependencies.h"
#include "argument_processor_distribution.h"
#include "argument_processor_basic.h"
#include "argument_processor_origins.h"

#include <wsjcpp_package_manager.h>
#include <iostream>
#include <wsjcpp_core.h>

ArgumentProcessorMain::ArgumentProcessorMain() 
  : WSJCppArgumentProcessor("main", "C++ Source Package manager") {
    registryProcessor(new ArgumentProcessorInstall());
    registryProcessor(new ArgumentProcessorReinstall());
    registryProcessor(new ArgumentProcessorUninstall());
    registryProcessor(new ArgumentProcessorList());
    registryProcessor(new ArgumentProcessorInfo());
    registryProcessor(new ArgumentProcessorUpdate());
    registryProcessor(new ArgumentProcessorDistribution());
    registryProcessor(new ArgumentProcessorRun());
    registryProcessor(new ArgumentProcessorTemplates());
    registryProcessor(new ArgumentProcessorUnitTests());
    registryProcessor(new ArgumentProcessorOrigins());
}

// ---------------------------------------------------------------------

int ArgumentProcessorMain::exec(const std::string &sProgramName, const std::vector<std::string> &vSubParams) {
    return -1;
}

// ---------------------------------------------------------------------
