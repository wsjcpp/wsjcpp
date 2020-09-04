#include "argument_processor_main.h"
#include "argument_processor_unit_tests.h"
#include "argument_processor_run.h"
#include "argument_processor_generate.h"
#include "argument_processor_dependencies.h"
#include "argument_processor_distribution.h"
#include "argument_processor_basic.h"
#include "argument_processor_origins.h"
#include "argument_processor_scan.h"
#include "argument_processor_prepare.h"
#include "argument_processor_resources.h"
#include "argument_processor_change.h"

#include <wsjcpp_package_manager.h>
#include <iostream>
#include <wsjcpp_core.h>

ArgumentProcessorMain::ArgumentProcessorMain() 
  : WsjcppArgumentProcessor({"main"}, "C++ Source Package Manager", "C++ Source Package Manager") {
    registryProcessor(new ArgumentProcessorVersion());
    registryProcessor(new ArgumentProcessorInfo());
    registryProcessor(new ArgumentProcessorChange());
    registryProcessor(new ArgumentProcessorInit());
    registryProcessor(new ArgumentProcessorClean());
    registryProcessor(new ArgumentProcessorScan());
    registryProcessor(new ArgumentProcessorInstall());
    registryProcessor(new ArgumentProcessorReinstall());
    registryProcessor(new ArgumentProcessorUninstall());
    registryProcessor(new ArgumentProcessorList());
    registryProcessor(new ArgumentProcessorUpdate());
    registryProcessor(new ArgumentProcessorDistribution());
    // registryProcessor(new ArgumentProcessorRun());
    registryProcessor(new ArgumentProcessorGenerate());
    registryProcessor(new ArgumentProcessorUnitTests());
    // registryProcessor(new ArgumentProcessorOrigins());
    registryProcessor(new ArgumentProcessorPrepare());
    registryProcessor(new ArgumentProcessorResources());
}

// ---------------------------------------------------------------------

int ArgumentProcessorMain::exec(const std::vector<std::string> &vRoutes, const std::vector<std::string> &vSubParams) {
    // TODO help i think
    return -1;
}

// ---------------------------------------------------------------------
