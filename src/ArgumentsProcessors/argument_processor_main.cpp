#include "argument_processor_main.h"
#include "argument_processor_unit_tests.h"
#include "argument_processor_run.h"
#include "argument_processor_templates.h"
#include "argument_processor_dependencies.h"
#include "argument_processor_sources.h"

#include <wsjcpp_package_manager.h>
#include <iostream>
#include <wsjcpp_core.h>

ArgumentProcessorMain::ArgumentProcessorMain() 
  : WSJCppArgumentProcessor("main", "C++ Source Package manager") {
    registryProcessor(new ArgumentProcessorInstall());
    registryProcessor(new ArgumentProcessorReinstall());
    registryProcessor(new ArgumentProcessorUninstall());
    registryProcessor(new ArgumentProcessorSources());
    registryProcessor(new ArgumentProcessorRun());
    registryProcessor(new ArgumentProcessorTemplates());
    registryProcessor(new ArgumentProcessorUnitTests());
}

// ---------------------------------------------------------------------

int ArgumentProcessorMain::exec(const std::string &sProgramName, const std::vector<std::string> &vSubParams) {
    if (vSubParams.size() == 0) {
        // printHelp(vArgs);
        return -1;
    }

    if (vSubParams[0] == "packages") {
        WSJCppPackageManager pkg(".");
        if (!pkg.load()) {
            WSJCppLog::err(TAG, "Could not load package info from current directory");
            std::cout << "Could not load package info from current directory" << std::endl;
            return -1;
        }

        pkg.printPackages();
        return 0;
    }
    return -1;
}

// ---------------------------------------------------------------------
