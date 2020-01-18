#include "argument_processor_basic.h"
#include <wsjcpp_package_manager.h>
#include <wsjcpp_core.h>

ArgumentProcessorInfo::ArgumentProcessorInfo() 
  : WSJCppArgumentProcessor("info", "information about package") {
      
}

// ---------------------------------------------------------------------

int ArgumentProcessorInfo::exec(const std::string &sProgramName, const std::vector<std::string> &vSubParams) {
    WSJCppPackageManager pkg(".");
    if (!pkg.load()) {
        WSJCppLog::err(TAG, "Could not load package info from current directory");
        return -1;
    }
    pkg.printInfo();
    
    return 0;
}

// ---------------------------------------------------------------------