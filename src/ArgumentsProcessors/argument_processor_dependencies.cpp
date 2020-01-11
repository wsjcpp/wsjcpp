#include "argument_processor_dependencies.h"
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
        pkg.save();
    } else {
        WSJCppLog::err(TAG, "Could not install '" + sPackage + "' package.");
        return -1;
    }
    return 0;
}

// ---------------------------------------------------------------------

ArgumentProcessorReinstall::ArgumentProcessorReinstall() 
  : WSJCppArgumentProcessor("reinstall", "Reinstall a source package (will be replaced all sources)") {
      TAG = "ArgumentProcessorReinstall";
      registrySingleArgument("--all", "reinstall all");
      registryExample("from github source `./wsjcpp reinstall 'https://github.com/sea-kg/nlohmann_json:v3.7.0'`");
      registryExample("from github source `./wsjcpp reinstall --all`");
      m_bReinstallAll = false;
}

bool ArgumentProcessorReinstall::applySingleArgument(const std::string &sProgramName, const std::string &sArgumentName) {
    if (sArgumentName == "--all") {
        m_bReinstallAll = true;
        return true;
    }
    return false;
}

int ArgumentProcessorReinstall::exec(const std::string &sProgramName, const std::vector<std::string> &vSubParams) {
    WSJCppPackageManager pkg(".");
    if (!pkg.load()) {
        WSJCppLog::err(TAG, "Could not load package info from current directory");
        return -1;
    }

    if (vSubParams.size() != 1 && !m_bReinstallAll) {
        WSJCppLog::err(TAG, "Expected url");
        // printHelp(vArgs);
        return -1;
    }

    if (vSubParams.size() != 0 && m_bReinstallAll) {
        WSJCppLog::err(TAG, "Don't need params");
        // printHelp(vArgs);
        return -1;
    }
    if (m_bReinstallAll) {
        std::vector<WSJCppPackageManagerDependence> deps = pkg.getListOfDependencies();
        for (int i = 0; i < deps.size(); i++) {
            WSJCppPackageManagerDependence dep = deps[i];
            std::string sPackage = dep.getUrl();
            WSJCppLog::info(TAG, "Reinstall package '" + sPackage + "' ...");
            if (pkg.reinstall(sPackage)) {
                std::cout << "Reinstalled." << std::endl;
                pkg.save();
            } else {
                WSJCppLog::warn(TAG, "Could not reinstall '" + sPackage + "' package.");
            }
        }
    } else {
        std::string sPackage = vSubParams[0];
        WSJCppLog::info(TAG, "Try reinstalling '" + sPackage + "' package...");
        if (pkg.reinstall(sPackage)) {
            std::cout << "Reinstalled." << std::endl;
            pkg.save();
        } else {
            WSJCppLog::err(TAG, "Could not reinstall '" + sPackage + "' package.");
            return -1;
        }
    }
    return 0;
}

// ---------------------------------------------------------------------

ArgumentProcessorUninstall::ArgumentProcessorUninstall() 
  : WSJCppArgumentProcessor("uninstall", "Uninstall source package (!will be removed sources)") {
      TAG = "ArgumentProcessorUninstall";
      registryExample("from github source `./wsjcpp uninstall 'https://github.com/sea-kg/nlohmann_json:v3.7.0'`");
}

int ArgumentProcessorUninstall::exec(const std::string &sProgramName, const std::vector<std::string> &vSubParams) {
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
    if (pkg.uninstall(sPackage)) {
        std::cout << "Installed." << std::endl;
        pkg.save();
    } else {
        WSJCppLog::err(TAG, "Could not uninstall '" + sPackage + "' package.");
        return -1;
    }
    return 0;
}

// ---------------------------------------------------------------------