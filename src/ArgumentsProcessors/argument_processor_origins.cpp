#include "argument_processor_origins.h"
#include "wsjcpp_package_manager.h"
#include <wsjcpp_core.h>

ArgumentProcessorOrigins::ArgumentProcessorOrigins() 
: WsjcppArgumentProcessor({"origins"}, "list of registry with packages", "list of servers with colelction packages") {
    registryProcessor(new ArgumentProcessorOriginsAdd());
    registryProcessor(new ArgumentProcessorOriginsRemove());
    registryProcessor(new ArgumentProcessorOriginsList());
}

// ---------------------------------------------------------------------

ArgumentProcessorOriginsAdd::ArgumentProcessorOriginsAdd() 
: WsjcppArgumentProcessor({"add"}, "add a new origin", "add a new origin") {

}

// ---------------------------------------------------------------------

int ArgumentProcessorOriginsAdd::exec(const std::vector<std::string> &vRoutes, const std::vector<std::string> &vSubParams) {
    WsjcppPackageManager pkg("./");
    if (!pkg.load()) {
        return -1;
    }

    if (vSubParams.size() != 2) {
        WsjcppLog::err(TAG, "Usage: <Name>");
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
: WsjcppArgumentProcessor({"reomve"}, "Remove origin", "Remove origin") {

}

// ---------------------------------------------------------------------

int ArgumentProcessorOriginsRemove::exec(const std::vector<std::string> &vRoutes, const std::vector<std::string> &vSubParams) {
    WsjcppPackageManager pkg("./");
    if (!pkg.load()) {
        return -1;
    }

    if (vSubParams.size() != 1) {
        WsjcppLog::err(TAG, "Usage: <Name>");
        return -1;
    }
    std::string sAddress = vSubParams[0];
    std::vector<WsjcppPackageManagerOrigin> vOrigins = pkg.getListOfOrigins();
    for (int i = 0; i < vOrigins.size(); i++) {
        WsjcppPackageManagerOrigin ut = vOrigins[i];
        if (ut.getAddress() == sAddress) {
            if (pkg.deleteOrigin(vSubParams[0])) {
                pkg.save();
                WsjcppLog::ok(TAG, "Origin '" + sAddress + "' removed successfully.");
                return 0;
            } else {
                WsjcppLog::err(TAG, "Could not delete origin with name '" + sAddress + "'");
                return -1;
            }
        }
    }
    WsjcppLog::err(TAG, "Origin with name '" + sAddress + "' did not found");
    return -1;
}

// ---------------------------------------------------------------------

ArgumentProcessorOriginsList::ArgumentProcessorOriginsList() 
: WsjcppArgumentProcessor({"list"}, "List of origns", "list of origns") {
}

// ---------------------------------------------------------------------

int ArgumentProcessorOriginsList::exec(const std::vector<std::string> &vRoutes, const std::vector<std::string> &vSubParams) {
    WsjcppPackageManager pkg("./");
    if (!pkg.load()) {
        return -1;
    }
    std::string sRes = "\nUnit Tests Cases:\n";
    std::vector<WsjcppPackageManagerOrigin> vOrigins = pkg.getListOfOrigins();
    for (int i = 0; i < vOrigins.size(); i++) {
      WsjcppPackageManagerOrigin ori = vOrigins[i];
      sRes += "* " + ori.getAddress() + " - " + ori.getType() + "\n";
    }
    WsjcppLog::info(TAG, sRes);
    return 0;
}

// ---------------------------------------------------------------------
