#include "argument_processor_origins.h"
#include "wsjcpp_package_manager.h"
#include <wsjcpp_core.h>

ArgumentProcessorOrigins::ArgumentProcessorOrigins() 
: WSJCppArgumentProcessor("origins", "list of servers with colelction packages") {
    registryProcessor(new ArgumentProcessorOriginsAdd());
    registryProcessor(new ArgumentProcessorOriginsRemove());
    registryProcessor(new ArgumentProcessorOriginsList());
}

// ---------------------------------------------------------------------

ArgumentProcessorOriginsAdd::ArgumentProcessorOriginsAdd() 
: WSJCppArgumentProcessor("add", "add a new origin") {

}

// ---------------------------------------------------------------------

int ArgumentProcessorOriginsAdd::exec(const std::string &sProgramName, const std::vector<std::string> &vSubParams) {
    WSJCppPackageManager pkg("./");
    if (!pkg.load()) {
        return -1;
    }

    if (vSubParams.size() != 2) {
        WSJCppLog::err(TAG, "Usage: <Name>");
        return -1;
    }
    if (pkg.addOrigin(vSubParams[0])) {
        pkg.save();
        return 0;
    }

    return -1;
}

// ---------------------------------------------------------------------

ArgumentProcessorOriginsRemove::ArgumentProcessorOriginsRemove() 
: WSJCppArgumentProcessor("reomve", "Remove origin") {

}

// ---------------------------------------------------------------------

int ArgumentProcessorOriginsRemove::exec(const std::string &sProgramName, const std::vector<std::string> &vSubParams) {
    WSJCppPackageManager pkg("./");
    if (!pkg.load()) {
        return -1;
    }

    if (vSubParams.size() != 1) {
        WSJCppLog::err(TAG, "Usage: <Name>");
        return -1;
    }
    std::string sAddress = vSubParams[0];
    std::vector<WSJCppPackageManagerOrigin> vOrigins = pkg.getListOfOrigins();
    for (int i = 0; i < vOrigins.size(); i++) {
        WSJCppPackageManagerOrigin ut = vOrigins[i];
        if (ut.getAddress() == sAddress) {
            if (pkg.deleteOrigin(vSubParams[0])) {
                pkg.save();
                WSJCppLog::ok(TAG, "Origin '" + sAddress + "' removed successfully.");
                return 0;
            } else {
                WSJCppLog::err(TAG, "Could not delete origin with name '" + sAddress + "'");
                return -1;
            }
        }
    }
    WSJCppLog::err(TAG, "Origin with name '" + sAddress + "' did not found");
    return -1;
}

// ---------------------------------------------------------------------

ArgumentProcessorOriginsList::ArgumentProcessorOriginsList() 
: WSJCppArgumentProcessor("list", "list of origns") {
}

// ---------------------------------------------------------------------

int ArgumentProcessorOriginsList::exec(const std::string &sProgramName, const std::vector<std::string> &vSubParams) {
    WSJCppPackageManager pkg("./");
    if (!pkg.load()) {
        return -1;
    }
    std::string sRes = "\nUnit Tests Cases:\n";
    std::vector<WSJCppPackageManagerOrigin> vOrigins = pkg.getListOfOrigins();
    for (int i = 0; i < vOrigins.size(); i++) {
      WSJCppPackageManagerOrigin ori = vOrigins[i];
      sRes += "* " + ori.getAddress() + " - " + ori.getType() + "\n";
    }
    WSJCppLog::info(TAG, sRes);
    return 0;
}

// ---------------------------------------------------------------------
