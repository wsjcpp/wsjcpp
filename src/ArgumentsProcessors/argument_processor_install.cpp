#include "argument_processor_install.h"
#include <wsjcpp_package_manager.h>
#include <iostream>
#include <wsjcpp_core.h>

ArgumentProcessorInstall::ArgumentProcessorInstall() 
  : WSJCppArgumentProcessor("install", "Install a source package from any sources (will be install deps)") {
      TAG = "ArgumentProcessorInstall";
    registryExample("from github source `./wsjcpp install 'https://github.com/sea-kg/nlohmann_json:v3.7.0'`");
    registryExample("from github source `./wsjcpp install 'https://github.com/sea-kg/nlohmann_json:master'`");
    registryExample("from local system `./wsjcpp install 'file:///usr/share/some_package'`");
    registryExample("from http(s) `./wsjcpp install 'https://sea-kg.com/wsjcpp/example/latest'`");
    registryExample("from http(s) `./wsjcpp install 'https://sea-kg.com/wsjcpp/example/v3.0.0'`");
}

int ArgumentProcessorInstall::exec(const std::string &sProgramName, const std::vector<std::string> &vSubParams) {
    WSJCppPackageManager pkg(".");
    if (!pkg.load()) {
        WSJCppLog::err(TAG, "Could not load package info from current directory");
        return -1;
    }

    if (vSubParams.size() != 1) {
        WSJCppLog::err(TAG, "Expected url");
        // printHelp(vArgs);
        return -1;
    }

    std::string sPackage = vSubParams[0];
    WSJCppLog::info(TAG, "Try installing source package '" + sPackage + "' ...");
    if (pkg.install(sPackage)) {
        std::cout << "Installed." << std::endl;
        // pkg.save();
    } else {
        WSJCppLog::err(TAG, "Could not install '" + sPackage + "' package.");
        return -1;
    }
    return 0;
}

// ---------------------------------------------------------------------